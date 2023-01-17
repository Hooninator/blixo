from __future__ import annotations
from curses import KEY_A3
from exo import *
from exo.libs.memories import DRAM_STATIC
from exo.platforms.x86 import *
from exo.platforms.neon import *
from exo.syntax import *
import time

from platforms.machine import *

# Portable microkernel generator

class MicrokernelGenerator:

    microkernel_id = 0

    def __init__(self):
        # Base SGEMM procedure
        @proc
        def SGEMM(M: size, N: size, K: size, A: f32[M, K], B: f32[K, N], C: f32[M, N]):
            assert M >= 1
            assert N >= 1
            assert K >= 1
            assert stride(A, 1) == 1
            assert stride(B, 1) == 1
            assert stride(C, 1) == 1

            for i in par(0, M):
                for j in par(0, N):
                    for k in par(0, K):
                        C[i, j] += A[i, k] * B[k, j]

        self.sgemm_window = (SGEMM
                            .rename('sgemm_win')
                            .set_window('A', True)
                            .set_window('B', True)
                            .set_window('C', True))
        self.sgemm_base = SGEMM
        self.microkernels = {}
    
    def clear_microkernels(self):
        self.microkernels = {}
    

    def generate_exo_sgemm(self, machine: MachineParameters, M_r: int, N_r: int, M: int, N: int, K: int):
        """
        Generate sgemm using microkernel with user defined M_r and N_r dimensions for MxK * K*N problem size, 
        and substitute it into the base sgemm procedure.
        """

        # Generate base microkernel
        scheduled_microkernel, microkernel = self.generate_microkernel(machine, M_r, N_r, 0, 'N')

        # Schedule microkernel within sgemm
        scheduled_sgemm = self.schedule_base_microkernel(microkernel, scheduled_microkernel, M_r, N_r)

        # Handle edge cases
        scheduled_sgemm = self.generate_edge_cases(machine, scheduled_sgemm, M_r, N_r, M, N, K)

        return scheduled_sgemm



    def generate_microkernel(self, machine: MachineParameters, M_r: int, N_r: int, K_r: int, dim: str):
        """
        Generate microkernel for MxN problem size for the given machine.
        Vectorizes along dimension N or dimension K.
        """

        if dim=='N':
            scheduled_microkernel, microkernel = self.generate_microkernel_n(machine, M_r, N_r)

        if dim=='K':
            scheduled_microkernel, microkernel = self.generate_microkernel_k(machine, M_r, N_r, K_r)

        self.microkernels[self.microkernel_id] = scheduled_microkernel
        self.microkernel_id += 1 # Ensure each microkernel has a unique name

        return scheduled_microkernel, microkernel
    

    def generate_microkernel_n(self, machine: MachineParameters, M_r: int, N_r: int):
        """
        Vectorize along dimension N
        """
        microkernel = (self.sgemm_window
                       .rename('microkernel')
                       .partial_eval(M_r,N_r)
                       .simplify())
        scheduled_microkernel = (microkernel.rename(f"microkernel_{M_r}x{N_r}_{self.microkernel_id}")
                                            .reorder('j','k')
                                            .reorder('i','k')
                                            .split('j', machine.vec_width, ['jo','ji'], perfect=True)
                                            .par_to_seq('for k in _: _')
                                            .stage_assn('C_reg', 'C[_] += _')
                                            .set_memory('C_reg', machine.mem_type)
                                            .lift_alloc('C_reg : _', n_lifts=4)
                                            .double_fission('C_reg[_] = C[_]', 'C_reg[_] += _', n_lifts=4)
                                            .stage_expr('A_vec', 'A[_,_]', memory=machine.mem_type)
                                            .stage_expr('B_vec', 'B[_,_]', memory=machine.mem_type)
                                            .replace(machine.load_instr, 'for ji in _: _ #0')
                                            .replace(machine.store_instr, 'for ji in _: _ #3')
                                            .replace_all(machine.broadcast_instr)
                                            .replace_all(machine.load_instr)
                                            .replace_all(machine.fmadd_instr)
                                            .lift_alloc('A_vec : _')
                                            .fission_after(machine.broadcast_instr_str)
                                            #.lift_alloc('B_vec : _', n_lifts=2)
                                            #.fission_after(machine.load_instr_str +' #1', n_lifts=2)
                                            .simplify())
        return scheduled_microkernel, microkernel

    
    def generate_microkernel_k(self, machine: MachineParameters, M_r: int, N_r: int, K_r: int):
        """
        Vectorize along dimension K
        """
        microkernel = (self.sgemm_window
                            .rename('microkernel')
                            .partial_eval(M_r,N_r)
                            .partial_eval(K=K_r)
                            .reorder('i', 'j')
                            .simplify())
        scheduled_microkernel = (microkernel.rename(f'microkernel_{M_r}x{N_r}x{K_r}_{self.microkernel_id}')
                                            .reorder('i', 'k')
                                            .split('i', machine.vec_width, ['io','ii'], perfect=True)
                                            .par_to_seq('for j in _: _')
                                            .stage_assn('C_reg', 'C[_] += _')
                                            .lift_alloc('C_reg : _', n_lifts=4)
                                            .double_fission('C_reg[_] = C[_]', 'C_reg[_] += _', n_lifts=4)
                                            .replace(machine.load_instr, 'for ii in _: _ #0')
                                            .replace(machine.store_instr, 'for ii in _: _ #1')
                                            .set_memory('C_reg', machine.mem_type)
                                            .stage_expr('A_vec', 'A[_,_]', memory=machine.mem_type)
                                            .stage_expr('B_vec', 'B[_,_]', memory=machine.mem_type)
                                            .replace_all(machine.load_instr)
                                            .replace_all(machine.broadcast_instr)
                                            .replace_all(machine.fmadd_instr)
                                            .lift_alloc('A_vec : _', n_lifts=2)
                                            .lift_alloc('B_vec : _', n_lifts=2)
                                            .simplify()
                                            )
        return scheduled_microkernel, microkernel

    
    def schedule_base_microkernel(self, microkernel: Procedure, scheduled_microkernel: Procedure, M_r: int, N_r: int):
        """
        Schedule the basic (non-edge case) microkernel in the base sgemm procedure.
        """
        sgemm_scheduled = (self.sgemm_base.reorder('i', 'j')
                                            .split('j', N_r, ['ji', 'jo'], tail='cut')
                                            .fission_after('for jo in _: _ ', n_lifts=2)
                                            .reorder('jo', 'i')
                                            .split('i', M_r, ['ii', 'io'], tail='cut')
                                            .fission_after('for io in _: _ ', n_lifts=2)
                                            #.reorder('jo', 'ii')
                                            #do the replacement
                                            .replace_all(microkernel)
                                            .call_eqv(scheduled_microkernel, 'microkernel(_)')
                                            .stage_mem(f'B[0:K,'
                                                f'{N_r}*ji:{N_r}*ji+{N_r}]',
                                                'B_strip', 'for ii in _:_ #0')
                                            #.replace_all(microkenel_edge)  
                                            .simplify())

        return sgemm_scheduled

    
    def generate_edge_cases(self, machine: MachineParameters, scheduled_sgemm: Procedure, 
                            M_r: int, N_r: int,
                            M: int, N: int, K: int):
        """
        Generates and schedules microkernels that handle edge cases for the given microkernel and problem dimensions.
        """

        counter = 1 

        
        edge_amt_1 = M % M_r
        if edge_amt_1>1:
            counter -= 1
            edge_handler_1, base_edge_handler_1 = self.generate_microkernel(machine, edge_amt_1, N_r, 0, 'N')
            scheduled_sgemm = (scheduled_sgemm
                                .split('io #0', edge_amt_1, ['iii', 'ioo'], tail='cut')
                                .replace(base_edge_handler_1, 'for ioo in _:_ #0')
                                .call_eqv(edge_handler_1, 'microkernel(_)')
                                .simplify())
        if edge_amt_1:
            edge_amt_2 = M % M_r % edge_amt_1
        else:
            edge_amt_2 = 0

        if edge_amt_2>1:
            edge_handler_2, base_edge_handler_2 = self.generate_microkernel(machine, edge_amt_2, N_r, 0, 'N')
            scheduled_sgemm = (scheduled_sgemm
                                .split('ioo', edge_amt_2, ['iooo', 'iiii'], tail='cut')
                                .replace(base_edge_handler_2, 'for io in _:_ #0')
                                .call_eqv(edge_handler_2, 'microkernel(_)')
                                .simplify())

        # Dimension N edge case
        edge_amt_3 = (N % N_r // machine.vec_width) * machine.vec_width
        if edge_amt_3>1:
            edge_handler_3, base_edge_handler_3 = self.generate_microkernel(machine, M_r, edge_amt_3, 0, 'N')
            scheduled_sgemm = (scheduled_sgemm
                                .reorder(f'io #{counter}', 'jo')
                                .split('jo #1', edge_amt_3, ['jii', 'joo'], tail='cut')
                                .reorder('joo', 'io')
                                .replace(base_edge_handler_3, f'for io in _:_ #{counter}')
                                .call_eqv(edge_handler_3, 'microkernel(_)')
                                .simplify())
            
        # Dimension K
        if edge_amt_3:
            edge_amt_4 = N % N_r % edge_amt_3
        else:
            edge_amt_4 = 0
        edge_k = (K // machine.vec_width) * machine.vec_width
        if edge_amt_4>1:
            edge_handler_4, base_edge_handler_4 = self.generate_microkernel(machine, M_r, edge_amt_4, edge_k, 'K')
            scheduled_sgemm = (scheduled_sgemm
                                .reorder('io', 'joo')
                                .reorder('io', 'k')
                                .reorder('joo', 'k')
                                .split('k #1', edge_k, ['ko', 'ki'], tail='cut')
                                .reorder('ki', 'joo')
                                .reorder('ki', 'io')
                                .split('joo', edge_amt_4, ['jiii', 'jooo'], tail='cut')
                                .replace(base_edge_handler_4, 'for jooo in _:_ #0')
                                .call_eqv(edge_handler_4, 'microkernel(_)')
                                .simplify())

        return scheduled_sgemm


    def zero_pad_edge_cases(self, machine: MachineParameters, scheduled_sgemm: Procedure, 
                            M_r: int, N_r: int,
                            M: int, N: int, K: int):
        """
        Zero pad edge cases so they're large enough for the M_r*N_r microkernel to handle.
        """

        # 



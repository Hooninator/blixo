from exo import *
from exo.libs.memories import DRAM_STATIC
from exo.platforms.x86 import *
from exo.platforms.neon import *
from exo.syntax import *
from dataclasses import dataclass
from typing import Any


# Data class representing an abstract model of a machine

@dataclass
class MachineParameters:

    name : str

    mem_type : Any
    n_vec_registers : int
    vec_width : int

    # These are not currently used for anything
    l1_cache : int
    l2_cache : int
    l3_cache : int

    load_instr : Any
    load_instr_str : str
    store_instr : Any
    broadcast_instr : Any
    broadcast_instr_str : str
    fmadd_instr : Any

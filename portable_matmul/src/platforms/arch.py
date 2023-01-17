from exo import *
from exo.libs.memories import DRAM_STATIC
from exo.platforms.x86 import *
from exo.platforms.neon import *
from exo.syntax import *
from typing import Any
from platforms.machine import *

NeonMachine = MachineParameters("Neon", Neon4f, # Memory types 
                                32, 4, # Vector registers, vector width
                                None, None, None, # cache sizes
                                neon_vld_4xf32, "neon_vld_4xf32(_)", # Instructions for matmul
                                neon_vst_4xf32,
                                neon_broadcast_4xf32, "neon_broadcast_4xf32(_)",
                                neon_vfmadd_4xf32_4xf32)

AVX512Machine = MachineParameters("AVX512", AVX512,
                                  32, 16,
                                  None, None, None,
                                  mm512_loadu_ps, "mm512_loadu_ps(_)",
                                  mm512_storeu_ps,
                                  mm512_set1_ps, "mm512_set1_ps(_)",
                                  mm512_fmadd_ps)
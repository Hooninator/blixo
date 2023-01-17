from __future__ import annotations
from curses import KEY_A3
from exo import *
from exo.libs.memories import DRAM_STATIC
from exo.platforms.x86 import *
from exo.platforms.neon import *
from exo.syntax import *
import numpy as np


@proc
def zero_pad_vecadd(N : size, M : size, V : f32[N]):
    assert N >= 1
    

def test_zero_pad_vecadd(m:int):
    return None

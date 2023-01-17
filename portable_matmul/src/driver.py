from __future__ import annotations
from exo import *
from exo.libs.memories import DRAM_STATIC
from exo.platforms.x86 import *
from exo.platforms.neon import *
from exo.syntax import *
import time
import sys

from microkernel_generator import *
from platforms.arch import *


if __name__=="__main__":

    n = int(sys.argv[1])
    machine = sys.argv[2]

    stime = time.time()
    file = open(f"../microkernels/{machine}_{n}x{n}_microkernel.c", 'w+')


    microkernel_generator = MicrokernelGenerator()

    machines = {
        "neon" : NeonMachine,
        "avx512" : AVX512Machine
    }

    exo_sgemm = microkernel_generator.generate_exo_sgemm(machines[machine], 4, 16, n, n, n)


    print(f"Total execution time: {time.time()-stime}s") 
    file.write(exo_sgemm.c_code_str())
    file.close()

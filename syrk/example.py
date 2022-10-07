from __future__ import annotations
from exo import *
from exo.libs.memories import DRAM_STATIC
from exo.platforms.x86 import *
from exo.platforms.neon import *
from exo.syntax import *



@proc
def foo(M: size, N: size, A: f32[M, N]):

    assert M<N+1

    for i in par(0, M):
        for j in par(0, i+1):
            A[i, j] = 1.0

@proc
def bar(M: size, N: size, A: f32[M, N]):

    assert M<N+1

    for i in par(0, M):
        for j in par(0, N):
            A[i, j] = 1.0

final = foo.replace_all(bar)
print(final)

"""
def foo(M: size, N: size, A: f32[M, N] @ DRAM):
    assert M < N + 1
    for i in par(0, M):
        for j in par(0, i + 1):
            A[i, j] = 1.0

Here's the final output. Note that foo does not have its body replaced with bar like we would hope. 
"""
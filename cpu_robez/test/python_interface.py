import torch
from robe import get_idx_p, get_idx_s, get_idx_st, get_idx_p_power2, get_idx_s_power2
from robez import par_idx_py

import time
from torch.profiler import profile, record_function, ProfilerActivity

PROFILE=False

torch.manual_seed(101)
indices = torch.randint(0, 10000000, (1, 1024))
dim=128
chunk=32

P = 2038074743
A = 938666641
B = 1164654427
C = 1986670565

def run(func):
    start = time.time()
    for i in range(indices.shape[0]):
        hashed_idx = func(indices[i], dim, chunk, 2700000, A, B, C, P)
    end = time.time()
    print("time taken for  size 1024x128 is", (end - start) / 100 * 1000, "ms")
    return hashed_idx

def run_bits(func):
    start = time.time()
    for i in range(indices.shape[0]):
        hashed_idx = func(indices[i], dim, chunk, 22, A, B, C, P)
    end = time.time()
    print("time taken for  size 1024x128 is", (end - start) / 100 * 1000, "ms")
    return hashed_idx

def run_tb():
    random_numbers = torch.randint(high=255, size = (256*5*4,), dtype=torch.uint8)
    start = time.time()
    for i in range(indices.shape[0]):
        hashed_idx = get_idx_st(indices[i], dim, chunk, 21, random_numbers)
    end = time.time()
    print("time taken for  size 1024x128 is", (end - start) / 100 * 1000, "ms")
    return hashed_idx

if PROFILE:
    torch.manual_seed(101)
    indices = torch.randint(0, 10000000, (1, 1024))
    dim=128
    chunk=32

    for func in [par_idx_py, get_idx_p, get_idx_s]:
        print(" --------", func, "------------")
        with profile(activities=[ProfilerActivity.CPU], record_shapes=True) as prof:
            with record_function("run"):
                run(func)
        print(prof.key_averages().table())
else:
    torch.manual_seed(101)
    indices = torch.randint(0, 10000000, (100, 1024))
    dim=128
    chunk=32
    for func in [par_idx_py, get_idx_p, get_idx_s]:
        print(" --------", func, "------------")
        hashed_idx = run(func)
        print(hashed_idx)

    for func in [get_idx_p_power2, get_idx_s_power2]:
        print(" --------", func, "------------")
        hashed_idx = run_bits(func)
        print(hashed_idx)

    print(" -------- s_tabulation ------------")
    hashed_idx = run_tb()
    print(hashed_idx)

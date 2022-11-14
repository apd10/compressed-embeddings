import torch
import time
from robez import par_idx_py
from torch.profiler import profile, record_function, ProfilerActivity

profile = False

P = 2038074743
A = 938666641
B = 1164654427
C = 1986670565

def run():
    start = time.time()
    for i in range(indices.shape[0]):
        hashed_idx = par_idx_py(indices[i], dim, chunk, 21, A, B, C, P)
    end = time.time()
    print("time taken for  size 1024x128 is", (end - start) / 100 * 1000, "ms");
    return hashed_idx

if profile:
    torch.manual_seed(101)
    indices = torch.randint(0, 10000000, (1, 1024))
    dim=128
    chunk=32
    with profile(activities=[ProfilerActivity.CPU], record_shapes=True) as prof:
        with record_function("run"):
            run()
    print(prof.key_averages().table())
else:
    torch.manual_seed(101)
    indices = torch.randint(0, 10000000, (100, 1024))
    dim=128
    chunk=32
    hashed_idx = run()
    print(hashed_idx)

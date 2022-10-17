import torch
import time
from robez import par_idx_py

indices = torch.randint(0, 10000000, (100, 1024))
P = 2038074743
A = 938666641
B = 1164654427
C = 1986670565

start = time.time()
for i in range(indices.shape[0]):
    hashed_idx = par_idx_py(indices[i], 128, 32, 21, A, B, C, P)
end = time.time()
print("time taken for  size 1024x128 is", (end - start) / 100 * 1000, "ms");#

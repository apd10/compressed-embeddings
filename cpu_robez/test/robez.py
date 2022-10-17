import torch



#torch::Tensor par_idx(torch::Tensor indices, int dimension, int chunk_size, int max_bits, int64_t A, int64_t B, int64_t C)
def par_idx_py(indices, dimension, chunk_size, max_bits, A, B, C, P):
    size = 1<<max_bits
    helper_Eidx_base = torch.floor_divide(torch.arange(dimension, dtype=torch.int64), chunk_size)
    helper_Eidx_offset = torch.arange(dimension, dtype=torch.int64) % chunk_size
    helper_E1sR = torch.ones(dimension, dtype=torch.int64) * C
    hashed_idx = ((((((indices.view(-1,1)) * helper_E1sR)  + helper_Eidx_base * B) + A) %P) % (size) + helper_Eidx_offset)
    return hashed_idx

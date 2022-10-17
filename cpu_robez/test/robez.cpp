#include <torch/extension.h>
#include <iostream>
#include <algorithm>
#define _OPENMP
#include <ATen/ParallelOpenMP.h>
#include <chrono>

torch::Tensor par_idx(torch::Tensor indices, int dimension, int chunk_size, int max_bits, int64_t A, int64_t B, int64_t C)
{
    torch::Tensor out = at::empty({indices.size(0), dimension}, indices.options());
    int64_t max_bit_mask = (1<<max_bits) -1;
    
    #pragma omp parallel if (!omp_in_parallel()) default(none) shared(out, indices, chunk_size, dimension, max_bit_mask, A, B, C)
    {
        int64_t tid = omp_get_thread_num();
        int64_t num_threads = omp_get_num_threads();
        int64_t num_ids = ((indices.size(0) + num_threads -1) / num_threads);
        int64_t start = num_ids * tid;
        int64_t end = std::min(indices.size(0), num_ids * (1 + tid));
        int64_t base = 0;

        for (int64_t i = start; i < end; i++) {
            for(int64_t j = 0; j < dimension; j++) {
                if ( j % chunk_size == 0 ){
                    base = (A * (i+1) + B * (j+1) + C) & max_bit_mask;
                    out[i][j] = base;
                } else {
                    out[i][j] = ++base;
                }
            }
        }
    }
    return out;
}


torch::Tensor sin_idx(torch::Tensor indices, int dimension, int chunk_size, int max_bits, int64_t A, int64_t B, int64_t C)
{
  torch::Tensor out = at::empty({indices.size(0), dimension}, indices.options());
  int64_t max_bit_mask = (1<<max_bits) -1;
  int64_t base = 0, idx = 0;
  int64_t num_chunks = int((dimension + chunk_size - 1) / chunk_size);
  int64_t i = 0, j = 0, k = 0;

  for (i = 0; i < indices.size(0); i++) {
    for(j = 0; j < num_chunks; j++) {
      base = (A * (i+1) + B * (j+1) + C) & max_bit_mask;
      idx = j*chunk_size;
      out[i][idx] = base;
      for(k = j*chunk_size + 1;  (k < dimension) && (k < (j+1)*chunk_size); k ++){
        out[i][++idx] = ++base;
      }
    }
  }
  return out;
}


torch::Tensor zer_idx(torch::Tensor indices, int dimension, int chunk_size, int max_bits, int64_t A, int64_t B, int64_t C)
{
  torch::Tensor out = at::zeros({indices.size(0), dimension}, indices.options());
  return out;
}


void  cpp_interface_time(int num, int dim, int batch, int chunk_size){ // 0: single , 1: parallel, 2: zero
    torch::Tensor indices = at::randint(100000000, {num, batch});
    int64_t P = 2038074743;
    int64_t A = 938666641;
    int64_t B = 1164654427;
    int64_t C = 1986670565;
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < num; i++) {
        torch::Tensor hashed_idx = par_idx(indices[i],  dim, chunk_size, 21, A, B, C);
    }
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::cout << "time taken per " << batch << "x" << dim << " is " << (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / num) << std::endl;
}

PYBIND11_MODULE(TORCH_EXTENSION_NAME, m)
{
    m.def("get_idx", &sin_idx, "get_idx");
    m.def("get_idx_p", &par_idx, "get_idx");
    m.def("get_idx_s", &sin_idx, "get_idx");
    m.def("get_idx_z", &zer_idx, "get_idx");
    m.def("cpp_interface_time", &cpp_interface_time, "time in cpp");
}


int main() {
  cpp_interface_time(100, 128, 1024, 32);
  return 0;
}

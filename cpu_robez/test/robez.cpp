#include <torch/extension.h>
#include <iostream>
#include <algorithm>
#define _OPENMP
#include <ATen/ParallelOpenMP.h>
#include <chrono>



torch::Tensor par_idx(torch::Tensor indices, int dimension, int chunk_size, int64_t size, int64_t A, int64_t B, int64_t C, int64_t P)
{
    torch::Tensor out = at::empty({indices.size(0), dimension}, indices.options());
    auto out_accessor = out.accessor<int64_t, 2>();
    auto indices_accessor = indices.accessor<int64_t, 1>();
    //int64_t max_bit_mask = (1<<max_bits) -1;
    //int64_t size = 1 <<max_bits; // not exact
    
    #pragma omp parallel if (!omp_in_parallel()) default(none) shared(out, indices, indices_accessor, out_accessor, chunk_size, dimension, size, A, B, C, P)
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
                    base = (A * (indices_accessor[i]) + B * ((j / chunk_size) +1) + C) % P % (size - chunk_size);
                    out_accessor[i][j] = base;
                } else {
                    out_accessor[i][j] = ++base;
                }
            }
        }
    }
    return out;
}


torch::Tensor par_idx_power2(torch::Tensor indices, int dimension, int chunk_size, int64_t max_bits, int64_t A, int64_t B, int64_t C, int64_t P)
{
    // expects size to be chunk_size + 1<<bits
    torch::Tensor out = at::empty({indices.size(0), dimension}, indices.options());
    auto out_accessor = out.accessor<int64_t, 2>();
    auto indices_accessor = indices.accessor<int64_t, 1>();
    int64_t max_bit_mask = (1<<max_bits) -1;
    //int64_t size = 1 <<max_bits; // not exact
    
    #pragma omp parallel if (!omp_in_parallel()) default(none) shared(out, indices, indices_accessor, out_accessor, chunk_size, dimension, A, B, C, P, max_bit_mask)
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
                    base = (A * (indices_accessor[i]) + B * ((j / chunk_size) +1) + C) & max_bit_mask;
                    out_accessor[i][j] = base;
                } else {
                    out_accessor[i][j] = ++base;
                }
            }
        }
    }
    return out;
}


torch::Tensor sin_idx(torch::Tensor indices, int dimension, int chunk_size, int64_t size, int64_t A, int64_t B, int64_t C, int64_t P)
{
  torch::Tensor out = at::empty({indices.size(0), dimension}, indices.options());
  auto out_accessor = out.accessor<int64_t, 2>();
  auto indices_accessor = indices.accessor<int64_t, 1>();
  //int64_t max_bit_mask = (1<<max_bits) -1;
  //int64_t size = 1 <<max_bits; // not exact
  int64_t base = 0, idx = 0;
  int64_t num_chunks = int((dimension + chunk_size - 1) / chunk_size);
  int64_t i = 0, j = 0, k = 0;
  int64_t indices_size = indices.size(0);

  for (i = 0; i < indices_size; i++) {
    for(j = 0; j < num_chunks; j++) {
      base = (A * (indices_accessor[i]) + B * ((j) +1) + C) % P % (size - chunk_size);
      idx = j*chunk_size;
      out_accessor[i][idx] = base;
      for(k = j*chunk_size + 1;  (k < dimension) && (k < (j+1)*chunk_size); k ++){
        out_accessor[i][++idx] = ++base;
      }
    }
  }
  return out;
}


torch::Tensor sin_idx_power2(torch::Tensor indices, int dimension, int chunk_size, int64_t max_bits, int64_t A, int64_t B, int64_t C, int64_t P)
{
  // the expected size is 1<< bits + chunk_size
  torch::Tensor out = at::empty({indices.size(0), dimension}, indices.options());
  auto out_accessor = out.accessor<int64_t, 2>();
  auto indices_accessor = indices.accessor<int64_t, 1>();
  int64_t max_bit_mask = (1<<max_bits) -1;
  //int64_t size = 1 <<max_bits; // not exact
  int64_t base = 0, idx = 0;
  int64_t num_chunks = int((dimension + chunk_size - 1) / chunk_size);
  int64_t i = 0, j = 0, k = 0;
  int64_t indices_size = indices.size(0);

  for (i = 0; i < indices_size; i++) {
    for(j = 0; j < num_chunks; j++) {
      base = (A * (indices_accessor[i]) + B * ((j) +1) + C) & max_bit_mask;
      idx = j*chunk_size;
      out_accessor[i][idx] = base;
      for(k = j*chunk_size + 1;  (k < dimension) && (k < (j+1)*chunk_size); k ++){
        out_accessor[i][++idx] = ++base;
      }
    }
  }
  return out;
}


torch::Tensor sin_tab_idx(torch::Tensor indices, int dimension, int chunk_size, int max_bits, torch::Tensor random_numbers)
{
  // assumes that 32 bit int in indices and output though stores it has int64
  //  assumes that dim / chunk size is int8

  torch::Tensor out = at::empty({indices.size(0), dimension}, indices.options());
  auto out_accessor = out.accessor<int64_t, 2>();
  auto indices_accessor = indices.accessor<int64_t, 1>();
  auto rand = random_numbers.accessor<uint8_t, 1>();
  int64_t max_bit_mask = (1<<max_bits) -1;
  int64_t base = 0, idx = 0;
  int64_t num_chunks = int((dimension + chunk_size - 1) / chunk_size);
  int64_t i = 0, j = 0, k = 0;
  assert(max_bits < 32);
  int64_t index = 0;
  int64_t base1, base2, base3, base4;

  for (i = 0; i < indices.size(0); i++) {
    index = indices_accessor[i];
    for(j = 0; j < num_chunks; j++) {
      // indices_accessor[i], (j+1)
      base1 = rand[(uint8_t) index ] ^ rand[256 + (uint8_t) (index >> 8) ] ^ rand[512 + (uint8_t) (index >> 16)] ^  rand[768 + (uint8_t) (index >> 24)] ^ rand[1024 + (uint8_t) (j+1)];
      base2 = rand[1280+(uint8_t) index ] ^ rand[1280 + 256 + (uint8_t) (index >> 8) ] ^ rand[1280 + 512 + (uint8_t) (index >> 16)] ^  rand[1280 + 768 + (uint8_t) (index >> 24)] ^ rand[1280 + (uint8_t) (j+1)];
      base3 = rand[2816+(uint8_t) index ] ^ rand[2816 + 256 + (uint8_t) (index >> 8) ] ^ rand[2816 + 512 + (uint8_t) (index >> 16)] ^  rand[2816 + 768 + (uint8_t) (index >> 24)] ^ rand[2816 + (uint8_t) (j+1)];
      base4 = rand[4096+(uint8_t) index ] ^ rand[4096 + 256 + (uint8_t) (index >> 8) ] ^ rand[4096 + 512 + (uint8_t) (index >> 16)] ^  rand[4096 + 768 + (uint8_t) (index >> 24)] ^ rand[4096 + (uint8_t) (j+1)];
      base = (base1 | (base2 << 8) | (base3 << 16) | (base4 << 24)) & max_bit_mask;

      idx = j*chunk_size;
      out_accessor[i][idx] = base;
      for(k = j*chunk_size + 1;  (k < dimension) && (k < (j+1)*chunk_size); k ++){
        out_accessor[i][++idx] = ++base;
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
        torch::Tensor hashed_idx = par_idx(indices[i],  dim, chunk_size, 21, A, B, C, P);
    }
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::cout << "time taken per " << batch << "x" << dim << " is " << (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / num) << std::endl;
}

PYBIND11_MODULE(TORCH_EXTENSION_NAME, m)
{
    m.def("get_idx", &sin_idx, "get_idx");
    m.def("get_idx_p", &par_idx, "get_idx");
    m.def("get_idx_s", &sin_idx, "get_idx");
    m.def("get_idx_p_power2", &par_idx_power2, "get_idx");
    m.def("get_idx_s_power2", &sin_idx_power2, "get_idx");
    m.def("get_idx_st", &sin_tab_idx, "get_idx");
    m.def("get_idx_z", &zer_idx, "get_idx");
    m.def("cpp_interface_time", &cpp_interface_time, "time in cpp");
}


int main() {
  cpp_interface_time(100, 128, 1024, 32);
  return 0;
}

Q1. Why are times for Adam so large as compared to times for other optimizers ? (tensorflow implementation of ROBEZ)

A1. The times for Adam are higher because of the fact that Adam does not support sparse gradients. So internally, with adam it uses dense gradients which is the issue. This can be resolved, however, using "LazyAdam" in tensorflow-addons The results of the (tensorflow code on my machine) are as follows. I have generated others as well for everything to be comparable (due to machine change) [tensorflow benchmark(victors) code](../)

On 1 CPU:


|    | Model                   |   batch_size |   memory_size |   forward_pass_ms |   gradient_computation_ms |   backward_pass_ms |   total_time_ms | model size   | optimizer   |
|----|-------------------------|--------------|---------------|-------------------|---------------------------|--------------------|-----------------|--------------|-------------|
|  0 | FullEmbTableModel       |        32768 |     100000000 |           77.2054 |                   81.8065 |            45.5938 |         204.606 | 381.5MB      | Adagrad     |
|  1 | CompressedEmbTableModel |        32768 |        262144 |          233.401  |                   80.7942 |           410.733  |         724.929 | 1.0MB        | Adagrad     |
|  2 | CompressedEmbTableModel |        32768 |     100000000 |          446.341  |                   82.189  |           885.563  |        1414.09  | 381.5MB      | Adagrad     |
|  3 | FullEmbTableModel       |        32768 |     100000000 |           73.0547 |                   80.1771 |            26.6799 |         179.912 | 381.5MB      | SGD         |
|  4 | CompressedEmbTableModel |        32768 |        262144 |          215.347  |                   81.4808 |           103.259  |         400.086 | 1.0MB        | SGD         |
|  5 | CompressedEmbTableModel |        32768 |     100000000 |          442.105  |                   84.0363 |           491.807  |        1017.95  | 381.5MB      | SGD         |
|  6 | FullEmbTableModel       |        32768 |     100000000 |           75.8073 |                   79.6531 |          1649.96   |        1805.42  | 381.5MB      | Adam        |
|  7 | CompressedEmbTableModel |        32768 |        262144 |          253.079  |                   79.3205 |           414.615  |         747.014 | 1.0MB        | Adam        |
|  8 | CompressedEmbTableModel |        32768 |     100000000 |          465.756  |                   80.9117 |          3203.01   |        3749.68  | 381.5MB      | Adam        |
|  9 | FullEmbTableModel       |        32768 |     100000000 |           72.7418 |                   77.6243 |            91.5522 |         241.918 | 381.5MB      | LazyAdam    |
| 10 | CompressedEmbTableModel |        32768 |        262144 |          248.944  |                   77.3822 |           414.938  |         741.264 | 1.0MB        | LazyAdam    |
| 11 | CompressedEmbTableModel |        32768 |     100000000 |          458.843  |                   77.8364 |          1811.34   |        2348.02  | 381.5MB      | LazyAdam    |



Q2. ROBE-Z times are much worse than the full embedding even when low memory footprint like (1MB or 10MB) Why is it so ? How to fix it ?

A2. A lot is hidden in the tensorflow implementation. Specifically it is not clear as to when using ROBE-Z whether we are using sparse gradients / dense gradients, whether the hash computation is being added to the computational graph ( as it is using auto-differentiation functionality) and so on. In any case, I thought it would be wiser to benchmark my implementation of ROBE-Z . The results below are from a simple implementation of ROBE-Z in pytorch ( as i am not familiar with tensorflow) [pytorch benchmark](../cpu_robez/)

a) First note that sparse gradients are good for full embedding table where memory footprint is large.  ( in pytorch below adam with sparse is using sparseadam)

On 1 CPU

| Model          | sparse   |    bs |   params | FWD(ms)  |  GRAD(ms) |    BKWD(ms) |   total(ms) | msize   | optim   |
|----------------|----------|-------|----------|----------|-----------|-------------|-------------|---------|---------|
| FullEmbedding  | False    | 32768 |100000000 |  15.0243 |  544.749  |   61.9037   |     621.677 | 381.5MB | sgd     |
| FullEmbedding  | True     | 32768 |100000000 |  16.8703 |   52.7694 |  181.493    |     251.133 | 381.5MB | sgd     |
| FullEmbedding  | False    | 32768 |100000000 |  13.4688 |  544.184  |  778.126    |    1335.78  | 381.5MB | adagrad |
| FullEmbedding  | True     | 32768 |100000000 |  13.8796 |   52.6822 |  373.726    |     440.288 | 381.5MB | adagrad |
| FullEmbedding  | False    | 32768 |100000000 |  13.244  |  532.946  | 1014.4      |    1560.59  | 381.5MB | adam    |
| FullEmbedding  | True     | 32768 |100000000 |  14.0889 |   52.2924 |  576.35     |     642.732 | 381.5MB | adam    |

b) However, the same is not true with ROBE-Z . With ROBE-Z with much smaller footprint, we can see that dense gradients are good. This is also because of the fact that sparser gradients require more complex backward computation. ( There is still some mystery in this. The algorithmic component does not depend on the memory footprint but we see an increase in the time when we go from 1MB to 10MB with sparse gradients)

On 1 CPU

| Model          | sparse   |    bs |   params | FWD(ms)  |  GRAD(ms) |    BKWD(ms) |   total(ms) | msize   | optim   |
|----------------|----------|-------|----------|----------|-----------|-------------|-------------|---------|---------|
| RobezEmbedding | False    | 32768 |   262144 | 211.153  |   58.0465 |    0.2818   |     269.481 | 1.0MB   | sgd     |
| RobezEmbedding | False    | 32768 |  2621440 | 193.784  |   64.5972 |    1.26291  |     259.644 | 10.0MB  | sgd     |
| RobezEmbedding | True     | 32768 |   262144 | 181.741  |  304.657  |   15.9764   |     502.375 | 1.0MB   | sgd     |
| RobezEmbedding | True     | 32768 |  2621440 | 183.131  | 1309.42   |  157.363    |    1649.91  | 10.0MB  | sgd     |
| RobezEmbedding | False    | 32768 |   262144 | 171.624  |   49.8069 |    1.01899  |     222.45  | 1.0MB   | adam    |
| RobezEmbedding | False    | 32768 |  2621440 | 182.792  |   62.8146 |    9.88975  |     255.496 | 10.0MB  | adam    |
| RobezEmbedding | True     | 32768 |   262144 | 171.639  |  294.887  |   65.4829   |     532.009 | 1.0MB   | adam    |
| RobezEmbedding | True     | 32768 |  2621440 | 183.915  | 1295.97   |  661.781    |    2141.67  | 10.0MB  | adam    |



c) Overall, the ROBE-Z (1MB, 10MB) (dense gradients) with 1CPU is **comparable (SGD) or better (Adam/adagrad)** in time when compared to full embedding (380MB) (sparse gradients)

On 1CPU

| Model          | sparse   |    bs |   params | FWD(ms)  |  GRAD(ms) |    BKWD(ms) |   total(ms) | msize   | optim   |
|----------------|----------|-------|----------|----------|-----------|-------------|-------------|---------|---------|
| RobezEmbedding | False    | 32768 |   262144 | 211.153  |   58.0465 |    0.2818   |     269.481 | 1.0MB   | sgd     |
| RobezEmbedding | False    | 32768 |  2621440 | 193.784  |   64.5972 |    1.26291  |     259.644 | 10.0MB  | sgd     |
| FullEmbedding  | True     | 32768 |100000000 |  16.8703 |   52.7694 |  181.493    |     251.133 | 381.5MB | sgd     |
|----------------|----------|-------|----------|----------|-----------|-------------|-------------|---------|---------|
| RobezEmbedding | False    | 32768 |   262144 | 171.541  |   50.2693 |    0.727138 |     222.538 | 1.0MB   | adagrad |
| RobezEmbedding | False    | 32768 |  2621440 | 185.182  |   63.8764 |    6.34646  |     255.405 | 10.0MB  | adagrad |
| FullEmbedding  | True     | 32768 |100000000 |  13.8796 |   52.6822 |  373.726    |     440.288 | 381.5MB | adagrad |
|----------------|----------|-------|----------|----------|-----------|-------------|-------------|---------|---------|
| RobezEmbedding | False    | 32768 |   262144 | 171.624  |   49.8069 |    1.01899  |     222.45  | 1.0MB   | adam    |
| RobezEmbedding | False    | 32768 |  2621440 | 182.792  |   62.8146 |    9.88975  |     255.496 | 10.0MB  | adam    |
| FullEmbedding  | True     | 32768 |100000000 |  14.0889 |   52.2924 |  576.35     |     642.732 | 381.5MB | adam    |
|----------------|----------|-------|----------|----------|-----------|-------------|-------------|---------|---------|

d) Both the forward pass and backward pass for ROBE-Z are parallelizable and can benefit from more compute which is not true for full embedding. With 10CPUs, ROBE-Z (1MB , 10MB) is **much much better** than full-embedding (380MB)

On 10 CPUS

| Model          | sparse   |    bs |    params |  FWD(ms) |  GRAD(ms) | BKWD(ms)   |   total(ms) | msize   | optim   |
|----------------|----------|-------|-----------|----------|-----------|------------|-------------|---------|---------|
| RobezEmbedding | False    | 32768 |    262144 | 24.5816  |   20.7463 |   0.216307 |     45.5441 | 1.0MB   | sgd     |
| RobezEmbedding | False    | 32768 |   2621440 | 26.0287  |   33.7644 |   0.668377 |     60.4614 | 10.0MB  | sgd     |
| FullEmbedding  | True     | 32768 | 100000000 |  3.60157 |   19.2835 | 183.97     |    206.855  | 381.5MB | sgd     |
|----------------|----------|-------|-----------|----------|-----------|------------|-------------|---------|---------|
| RobezEmbedding | False    | 32768 |    262144 | 23.1123  |   15.3403 |   0.423025 |     38.8755 | 1.0MB   | adagrad |
| RobezEmbedding | False    | 32768 |   2621440 | 24.7194  |   28.0505 |   1.41813  |     54.188  | 10.0MB  | adagrad |
| FullEmbedding  | True     | 32768 | 100000000 |  3.10821 |   15.5356 | 282.721    |    301.365  | 381.5MB | adagrad |
|----------------|----------|-------|-----------|----------|-----------|------------|-------------|---------|---------|
| RobezEmbedding | False    | 32768 |    262144 | 22.7178  |   19.5777 |   0.631168 |     42.9267 | 1.0MB   | adam    |
| RobezEmbedding | False    | 32768 |   2621440 | 25.5613  |   35.7296 |   4.97946  |     66.2703 | 10.0MB  | adam    |
| FullEmbedding  | True     | 32768 | 100000000 |  5.62251 |   14.1575 | 444.051    |    463.831  | 381.5MB | adam    |
|----------------|----------|-------|-----------|----------|-----------|------------|-------------|---------|---------|

Q. Are there latency improvements possible to this code?
A. 
 -  This version of ROBE-Z uses pytorch for vectorized operations. I am sure it can be improved with custom code
 -  It uses hash function with mod operations which are slow. with cheaper hash functions, it can be improved further ()

Full details : (pytorch ROBE-Z : )[pytorch benchmark](../cpu_robez/)

Full details : (tensorflow ROBE-Z (victors code): )[tensorflow benchmark](../)


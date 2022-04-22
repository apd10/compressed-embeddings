# compressed-embeddings

This repo trains compressed embeddings to factorize a PMI matrix.

## How to run a benchmark

First create a virtual environment and install dependencies
```python
python -m venv .env
source .env/bin/activate
pip install -U pip setuptools wheel
pip install -r requirements.txt
```

Then run the following command to benchmark the training speed of compressed embeddings versus not compressed embeddings.	
```python
python benchmark.py
```
The output of this command is a csv file.

Here is an extract of the current output results:

| Model                   | Batch Size | Memory pool size (nb values) | Forward pass (ms) | gradient computation (ms) | backward pass (ms) | total time (ms) | model size | optimizer |
|-------------------------|------------|------------------------------|-------------------|---------------------------|--------------------|-----------------|------------|-----------|
| FullEmbTableModel       | 32768      |                              | 24.61             | 28.51                     | 21.8               | 74.92           | 381.5MB    | Adagrad   |
| CompressedEmbTableModel | 32768      | 262144                       | 94.95             | 27.13                     | 389.54             | 511.62          | 1.0MB      | Adagrad   |
| CompressedEmbTableModel | 32768      | 100000000                    | 119.08            | 26.52                     | 1096.84            | 1242.45         | 381.5MB    | Adagrad   |
| FullEmbTableModel       | 32768      |                              | 23.59             | 27.27                     | 12.73              | 63.59           | 381.5MB    | SGD       |
| CompressedEmbTableModel | 32768      | 262144                       | 94.49             | 27.5                      | 77.02              | 199.01          | 1.0MB      | SGD       |
| CompressedEmbTableModel | 32768      | 100000000                    | 117.99            | 27                        | 104.76             | 249.75          | 381.5MB    | SGD       |
| FullEmbTableModel       | 32768      |                              | 23.86             | 28.76                     | 1900.49            | 1953.11         | 381.5MB    | Adam      |
| CompressedEmbTableModel | 32768      | 262144                       | 95.39             | 26.62                     | 393.24             | 515.25          | 1.0MB      | Adam      |
| CompressedEmbTableModel | 32768      | 100000000                    | 120.13            | 26.72                     | 2873.85            | 3020.7          | 381.5MB    | Adam      |


With Lazy Adam -- 1 CPU
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


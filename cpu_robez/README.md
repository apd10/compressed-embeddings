CPUs :

Architecture:                    x86_64
CPU op-mode(s):                  32-bit, 64-bit
Byte Order:                      Little Endian
Address sizes:                   43 bits physical, 48 bits virtual
CPU(s):                          256
On-line CPU(s) list:             0-254
Off-line CPU(s) list:            255
Thread(s) per core:              1
Core(s) per socket:              64
Socket(s):                       2
NUMA node(s):                    2
Vendor ID:                       AuthenticAMD
CPU family:                      23
Model:                           49
Model name:                      AMD EPYC 7742 64-Core Processor
Stepping:                        0
Frequency boost:                 enabled
CPU MHz:                         1492.022
CPU max MHz:                     2250.0000
CPU min MHz:                     1500.0000
BogoMIPS:                        4500.03
Virtualization:                  AMD-V
L1d cache:                       2 MiB
L1i cache:                       2 MiB
L2 cache:                        32 MiB
L3 cache:                        256 MiB



1 CPU comparisions

|    | Model          | sparse   |    bs |   mem_params |   forward(ms) |   gradcomp(ms) |   backward(ms) |   total(ms) | msize   | optim   |
|----|----------------|----------|-------|--------------|---------------|----------------|----------------|-------------|---------|---------|
|  0 | FullEmbedding  | False    | 32768 |    100000000 |       15.0243 |       544.749  |      61.9037   |     621.677 | 381.5MB | sgd     |
|  0 | RobezEmbedding | False    | 32768 |       262144 |      211.153  |        58.0465 |       0.2818   |     269.481 | 1.0MB   | sgd     |
|  0 | RobezEmbedding | False    | 32768 |      2621440 |      193.784  |        64.5972 |       1.26291  |     259.644 | 10.0MB  | sgd     |
|  0 | RobezEmbedding | False    | 32768 |    100000000 |      224.997  |       573.319  |      43.8911   |     842.207 | 381.5MB | sgd     |
|  0 | FullEmbedding  | True     | 32768 |    100000000 |       16.8703 |        52.7694 |     181.493    |     251.133 | 381.5MB | sgd     |
|  0 | RobezEmbedding | True     | 32768 |       262144 |      181.741  |       304.657  |      15.9764   |     502.375 | 1.0MB   | sgd     |
|  0 | RobezEmbedding | True     | 32768 |      2621440 |      183.131  |      1309.42   |     157.363    |    1649.91  | 10.0MB  | sgd     |
|  0 | RobezEmbedding | True     | 32768 |    100000000 |      202.37   |      2510.23   |     498.962    |    3211.56  | 381.5MB | sgd     |
|  0 | FullEmbedding  | False    | 32768 |    100000000 |       13.4688 |       544.184  |     778.126    |    1335.78  | 381.5MB | adagrad |
|  0 | RobezEmbedding | False    | 32768 |       262144 |      171.541  |        50.2693 |       0.727138 |     222.538 | 1.0MB   | adagrad |
|  0 | RobezEmbedding | False    | 32768 |      2621440 |      185.182  |        63.8764 |       6.34646  |     255.405 | 10.0MB  | adagrad |
|  0 | RobezEmbedding | False    | 32768 |    100000000 |      200.69   |       564.485  |     817.671    |    1582.85  | 381.5MB | adagrad |
|  0 | FullEmbedding  | True     | 32768 |    100000000 |       13.8796 |        52.6822 |     373.726    |     440.288 | 381.5MB | adagrad |
|  0 | RobezEmbedding | True     | 32768 |       262144 |      173.493  |       299.84   |      47.1608   |     520.493 | 1.0MB   | adagrad |
|  0 | RobezEmbedding | True     | 32768 |      2621440 |      184.109  |      1302.36   |     482.181    |    1968.65  | 10.0MB  | adagrad |
|  0 | RobezEmbedding | True     | 32768 |    100000000 |      198.553  |      2507.93   |    1565.1      |    4271.58  | 381.5MB | adagrad |
|  0 | FullEmbedding  | False    | 32768 |    100000000 |       13.244  |       532.946  |    1014.4      |    1560.59  | 381.5MB | adam    |
|  0 | RobezEmbedding | False    | 32768 |       262144 |      171.624  |        49.8069 |       1.01899  |     222.45  | 1.0MB   | adam    |
|  0 | RobezEmbedding | False    | 32768 |      2621440 |      182.792  |        62.8146 |       9.88975  |     255.496 | 10.0MB  | adam    |
|  0 | RobezEmbedding | False    | 32768 |    100000000 |      199.963  |       558.193  |    1069.96     |    1828.11  | 381.5MB | adam    |
|  0 | FullEmbedding  | True     | 32768 |    100000000 |       14.0889 |        52.2924 |     576.35     |     642.732 | 381.5MB | adam    |
|  0 | RobezEmbedding | True     | 32768 |       262144 |      171.639  |       294.887  |      65.4829   |     532.009 | 1.0MB   | adam    |
|  0 | RobezEmbedding | True     | 32768 |      2621440 |      183.915  |      1295.97   |     661.781    |    2141.67  | 10.0MB  | adam    |
|  0 | RobezEmbedding | True     | 32768 |    100000000 |      198.546  |      2492.79   |    2206.1      |    4897.43  | 381.5MB | adam    |


10 CPUs comparisions
|    | Model          | sparse   |    bs |   mem_params |   forward(ms) |   gradcomp(ms) |   backward(ms) |   total(ms) | msize   | optim   |
|----|----------------|----------|-------|--------------|---------------|----------------|----------------|-------------|---------|---------|
|  0 | FullEmbedding  | False    | 32768 |    100000000 |       4.11161 |       181.958  |      30.2938   |    216.363  | 381.5MB | sgd     |
|  0 | RobezEmbedding | False    | 32768 |       262144 |      24.5816  |        20.7463 |       0.216307 |     45.5441 | 1.0MB   | sgd     |
|  0 | RobezEmbedding | False    | 32768 |      2621440 |      26.0287  |        33.7644 |       0.668377 |     60.4614 | 10.0MB  | sgd     |
|  0 | RobezEmbedding | False    | 32768 |    100000000 |      26.9037  |       221.748  |      29.2669   |    277.918  | 381.5MB | sgd     |
|  0 | FullEmbedding  | True     | 32768 |    100000000 |       3.60157 |        19.2835 |     183.97     |    206.855  | 381.5MB | sgd     |
|  0 | RobezEmbedding | True     | 32768 |       262144 |      26.0533  |       273.425  |      14.2834   |    313.761  | 1.0MB   | sgd     |
|  0 | RobezEmbedding | True     | 32768 |      2621440 |      25.6889  |      1305.5    |     136.552    |   1467.74   | 10.0MB  | sgd     |
|  0 | RobezEmbedding | True     | 32768 |    100000000 |      24.4683  |      2497.69   |     399.116    |   2921.27   | 381.5MB | sgd     |
|  0 | FullEmbedding  | False    | 32768 |    100000000 |       4.25564 |       187.102  |     170.694    |    362.051  | 381.5MB | adagrad |
|  0 | RobezEmbedding | False    | 32768 |       262144 |      23.1123  |        15.3403 |       0.423025 |     38.8755 | 1.0MB   | adagrad |
|  0 | RobezEmbedding | False    | 32768 |      2621440 |      24.7194  |        28.0505 |       1.41813  |     54.188  | 10.0MB  | adagrad |
|  0 | RobezEmbedding | False    | 32768 |    100000000 |      25.8944  |       202.048  |     164.304    |    392.246  | 381.5MB | adagrad |
|  0 | FullEmbedding  | True     | 32768 |    100000000 |       3.10821 |        15.5356 |     282.721    |    301.365  | 381.5MB | adagrad |
|  0 | RobezEmbedding | True     | 32768 |       262144 |      22.979   |       204.874  |      28.0649   |    255.918  | 1.0MB   | adagrad |
|  0 | RobezEmbedding | True     | 32768 |      2621440 |      25.2149  |       949.849  |     281.001    |   1256.07   | 10.0MB  | adagrad |
|  0 | RobezEmbedding | True     | 32768 |    100000000 |      73.7067  |      1957.53   |     974.717    |   3005.96   | 381.5MB | adagrad |
|  0 | FullEmbedding  | False    | 32768 |    100000000 |       3.84965 |       173.657  |     277.04     |    454.546  | 381.5MB | adam    |
|  0 | RobezEmbedding | False    | 32768 |       262144 |      22.7178  |        19.5777 |       0.631168 |     42.9267 | 1.0MB   | adam    |
|  0 | RobezEmbedding | False    | 32768 |      2621440 |      25.5613  |        35.7296 |       4.97946  |     66.2703 | 10.0MB  | adam    |
|  0 | RobezEmbedding | False    | 32768 |    100000000 |      25.8617  |       206.94   |     278.792    |    511.594  | 381.5MB | adam    |
|  0 | FullEmbedding  | True     | 32768 |    100000000 |       5.62251 |        14.1575 |     444.051    |    463.831  | 381.5MB | adam    |
|  0 | RobezEmbedding | True     | 32768 |       262144 |      25.17    |       205.65   |      42.6586   |    273.479  | 1.0MB   | adam    |
|  0 | RobezEmbedding | True     | 32768 |      2621440 |      24.5073  |       986.841  |     368.247    |   1379.6    | 10.0MB  | adam    |
|  0 | RobezEmbedding | True     | 32768 |    100000000 |      24.2058  |      1970.75   |    1301.54     |   3296.5    | 381.5MB | adam    |


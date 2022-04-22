1 CPU comparisions


|    | Model          | sparse   |   batch_size |   memory_size |   forward_pass_ms |   gradient_computation_ms |   backward_pass_ms |   total_time_ms | model size   | optimizer   |
|----|----------------|----------|--------------|---------------|-------------------|---------------------------|--------------------|-----------------|--------------|-------------|
|  0 | FullEmbedding  | False    |        32768 |     100000000 |          13.7593  |                  498.041  |          34.2359   |         546.036 | 381.5MB      | sgd         |
|  1 | RobezEmbedding | False    |        32768 |        262144 |         159.474   |                   35.6201 |           0.214481 |         195.309 | 2.0MB        | sgd         |
|  2 | RobezEmbedding | False    |        32768 |       2621440 |         186.05    |                   49.7624 |           1.1583   |         236.971 | 20.0MB       | sgd         |
|  3 | RobezEmbedding | False    |        32768 |     100000000 |         175.09    |                  501.508  |          47.1548   |         723.753 | 762.9MB      | sgd         |
|  4 | FullEmbedding  | True     |        32768 |     100000000 |          13.3693  |                   32.1751 |         136.307    |         181.852 | 381.5MB      | sgd         |
|  5 | RobezEmbedding | True     |        32768 |        262144 |         153.108   |                  223.531  |          10.1484   |         386.787 | 2.0MB        | sgd         |
|  6 | RobezEmbedding | True     |        32768 |       2621440 |         162.322   |                  981.607  |         103.859    |        1247.79  | 20.0MB       | sgd         |
|  7 | RobezEmbedding | True     |        32768 |     100000000 |         172.21    |                 1988.71   |         377.039    |        2537.96  | 762.9MB      | sgd         |
|  8 | FullEmbedding  | False    |        32768 |     100000000 |           9.72683 |                  475.704  |         547.957    |        1033.39  | 381.5MB      | adagrad     |
|  9 | RobezEmbedding | False    |        32768 |        262144 |         153.942   |                   32.6424 |           0.610278 |         187.195 | 2.0MB        | adagrad     |
| 10 | RobezEmbedding | False    |        32768 |       2621440 |         165.108   |                   44.2357 |           6.02938  |         215.373 | 20.0MB       | adagrad     |
| 11 | RobezEmbedding | False    |        32768 |     100000000 |         178.755   |                  471.536  |         568.374    |        1218.67  | 762.9MB      | adagrad     |
| 12 | FullEmbedding  | True     |        32768 |     100000000 |           9.99964 |                   33.7962 |         288.274    |         332.07  | 381.5MB      | adagrad     |
| 13 | RobezEmbedding | True     |        32768 |        262144 |         160.78    |                  229.125  |          33.1318   |         423.037 | 2.0MB        | adagrad     |
| 14 | RobezEmbedding | True     |        32768 |       2621440 |         163.038   |                  977.962  |         315.363    |        1456.36  | 20.0MB       | adagrad     |
| 15 | RobezEmbedding | True     |        32768 |     100000000 |         169.85    |                 1974.16   |        1115.89     |        3259.9   | 762.9MB      | adagrad     |
| 16 | FullEmbedding  | False    |        32768 |     100000000 |           9.64    |                  447.202  |         740.911    |        1197.75  | 381.5MB      | adam        |
| 17 | RobezEmbedding | False    |        32768 |        262144 |         151.221   |                   32.2502 |           0.874652 |         184.346 | 2.0MB        | adam        |
| 18 | RobezEmbedding | False    |        32768 |       2621440 |         161.458   |                   44.388  |           7.78903  |         213.635 | 20.0MB       | adam        |
| 19 | RobezEmbedding | False    |        32768 |     100000000 |         173.032   |                  467.8    |         775.975    |        1416.81  | 762.9MB      | adam        |
| 20 | FullEmbedding  | True     |        32768 |     100000000 |           9.84504 |                   33.0789 |         430.761    |         473.685 | 381.5MB      | adam        |
| 21 | RobezEmbedding | True     |        32768 |        262144 |         150.647   |                  223.097  |          42.4668   |         416.211 | 2.0MB        | adam        |
| 22 | RobezEmbedding | True     |        32768 |       2621440 |         160.414   |                  971.25   |         435.708    |        1567.37  | 20.0MB       | adam        |
| 23 | RobezEmbedding | True     |        32768 |     100000000 |         169.502   |                 1957.05   |        1594.29     |        3720.85  | 762.9MB      | adam        |

10 CPUs comparisions

|    | Model          | sparse   |   batch_size |   memory_size |   forward_pass_ms |   gradient_computation_ms |   backward_pass_ms |   total_time_ms | model size   | optimizer   |
|----|----------------|----------|--------------|---------------|-------------------|---------------------------|--------------------|-----------------|--------------|-------------|
|  0 | FullEmbedding  | False    |        32768 |     100000000 |           9.62667 |                  197.582  |          21.7405   |        228.949  | 381.5MB      | sgd         |
|  1 | RobezEmbedding | False    |        32768 |        262144 |          24.6668  |                   25.8354 |           0.218164 |         50.7203 | 2.0MB        | sgd         |
|  2 | RobezEmbedding | False    |        32768 |       2621440 |          38.1096  |                   35.5263 |           0.508306 |         74.1442 | 20.0MB       | sgd         |
|  3 | RobezEmbedding | False    |        32768 |     100000000 |          22.629   |                  223.928  |          19.2195   |        265.777  | 762.9MB      | sgd         |
|  4 | FullEmbedding  | True     |        32768 |     100000000 |           3.19177 |                   18.5081 |         187.07     |        208.77   | 381.5MB      | sgd         |
|  5 | RobezEmbedding | True     |        32768 |        262144 |          28.0239  |                  263.62   |          15.241    |        306.885  | 2.0MB        | sgd         |
|  6 | RobezEmbedding | True     |        32768 |       2621440 |          22.7164  |                  989.683  |          87.4508   |       1099.85   | 20.0MB       | sgd         |
|  7 | RobezEmbedding | True     |        32768 |     100000000 |          23.7144  |                 1973.18   |         295.099    |       2291.99   | 762.9MB      | sgd         |
|  8 | FullEmbedding  | False    |        32768 |     100000000 |           3.2562  |                  162.149  |         157.142    |        322.548  | 381.5MB      | adagrad     |
|  9 | RobezEmbedding | False    |        32768 |        262144 |          21.6468  |                   22.0605 |           0.43498  |         44.1423 | 2.0MB        | adagrad     |
| 10 | RobezEmbedding | False    |        32768 |       2621440 |          25.6614  |                   34.5822 |           1.26153  |         61.5052 | 20.0MB       | adagrad     |
| 11 | RobezEmbedding | False    |        32768 |     100000000 |          87.4099  |                  214.299  |         173.244    |        474.953  | 762.9MB      | adagrad     |
| 12 | FullEmbedding  | True     |        32768 |     100000000 |           2.32499 |                   14.2971 |         274.578    |        291.2    | 381.5MB      | adagrad     |
| 13 | RobezEmbedding | True     |        32768 |        262144 |          21.1345  |                  210.039  |          28.0562   |        259.23   | 2.0MB        | adagrad     |
| 14 | RobezEmbedding | True     |        32768 |       2621440 |          21.955   |                  971.435  |         266.236    |       1259.63   | 20.0MB       | adagrad     |
| 15 | RobezEmbedding | True     |        32768 |     100000000 |          22.6538  |                 1970.47   |         900.84     |       2893.97   | 762.9MB      | adagrad     |
| 16 | FullEmbedding  | False    |        32768 |     100000000 |           3.23485 |                  167.631  |         248.234    |        419.1    | 381.5MB      | adam        |
| 17 | RobezEmbedding | False    |        32768 |        262144 |          21.4975  |                   15.4086 |           0.520984 |         37.427  | 2.0MB        | adam        |
| 18 | RobezEmbedding | False    |        32768 |       2621440 |          21.8592  |                   27.2427 |           2.30835  |         51.4102 | 20.0MB       | adam        |
| 19 | RobezEmbedding | False    |        32768 |     100000000 |          21.9874  |                  196.855  |         257.862    |        476.705  | 762.9MB      | adam        |
| 20 | FullEmbedding  | True     |        32768 |     100000000 |           2.57619 |                   13.7143 |         405.542    |        421.833  | 381.5MB      | adam        |
| 21 | RobezEmbedding | True     |        32768 |        262144 |          24.3594  |                  272.45   |          59.6878   |        356.498  | 2.0MB        | adam        |
| 22 | RobezEmbedding | True     |        32768 |       2621440 |          22.2322  |                  947.598  |         360.598    |       1330.43   | 20.0MB       | adam        |
| 23 | RobezEmbedding | True     |        32768 |     100000000 |          23.5325  |                 1958.58   |        1343.55     |       3325.66   | 762.9MB      | adam        |


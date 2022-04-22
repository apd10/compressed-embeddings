""" Benchmark on compressed embedding table speed """

import torch
import torch.nn as nn
from typing import List
from PairModel import ModelWithPairEmbeddings
from compressed_embeddings.utils.converter import cast_bytes_to_memory_string
from compressed_embeddings.utils.decorators import timing

from tqdm import tqdm as tq
import pandas as pd
import numpy as np
import pdb
from tabulate import tabulate

def count_parameters(model):
    num = np.sum([p.numel() for p in model.parameters()])
    return num



def benchmark(nb_embeddings:int, embeding_dim:int, batch_sizes: List[int], mem_size: List[int], sparsity: List[bool]) -> pd.DataFrame:
    """ Benchmark compressed embedding table speed """

    report = pd.DataFrame()
    model_names = ["FullEmbedding", "RobezEmbedding"]
    robezs = [0,1]
    optimizers = [
        'sgd',
        'adagrad',
        'adam'
    ]

    for optimizer_name in optimizers:
        for sparse in sparsity:
            for bs in tq(batch_sizes):
                for robez in robezs:
                    model_name = model_names[robez]
                    for i, mem in enumerate(mem_size):
                        if robez == 0:
                            mem = (nb_embeddings * embeding_dim)
                            if i != 0:
                                continue
                        model = ModelWithPairEmbeddings(
                            nb_embeddings,
                            embeding_dim,
                            sparse,
                            robez,
                            mem,
                            32
                        )
                        if optimizer_name == "sgd":
                            optimizer = torch.optim.SGD(model.parameters(), lr=0.001)
                        elif optimizer_name == "adagrad":
                            optimizer = torch.optim.Adagrad(model.parameters(), lr=0.001)
                        elif optimizer_name == "adam":
                            if sparse:
                                optimizer = torch.optim.SparseAdam(model.parameters(), lr=0.001)
                            else:
                                optimizer = torch.optim.Adam(model.parameters(), lr=0.001)
    
                        loss_fct = nn.MSELoss()
    
                        forward_pass = []
                        gradient_computation = []
                        backward_pass = []
                        model.train()

                        for _ in range(8):
                            x = torch.from_numpy(np.random.randint(0, nb_embeddings, (bs, 2))).long()
                            y = torch.from_numpy(np.random.rand(bs, 1).astype(np.float32))
                            t, y_pred = timing(model)(x)
                            forward_pass.append(t)
                            loss_value = loss_fct(y, y_pred)
                            # grad
                            t,_ = timing(loss_value.backward)()
                            gradient_computation.append(t)
    
                            # apply
                            t, _ = timing(optimizer.step)()
                            backward_pass.append(t)
                            optimizer.zero_grad()
    
                        forward_pass = np.mean(forward_pass[2:])
                        gradient_computation = np.mean(gradient_computation[2:])
                        backward_pass = np.mean(backward_pass[2:])

    
                        infos = pd.DataFrame(
                            {
                                "Model": model_name,
                                "sparse" : sparse,
                                "bs": [bs],
                                "mem_params": [mem],
                                "forward(ms)": [forward_pass * 1000],
                                "gradcomp(ms)": [gradient_computation * 1000],
                                "backward(ms)": [backward_pass * 1000],
                                "total(ms)": [forward_pass * 1000 + gradient_computation * 1000 + backward_pass * 1000],
                                "msize": [cast_bytes_to_memory_string(4 * count_parameters(model))],
                                "optim": [optimizer_name],
                            }
                        )
                        print(infos)
                        report = report.append(infos)

    return report


# pylint: disable=redefined-outer-name
if __name__ == "__main__":

    nb_embeddings = 1_000_000
    embeding_dim = 100
    #batch_sizes = [64, 512, 4096, 32768]
    batch_sizes = [32768]
    #mem_size = [1, 8, 64, 512] + [32768 * 8 ** i for i in range(5)] + [nb_embeddings*embeding_dim]
    #mem_size = [64, 512] + [32768 * 8 ** i for i in range(5)]
    mem_size=[262144, 2621440, 100000000]

    sparsity = [False, True]
    my_report = benchmark(nb_embeddings, embeding_dim, batch_sizes, mem_size, sparsity)
    my_report.to_csv("benchmark.csv", index=False)
    print(tabulate(my_report, headers='keys', tablefmt='github'))

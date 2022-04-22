import torch
import torch.nn as nn
from RobezEmbedding import RobezEmbedding
import numpy as np
import pdb


class ModelWithPairEmbeddings(nn.Module):
    def __init__(self,
                nb_embeddings : int,
                embeddings_dim: int,
                sparse: bool,
                use_compressed_embeddings : bool,
                memory_size: int = None,
                robez_chunk_size : int  = None):
      super(ModelWithPairEmbeddings, self).__init__()
      
      if use_compressed_embeddings:
          assert (memory_size is not None) and (robez_chunk_size is not None)
          self.compressed_memory = nn.Parameter(torch.FloatTensor(memory_size).uniform_(-1/np.sqrt(nb_embeddings), 1/np.sqrt(nb_embeddings)), requires_grad = True)
          self.embedding = RobezEmbedding(nb_embeddings, embeddings_dim, _weight = self.compressed_memory, val_offset = 0, robez_chunk_size=robez_chunk_size, sparse=sparse)
      else:
          self.embedding = nn.Embedding(nb_embeddings, embeddings_dim, sparse=sparse)

    def forward(self, pair: torch.Tensor):
      i,j = pair[:,0], pair[:,1]
      i_embedding = self.embedding(i)
      j_embedding = self.embedding(j)
      sim = torch.einsum("ij,ij->i", i_embedding, j_embedding)
      return torch.unsqueeze(sim, 1)

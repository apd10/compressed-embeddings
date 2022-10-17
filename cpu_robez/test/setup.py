from setuptools import setup, Extension
from torch.utils import cpp_extension

cpp_module = cpp_extension.CppExtension('robe',
                                        sources=['robez.cpp'],
                                        extra_compile_args=['-fopenmp', '-O2'],
                                        #extra_compile_args=['-O2'],
                                        extra_link_args=['-lgomp']
                                        )

setup(name='robe',
      ext_modules=[cpp_module],
      cmdclass={'build_ext': cpp_extension.BuildExtension})

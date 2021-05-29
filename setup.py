#!/usr/bin/env python3
# encoding: utf-8
from distutils.core import setup, Extension
c_reader_module = Extension('c_reader', 
                  extra_compile_args = ['-std=c++11'],
                    sources = ['c_reader.cpp'])
setup(name='c_reader',
  version='0.1.0',
  description='File reader module written in C',
  ext_modules=[c_reader_module])
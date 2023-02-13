#!/usr/bin/bash
export LD_LIBRARY_PATH=`pwd`/lib:$LD_LIBRARY_PATH
ldd ./bin/bench_kernels

./bin/bench_kernels --benchmark_out="bench_result.json" --benchmark_out_format=json

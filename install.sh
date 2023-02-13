#!/bin/bash -e

#$1 = gcc_build or clang_build

#package name
PL="pennylane-lightning"
COMP="$2"
echo "$COMP $2"
working_dir="${COMP}_install"
# make working dir
echo started in `pwd`
echo $working_dir
if [ -d "$working_dir" ]; then
    rm -rf $working_dir
fi
mkdir $working_dir
mkdir $working_dir/bin
mkdir $working_dir/lib

if [ -d "$1" ]
then
    cp -Lr ./$1/spack/var/spack/environments/env_${PL}/.spack-env/view/bin/bench_kernels $working_dir/bin/
    ldd ./$1/spack/var/spack/environments/env_${PL}/.spack-env/view/bin/bench_kernels | grep "=> /" | awk '{print $3}' | xargs -I '{}' cp -Lv '{}' $working_dir/lib/
    cp ./benchmark_all.sh $working_dir/
    cp ./plot_gate_benchmark.py $working_dir/
else
    echo "$2 does not exist"
fi

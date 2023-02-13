#!/bin/bash -e

#$1 = gbuild, $2= gcc or clang

#package name
PL="pennylane-lightning"
COMP="$2"
echo "$COMP $2"
working_dir="${COMP}_build"
# make working dir
echo started in `pwd`
echo $working_dir
if [ -d "$working_dir" ]; then
    rm -rf $working_dir
fi
mkdir $working_dir
cd $working_dir
# clean up spack configuration
echo entering `pwd`
rm -rf ~/.spack/*
# clone a new spack
git clone https://github.com/mlxd/spack.git
cd spack
echo entering `pwd`
# shell init
source share/spack/setup-env.sh
which spack

#create and active spack environment for pennylane-lightning
spack env create env_${PL}
spack env activate env_${PL}

if [ "$2" == "clang" ]; then
    echo "installing llvm========"
    spack add llvm
    spack install llvm
    spack compiler add `spack location -i llvm`
    export PATH=./var/spack/environments/env_${PL}/.spack-env/view/bin:$PATH
    export LD_LIBRARY_PATH=./var/spack/environments/env_${PL}/.spack-env/view/lib:$LD_LIBRARY_PATH

fi

# finding and setting compilers
spack find # This will find only what packages are installed
# if you want to used spack installed compilers
#spack compiler add `spack location -i gcc@11.3.0` # this will add compiler
spack compiler find # it only shows system compilers that used by spack written in ~/.spack/linux/compilers.yaml
spack compilers # it will show what are in ~/.spack/linux/compilers.yaml
# clean up compilers if required
#spack config edit compilers
#spack compilers # it will show what are in ~/.spack/linux/compilers.yaml
# clean up and remove if any bad repos
#spack clean
spack repo list
if [ -d "../repo_${COMP}_${PL}" ]; then
    spack repo rm ../repo_${COMP}_${PL}
    rm -rf ../repo_${COMP}_${PL}
fi
# copy config.yaml so spack-stage will be in ~/.spack
#cp ../../config.yaml ./etc/spack/
cp ../../config.yaml ~/.spack/
# to make sure build_stage directory is ~/.spack/spack-stage
#spack config edit config
#build_stage:
#    - ~/.spack/spack-stage
#    - $user_cache_path/stage
#  # - $spack/var/spack/stage
# create repo and your own package
spack repo create ../repo_${COMP}_${PL}
spack repo add ../repo_${COMP}_${PL}
spack create --skip-editor https://github.com/PennyLaneAI/${PL}/archive/refs/tags/v0.27.0.tar.gz
cp ../../spack_packages/${COMP}/package.py ../repo_${COMP}_${PL}/packages/${PL}/package.py
#make edit and sure everything is fine
#spack edit ${PL}

#add pennylane-lightning into environment
spack add ${PL}

echo "start installation====================================="
spack install
echo "Installation Done!"

#run bench_kernels
ldd ./var/spack/environments/env_${PL}/.spack-env/view/bin/bench_kernels
#./var/spack/environments/env_${PL}/.spack-env/view/bin/bench_kernels
#That is all
cd ..
echo leaving `pwd`
cd ..
echo leaving `pwd`



# Copyright 2018-2021 Xanadu Quantum Technologies Inc.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

FROM ghcr.io/spack/ubuntu-focal:latest AS base


WORKDIR /opt/pennylane
COPY ./spack_packages/gcc/package.py ./package.py
COPY ./config.yaml ./config.yaml
COPY ./benchmark_all.sh ./benchmark_all.sh
COPY ./plot_gate_benchmark.py ./plot_gate_benchmark.py

RUN which spack \
    && ls -l \
    && cp ./config.yaml ~/.spack/ \
    && spack env create myenv \
    && spack env activate myenv \
    && spack add gcc@11.3.0 \
    && spack install \
    && spack compiler add `spack location -i gcc@11.3.0`

ENV PATH="/opt/spack/var/spack/environments/myenv/.spack-env/view/bin:$PATH"
ENV LD_LIBRARY_PATH="/opt/spack/var/spack/environments/myenv/.spack-env/view/lib:$LD_LIBRARY_PATH"

RUN spack find \
    && spack compiler find \
    && spack compilers \
    && spack repo create /opt/spack/var/spack/repos/gcc-pennylane-lightning \
    && spack repo add /opt/spack/var/spack/repos/gcc-pennylane-lightning \
    && spack create --skip-editor https://github.com/PennyLaneAI/pennylane-lightning/archive/refs/tags/v0.27.0.tar.gz \
    && cp ./package.py /opt/spack/var/spack/repos/gcc-pennylane-lightning/packages/pennylane-lightning/package.py \
    && spack env activate myenv \
    && spack compiler find \
    && spack compilers \
    && spack add pennylane-lightning%gcc@11.3.0 \
    && spack install

RUN mkdir ./install \
    && mkdir ./install/bin \
    && mkdir ./install/lib \
    && cp -Lr /opt/spack/var/spack/environments/myenv/.spack-env/view/bin/bench_kernels ./install/bin/ \
    && ldd /opt/spack/var/spack/environments/myenv/.spack-env/view/bin/bench_kernels | grep "=> /" | awk '{print $3}' | xargs -I '{}' cp -Lv '{}' ./install/lib/ \
    && cp ./benchmark_all.sh ./install/ \
    && cp ./plot_gate_benchmark.py ./install/


# create Second small build.
FROM ubuntu:latest
COPY --from=base /opt/pennylane/install /opt/install
#ENV PATH="/opt/install/bin:$PATH"
#ENV LD_LIBRARY_PATH="/opt/install/lib:$LD_LIBRARY_PATH"

RUN apt-get update \
    && apt-get install -y apt-utils \
    --no-install-recommends python3 python3-pip python3-venv

ENV PATH="/opt/install/bin:$PATH"
RUN ldd /opt/install/bin/bench_kernels | grep "=> /" | awk '{print $3}' | xargs -I '{}' cp -Lv '{}' /opt/install/lib/
ENV LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/opt/install/lib"
RUN ldd /opt/install/bin/bench_kernels
#RUN /opt/install/bin/bench_kernels

# Image build completed.
CMD echo "Successfully built Docker image"

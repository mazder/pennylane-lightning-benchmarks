# Copyright 2013-2022 Lawrence Livermore National Security, LLC and other
# Spack Project Developers. See the top-level COPYRIGHT file for details.
#
# SPDX-License-Identifier: (Apache-2.0 OR MIT)

# ----------------------------------------------------------------------------
# If you submit this package back to Spack as a pull request,
# please first remove this boilerplate and all FIXME comments.
#
# This is a template package file for Spack.  We've put "FIXME"
# next to all the things you'll want to change. Once you've handled
# them, you can save this file and test your package like this:
#
#     spack install pennylane-lightning
#
# You can edit this file again by typing:
#
#     spack edit pennylane-lightning
#
# See the Spack documentation for more information on packaging.
# ----------------------------------------------------------------------------

from spack.package import *


class PennylaneLightning(CMakePackage):
    #"""FIXME: Put a proper description of your package here."""

    # FIXME: Add a proper url for your package's homepage here.
    #homepage = "https://www.example.com"
    #url = "https://github.com/PennyLaneAI/pennylane-lightning/archive/refs/tags/v0.27.0.tar.gz"

    # FIXME: Add a list of GitHub accounts to
    # notify when the package is updated.
    # maintainers = ["github_user1", "github_user2"]

    #version("0.27.0", sha256="588d67aef2ef2e8776eb111cb9d7dcb2493beb58e9e9fcf5e10317ddfdeaaf85")

    # FIXME: Add dependencies if required.
    # depends_on("foo")

    #def cmake_args(self):
        # FIXME: Add arguments other than
        # FIXME: CMAKE_INSTALL_PREFIX and CMAKE_BUILD_TYPE
        # FIXME: If not needed delete this function
    #    args = []
    #    return args
    """FIXME: Put a proper description of your package here."""

    # FIXME: Add a proper url for your package's homepage here.
    #homepage = "https://www.example.com"
    url = "https://github.com/PennyLaneAI/pennylane-lightning/archive/refs/tags/v0.27.0.tar.gz"
    homepage = "https://docs.pennylane.ai/projects/lightning"
    git = "https://github.com/PennyLaneAI/pennylane-lightning.git"
    tag = "v0.27.0"


    # FIXME: Add a list of GitHub accounts to
    # notify when the package is updated.
    # maintainers = ["github_user1", "github_user2"]

    version("0.27.0", sha256="588d67aef2ef2e8776eb111cb9d7dcb2493beb58e9e9fcf5e10317ddfdeaaf85")

    # FIXME: Add dependencies if required.
    # depends_on("foo")
    # Hard deps needed to build package
    depends_on('cmake@3.21.0:', type='build') #3.21 and newer
    depends_on('ninja', type='build')

    variant("python", default=False, description="Build with Python support")
    variant("native", default=False, description="Build natively for given hardware")
    variant("blas", default=True, description="Build with BLAS support")
    variant("openmp", default=True, description="Build with BLAS support")
    variant("kokkos", default=True, description="Build with Kokkos support")
    variant("verbose", default=True, description="Build with full verbosity")

    variant('cpptests', default=False, description='Build CPP tests')
    variant('cppbenchmark', default=True, description='Build CPP bechmark examples')

    variant(
        "build_type",
        default="Release",
        description="CMake build type",
        values=("Debug", "Release", "RelWithDebInfo", "MinSizeRel"),
    )


    # Variant defined deps
    depends_on("blas", when="+blas")
    depends_on("kokkos@3.6.00", when="+kokkos")
    depends_on("kokkos-kernels@3.6.00", when="+kokkos")
    depends_on("llvm-openmp", when="+openmp %apple-clang")

    depends_on("python@3.7:", type=("build", "run"), when="+python")
    #depends_on("py-pennylane", type=("build", "run"), when="+python")
    depends_on("py-numpy", type=("build", "run"), when="+python")
    depends_on("py-pybind11", type=("build"), when="+python")
    depends_on("py-pip", type="build", when="+python")
    depends_on("py-wheel", type="build", when="+python")


    root_cmakelists_dir = 'pennylane_lightning/src/'
    build_targets=['bench_kernels']

    def cmake_args(self):
        # FIXME: Add arguments other than
        # FIXME: CMAKE_INSTALL_PREFIX and CMAKE_BUILD_TYPE
        # FIXME: If not needed delete this function
        #args = []

        args = [f"-DCMAKE_BUILD_TYPE={self.spec.variants['build_type'].value}"]
        if self.spec.variants['native'].value:
            args += ["-DENABLE_NATIVE=ON"]
        if self.spec.variants['blas'].value:
            args += ["-DENABLE_BLAS=ON"]
        if self.spec.variants['openmp'].value:
            args += ["-DENABLE_OPENMP=ON"]
        if not self.spec.variants['kokkos'].value:
            args += ["-DENABLE_KOKKOS=OFF"]
        else:
            args += [   "-DENABLE_KOKKOS=ON", 
                        f"-DKokkos_Core_DIR={self.spec['kokkos'].home}",
                        f"-DKokkos_Kernels_DIR={self.spec['kokkos-kernels'].home}",
                    ]
        if self.spec.variants['verbose'].value:
            args += ["-DCMAKE_VERBOSE_MAKEFILE:BOOL=ON"]

        #if not self.spec.variants['python'].value:
        #    args += ["-DENABLE_PYTHON=OFF"]
        #else:
        #    args += [  
        #                f"-DPYTHON_EXECUTABLE={self.spec['python'].command.path}", 
        #                f"-DPYTHON_INCLUDE_DIR={self.spec['python'].headers.directories[0]}",
        #                f"-DPYTHON_LIBRARY={self.spec['python'].libs.libraries[0]}",
        #            ]

        # Build tests
        if self.spec.variants['cpptests'].value:
            args += ["-DBUILD_TESTS=ON"]
        # Build benchmarks
        if self.spec.variants['cppbenchmark'].value:
            args += ["-DBUILD_BENCHMARKS=ON"]
        
        #args += ["-DCMAKE_INSTALL_PREFIX:PATH=BuildMyBench"]
        args += ["-DCMAKE_CXX_COMPILER=clang++"]
        args += ["-DCMAKE_C_COMPILER=clang"]
        args += ["-DCMAKE_TOOLCHAIN_PREFIX=llvm-"]
        args += ["-DLLVM_USE_LINKER=lld"]
        return args

    # the build process doesn't actually install anything, do it by hand
    def install(self, spec, prefix):
        mkdir(prefix.bin)
        #print(prefix.bin)
        src = self.build_directory+"/benchmarks"
        binaries = ['bench_kernels']
        for b in binaries:
            install(join_path(src, b), join_path(prefix.bin, b))

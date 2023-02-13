# pennylane-lightning-benchmarks

The repository is about
```
    1. Build pennylane-lightning target 'Bench_Kernels.cpp' using spack with gcc/c++ and
    llvm clang/clang++ separately in a bare-metal hardware and in a docker container.

    2. Run the target executable in both a bare-metal and a docker container

    3. Analyze the runtimes and any impacts when running in a docker container

Note:
This experiment shows that when running in a bare-metal, the runtime of target 'bench_kernels'
built with clang/clang++ is lower than the runtime of target 'bench_kernels' built with gcc/g++.
The similar results are observed that when running in a container, the runtime of
target 'bench_kernels' built with clang/clang++ is lower than the runtime of target
'bench_kernels' built with gcc/g++.

Moreover, this experiemnt also show that no significant impacts in runtime when running in
a docker container. Therefore, in comparing with gcc/g++, clang/clang++ compiler will be a better choice
 for pennylane-lightning 'Bench_Kernels.cpp'.

See the report Report.pdf for details of analysis results and 
further discussion on the results in Questions_Answers_On_Report.pdf.
```

# HOW TO USE IT #
```
  $git clone https://github.com/mazder/pennylane-lightning-benchmarks.git

  1. To build and install Bench_Kernels.cpp in Bare-Metal Hardware

	$cd pennylane-lightning-benchmarks

  	$make <B>build	// <B>=g for building with gcc/g++ or
                        // <B>=l for building with llvm clang/clang++

  	$make <I>install  // <I>=g for built with gcc/g++ or
  	                  // <I>=l for built with llvm clang/clang++

  2. To run the target binary 'bench_kernels' in Bare-Metal Hardware,
  do step 1 followed by the following commands

  	$export LD_LIBRARY_PATH=./XXX_install/lib:$LD_LIBRARY_PATH  // XXX=gcc or clang

	$./XXX_install/bin/bench_kernels


  3. To build Bench_Kernels.cpp` in a docker container

  	$make <B>docker //<B>=g for built  with gcc/g++ or
                        // <B>=l for built with llvm clang/clang++
                        // This will create a docker image named gcc-lightning or
                        // clang-lightning installed with the target binary 'bench_kernels'.

  4. To run the target binary 'bench_kernels' in docker container

    $docker container run -it --rm IMAGE_ID /opt/install/bin/bench_kernels

  Note: See the examples and runtimes in subsequent sections, also the runtime statistics for 
  all benchmarks with different runs are given in the data_post_processing directory.

```

### Runtime of 'bench_kernels' built with gcc/g++ and run in a bare-metal ###
```
Run on (48 X 3000 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x24)
  L1 Instruction 32 KiB (x24)
  L2 Unified 1024 KiB (x24)
  L3 Unified 16896 KiB (x2)
Load Average: 1.64, 1.64, 1.47
CPU::AVX: True
CPU::AVX2: True
CPU::AVX512F: True
CPU::Brand: Intel(R) Xeon(R) Silver 4116 CPU @ 2.10GHz
CPU::Vendor: GenuineIntel
Compiler::Name: GCC
Compiler::Version: 11.3.0
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy
and will incur extra overhead.
---------------------------------------------------------------------------------------
Benchmark                                             Time             CPU   Iterations
---------------------------------------------------------------------------------------
GeneratorRY<float>/AVX512/6                        3552 ns         3552 ns       199456
GeneratorRY<float>/AVX512/8                        4278 ns         4278 ns       162298
GeneratorRY<float>/AVX512/10                      11322 ns        11320 ns        61888
GeneratorRY<float>/AVX512/12                      28866 ns        28862 ns        24310
GeneratorRY<float>/AVX512/14                     144650 ns       144631 ns         5059
GeneratorRY<float>/AVX512/16                     498500 ns       498493 ns         1559
GeneratorRY<float>/AVX512/18                    3149120 ns      3149083 ns          218
GeneratorRY<float>/AVX512/20                   14261444 ns     14258894 ns           46
GeneratorRY<float>/AVX512/22                  110621887 ns    110601823 ns            6
GeneratorRY<float>/AVX512/24                  509250874 ns    509176345 ns            1
```
### Runtime of 'bench_kernels' built with llvm clang/clang++ and run in a bare-metal ###
```
Run on (48 X 3000 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x24)
  L1 Instruction 32 KiB (x24)
  L2 Unified 1024 KiB (x24)
  L3 Unified 16896 KiB (x2)
Load Average: 2.37, 1.92, 1.59
CPU::AVX: True
CPU::AVX2: True
CPU::AVX512F: True
CPU::Brand: Intel(R) Xeon(R) Silver 4116 CPU @ 2.10GHz
CPU::Vendor: GenuineIntel
Compiler::Name: Clang
Compiler::Version: 15.0.0
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy
and will incur extra overhead.
---------------------------------------------------------------------------------------
Benchmark                                             Time             CPU   Iterations
---------------------------------------------------------------------------------------
GeneratorRY<float>/AVX512/6                        3203 ns         3203 ns       219841
GeneratorRY<float>/AVX512/8                        4140 ns         4140 ns       158421
GeneratorRY<float>/AVX512/10                      12484 ns        12482 ns        57467
GeneratorRY<float>/AVX512/12                      35304 ns        35302 ns        20825
GeneratorRY<float>/AVX512/14                     147889 ns       147880 ns         4669
GeneratorRY<float>/AVX512/16                     590635 ns       590611 ns         1189
GeneratorRY<float>/AVX512/18                    3951325 ns      3951129 ns          165
GeneratorRY<float>/AVX512/20                   17946439 ns     17945707 ns           37
GeneratorRY<float>/AVX512/22                  112221043 ns    112210249 ns            6
GeneratorRY<float>/AVX512/24                  531368349 ns    531369583 ns            1
```
### Runtime of 'bench_kernels' built with gcc/g++ in a docker container and run it inside the container ###
```
Run on (48 X 3000 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x24)
  L1 Instruction 32 KiB (x24)
  L2 Unified 1024 KiB (x24)
  L3 Unified 16896 KiB (x2)
Load Average: 1.00, 0.63, 0.57
CPU::AVX: True
CPU::AVX2: True
CPU::AVX512F: True
CPU::Brand: Intel(R) Xeon(R) Silver 4116 CPU @ 2.10GHz
CPU::Vendor: GenuineIntel
Compiler::Name: GCC
Compiler::Version: 11.3.0
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy
and will incur extra overhead.
---------------------------------------------------------------------------------------
Benchmark                                             Time             CPU   Iterations
---------------------------------------------------------------------------------------
GeneratorRY<float>/AVX512/6                        4433 ns         4433 ns       155085
GeneratorRY<float>/AVX512/8                        5315 ns         5315 ns       136292
GeneratorRY<float>/AVX512/10                      12564 ns        12565 ns        55074
GeneratorRY<float>/AVX512/12                      31032 ns        31030 ns        23208
GeneratorRY<float>/AVX512/14                     136897 ns       136896 ns         4819
GeneratorRY<float>/AVX512/16                     472090 ns       472034 ns         1593
GeneratorRY<float>/AVX512/18                    3266193 ns      3266022 ns          218
GeneratorRY<float>/AVX512/20                   13793189 ns     13792551 ns           47
GeneratorRY<float>/AVX512/22                  103631431 ns    103626142 ns            6
GeneratorRY<float>/AVX512/24                  490459526 ns    490436107 ns            2
```
### Runtime of 'bench_kernels' built with llvm clang/clang++ in a docker container and run it inside the container ###
```
Run on (48 X 3000 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x24)
  L1 Instruction 32 KiB (x24)
  L2 Unified 1024 KiB (x24)
  L3 Unified 16896 KiB (x2)
Load Average: 0.89, 0.80, 0.63
CPU::AVX: True
CPU::AVX2: True
CPU::AVX512F: True
CPU::Brand: Intel(R) Xeon(R) Silver 4116 CPU @ 2.10GHz
CPU::Vendor: GenuineIntel
Compiler::Name: Clang
Compiler::Version: 15.0.6
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy
and will incur extra overhead.
---------------------------------------------------------------------------------------
Benchmark                                             Time             CPU   Iterations
---------------------------------------------------------------------------------------
GeneratorRY<float>/AVX512/6                        4799 ns         4799 ns       125353
GeneratorRY<float>/AVX512/8                        5188 ns         5188 ns       134858
GeneratorRY<float>/AVX512/10                      13633 ns        13633 ns        51393
GeneratorRY<float>/AVX512/12                      36950 ns        36949 ns        18762
GeneratorRY<float>/AVX512/14                     145667 ns       145652 ns         4748
GeneratorRY<float>/AVX512/16                     575187 ns       575157 ns         1232
GeneratorRY<float>/AVX512/18                    4079620 ns      4079477 ns          173
GeneratorRY<float>/AVX512/20                   17379203 ns     17379281 ns           40
GeneratorRY<float>/AVX512/22                  110704297 ns    110695856 ns            6
GeneratorRY<float>/AVX512/24                  508960588 ns    508826569 ns            1
```

# How to Use It

Run the following command from the top of data_post_processiong directory
```
data_post_processiong$g++ main.cpp -o main
data_post_processiong$./main gcc_run_bare_metal.txt clang_run_bare_metal.txt gcc_run_docker_container.txt clang_run_docker_container.txt

```

# Output
```

pennylane-lightning-benchmarks/data_post_processing$ ./main gcc_run_bare_metal_2.txt clang_run_bare_metal_2.txt gcc_run_docker_container_2.txt clang_run_docker_container_2.txt


===========================================================================================================================================
Comparison   gcc_run_bare_metal_2.txt  vs  clang_run_bare_metal_2.txt
Load Average: 0.69, 0.60, 0.70    vs      Load Average: 0.52, 0.65, 1.03
RT1             CPUT1           IT1
#1 1336008819551   1335759811010   55934441
#1 4.42241e+08     4.42158e+08     18515.2
#2 830112010356    829955389480    62061339
#2 2.74781e+08     2.74729e+08     20543.3
37.8663         37.8664         -10.9537
Total #ops: 3021
#op 2nd one Dominant: 1721            1720            1516
#op 1st one Dominant: 1300            1301            1505


===========================================================================================================================================
Comparison   gcc_run_docker_container_2.txt  vs  clang_run_docker_container_2.txt
Load Average: 0.62, 0.58, 0.72    vs      Load Average: 0.70, 0.56, 0.55
RT1             CPUT1           IT1
#1 1327611718045   1327415567695   50684446
#1 4.39461e+08     4.39396e+08     16777.4
#2 896466824302    896279860413    51617049
#2 2.96745e+08     2.96683e+08     17086.1
32.4752         32.4793         -1.84002
Total #ops: 3021
#op 2nd one Dominant: 1534            1534            1705
#op 1st one Dominant: 1487            1487            1316


===========================================================================================================================================
Comparison   gcc_run_bare_metal_2.txt  vs  gcc_run_docker_container_2.txt
Load Average: 0.69, 0.60, 0.70    vs      Load Average: 0.62, 0.58, 0.72
RT1             CPUT1           IT1
#1 1336008819551   1335759811010   55934441
#1 4.42241e+08     4.42158e+08     18515.2
#2 1327611718045   1327415567695   50684446
#2 4.39461e+08     4.39396e+08     16777.4
0.628521        0.624681        9.38598
Total #ops: 3021
#op 2nd one Dominant: 1282            1283            2223
#op 1st one Dominant: 1739            1738            798


===========================================================================================================================================
Comparison   clang_run_bare_metal_2.txt  vs  clang_run_docker_container_2.txt
Load Average: 0.52, 0.65, 1.03    vs      Load Average: 0.70, 0.56, 0.55
RT1             CPUT1           IT1
#1 830112010356    829955389480    62061339
#1 2.74781e+08     2.74729e+08     20543.3
#2 896466824302    896279860413    51617049
#2 2.96745e+08     2.96683e+08     17086.1
-7.99348        -7.99133        16.829
Total #ops: 3021
#op 2nd one Dominant: 983             985             2319
#op 1st one Dominant: 2038            2036            702

```

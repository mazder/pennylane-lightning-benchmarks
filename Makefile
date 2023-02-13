DOCKER := $(shell which docker 2>/dev/null)

.PHONY: help gbuild lbuild ginstall linstall gdocker ldocker clean

help:
	@echo "Please use \`make <target>' where <target> is one of the following to build pennylane-lightning benchmark.cpp using spack"
	@echo "gbuild		to build with gcc/g++ in bare-metal"
	@echo "lbuild 		to build with clang/clang++ in bare-metal"
	@echo "ginstall	to create installation compiled with gcc/g++ in bare-metal"
	@echo "linstall	to create installation compiled with clang/clang++ in bare-metal"
	@echo "gdocker		to build with gcc/g++ in docker container"
	@echo "ldocker		to build with clang/clang++ docker container"

	@echo "clean		to delete all build files"


gbuild:
	./setup.sh gbuild gcc GCCVERSIONGTE11

lbuild:
	./setup.sh lbuild clang CLANGVERSIONGTE14

ginstall:
	./install.sh gcc_build gcc

linstall:
	./install.sh clang_build clang

gdocker:
	docker build -t gcc-lightning -f ./gcc_docker/Dockerfile .

ldocker:
	docker build -t clang-lightning -f ./llvm_gcc_docker/Dockerfile .

clean:
	rm -rf gcc_build
	rm -rf clang_build

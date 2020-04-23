# This Makefile is just a shorthand for creating directories and running CMake build modes

ROOT_DIR := $(shell dirname $(abspath $(lastword $(MAKEFILE_LIST))))

BUILD_TYPE ?= Debug
BUILD_DIR := $(shell echo $(BUILD_TYPE) | tr A-Z a-z)
ADDITIONAL_ARGS ?= 

THREAD_NUM ?= 4

.PHONY: all build debug release relwithdebinfo minsizerel clean

all: debug

.ONESHELL:
build:
	mkdir -p build/$(BUILD_DIR) && cd build/$(BUILD_DIR)
	cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) $(ADDITIONAL_ARGS) $(ROOT_DIR)
	cmake --build . --config $(BUILD_TYPE) -- -j$(THREAD_NUM)

debug:
	$(MAKE) build BUILD_TYPE=Debug

release:
	$(MAKE) build BUILD_TYPE=Release

dist:
	$(MAKE) build BUILD_DIR=dist BUILD_TYPE=Release ADDITIONAL_ARGS=-DPYRE_DISTRIBUTION:BOOL=ON

clean:
	rm -rf build/debug bin/debug
	rm -rf build/release bin/release
	rm -rf build/dist bin/dist
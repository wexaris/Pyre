# This Makefile is just a shorthand for creating directories and running CMake build modes

ROOT_DIR := $(shell dirname $(abspath $(lastword $(MAKEFILE_LIST))))

BUILD_TYPE ?= Debug
BUILD_DIR := $(shell echo $(BUILD_TYPE) | tr A-Z a-z)

THREAD_NUM ?= 4

.PHONY: all build debug release relwithdebinfo minsizerel clean

all: debug

.ONESHELL:
build:
	mkdir -p build/$(BUILD_DIR) && cd build/$(BUILD_DIR)
	cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) $(ROOT_DIR)
	cmake --build . --config $(BUILD_TYPE) -- -j$(THREAD_NUM)

debug:
	$(MAKE) build BUILD_TYPE=Debug

release:
	$(MAKE) build BUILD_TYPE=Release

dist:
	mkdir -p build/dist && cd build/dist
	cmake -DCMAKE_BUILD_TYPE=Release -DPYRE_DISTRIBUTION $(ROOT_DIR)
	cmake --build . --config $(BUILD_TYPE) -- -j$(THREAD_NUM)

clean:
	rm -rf build/debug bin/debug
	rm -rf build/release bin/release
	rm -rf build/dist bin/dist
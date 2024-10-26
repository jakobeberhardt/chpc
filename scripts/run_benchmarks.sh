#!/bin/bash

set -e

echo "Building all benchmarks..."
make clean
make all

echo "Running benchmarks..."
make run

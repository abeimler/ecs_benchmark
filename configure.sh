#!/bin/bash

python -m cogapp -r ./app/CMakeLists.txt
python -m cogapp -r ./src/CMakeLists.txt
python -m cogapp -r ./test/CMakeLists.txt
python -m cogapp -r ./benchmark/CMakeLists.txt

cmake . --build build
cmake_minimum_required(VERSION 3.20)
project(CorrelacaoCruzada1D C)

set(CMAKE_C_STANDARD 90)

add_executable(test_suite src/cross_correlation.c tests/test_suite.c)
target_include_directories(test_suite PRIVATE include)
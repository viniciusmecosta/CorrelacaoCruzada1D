cmake_minimum_required(VERSION 3.20)
project(CorrelacaoCruzada1D C)

set(CMAKE_C_STANDARD 90)

add_executable(test_impulso src/cross_correlation.c tests/test_impulso.c)
target_include_directories(test_impulso PRIVATE include)

add_executable(test_atraso src/cross_correlation.c tests/test_atraso.c)
target_include_directories(test_atraso PRIVATE include)

add_executable(test_sinais src/cross_correlation.c tests/test_sinais.c)
target_include_directories(test_sinais PRIVATE include)
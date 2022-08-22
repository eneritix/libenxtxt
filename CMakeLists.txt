cmake_minimum_required(VERSION 3.5)
project(libenxtxt LANGUAGES C)

add_library(
    enxtxt
    src/convert.c
    include/enx/txt/convert.h
    )

target_include_directories(enxtxt PUBLIC include)
target_include_directories(enxtxt PRIVATE include/enx/txt)

add_executable(enxtxt_test_convert tests/test_convert.c)
target_link_libraries(enxtxt_test_convert enxtxt cmocka)

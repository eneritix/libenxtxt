cmake_minimum_required(VERSION 3.5)
project(libenxtxt LANGUAGES C)

add_library(
    enxtxt
    source/convert.c
    source/format.c
    source/tokenizer.c
    source/fstr.c
    )

target_include_directories(enxtxt PUBLIC include)
target_include_directories(enxtxt PRIVATE include/enx/txt)

add_executable(enxtxt_test_convert tests/test_convert.c)
target_link_libraries(enxtxt_test_convert enxtxt cmocka)

add_executable(enxtxt_test_format tests/test_format.c)
target_link_libraries(enxtxt_test_format enxtxt cmocka)

add_executable(enxtxt_test_tokenizer tests/test_tokenizer.c)
target_link_libraries(enxtxt_test_tokenizer enxtxt cmocka)

add_executable(enxtxt_test_fstr tests/test_fstr.c)
target_link_libraries(enxtxt_test_fstr enxtxt cmocka)

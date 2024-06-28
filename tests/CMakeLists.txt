
add_executable(enxtxt_test_convert source/test_convert.c)
target_link_libraries(enxtxt_test_convert enxtxt cmocka)

add_executable(enxtxt_test_format source/test_format.c)
target_link_libraries(enxtxt_test_format enxtxt cmocka)

add_executable(enxtxt_test_format_flt source/test_format_flt.c)
target_link_libraries(enxtxt_test_format_flt enxtxt cmocka)

add_executable(enxtxt_test_tokenizer source/test_tokenizer.c)
target_link_libraries(enxtxt_test_tokenizer enxtxt cmocka)

add_executable(enxtxt_test_fstr source/test_fstr.c)
target_link_libraries(enxtxt_test_fstr enxtxt cmocka)


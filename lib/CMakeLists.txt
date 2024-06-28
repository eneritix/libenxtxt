
add_library(
    enxtxt
    source/convert.c
    source/format.c
    source/tokenizer.c
    source/fstr.c
    )

target_compile_options(enxtxt PRIVATE -Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter)
target_include_directories(enxtxt PUBLIC include)
target_include_directories(enxtxt PRIVATE include/enx/txt)
target_include_directories(enxtxt PRIVATE source)

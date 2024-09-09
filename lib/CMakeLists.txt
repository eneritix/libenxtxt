
option(LIBENXTXT_USE_SPRINTF "Use sprintf for formatting" ON)

set(enxtxt_SOURCES
    source/convert.c
    source/tokenizer.c
    source/fstr.c
)

if (LIBENXTXT_USE_SPRINTF)
    set(enxtxt_SOURCES
        ${enxtxt_SOURCES}
        source/format_sprintf.c
    )
else()
    set(enxtxt_SOURCES
        ${enxtxt_SOURCES}
        source/format.c
    )
endif(LIBENXTXT_USE_SPRINTF)

add_library(
    enxtxt
    ${enxtxt_SOURCES}
    )

target_compile_options(enxtxt PRIVATE -Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter)
target_include_directories(enxtxt PUBLIC include)
target_include_directories(enxtxt PRIVATE include/enx/txt)
target_include_directories(enxtxt PRIVATE source)

if (NOT LIBENXTXT_USE_SPRINTF)
    target_link_libraries(enxtxt PRIVATE ryu)
endif()

set(CMAKE_C_STANDARD 11)
add_library(hashtable STATIC
        hash_table.c
        )

target_include_directories(hashtable PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )

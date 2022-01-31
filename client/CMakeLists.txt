cmake_minimum_required(VERSION 3.13)
project(gestione_farmacia C)

set(CMAKE_C_STANDARD 11)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
find_package(MySQL REQUIRED)

add_executable(gestione_farmacia
        main.c
        controller/amministrativo.c
        controller/medico.c
        controller/login.c
        model/db.c
        utils/db.c
        utils/dotenv.c
        utils/io.c
        utils/validation.c
        view/amministrativo.c
        view/medico.c
        view/login.c
)

include_directories(${MYSQL_INCLUDE_DIR})
target_link_libraries(gestione_farmacia ${MYSQL_LIBRARIES})

if(MSVC)
    add_compile_options(PRIVATE /W4 /WX)
else()
    add_compile_options(PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

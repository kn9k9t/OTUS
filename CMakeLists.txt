cmake_minimum_required(VERSION 3.5)

set(PROJECT_VERSION 0.0.1)
project(matrix VERSION ${PROJECT_VERSION})

add_executable(matrix src/main.cpp)
add_library(libmatrix src/Matrix.h)

set_target_properties(matrix PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(matrix PRIVATE libmatrix)

set_target_properties(libmatrix PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(matrix PRIVATE
        /W4
    )
    target_compile_options(libmatrix PRIVATE
        /W4
    )
else ()
    target_compile_options(matrix PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(libmatrix PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS matrix RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT nikpavl04@gmail.com)
include(CPack)

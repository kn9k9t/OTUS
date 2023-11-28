cmake_minimum_required(VERSION 3.2)

set(PROJECT_VERSION 0.0.1)
project(allocator VERSION ${PROJECT_VERSION})

find_package(GTest REQUIRED)

add_executable(allocator src/main.cpp)
add_library(liballocator src/CustomAllocator.h )
add_library(libcontainer src/CustomContainer.h)

set_target_properties(allocator liballocator libcontainer PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(allocator PRIVATE liballocator)
target_include_directories(allocator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/IPv4)

set_target_properties(liballocator PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(libcontainer PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(allocator PRIVATE
        /W4
    )
    target_compile_options(liballocator PRIVATE
        /W4
    )
    target_compile_options(libcontainer PRIVATE
        /W4
    )
else ()
    target_compile_options(allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(liballocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(libcontainer PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT nikpavl04@gmail.com)
include(CPack)

cmake_minimum_required(VERSION 3.2)

set(PROJECT_VERSION 0.0.1)
project(ip_filter VERSION ${PROJECT_VERSION})

find_package(GTest REQUIRED)

add_executable(ip_filter src/main.cpp)
add_library(libipv4 src/IPv4/IPv4.h src/IPv4/IPv4.cpp)
add_executable(ipv4tests src/Tests/IPv4Test.cpp)

set_target_properties(ip_filter libipv4 PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(ip_filter PRIVATE libipv4)
target_include_directories(ip_filter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/IPv4)

target_include_directories(ipv4tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/IPv4)

set_target_properties(libipv4 PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(ipv4tests
    GTest::gtest_main
    libipv4
)

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(libipv4 PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(libipv4 PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT nikpavl04@gmail.com)
include(CPack)

enable_testing()
add_test(ipv4tests ipv4tests)

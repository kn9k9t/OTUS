cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(helloworld VERSION ${PROJECT_VERSION})

find_package(GTest REQUIRED)

configure_file(src/Version/version.h.in version.h)

add_executable(helloworld_cli src/main.cpp)
add_library(libversion src/Version/SoftwareVersion.h)
add_executable(tests src/Tests/SoftwareVersionTest.cpp)

set_target_properties(helloworld_cli libversion tests PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(libversion PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(libversion
    PUBLIC "${CMAKE_BINARY_DIR}"
)

target_link_libraries(helloworld_cli PRIVATE
    libversion
)
target_link_libraries(tests
    GTest::gtest_main
    libversion
)

if (MSVC)
    target_compile_options(helloworld_cli PRIVATE
        /W4
    )
    target_compile_options(libversion PRIVATE
        /W4
    )
    target_compile_options(tests PRIVATE
        /W4
    )
else ()
    target_compile_options(helloworld_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(libversion PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(tests PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT nikpavl04@gmail.com)

include(CPack)

enable_testing()

add_test(tests tests)

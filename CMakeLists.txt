cmake_minimum_required(VERSION 3.5)

set(PROJECT_VERSION 0.0.1)
project(bayan VERSION ${PROJECT_VERSION})

find_package(Boost COMPONENTS program_options filesystem regex REQUIRED)

add_executable(bayan src/main.cpp)
add_library(libbayan
  src/File.h
  src/Hash.h
  src/Settings.h
  src/Settings.cpp
  src/Scaner.h
  src/Scaner.cpp)

set_target_properties(bayan libbayan PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_link_libraries(libbayan PRIVATE ${Boost_LIBRARIES})

target_link_libraries(bayan PRIVATE libbayan ${Boost_LIBRARIES})

set_target_properties(libbayan PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(bayan PRIVATE
        /W4
    )
    target_compile_options(libbayan PRIVATE
        /W4
    )
else ()
    target_compile_options(bayan PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(libbayan PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS bayan RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT nikpavl04@gmail.com)
include(CPack)

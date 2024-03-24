cmake_minimum_required(VERSION 3.5)

set(PROJECT_VERSION 0.0.1)
project(bulk VERSION ${PROJECT_VERSION})

add_executable(bulk src/main.cpp)
add_library(libbulk
  src/CmdMng.h
  src/CmdMng.cpp
  src/Bulk.h
  src/Bulk.cpp
  src/Common/CommonTypes.h
  src/Handlers/FileHandler.h
  src/Handlers/TerminalHandler.h
)

include_directories(libulk src/Handlers src/Common)

set_target_properties(bulk PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(bulk PRIVATE libbulk)

set_target_properties(libbulk PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(bulk PRIVATE
        /W4
    )
    target_compile_options(libbulk PRIVATE
        /W4
    )
else ()
    target_compile_options(bulk PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(libbulk PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS bulk RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT nikpavl04@gmail.com)
include(CPack)

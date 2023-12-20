cmake_minimum_required(VERSION 3.5)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(vector_editor VERSION ${PROJECT_VERSION})

add_executable(graphic-editor src/main.cpp)
add_library(editor-lib
  src/Primitives.h
  src/FileHandler.h
  src/EditorController.h
  src/UserInterface.h
  )

set_target_properties(graphic-editor PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(editor-lib PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(editor-lib PRIVATE src)

target_link_libraries(graphic-editor PRIVATE editor-lib)

if (MSVC)
    target_compile_options(graphic-editor PRIVATE
        /W4
    )
    target_compile_options(editor-lib PRIVATE
        /W4
    )
else ()
    target_compile_options(graphic-editor PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(editor-lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS graphic-editor RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT nikpavl04@gmail.com)

include(CPack)

enable_testing()

add_test(tests tests)

cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(CUSTOM_ALLOCATOR VERSION ${PROJECT_VERSION})

configure_file(version.h.in version.h)

add_executable(main main.cpp)
add_library(lib lib.cpp
        profile.hpp
        custom_container.hpp
)
target_link_libraries(main lib)

# add_subdirectory(googletest)
# enable_testing()
# include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
# file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
# add_executable(tests filter_test.cpp)
# target_link_libraries(tests gtest gtest_main)
# target_link_libraries(tests lib)
# add_test(UnitTests tests)

set_target_properties(main lib PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)

# target_include_directories(lib
#     PUBLIC ${CMAKE_CURRENT_DIR}/googletest
# )

install(TARGETS main RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
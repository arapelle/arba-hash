include(cmtk/CppLibraryTests)
include(GoogleTest)

find_package(GTest 1.14 CONFIG REQUIRED)

add_cpp_library_basic_tests(${PROJECT_TARGET_NAME} GTest::gtest_main
    SOURCES
        murmur_hash_tests.cpp
        murmur_hash_2_tests.cpp
        project_version_tests.cpp
)

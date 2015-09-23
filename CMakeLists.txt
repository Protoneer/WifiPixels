cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(gtest-demo)

enable_language(C CXX)

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake
    )

include(ConfigSafeGuards)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS         "-Wall -Wno-unknown-pragmas -Wno-sign-compare -Woverloaded-virtual -Wwrite-strings -Wno-unused")
    set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
#   set(CMAKE_CXX_LINK_FLAGS "-fprofile-arcs -ftest-coverage")
endif()

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/third-party/gtest-1.7.0
    ${PROJECT_SOURCE_DIR}/third-party/gtest-1.7.0/include
    $HOME/arduino_ide/libraries
    ~/.arduino15/packages/esp8266/hardware/esp8266/1.6.5-947-g39819f0/libraries/ESP8266WiFi/src
    ~/.arduino15/packages/esp8266/hardware/esp8266/1.6.5-947-g39819f0/cores/esp8266
    ~/.arduino15/packages/esp8266/hardware/esp8266/1.6.5-947-g39819f0/tools/sdk/include
    
    )

#add_library(
#    src/config.cpp
#    )

add_custom_target(
    git_update
    COMMAND git submodule init
    COMMAND git submodule update
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    )

add_library(
    gtest
    ${PROJECT_SOURCE_DIR}/third-party/gtest-1.7.0/src/gtest-all.cc
    ${PROJECT_SOURCE_DIR}/third-party/gtest-1.7.0/src/gtest_main.cc
    )

add_dependencies(gtest git_update)

set_source_files_properties(${PROJECT_SOURCE_DIR}/third-party/gtest-1.7.0/src/gtest-all.cc  PROPERTIES GENERATED 1)
set_source_files_properties(${PROJECT_SOURCE_DIR}/third-party/gtest-1.7.0/src/gtest_main.cc PROPERTIES GENERATED 1)

add_executable(
    unit_tests
    test/main.cpp
    test/test_config.cpp
    )

add_dependencies(unit_tests gtest)

target_link_libraries(
    unit_tests
    gtest
    pthread
    )

include(CTest)
enable_testing()

add_test(unit ${PROJECT_BINARY_DIR}/unit_tests)

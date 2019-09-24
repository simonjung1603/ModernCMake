cmake_minimum_required(VERSION 3.10)

#configure main project
set(PROJECT_NAME "MidiBuddy")
project(${PROJECT_NAME})

set(PROJ_NAME "\"Modern CMake\"") # PROJECT_NAME is a predefined variable
set(PROJECT_DESCRIPTION "\"A CMake example\"")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
option(BUILD_TESTS "Build test executable" OFF)
option(GEN_DOCS "Generate documentation" OFF)
option(ENABLE_COVERAGE "Enable code coverage" OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as no build type was specified")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the build type (Debug/Release)" FORCE)
endif (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)

if (ENABLE_COVERAGE AND NOT CMAKE_CONFIGURATION_TYPES)
    if (NOT BUILD_TESTS)
        message(FATAL_ERROR "Tests must be enabled for code coverage!")
    endif (NOT BUILD_TESTS)
    
    include(CodeCoverage)
    
    append_coverage_compiler_flags()
    set(COVERAGE_EXCLUDES "/usr/include/\\*;${CMAKE_SOURCE_DIR}/src/main.cpp;${CMAKE_SOURCE_DIR}/test/*;${CMAKE_SOURCE_DIR}/third_party/doctest/*")
    
    setup_target_for_coverage(NAME coverage EXECUTABLE ctest DEPENDENCIES coverage)
else (ENABLE_COVERAGE AND NOT CMAKE_CONFIGURATION_TYPES)
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    endif(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
endif (ENABLE_COVERAGE AND NOT CMAKE_CONFIGURATION_TYPES)

add_executable(${PROJECT_NAME} Main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
  # This is required for every bundle
  COMPILE_DEFINITIONS US_BUNDLE_NAME=${PROJECT_NAME}
  # This is for convenience, used by other CMake functions
  US_BUNDLE_NAME ${PROJECT_NAME}
  )

option(BUILD_SHARED_LIBS "Build shared libs" ON)

find_package(CppMicroServices REQUIRED PATHS ${CMAKE_BINARY_DIR}/../cppmicroservices-prefix/src/cppmicroservices-build)
#target_include_directories(${PROJECT_NAME} PRIVATE CppMicroServices)

#bundles
include("${CMAKE_CURRENT_SOURCE_DIR}/BundleList.cmake")
add_dependencies(${PROJECT_NAME} core)
target_link_libraries(${PROJECT_NAME} PRIVATE CppMicroServices)

configure_file(project.vcxproj.user.in ${PROJECT_NAME}.vcxproj.user)

foreach(mb_bundle ${MB_BUNDLES})
  add_subdirectory(${mb_bundle})
endforeach()
#todo remove
target_include_directories(${PROJECT_NAME} PRIVATE core)
target_link_libraries(${PROJECT_NAME} PRIVATE core)

if (BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(test)
endif (BUILD_TESTS)

if (GEN_DOCS)
    add_subdirectory(doc)
endif (GEN_DOCS)

# Install the built library and executable into the appropriate directory
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# Install the project header files into the appropriate directory
# install(DIRECTORY include/ DESTINATION include PATTERN "config.hpp.in" EXCLUDE) # Install our main header files
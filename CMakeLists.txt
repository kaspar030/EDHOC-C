cmake_minimum_required(VERSION 3.11)

set(VERSION_MAJOR 0 CACHE STRING "Project major version number")
set(VERSION_MINOR "1" CACHE STRING "Project minor version number")
set(VERSION_PATCH "0" CACHE STRING "Project patch version number")
set(EDHOC_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

message(STATUS "Compiling with: ${CMAKE_C_COMPILER}")

project("edhoc-c" LANGUAGES C VERSION "${EDHOC_VERSION}")

include(ExternalProject)

set(CMAKE_C_STANDARD 11)

# Set the output of the libraries and executables.
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

###############################################################################
# OPTIONS
###############################################################################

option(EDHOC_FATAL_WARNINGS "fail build when there are compile warnings" OFF)
option(EDHOC_BUILD_TESTS "build tests" ON)
option(EDHOC_BUILD_EXAMPLES "build examples" ON)
option(BUILD_SHARED_LIBS "Build Shared Libraries" ON)
option(EDHOC_USE_ASAN "Use address sanitizers" ON)
option(EDHOC_USE_LSAN "Use leak sanitizers" ON)
option(EDHOC_USE_USAN "Use undefined sanitizers" ON)
option(EDHOC_USE_MSAN "Use memory sanitizers" OFF)
option(EDHOC_BUILD_FUZZ_TARGETS "Compile fuzz targets" ON)

if (BUILD_SHARED_LIBS)
    set(BUILD_STATIC_LIBS OFF)
else ()
    set(BUILD_STATIC_LIBS ON)
endif ()

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif ()

set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "MinSizeRel" "Release")

if (NOT EDHOC_CRYPTO_BACKEND)
    set(EDHOC_CRYPTO_BACKEND "TINYCRYPT" CACHE STRING "Backend for cryptography" FORCE)
endif ()

set_property(CACHE EDHOC_CRYPTO_BACKEND PROPERTY STRINGS "WOLFSSL" "HACL" "TINYCRYPT" "EMPTY_CRYPTO")

if (NOT EDHOC_CBOR_BACKEND)
    set(EDHOC_CBOR_BACKEND "NANOCBOR" CACHE STRING "Backend for CBOR encoding/decoding" FORCE)
endif ()

set_property(CACHE EDHOC_CBOR_BACKEND PROPERTY STRINGS "NANOCBOR" "EMPTY_CBOR")

if (NOT EDHOC_X509_BACKEND)
    set(EDHOC_X509_BACKEND "MBEDTLS_X509" CACHE STRING "Backend parsing X509 certificates and PKI keys" FORCE)
endif ()

set_property(CACHE EDHOC_X509_BACKEND PROPERTY STRINGS "MBEDTLS_X509" "EMPTY_X509")

include(sanitizers)

###############################################################################
# SOURCE FILES
###############################################################################

add_subdirectory(src)

###############################################################################
# ADD TESTS
###############################################################################

if (EDHOC_BUILD_TESTS)
    enable_testing()
    # include(CTest)
    add_subdirectory(test)
endif ()

###############################################################################
# ADD EXAMPLES
###############################################################################

if (EDHOC_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()

###############################################################################
# ADD FUZZ TARGETS
###############################################################################

if (EDHOC_BUILD_FUZZ_TARGETS)
    add_subdirectory(fuzzing)
endif ()

###############################################################################
# PRINT CONFIG
###############################################################################

message(STATUS "EDHOC_BUILD_TYPE:...............${CMAKE_BUILD_TYPE}")
message(STATUS "EDHOC_FATAL_WARNINGS:...........${EDHOC_FATAL_WARNINGS}")
message(STATUS "EDHOC_USE_ASAN:.................${EDHOC_USE_ASAN}")
message(STATUS "EDHOC_USE_LSAN:.................${EDHOC_USE_LSAN}")
message(STATUS "EDHOC_USE_USAN:.................${EDHOC_USE_USAN}")
message(STATUS "EDHOC_USE_MSAN:.................${EDHOC_USE_MSAN}")
message(STATUS "EDHOC_BUILD_TESTS:..............${EDHOC_BUILD_TESTS}")
message(STATUS "EDHOC_BUILD_EXAMPLES:...........${EDHOC_BUILD_EXAMPLES}")
message(STATUS "EDHOC_BUILD_FUZZ_TARGETS........${EDHOC_BUILD_FUZZ_TARGETS}")
message(STATUS "EDHOC_SHARED_LIBS:..............${BUILD_SHARED_LIBS}")
message(STATUS "EDHOC_CRYPTO_BACKEND:...........${EDHOC_CRYPTO_BACKEND}")
message(STATUS "EDHOC_X509_BACKEND:.............${EDHOC_X509_BACKEND}")
message(STATUS "EDHOC_CBOR_BACKEND:.............${EDHOC_CBOR_BACKEND}")

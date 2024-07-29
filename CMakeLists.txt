# The MIT License (MIT)
#
# Copyright (c) 2021-2024 Alexander Kurbatov
# Copyright (c) 2024      Gapry

cmake_minimum_required(VERSION 3.15)

project(Digamma)

include(FetchContent)

option(BUILD_FOR_LADDER "Create build for the AIArena ladder" OFF)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

if(MSVC)
  add_compile_options(/MP)
  set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>)
endif()

list(APPEND CMAKE_MODULE_PATH thirdparty)

include(cpp_sc2)

add_subdirectory(digamma)
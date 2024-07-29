# The MIT License (MIT)
#
# Copyright (c) 2021-2024 Alexander Kurbatov
# Copyright (c) 2024      Gapry

set(target "Digamma")

include_directories("${CMAKE_CURRENT_LIST_DIR}")

file(GLOB_RECURSE src_bot "*.cpp")

add_executable(${target} ${src_bot})

if(BUILD_FOR_LADDER)
  target_compile_definitions(${target} PRIVATE BUILD_FOR_LADDER)
endif()

if(MSVC)
  target_compile_options(${target} PRIVATE /W4 /EHsc)
endif()

target_link_libraries(${target} PRIVATE cpp_sc2)

if(MINGW)
  target_link_libraries(${target} PRIVATE ssp)
endif()

set(game_map "D:\\StarCraft II\\Maps\\Ladder2019Season3\\AcropolisLE.SC2Map")

set_target_properties(${target} PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS "${game_map}" )
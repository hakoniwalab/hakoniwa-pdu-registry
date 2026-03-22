cmake_minimum_required(VERSION 3.16)
project(hakoniwa_pdu_godot_smoke LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT DEFINED ENV{HAKO_GODOT_CPP_ROOT})
  message(FATAL_ERROR "HAKO_GODOT_CPP_ROOT is not set")
endif()

set(HAKO_GODOT_CPP_ROOT $ENV{HAKO_GODOT_CPP_ROOT})
set(GODOT_CPP_INCLUDE_DIR ${HAKO_GODOT_CPP_ROOT}/include)
set(GODOT_CPP_GEN_INCLUDE_DIR ${HAKO_GODOT_CPP_ROOT}/gen/include)
set(GODOT_CPP_GDEXT_DIR ${HAKO_GODOT_CPP_ROOT}/gdextension)
set(GODOT_CPP_LIB ${HAKO_GODOT_CPP_ROOT}/bin/libgodot-cpp.macos.template_debug.universal.a)

add_library(hako_pdu_godot_smoke SHARED
  src/register_types.cpp
  src/godot_pdu_smoke_bridge.cpp
)

target_include_directories(hako_pdu_godot_smoke PRIVATE
  ${GODOT_CPP_INCLUDE_DIR}
  ${GODOT_CPP_GEN_INCLUDE_DIR}
  ${GODOT_CPP_GDEXT_DIR}
  ${PROJECT_SOURCE_DIR}/../../pdu/godot_cpp
  ${PROJECT_SOURCE_DIR}/../../pdu
)

target_compile_definitions(hako_pdu_godot_smoke PRIVATE
  MACOS_ENABLED
  HOT_RELOAD_ENABLED
)

target_link_libraries(hako_pdu_godot_smoke PRIVATE
  ${GODOT_CPP_LIB}
)

target_link_options(hako_pdu_godot_smoke PRIVATE
  "LINKER:-force_load,${GODOT_CPP_LIB}"
)

set_target_properties(hako_pdu_godot_smoke PROPERTIES
  PREFIX ""
  OUTPUT_NAME "libhako_pdu_godot_smoke"
  LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)

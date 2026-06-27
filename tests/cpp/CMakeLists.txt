cmake_minimum_required(VERSION 3.16)
project(hakoniwa_pdu_cpp_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

find_package(GTest REQUIRED)
find_package(fastcdr CONFIG QUIET)

option(HAKO_PDU_FETCH_FASTCDR "Fetch Fast-CDR when it is not installed" ON)

if(NOT fastcdr_FOUND AND HAKO_PDU_FETCH_FASTCDR)
  include(FetchContent)
  FetchContent_Declare(
    fastcdr
    GIT_REPOSITORY https://github.com/eProsima/Fast-CDR.git
    GIT_TAG        v2.3.6
  )
  FetchContent_MakeAvailable(fastcdr)
  set(fastcdr_FOUND TRUE)
endif()

add_executable(hakoniwa_pdu_cpp_tests
  drone_visual_state_cpp_interop_test.cpp
  disturbance_cpp_interop_test.cpp
  disturbance_user_custom_cpp_interop_test.cpp
  game_controller_operation_cpp_interop_test.cpp
  joint_state_cpp_interop_test.cpp
  point_cloud2_cpp_interop_test.cpp
  simple_struct_varray_cpp_interop_test.cpp
)

add_executable(disturbance_cpp_dump
  disturbance_cpp_dump.cpp
)

add_executable(drone_visual_state_array_cpp_dump
  drone_visual_state_array_cpp_dump.cpp
)

add_executable(disturbance_user_custom_cpp_dump
  disturbance_user_custom_cpp_dump.cpp
)

add_executable(game_controller_operation_cpp_dump
  game_controller_operation_cpp_dump.cpp
)

add_executable(joint_state_cpp_dump
  joint_state_cpp_dump.cpp
)

add_executable(simple_struct_varray_cpp_dump
  simple_struct_varray_cpp_dump.cpp
)

add_executable(point_cloud2_cpp_dump
  point_cloud2_cpp_dump.cpp
)

add_executable(laser_scan_cpp_dump
  laser_scan_cpp_dump.cpp
)

add_executable(camera_info_cpp_dump
  camera_info_cpp_dump.cpp
)

add_executable(multi_array_layout_cpp_dump
  multi_array_layout_cpp_dump.cpp
)

add_executable(float64_multi_array_cpp_dump
  float64_multi_array_cpp_dump.cpp
)

target_include_directories(hakoniwa_pdu_cpp_tests PRIVATE
  ${PROJECT_SOURCE_DIR}/../../pdu/types
)

target_link_libraries(hakoniwa_pdu_cpp_tests PRIVATE
  GTest::gtest_main
)

target_include_directories(disturbance_cpp_dump PRIVATE
  ${PROJECT_SOURCE_DIR}/../../pdu/types
)

target_include_directories(drone_visual_state_array_cpp_dump PRIVATE
  ${PROJECT_SOURCE_DIR}/../../pdu/types
)

target_include_directories(disturbance_user_custom_cpp_dump PRIVATE
  ${PROJECT_SOURCE_DIR}/../../pdu/types
)

target_include_directories(joint_state_cpp_dump PRIVATE
  ${PROJECT_SOURCE_DIR}/../../pdu/types
)

target_include_directories(game_controller_operation_cpp_dump PRIVATE
  ${PROJECT_SOURCE_DIR}/../../pdu/types
)

target_include_directories(simple_struct_varray_cpp_dump PRIVATE
  ${PROJECT_SOURCE_DIR}/../../pdu/types
)

target_include_directories(point_cloud2_cpp_dump PRIVATE
  ${PROJECT_SOURCE_DIR}/../../pdu/types
)

target_include_directories(laser_scan_cpp_dump PRIVATE
  ${PROJECT_SOURCE_DIR}/../../pdu/types
)

target_include_directories(camera_info_cpp_dump PRIVATE
  ${PROJECT_SOURCE_DIR}/../../pdu/types
)

target_include_directories(multi_array_layout_cpp_dump PRIVATE
  ${PROJECT_SOURCE_DIR}/../../pdu/types
)

target_include_directories(float64_multi_array_cpp_dump PRIVATE
  ${PROJECT_SOURCE_DIR}/../../pdu/types
)

include(GoogleTest)
gtest_discover_tests(hakoniwa_pdu_cpp_tests)

if(fastcdr_FOUND)
  add_executable(hakoniwa_pdu_cpp_cdr_tests
    cdr_conversion_test.cpp
  )

  add_executable(hakoniwa_pdu_cpp_cdr_oracle_tool
    cdr_oracle_tool.cpp
  )

  target_include_directories(hakoniwa_pdu_cpp_cdr_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/../../pdu/types
  )

  target_include_directories(hakoniwa_pdu_cpp_cdr_oracle_tool PRIVATE
    ${PROJECT_SOURCE_DIR}/../../pdu/types
  )

  target_link_libraries(hakoniwa_pdu_cpp_cdr_tests PRIVATE
    GTest::gtest_main
    fastcdr
  )

  target_link_libraries(hakoniwa_pdu_cpp_cdr_oracle_tool PRIVATE
    fastcdr
  )

  gtest_discover_tests(hakoniwa_pdu_cpp_cdr_tests)
else()
  message(STATUS "fastcdr was not found; skipping Fast-CDR C++ tests")
endif()

cmake_minimum_required(VERSION 3.16)
project(hakoniwa_pdu_cpp_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

find_package(GTest REQUIRED)

add_executable(hakoniwa_pdu_cpp_tests
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

target_include_directories(hakoniwa_pdu_cpp_tests PRIVATE
  ${PROJECT_SOURCE_DIR}/../../pdu/types
)

target_link_libraries(hakoniwa_pdu_cpp_tests PRIVATE
  GTest::gtest_main
)

target_include_directories(disturbance_cpp_dump PRIVATE
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

include(GoogleTest)
gtest_discover_tests(hakoniwa_pdu_cpp_tests)

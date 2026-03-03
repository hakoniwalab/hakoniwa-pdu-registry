import unittest
from pathlib import Path

from generators.generate_hako_pdu_msgs.validate_generated_artifacts import (
    validate_disturbance_cpp_oracle_interop,
    validate_disturbance_js_python_interop,
    validate_disturbance_python_encode_size_case,
    validate_disturbance_user_custom_python_encode_size_case,
    validate_disturbance_user_custom_cpp_oracle_interop,
    validate_game_controller_operation_cpp_oracle_interop,
    validate_javascript_from_dict_roundtrip,
    validate_javascript_bool_array_roundtrip,
    validate_joint_state_cpp_oracle_interop,
    validate_joint_state_python_encode_size_case,
    validate_joint_state_string_varray_interop,
    validate_point_cloud2_cpp_oracle_interop,
    validate_point_cloud2_python_encode_size_case,
    validate_laser_scan_python_encode_size_case,
    validate_camera_info_python_encode_size_case,
    validate_multi_array_layout_python_encode_size_case,
    validate_float64_multi_array_python_encode_size_case,
    validate_python_disturbance_layout,
    validate_python_joint_state_layout,
    validate_python_bool_array_roundtrip,
    validate_simple_struct_varray_cpp_oracle_interop,
    validate_simple_struct_varray_python_encode_size_case,
    validate_size_registries,
)


class GeneratedArtifactsTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.repo_root = Path(__file__).resolve().parents[1]

    def assert_python_js_size_case(self, validator, *args):
        result = validator(self.repo_root, *args)
        self.assertEqual(result["python_decoded"], result["expected"])
        self.assertEqual(result["javascript_decoded"], result["expected"])

    def test_size_registries_match_offsets(self):
        mismatches = validate_size_registries(self.repo_root)
        self.assertEqual(mismatches, [])

    def test_python_bool_array_uses_4_byte_layout(self):
        result = validate_python_bool_array_roundtrip(self.repo_root)
        self.assertEqual(result["button_bytes"], result["expected_bytes"])
        self.assertEqual(result["restored_buttons"], result["expected_buttons"])

    def test_javascript_bool_array_uses_4_byte_layout(self):
        result = validate_javascript_bool_array_roundtrip(self.repo_root)
        self.assertEqual(result["button_bytes"], result["expected_bytes"])
        self.assertEqual(result["restored_buttons"], result["expected_buttons"])

    def test_javascript_from_dict_handles_primitive_and_struct_arrays(self):
        result = validate_javascript_from_dict_roundtrip(self.repo_root)
        self.assertEqual(result["game_axis"], result["expected_game_axis"])
        self.assertEqual(result["game_buttons"], result["expected_game_buttons"])
        self.assertEqual(result["game_json_axis"], result["expected_game_axis"])
        self.assertEqual(result["game_json_buttons"], result["expected_game_buttons"])
        self.assertEqual(result["fixed_str"], result["expected_fixed_str"])
        self.assertEqual(result["varray_str"], result["expected_varray_str"])
        self.assertEqual(result["fixed_array_data0"], result["expected_fixed_array_data0"])
        self.assertEqual(result["data_array0"], result["expected_data_array0"])
        self.assertEqual(result["fixed_str_json"], result["expected_fixed_str"])
        self.assertEqual(result["varray_str_json"], result["expected_varray_str"])
        self.assertEqual(result["fixed_array_data0_json"], result["expected_fixed_array_data0"])
        self.assertEqual(result["data_array0_json"], result["expected_data_array0"])

    def test_game_controller_operation_cpp_oracle_interop(self):
        result = validate_game_controller_operation_cpp_oracle_interop(self.repo_root)
        self.assertEqual(result["cpp_to_python"], result["expected"])
        self.assertEqual(result["cpp_to_javascript"], result["expected"])
        self.assertEqual(result["python_generated"], result["expected"])
        self.assertEqual(result["javascript_generated"], result["expected"])

    def test_disturbance_js_python_interop_preserves_nested_varray(self):
        result = validate_disturbance_js_python_interop(self.repo_root)
        self.assertEqual(result["py_to_js"], result["expected"])
        self.assertEqual(result["js_to_py"], result["expected"])
        self.assertTrue(result["binaries_equal"])

    def test_disturbance_python_encode_size_0_case(self):
        self.assert_python_js_size_case(validate_disturbance_python_encode_size_case, [])

    def test_disturbance_python_encode_size_1_case(self):
        self.assert_python_js_size_case(validate_disturbance_python_encode_size_case, [[3.75]])

    def test_disturbance_python_encode_size_2_case(self):
        self.assert_python_js_size_case(validate_disturbance_python_encode_size_case, [[1.25, 2.5], [3.75]])

    def test_disturbance_user_custom_cpp_oracle_interop(self):
        result = validate_disturbance_user_custom_cpp_oracle_interop(self.repo_root)
        self.assertEqual(result["cpp_to_python"], result["expected"])
        self.assertEqual(result["cpp_to_javascript"], result["expected"])
        self.assertEqual(result["python_generated"], result["expected"])
        self.assertEqual(result["javascript_generated"], result["expected"])

    def test_disturbance_user_custom_python_encode_size_0_case(self):
        self.assert_python_js_size_case(validate_disturbance_user_custom_python_encode_size_case, [])

    def test_disturbance_user_custom_python_encode_size_1_case(self):
        self.assert_python_js_size_case(validate_disturbance_user_custom_python_encode_size_case, [3.75])

    def test_disturbance_user_custom_python_encode_size_2_case(self):
        self.assert_python_js_size_case(validate_disturbance_user_custom_python_encode_size_case, [1.25, 2.5])

    def test_disturbance_cpp_oracle_interop(self):
        result = validate_disturbance_cpp_oracle_interop(self.repo_root)
        self.assertEqual(result["cpp_to_python"], result["expected"])
        self.assertEqual(result["cpp_to_javascript"], result["expected"])
        self.assertEqual(result["python_generated"], result["expected"])
        self.assertEqual(result["javascript_generated"], result["expected"])

    def test_joint_state_js_python_interop_preserves_string_varray(self):
        result = validate_joint_state_string_varray_interop(self.repo_root)
        self.assertEqual(result["py_to_js"], result["expected"])
        self.assertEqual(result["js_to_py"], result["expected"])
        self.assertTrue(result["binaries_equal"])

    def test_joint_state_cpp_oracle_interop(self):
        result = validate_joint_state_cpp_oracle_interop(self.repo_root)
        self.assertEqual(result["cpp_to_python"], result["expected"])
        self.assertEqual(result["cpp_to_javascript"], result["expected"])
        self.assertEqual(result["python_generated"], result["expected"])
        self.assertEqual(result["javascript_generated"], result["expected"])

    def test_point_cloud2_cpp_oracle_interop(self):
        result = validate_point_cloud2_cpp_oracle_interop(self.repo_root)
        self.assertEqual(result["cpp_to_python"], result["expected"])
        self.assertEqual(result["cpp_to_javascript"], result["expected"])
        self.assertEqual(result["python_generated"], result["expected"])
        self.assertEqual(result["javascript_generated"], result["expected"])

    def test_point_cloud2_python_encode_size_0_case(self):
        self.assert_python_js_size_case(validate_point_cloud2_python_encode_size_case, [], [])

    def test_point_cloud2_python_encode_size_1_case(self):
        self.assert_python_js_size_case(
            validate_point_cloud2_python_encode_size_case,
            [{"name": "x", "offset": 0, "datatype": 7, "count": 1}],
            [1],
        )

    def test_point_cloud2_python_encode_size_2_case(self):
        self.assert_python_js_size_case(
            validate_point_cloud2_python_encode_size_case,
            [
                {"name": "x", "offset": 0, "datatype": 7, "count": 1},
                {"name": "intensity", "offset": 4, "datatype": 7, "count": 1},
            ],
            [1, 2],
        )

    def test_laser_scan_python_encode_size_0_case(self):
        self.assert_python_js_size_case(validate_laser_scan_python_encode_size_case, [], [])

    def test_laser_scan_python_encode_size_1_case(self):
        self.assert_python_js_size_case(validate_laser_scan_python_encode_size_case, [1.5], [10.0])

    def test_laser_scan_python_encode_size_2_case(self):
        self.assert_python_js_size_case(validate_laser_scan_python_encode_size_case, [1.5, 2.5], [10.0, 20.0])

    def test_camera_info_python_encode_size_0_case(self):
        self.assert_python_js_size_case(validate_camera_info_python_encode_size_case, [])

    def test_camera_info_python_encode_size_1_case(self):
        self.assert_python_js_size_case(validate_camera_info_python_encode_size_case, [0.1])

    def test_camera_info_python_encode_size_2_case(self):
        self.assert_python_js_size_case(validate_camera_info_python_encode_size_case, [0.1, 0.2])

    def test_multi_array_layout_python_encode_size_0_case(self):
        self.assert_python_js_size_case(validate_multi_array_layout_python_encode_size_case, [])

    def test_multi_array_layout_python_encode_size_1_case(self):
        self.assert_python_js_size_case(
            validate_multi_array_layout_python_encode_size_case,
            [{"label": "x", "size": 1, "stride": 1}],
        )

    def test_multi_array_layout_python_encode_size_2_case(self):
        self.assert_python_js_size_case(
            validate_multi_array_layout_python_encode_size_case,
            [
                {"label": "x", "size": 2, "stride": 2},
                {"label": "y", "size": 3, "stride": 6},
            ],
        )

    def test_float64_multi_array_python_encode_size_0_case(self):
        self.assert_python_js_size_case(validate_float64_multi_array_python_encode_size_case, [], [])

    def test_float64_multi_array_python_encode_size_1_case(self):
        self.assert_python_js_size_case(
            validate_float64_multi_array_python_encode_size_case,
            [{"label": "x", "size": 1, "stride": 1}],
            [1.5],
        )

    def test_float64_multi_array_python_encode_size_2_case(self):
        self.assert_python_js_size_case(
            validate_float64_multi_array_python_encode_size_case,
            [
                {"label": "x", "size": 2, "stride": 2},
                {"label": "y", "size": 3, "stride": 6},
            ],
            [1.5, 2.5],
        )

    def test_simple_struct_varray_cpp_oracle_interop(self):
        result = validate_simple_struct_varray_cpp_oracle_interop(self.repo_root)
        self.assertEqual(result["cpp_to_python"], result["expected"])
        self.assertEqual(result["cpp_to_javascript"], result["expected"])
        self.assertEqual(result["python_generated"], result["expected"])
        self.assertEqual(result["javascript_generated"], result["expected"])

    def test_simple_struct_varray_python_encode_size_0_case(self):
        self.assert_python_js_size_case(validate_simple_struct_varray_python_encode_size_case, [], [])

    def test_simple_struct_varray_python_encode_size_1_case(self):
        self.assert_python_js_size_case(
            validate_simple_struct_varray_python_encode_size_case,
            ["gamma"],
            [{"data": [10], "fixed_array": [12, 13], "p_mem1": 14}],
        )

    def test_simple_struct_varray_python_encode_size_2_case(self):
        self.assert_python_js_size_case(
            validate_simple_struct_varray_python_encode_size_case,
            ["gamma", "delta"],
            [
                {"data": [10, 11], "fixed_array": [12, 13], "p_mem1": 14},
                {"data": [15], "fixed_array": [16, 17], "p_mem1": 18},
            ],
        )

    def test_joint_state_python_encode_size_0_case(self):
        self.assert_python_js_size_case(validate_joint_state_python_encode_size_case, [], [], [], [])

    def test_joint_state_python_encode_size_1_case(self):
        self.assert_python_js_size_case(
            validate_joint_state_python_encode_size_case,
            ["a"],
            [1.0],
            [3.0],
            [4.0],
        )

    def test_joint_state_python_encode_size_2_case(self):
        self.assert_python_js_size_case(
            validate_joint_state_python_encode_size_case,
            ["a", "b"],
            [1.0, 2.0],
            [3.0, 5.0],
            [4.0, 6.0],
        )

    def test_python_disturbance_layout_matches_spec(self):
        result = validate_python_disturbance_layout(self.repo_root)
        self.assertEqual(result["top_len"], result["expected_top_len"])
        self.assertEqual(result["top_off"], result["expected_top_off"])
        self.assertEqual(result["heap_bytes"], result["expected_heap_bytes"])

    def test_python_joint_state_layout_matches_spec(self):
        result = validate_python_joint_state_layout(self.repo_root)
        self.assertEqual(result["refs"], result["expected_refs"])
        self.assertEqual(result["heap_bytes"], result["expected_heap_bytes"])


if __name__ == "__main__":
    unittest.main()

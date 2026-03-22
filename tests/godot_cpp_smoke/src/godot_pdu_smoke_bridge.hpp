#pragma once

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>

namespace godot {

class HakoPduGodotSmokeBridge : public RefCounted {
    GDCLASS(HakoPduGodotSmokeBridge, RefCounted)

protected:
    static void _bind_methods();

public:
    Dictionary pdu_to_godot_game_controller_operation(const PackedByteArray &binary_data) const;
    PackedByteArray godot_to_pdu_game_controller_operation(const Dictionary &obj) const;

    Dictionary pdu_to_godot_disturbance_user_custom(const PackedByteArray &binary_data) const;
    PackedByteArray godot_to_pdu_disturbance_user_custom(const Dictionary &obj) const;

    Dictionary pdu_to_godot_disturbance(const PackedByteArray &binary_data) const;
    PackedByteArray godot_to_pdu_disturbance(const Dictionary &obj) const;

    Dictionary pdu_to_godot_joint_state(const PackedByteArray &binary_data) const;
    PackedByteArray godot_to_pdu_joint_state(const Dictionary &obj) const;

    Dictionary pdu_to_godot_simple_struct_varray(const PackedByteArray &binary_data) const;
    PackedByteArray godot_to_pdu_simple_struct_varray(const Dictionary &obj) const;

    Dictionary pdu_to_godot_point_cloud2(const PackedByteArray &binary_data) const;
    PackedByteArray godot_to_pdu_point_cloud2(const Dictionary &obj) const;

    Dictionary pdu_to_godot_laser_scan(const PackedByteArray &binary_data) const;
    PackedByteArray godot_to_pdu_laser_scan(const Dictionary &obj) const;

    Dictionary pdu_to_godot_camera_info(const PackedByteArray &binary_data) const;
    PackedByteArray godot_to_pdu_camera_info(const Dictionary &obj) const;

    Dictionary pdu_to_godot_multi_array_layout(const PackedByteArray &binary_data) const;
    PackedByteArray godot_to_pdu_multi_array_layout(const Dictionary &obj) const;

    Dictionary pdu_to_godot_float64_multi_array(const PackedByteArray &binary_data) const;
    PackedByteArray godot_to_pdu_float64_multi_array(const Dictionary &obj) const;
};

} // namespace godot

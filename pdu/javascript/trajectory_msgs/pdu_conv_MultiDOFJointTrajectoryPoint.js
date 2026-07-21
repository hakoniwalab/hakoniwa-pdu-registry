import * as PduUtils from '../pdu_utils.js';
import { MultiDOFJointTrajectoryPoint } from './pdu_jstype_MultiDOFJointTrajectoryPoint.js';
import { Transform } from '../geometry_msgs/pdu_jstype_Transform.js';
import { binary_read_recursive_Transform, binary_write_recursive_Transform } from '../geometry_msgs/pdu_conv_Transform.js';
import { Twist } from '../geometry_msgs/pdu_jstype_Twist.js';
import { binary_read_recursive_Twist, binary_write_recursive_Twist } from '../geometry_msgs/pdu_conv_Twist.js';
import { Duration } from '../builtin_interfaces/pdu_jstype_Duration.js';
import { binary_read_recursive_Duration, binary_write_recursive_Duration } from '../builtin_interfaces/pdu_conv_Duration.js';


/**
 * Deserializes a binary PDU into a MultiDOFJointTrajectoryPoint object.
 * @param {ArrayBuffer} binary_data
 * @returns { MultiDOFJointTrajectoryPoint }
 */
export function pduToJs_MultiDOFJointTrajectoryPoint(binary_data) {
    const js_obj = new MultiDOFJointTrajectoryPoint();
    const meta_parser = new PduUtils.PduMetaDataParser();
    const meta = meta_parser.load_pdu_meta(binary_data);
    if (meta === null) {
        throw new Error("Invalid PDU binary data: MetaData not found or corrupted");
    }
    binary_read_recursive_MultiDOFJointTrajectoryPoint(meta, binary_data, js_obj, meta.base_off);
    return js_obj;
}

export function binary_read_recursive_MultiDOFJointTrajectoryPoint(meta, binary_data, js_obj, base_off) {
    const view = new DataView(binary_data);
    const littleEndian = true;
    // member: transforms, type: geometry_msgs/Transform (struct)

    { // varray
        const array_size = view.getInt32(base_off + 0, littleEndian);
        const offset_from_heap = view.getInt32(base_off + 0 + 4, littleEndian);
        const one_elm_size = 56;
        const array_value = [];
        for (let i = 0; i < array_size; i++) {
            const tmp_obj = new Transform();
            const item_offset = meta.heap_off + offset_from_heap + (i * one_elm_size);
            binary_read_recursive_Transform(meta, binary_data, tmp_obj, item_offset);
            array_value.push(tmp_obj);
        }
        js_obj.transforms = array_value;
    }
    
    // member: velocities, type: geometry_msgs/Twist (struct)

    { // varray
        const array_size = view.getInt32(base_off + 8, littleEndian);
        const offset_from_heap = view.getInt32(base_off + 8 + 4, littleEndian);
        const one_elm_size = 48;
        const array_value = [];
        for (let i = 0; i < array_size; i++) {
            const tmp_obj = new Twist();
            const item_offset = meta.heap_off + offset_from_heap + (i * one_elm_size);
            binary_read_recursive_Twist(meta, binary_data, tmp_obj, item_offset);
            array_value.push(tmp_obj);
        }
        js_obj.velocities = array_value;
    }
    
    // member: accelerations, type: geometry_msgs/Twist (struct)

    { // varray
        const array_size = view.getInt32(base_off + 16, littleEndian);
        const offset_from_heap = view.getInt32(base_off + 16 + 4, littleEndian);
        const one_elm_size = 48;
        const array_value = [];
        for (let i = 0; i < array_size; i++) {
            const tmp_obj = new Twist();
            const item_offset = meta.heap_off + offset_from_heap + (i * one_elm_size);
            binary_read_recursive_Twist(meta, binary_data, tmp_obj, item_offset);
            array_value.push(tmp_obj);
        }
        js_obj.accelerations = array_value;
    }
    
    // member: time_from_start, type: builtin_interfaces/Duration (struct)

    {
        const tmp_obj = new Duration();
        binary_read_recursive_Duration(meta, binary_data, tmp_obj, base_off + 24);
        js_obj.time_from_start = tmp_obj;
    }
    
    return js_obj;
}

/**
 * Serializes a MultiDOFJointTrajectoryPoint object into a binary PDU.
 * @param { MultiDOFJointTrajectoryPoint } js_obj
 * @returns {ArrayBuffer}
 */
export function jsToPdu_MultiDOFJointTrajectoryPoint(js_obj) {
    const base_allocator = new PduUtils.DynamicAllocator();
    const bw_container = new PduUtils.BinaryWriterContainer(new PduUtils.PduMetaData());

    binary_write_recursive_MultiDOFJointTrajectoryPoint(0, bw_container, base_allocator, js_obj);

    const base_data_size = base_allocator.size();
    const heap_data_size = bw_container.heap_allocator.size();
    
    bw_container.meta.heap_off = PduUtils.PDU_META_DATA_SIZE + base_data_size;
    bw_container.meta.total_size = bw_container.meta.heap_off + heap_data_size;

    const final_buffer = new ArrayBuffer(bw_container.meta.total_size);
    const final_view = new Uint8Array(final_buffer);

    PduUtils.writeBinary(final_view, 0, bw_container.meta.to_bytes());
    PduUtils.writeBinary(final_view, bw_container.meta.base_off, base_allocator.toArray());
    PduUtils.writeBinary(final_view, bw_container.meta.heap_off, bw_container.heap_allocator.toArray());

    return final_buffer;
}

export function binary_write_recursive_MultiDOFJointTrajectoryPoint(parent_off, bw_container, allocator, js_obj) {
    const littleEndian = true;
    // member: transforms, type: geometry_msgs/Transform (struct)

    { // varray
        const offset_from_heap = bw_container.heap_allocator.size();
        const array_size = js_obj.transforms.length;
        const one_elm_size = 56;
        const array_base_offset = bw_container.heap_allocator.add(new ArrayBuffer(one_elm_size * array_size));
        for (let item_index = 0; item_index < array_size; item_index++) {
            const item_offset = array_base_offset + (item_index * one_elm_size);
            binary_write_recursive_Transform(item_offset, bw_container, bw_container.heap_allocator, js_obj.transforms[item_index]);
        }

        const ref_buffer = new ArrayBuffer(8);
        const ref_view = new DataView(ref_buffer);
        ref_view.setInt32(0, array_size, littleEndian); // array_size
        ref_view.setInt32(4, offset_from_heap, littleEndian);
        allocator.add(ref_buffer, parent_off + 0);
    }
    
    // member: velocities, type: geometry_msgs/Twist (struct)

    { // varray
        const offset_from_heap = bw_container.heap_allocator.size();
        const array_size = js_obj.velocities.length;
        const one_elm_size = 48;
        const array_base_offset = bw_container.heap_allocator.add(new ArrayBuffer(one_elm_size * array_size));
        for (let item_index = 0; item_index < array_size; item_index++) {
            const item_offset = array_base_offset + (item_index * one_elm_size);
            binary_write_recursive_Twist(item_offset, bw_container, bw_container.heap_allocator, js_obj.velocities[item_index]);
        }

        const ref_buffer = new ArrayBuffer(8);
        const ref_view = new DataView(ref_buffer);
        ref_view.setInt32(0, array_size, littleEndian); // array_size
        ref_view.setInt32(4, offset_from_heap, littleEndian);
        allocator.add(ref_buffer, parent_off + 8);
    }
    
    // member: accelerations, type: geometry_msgs/Twist (struct)

    { // varray
        const offset_from_heap = bw_container.heap_allocator.size();
        const array_size = js_obj.accelerations.length;
        const one_elm_size = 48;
        const array_base_offset = bw_container.heap_allocator.add(new ArrayBuffer(one_elm_size * array_size));
        for (let item_index = 0; item_index < array_size; item_index++) {
            const item_offset = array_base_offset + (item_index * one_elm_size);
            binary_write_recursive_Twist(item_offset, bw_container, bw_container.heap_allocator, js_obj.accelerations[item_index]);
        }

        const ref_buffer = new ArrayBuffer(8);
        const ref_view = new DataView(ref_buffer);
        ref_view.setInt32(0, array_size, littleEndian); // array_size
        ref_view.setInt32(4, offset_from_heap, littleEndian);
        allocator.add(ref_buffer, parent_off + 16);
    }
    
    // member: time_from_start, type: builtin_interfaces/Duration (struct)

    {
        binary_write_recursive_Duration(parent_off + 24, bw_container, allocator, js_obj.time_from_start);
    }
    
}

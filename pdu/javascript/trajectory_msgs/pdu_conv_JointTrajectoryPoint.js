import * as PduUtils from '../pdu_utils.js';
import { JointTrajectoryPoint } from './pdu_jstype_JointTrajectoryPoint.js';
import { Duration } from '../builtin_interfaces/pdu_jstype_Duration.js';
import { binary_read_recursive_Duration, binary_write_recursive_Duration } from '../builtin_interfaces/pdu_conv_Duration.js';


/**
 * Deserializes a binary PDU into a JointTrajectoryPoint object.
 * @param {ArrayBuffer} binary_data
 * @returns { JointTrajectoryPoint }
 */
export function pduToJs_JointTrajectoryPoint(binary_data) {
    const js_obj = new JointTrajectoryPoint();
    const meta_parser = new PduUtils.PduMetaDataParser();
    const meta = meta_parser.load_pdu_meta(binary_data);
    if (meta === null) {
        throw new Error("Invalid PDU binary data: MetaData not found or corrupted");
    }
    binary_read_recursive_JointTrajectoryPoint(meta, binary_data, js_obj, meta.base_off);
    return js_obj;
}

export function binary_read_recursive_JointTrajectoryPoint(meta, binary_data, js_obj, base_off) {
    const view = new DataView(binary_data);
    const littleEndian = true;
    // member: positions, type: float64 (primitive)

    { // varray
        const array_size = view.getInt32(base_off + 0, littleEndian);
        const offset_from_heap = view.getInt32(base_off + 0 + 4, littleEndian);
        const one_elm_size = 8;
        const array_bin = PduUtils.readBinary(binary_data, meta.heap_off + offset_from_heap, one_elm_size * array_size);
        
        if ("float64" === 'string') {
            js_obj.positions = PduUtils.binToArrayValues("string", array_bin, array_size, one_elm_size);
        } else {
            js_obj.positions = PduUtils.binToArrayValues("float64", array_bin, array_size);
        }
    }
    
    // member: velocities, type: float64 (primitive)

    { // varray
        const array_size = view.getInt32(base_off + 8, littleEndian);
        const offset_from_heap = view.getInt32(base_off + 8 + 4, littleEndian);
        const one_elm_size = 8;
        const array_bin = PduUtils.readBinary(binary_data, meta.heap_off + offset_from_heap, one_elm_size * array_size);
        
        if ("float64" === 'string') {
            js_obj.velocities = PduUtils.binToArrayValues("string", array_bin, array_size, one_elm_size);
        } else {
            js_obj.velocities = PduUtils.binToArrayValues("float64", array_bin, array_size);
        }
    }
    
    // member: accelerations, type: float64 (primitive)

    { // varray
        const array_size = view.getInt32(base_off + 16, littleEndian);
        const offset_from_heap = view.getInt32(base_off + 16 + 4, littleEndian);
        const one_elm_size = 8;
        const array_bin = PduUtils.readBinary(binary_data, meta.heap_off + offset_from_heap, one_elm_size * array_size);
        
        if ("float64" === 'string') {
            js_obj.accelerations = PduUtils.binToArrayValues("string", array_bin, array_size, one_elm_size);
        } else {
            js_obj.accelerations = PduUtils.binToArrayValues("float64", array_bin, array_size);
        }
    }
    
    // member: effort, type: float64 (primitive)

    { // varray
        const array_size = view.getInt32(base_off + 24, littleEndian);
        const offset_from_heap = view.getInt32(base_off + 24 + 4, littleEndian);
        const one_elm_size = 8;
        const array_bin = PduUtils.readBinary(binary_data, meta.heap_off + offset_from_heap, one_elm_size * array_size);
        
        if ("float64" === 'string') {
            js_obj.effort = PduUtils.binToArrayValues("string", array_bin, array_size, one_elm_size);
        } else {
            js_obj.effort = PduUtils.binToArrayValues("float64", array_bin, array_size);
        }
    }
    
    // member: time_from_start, type: builtin_interfaces/Duration (struct)

    {
        const tmp_obj = new Duration();
        binary_read_recursive_Duration(meta, binary_data, tmp_obj, base_off + 32);
        js_obj.time_from_start = tmp_obj;
    }
    
    return js_obj;
}

/**
 * Serializes a JointTrajectoryPoint object into a binary PDU.
 * @param { JointTrajectoryPoint } js_obj
 * @returns {ArrayBuffer}
 */
export function jsToPdu_JointTrajectoryPoint(js_obj) {
    const base_allocator = new PduUtils.DynamicAllocator();
    const bw_container = new PduUtils.BinaryWriterContainer(new PduUtils.PduMetaData());

    binary_write_recursive_JointTrajectoryPoint(0, bw_container, base_allocator, js_obj);

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

export function binary_write_recursive_JointTrajectoryPoint(parent_off, bw_container, allocator, js_obj) {
    const littleEndian = true;
    // member: positions, type: float64 (primitive)

    { // varray
        const offset_from_heap = bw_container.heap_allocator.size();
        let data_buffer;
        let array_size;
        if ("float64" === 'string') {
            data_buffer = PduUtils.typesToBin("string", js_obj.positions, 8);
            array_size = js_obj.positions.length;
        } else {
            data_buffer = PduUtils.typesToBin("float64", js_obj.positions);
            array_size = js_obj.positions.length;
        }
        bw_container.heap_allocator.add(data_buffer);

        const ref_buffer = new ArrayBuffer(8);
        const ref_view = new DataView(ref_buffer);
        ref_view.setInt32(0, array_size, littleEndian);
        ref_view.setInt32(4, offset_from_heap, littleEndian);
        allocator.add(ref_buffer, parent_off + 0);
    }
    
    // member: velocities, type: float64 (primitive)

    { // varray
        const offset_from_heap = bw_container.heap_allocator.size();
        let data_buffer;
        let array_size;
        if ("float64" === 'string') {
            data_buffer = PduUtils.typesToBin("string", js_obj.velocities, 8);
            array_size = js_obj.velocities.length;
        } else {
            data_buffer = PduUtils.typesToBin("float64", js_obj.velocities);
            array_size = js_obj.velocities.length;
        }
        bw_container.heap_allocator.add(data_buffer);

        const ref_buffer = new ArrayBuffer(8);
        const ref_view = new DataView(ref_buffer);
        ref_view.setInt32(0, array_size, littleEndian);
        ref_view.setInt32(4, offset_from_heap, littleEndian);
        allocator.add(ref_buffer, parent_off + 8);
    }
    
    // member: accelerations, type: float64 (primitive)

    { // varray
        const offset_from_heap = bw_container.heap_allocator.size();
        let data_buffer;
        let array_size;
        if ("float64" === 'string') {
            data_buffer = PduUtils.typesToBin("string", js_obj.accelerations, 8);
            array_size = js_obj.accelerations.length;
        } else {
            data_buffer = PduUtils.typesToBin("float64", js_obj.accelerations);
            array_size = js_obj.accelerations.length;
        }
        bw_container.heap_allocator.add(data_buffer);

        const ref_buffer = new ArrayBuffer(8);
        const ref_view = new DataView(ref_buffer);
        ref_view.setInt32(0, array_size, littleEndian);
        ref_view.setInt32(4, offset_from_heap, littleEndian);
        allocator.add(ref_buffer, parent_off + 16);
    }
    
    // member: effort, type: float64 (primitive)

    { // varray
        const offset_from_heap = bw_container.heap_allocator.size();
        let data_buffer;
        let array_size;
        if ("float64" === 'string') {
            data_buffer = PduUtils.typesToBin("string", js_obj.effort, 8);
            array_size = js_obj.effort.length;
        } else {
            data_buffer = PduUtils.typesToBin("float64", js_obj.effort);
            array_size = js_obj.effort.length;
        }
        bw_container.heap_allocator.add(data_buffer);

        const ref_buffer = new ArrayBuffer(8);
        const ref_view = new DataView(ref_buffer);
        ref_view.setInt32(0, array_size, littleEndian);
        ref_view.setInt32(4, offset_from_heap, littleEndian);
        allocator.add(ref_buffer, parent_off + 24);
    }
    
    // member: time_from_start, type: builtin_interfaces/Duration (struct)

    {
        binary_write_recursive_Duration(parent_off + 32, bw_container, allocator, js_obj.time_from_start);
    }
    
}

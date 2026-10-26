import * as PduUtils from '../pdu_utils.js';
import { AckermannStepResponse } from './pdu_jstype_AckermannStepResponse.js';
import { Transform } from '../geometry_msgs/pdu_jstype_Transform.js';
import { binary_read_recursive_Transform, binary_write_recursive_Transform } from '../geometry_msgs/pdu_conv_Transform.js';
import { Twist } from '../geometry_msgs/pdu_jstype_Twist.js';
import { binary_read_recursive_Twist, binary_write_recursive_Twist } from '../geometry_msgs/pdu_conv_Twist.js';


/**
 * Deserializes a binary PDU into a AckermannStepResponse object.
 * @param {ArrayBuffer} binary_data
 * @returns { AckermannStepResponse }
 */
export function pduToJs_AckermannStepResponse(binary_data) {
    const js_obj = new AckermannStepResponse();
    const meta_parser = new PduUtils.PduMetaDataParser();
    const meta = meta_parser.load_pdu_meta(binary_data);
    if (meta === null) {
        throw new Error("Invalid PDU binary data: MetaData not found or corrupted");
    }
    binary_read_recursive_AckermannStepResponse(meta, binary_data, js_obj, meta.base_off);
    return js_obj;
}

export function binary_read_recursive_AckermannStepResponse(meta, binary_data, js_obj, base_off) {
    const view = new DataView(binary_data);
    const littleEndian = true;
    // member: step, type: uint64 (primitive)

    
    {
        const bin = PduUtils.readBinary(binary_data, base_off + 0, 8);
        js_obj.step = PduUtils.binToValue("uint64", bin);
    }
    
    // member: result_code, type: uint32 (primitive)

    
    {
        const bin = PduUtils.readBinary(binary_data, base_off + 8, 4);
        js_obj.result_code = PduUtils.binToValue("uint32", bin);
    }
    
    // member: sim_time_usec, type: uint64 (primitive)

    
    {
        const bin = PduUtils.readBinary(binary_data, base_off + 16, 8);
        js_obj.sim_time_usec = PduUtils.binToValue("uint64", bin);
    }
    
    // member: pose, type: geometry_msgs/Transform (struct)

    {
        const tmp_obj = new Transform();
        binary_read_recursive_Transform(meta, binary_data, tmp_obj, base_off + 24);
        js_obj.pose = tmp_obj;
    }
    
    // member: twist, type: geometry_msgs/Twist (struct)

    {
        const tmp_obj = new Twist();
        binary_read_recursive_Twist(meta, binary_data, tmp_obj, base_off + 80);
        js_obj.twist = tmp_obj;
    }
    
    return js_obj;
}

/**
 * Serializes a AckermannStepResponse object into a binary PDU.
 * @param { AckermannStepResponse } js_obj
 * @returns {ArrayBuffer}
 */
export function jsToPdu_AckermannStepResponse(js_obj) {
    const base_allocator = new PduUtils.DynamicAllocator();
    const bw_container = new PduUtils.BinaryWriterContainer(new PduUtils.PduMetaData());

    binary_write_recursive_AckermannStepResponse(0, bw_container, base_allocator, js_obj);

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

export function binary_write_recursive_AckermannStepResponse(parent_off, bw_container, allocator, js_obj) {
    const littleEndian = true;
    // member: step, type: uint64 (primitive)

    
    {
        const bin = PduUtils.typeToBin("uint64", js_obj.step, 8);
        allocator.add(bin, parent_off + 0);
    }
    
    // member: result_code, type: uint32 (primitive)

    
    {
        const bin = PduUtils.typeToBin("uint32", js_obj.result_code, 4);
        allocator.add(bin, parent_off + 8);
    }
    
    // member: sim_time_usec, type: uint64 (primitive)

    
    {
        const bin = PduUtils.typeToBin("uint64", js_obj.sim_time_usec, 8);
        allocator.add(bin, parent_off + 16);
    }
    
    // member: pose, type: geometry_msgs/Transform (struct)

    {
        binary_write_recursive_Transform(parent_off + 24, bw_container, allocator, js_obj.pose);
    }
    
    // member: twist, type: geometry_msgs/Twist (struct)

    {
        binary_write_recursive_Twist(parent_off + 80, bw_container, allocator, js_obj.twist);
    }
    
}

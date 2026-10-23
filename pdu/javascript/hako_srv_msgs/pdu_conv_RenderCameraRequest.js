import * as PduUtils from '../pdu_utils.js';
import { RenderCameraRequest } from './pdu_jstype_RenderCameraRequest.js';
import { Pose } from '../geometry_msgs/pdu_jstype_Pose.js';
import { binary_read_recursive_Pose, binary_write_recursive_Pose } from '../geometry_msgs/pdu_conv_Pose.js';


/**
 * Deserializes a binary PDU into a RenderCameraRequest object.
 * @param {ArrayBuffer} binary_data
 * @returns { RenderCameraRequest }
 */
export function pduToJs_RenderCameraRequest(binary_data) {
    const js_obj = new RenderCameraRequest();
    const meta_parser = new PduUtils.PduMetaDataParser();
    const meta = meta_parser.load_pdu_meta(binary_data);
    if (meta === null) {
        throw new Error("Invalid PDU binary data: MetaData not found or corrupted");
    }
    binary_read_recursive_RenderCameraRequest(meta, binary_data, js_obj, meta.base_off);
    return js_obj;
}

export function binary_read_recursive_RenderCameraRequest(meta, binary_data, js_obj, base_off) {
    const view = new DataView(binary_data);
    const littleEndian = true;
    // member: camera_name, type: string (primitive)

    
    {
        const bin = PduUtils.readBinary(binary_data, base_off + 0, 128);
        js_obj.camera_name = PduUtils.binToValue("string", bin);
    }
    
    // member: sim_time_usec, type: uint64 (primitive)

    
    {
        const bin = PduUtils.readBinary(binary_data, base_off + 128, 8);
        js_obj.sim_time_usec = PduUtils.binToValue("uint64", bin);
    }
    
    // member: camera_pose, type: geometry_msgs/Pose (struct)

    {
        const tmp_obj = new Pose();
        binary_read_recursive_Pose(meta, binary_data, tmp_obj, base_off + 136);
        js_obj.camera_pose = tmp_obj;
    }
    
    return js_obj;
}

/**
 * Serializes a RenderCameraRequest object into a binary PDU.
 * @param { RenderCameraRequest } js_obj
 * @returns {ArrayBuffer}
 */
export function jsToPdu_RenderCameraRequest(js_obj) {
    const base_allocator = new PduUtils.DynamicAllocator();
    const bw_container = new PduUtils.BinaryWriterContainer(new PduUtils.PduMetaData());

    binary_write_recursive_RenderCameraRequest(0, bw_container, base_allocator, js_obj);

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

export function binary_write_recursive_RenderCameraRequest(parent_off, bw_container, allocator, js_obj) {
    const littleEndian = true;
    // member: camera_name, type: string (primitive)

    
    {
        const bin = PduUtils.typeToBin("string", js_obj.camera_name, 128);
        allocator.add(bin, parent_off + 0);
    }
    
    // member: sim_time_usec, type: uint64 (primitive)

    
    {
        const bin = PduUtils.typeToBin("uint64", js_obj.sim_time_usec, 8);
        allocator.add(bin, parent_off + 128);
    }
    
    // member: camera_pose, type: geometry_msgs/Pose (struct)

    {
        binary_write_recursive_Pose(parent_off + 136, bw_container, allocator, js_obj.camera_pose);
    }
    
}

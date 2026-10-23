import * as PduUtils from '../pdu_utils.js';
import { RenderCameraFrameResponse } from './pdu_jstype_RenderCameraFrameResponse.js';
import { Image } from '../sensor_msgs/pdu_jstype_Image.js';
import { binary_read_recursive_Image, binary_write_recursive_Image } from '../sensor_msgs/pdu_conv_Image.js';


/**
 * Deserializes a binary PDU into a RenderCameraFrameResponse object.
 * @param {ArrayBuffer} binary_data
 * @returns { RenderCameraFrameResponse }
 */
export function pduToJs_RenderCameraFrameResponse(binary_data) {
    const js_obj = new RenderCameraFrameResponse();
    const meta_parser = new PduUtils.PduMetaDataParser();
    const meta = meta_parser.load_pdu_meta(binary_data);
    if (meta === null) {
        throw new Error("Invalid PDU binary data: MetaData not found or corrupted");
    }
    binary_read_recursive_RenderCameraFrameResponse(meta, binary_data, js_obj, meta.base_off);
    return js_obj;
}

export function binary_read_recursive_RenderCameraFrameResponse(meta, binary_data, js_obj, base_off) {
    const view = new DataView(binary_data);
    const littleEndian = true;
    // member: result_code, type: uint32 (primitive)

    
    {
        const bin = PduUtils.readBinary(binary_data, base_off + 0, 4);
        js_obj.result_code = PduUtils.binToValue("uint32", bin);
    }
    
    // member: sim_time_usec, type: uint64 (primitive)

    
    {
        const bin = PduUtils.readBinary(binary_data, base_off + 8, 8);
        js_obj.sim_time_usec = PduUtils.binToValue("uint64", bin);
    }
    
    // member: rgb, type: sensor_msgs/Image (struct)

    {
        const tmp_obj = new Image();
        binary_read_recursive_Image(meta, binary_data, tmp_obj, base_off + 16);
        js_obj.rgb = tmp_obj;
    }
    
    // member: depth, type: sensor_msgs/Image (struct)

    {
        const tmp_obj = new Image();
        binary_read_recursive_Image(meta, binary_data, tmp_obj, base_off + 304);
        js_obj.depth = tmp_obj;
    }
    
    // member: segmentation, type: sensor_msgs/Image (struct)

    {
        const tmp_obj = new Image();
        binary_read_recursive_Image(meta, binary_data, tmp_obj, base_off + 592);
        js_obj.segmentation = tmp_obj;
    }
    
    return js_obj;
}

/**
 * Serializes a RenderCameraFrameResponse object into a binary PDU.
 * @param { RenderCameraFrameResponse } js_obj
 * @returns {ArrayBuffer}
 */
export function jsToPdu_RenderCameraFrameResponse(js_obj) {
    const base_allocator = new PduUtils.DynamicAllocator();
    const bw_container = new PduUtils.BinaryWriterContainer(new PduUtils.PduMetaData());

    binary_write_recursive_RenderCameraFrameResponse(0, bw_container, base_allocator, js_obj);

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

export function binary_write_recursive_RenderCameraFrameResponse(parent_off, bw_container, allocator, js_obj) {
    const littleEndian = true;
    // member: result_code, type: uint32 (primitive)

    
    {
        const bin = PduUtils.typeToBin("uint32", js_obj.result_code, 4);
        allocator.add(bin, parent_off + 0);
    }
    
    // member: sim_time_usec, type: uint64 (primitive)

    
    {
        const bin = PduUtils.typeToBin("uint64", js_obj.sim_time_usec, 8);
        allocator.add(bin, parent_off + 8);
    }
    
    // member: rgb, type: sensor_msgs/Image (struct)

    {
        binary_write_recursive_Image(parent_off + 16, bw_container, allocator, js_obj.rgb);
    }
    
    // member: depth, type: sensor_msgs/Image (struct)

    {
        binary_write_recursive_Image(parent_off + 304, bw_container, allocator, js_obj.depth);
    }
    
    // member: segmentation, type: sensor_msgs/Image (struct)

    {
        binary_write_recursive_Image(parent_off + 592, bw_container, allocator, js_obj.segmentation);
    }
    
}

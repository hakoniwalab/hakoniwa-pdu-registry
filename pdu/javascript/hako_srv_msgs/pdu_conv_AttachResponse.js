import * as PduUtils from '../pdu_utils.js';
import { AttachResponse } from './pdu_jstype_AttachResponse.js';
import { LogicalTime } from './pdu_jstype_LogicalTime.js';
import { binary_read_recursive_LogicalTime, binary_write_recursive_LogicalTime } from './pdu_conv_LogicalTime.js';


/**
 * Deserializes a binary PDU into a AttachResponse object.
 * @param {ArrayBuffer} binary_data
 * @returns { AttachResponse }
 */
export function pduToJs_AttachResponse(binary_data) {
    const js_obj = new AttachResponse();
    const meta_parser = new PduUtils.PduMetaDataParser();
    const meta = meta_parser.load_pdu_meta(binary_data);
    if (meta === null) {
        throw new Error("Invalid PDU binary data: MetaData not found or corrupted");
    }
    binary_read_recursive_AttachResponse(meta, binary_data, js_obj, meta.base_off);
    return js_obj;
}

export function binary_read_recursive_AttachResponse(meta, binary_data, js_obj, base_off) {
    const view = new DataView(binary_data);
    const littleEndian = true;
    // member: result_code, type: uint32 (primitive)

    
    {
        const bin = PduUtils.readBinary(binary_data, base_off + 0, 4);
        js_obj.result_code = PduUtils.binToValue("uint32", bin);
    }
    
    // member: session_id, type: uint64 (primitive)

    
    {
        const bin = PduUtils.readBinary(binary_data, base_off + 8, 8);
        js_obj.session_id = PduUtils.binToValue("uint64", bin);
    }
    
    // member: world_time, type: LogicalTime (struct)

    {
        const tmp_obj = new LogicalTime();
        binary_read_recursive_LogicalTime(meta, binary_data, tmp_obj, base_off + 16);
        js_obj.world_time = tmp_obj;
    }
    
    // member: delta_asset_tick, type: uint64 (primitive)

    
    {
        const bin = PduUtils.readBinary(binary_data, base_off + 32, 8);
        js_obj.delta_asset_tick = PduUtils.binToValue("uint64", bin);
    }
    
    return js_obj;
}

/**
 * Serializes a AttachResponse object into a binary PDU.
 * @param { AttachResponse } js_obj
 * @returns {ArrayBuffer}
 */
export function jsToPdu_AttachResponse(js_obj) {
    const base_allocator = new PduUtils.DynamicAllocator();
    const bw_container = new PduUtils.BinaryWriterContainer(new PduUtils.PduMetaData());

    binary_write_recursive_AttachResponse(0, bw_container, base_allocator, js_obj);

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

export function binary_write_recursive_AttachResponse(parent_off, bw_container, allocator, js_obj) {
    const littleEndian = true;
    // member: result_code, type: uint32 (primitive)

    
    {
        const bin = PduUtils.typeToBin("uint32", js_obj.result_code, 4);
        allocator.add(bin, parent_off + 0);
    }
    
    // member: session_id, type: uint64 (primitive)

    
    {
        const bin = PduUtils.typeToBin("uint64", js_obj.session_id, 8);
        allocator.add(bin, parent_off + 8);
    }
    
    // member: world_time, type: LogicalTime (struct)

    {
        binary_write_recursive_LogicalTime(parent_off + 16, bw_container, allocator, js_obj.world_time);
    }
    
    // member: delta_asset_tick, type: uint64 (primitive)

    
    {
        const bin = PduUtils.typeToBin("uint64", js_obj.delta_asset_tick, 8);
        allocator.add(bin, parent_off + 32);
    }
    
}

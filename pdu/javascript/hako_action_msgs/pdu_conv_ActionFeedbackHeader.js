import * as PduUtils from '../pdu_utils.js';
import { ActionFeedbackHeader } from './pdu_jstype_ActionFeedbackHeader.js';


/**
 * Deserializes a binary PDU into a ActionFeedbackHeader object.
 * @param {ArrayBuffer} binary_data
 * @returns { ActionFeedbackHeader }
 */
export function pduToJs_ActionFeedbackHeader(binary_data) {
    const js_obj = new ActionFeedbackHeader();
    const meta_parser = new PduUtils.PduMetaDataParser();
    const meta = meta_parser.load_pdu_meta(binary_data);
    if (meta === null) {
        throw new Error("Invalid PDU binary data: MetaData not found or corrupted");
    }
    binary_read_recursive_ActionFeedbackHeader(meta, binary_data, js_obj, meta.base_off);
    return js_obj;
}

export function binary_read_recursive_ActionFeedbackHeader(meta, binary_data, js_obj, base_off) {
    const view = new DataView(binary_data);
    const littleEndian = true;
    // member: version, type: uint8 (primitive)

    
    {
        const bin = PduUtils.readBinary(binary_data, base_off + 0, 1);
        js_obj.version = PduUtils.binToValue("uint8", bin);
    }
    
    // member: reserved, type: uint8 (primitive)

    
    {
        const array_bin = PduUtils.readBinary(binary_data, base_off + 1, 3);
        js_obj.reserved = PduUtils.binToArrayValues("uint8", array_bin, 3, 3 / 3);
    }
    
    // member: goal_id, type: uint8 (primitive)

    
    {
        const array_bin = PduUtils.readBinary(binary_data, base_off + 4, 16);
        js_obj.goal_id = PduUtils.binToArrayValues("uint8", array_bin, 16, 16 / 16);
    }
    
    // member: sequence_no, type: uint32 (primitive)

    
    {
        const bin = PduUtils.readBinary(binary_data, base_off + 20, 4);
        js_obj.sequence_no = PduUtils.binToValue("uint32", bin);
    }
    
    return js_obj;
}

/**
 * Serializes a ActionFeedbackHeader object into a binary PDU.
 * @param { ActionFeedbackHeader } js_obj
 * @returns {ArrayBuffer}
 */
export function jsToPdu_ActionFeedbackHeader(js_obj) {
    const base_allocator = new PduUtils.DynamicAllocator();
    const bw_container = new PduUtils.BinaryWriterContainer(new PduUtils.PduMetaData());

    binary_write_recursive_ActionFeedbackHeader(0, bw_container, base_allocator, js_obj);

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

export function binary_write_recursive_ActionFeedbackHeader(parent_off, bw_container, allocator, js_obj) {
    const littleEndian = true;
    // member: version, type: uint8 (primitive)

    
    {
        const bin = PduUtils.typeToBin("uint8", js_obj.version, 1);
        allocator.add(bin, parent_off + 0);
    }
    
    // member: reserved, type: uint8 (primitive)

    
    {
        const buffer = PduUtils.typesToBin("uint8", js_obj.reserved, 3 / 3);
        allocator.add(buffer, parent_off + 1);
    }
    
    // member: goal_id, type: uint8 (primitive)

    
    {
        const buffer = PduUtils.typesToBin("uint8", js_obj.goal_id, 16 / 16);
        allocator.add(buffer, parent_off + 4);
    }
    
    // member: sequence_no, type: uint32 (primitive)

    
    {
        const bin = PduUtils.typeToBin("uint32", js_obj.sequence_no, 4);
        allocator.add(bin, parent_off + 20);
    }
    
}

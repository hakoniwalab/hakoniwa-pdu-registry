import * as PduUtils from '../pdu_utils.js';
import { FibonacciActionRequest } from './pdu_jstype_FibonacciActionRequest.js';
import { ActionRequestHeader } from '../hako_action_msgs/pdu_jstype_ActionRequestHeader.js';
import { binary_read_recursive_ActionRequestHeader, binary_write_recursive_ActionRequestHeader } from '../hako_action_msgs/pdu_conv_ActionRequestHeader.js';
import { FibonacciGoal } from './pdu_jstype_FibonacciGoal.js';
import { binary_read_recursive_FibonacciGoal, binary_write_recursive_FibonacciGoal } from './pdu_conv_FibonacciGoal.js';


/**
 * Deserializes a binary PDU into a FibonacciActionRequest object.
 * @param {ArrayBuffer} binary_data
 * @returns { FibonacciActionRequest }
 */
export function pduToJs_FibonacciActionRequest(binary_data) {
    const js_obj = new FibonacciActionRequest();
    const meta_parser = new PduUtils.PduMetaDataParser();
    const meta = meta_parser.load_pdu_meta(binary_data);
    if (meta === null) {
        throw new Error("Invalid PDU binary data: MetaData not found or corrupted");
    }
    binary_read_recursive_FibonacciActionRequest(meta, binary_data, js_obj, meta.base_off);
    return js_obj;
}

export function binary_read_recursive_FibonacciActionRequest(meta, binary_data, js_obj, base_off) {
    const view = new DataView(binary_data);
    const littleEndian = true;
    // member: header, type: hako_action_msgs/ActionRequestHeader (struct)

    {
        const tmp_obj = new ActionRequestHeader();
        binary_read_recursive_ActionRequestHeader(meta, binary_data, tmp_obj, base_off + 0);
        js_obj.header = tmp_obj;
    }
    
    // member: body, type: FibonacciGoal (struct)

    {
        const tmp_obj = new FibonacciGoal();
        binary_read_recursive_FibonacciGoal(meta, binary_data, tmp_obj, base_off + 20);
        js_obj.body = tmp_obj;
    }
    
    return js_obj;
}

/**
 * Serializes a FibonacciActionRequest object into a binary PDU.
 * @param { FibonacciActionRequest } js_obj
 * @returns {ArrayBuffer}
 */
export function jsToPdu_FibonacciActionRequest(js_obj) {
    const base_allocator = new PduUtils.DynamicAllocator();
    const bw_container = new PduUtils.BinaryWriterContainer(new PduUtils.PduMetaData());

    binary_write_recursive_FibonacciActionRequest(0, bw_container, base_allocator, js_obj);

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

export function binary_write_recursive_FibonacciActionRequest(parent_off, bw_container, allocator, js_obj) {
    const littleEndian = true;
    // member: header, type: hako_action_msgs/ActionRequestHeader (struct)

    {
        binary_write_recursive_ActionRequestHeader(parent_off + 0, bw_container, allocator, js_obj.header);
    }
    
    // member: body, type: FibonacciGoal (struct)

    {
        binary_write_recursive_FibonacciGoal(parent_off + 20, bw_container, allocator, js_obj.body);
    }
    
}

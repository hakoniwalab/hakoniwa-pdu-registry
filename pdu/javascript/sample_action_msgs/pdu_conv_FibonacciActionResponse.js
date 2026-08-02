import * as PduUtils from '../pdu_utils.js';
import { FibonacciActionResponse } from './pdu_jstype_FibonacciActionResponse.js';
import { ActionResponseHeader } from '../hako_action_msgs/pdu_jstype_ActionResponseHeader.js';
import { binary_read_recursive_ActionResponseHeader, binary_write_recursive_ActionResponseHeader } from '../hako_action_msgs/pdu_conv_ActionResponseHeader.js';
import { FibonacciResult } from './pdu_jstype_FibonacciResult.js';
import { binary_read_recursive_FibonacciResult, binary_write_recursive_FibonacciResult } from './pdu_conv_FibonacciResult.js';


/**
 * Deserializes a binary PDU into a FibonacciActionResponse object.
 * @param {ArrayBuffer} binary_data
 * @returns { FibonacciActionResponse }
 */
export function pduToJs_FibonacciActionResponse(binary_data) {
    const js_obj = new FibonacciActionResponse();
    const meta_parser = new PduUtils.PduMetaDataParser();
    const meta = meta_parser.load_pdu_meta(binary_data);
    if (meta === null) {
        throw new Error("Invalid PDU binary data: MetaData not found or corrupted");
    }
    binary_read_recursive_FibonacciActionResponse(meta, binary_data, js_obj, meta.base_off);
    return js_obj;
}

export function binary_read_recursive_FibonacciActionResponse(meta, binary_data, js_obj, base_off) {
    const view = new DataView(binary_data);
    const littleEndian = true;
    // member: header, type: hako_action_msgs/ActionResponseHeader (struct)

    {
        const tmp_obj = new ActionResponseHeader();
        binary_read_recursive_ActionResponseHeader(meta, binary_data, tmp_obj, base_off + 0);
        js_obj.header = tmp_obj;
    }
    
    // member: body, type: FibonacciResult (struct)

    {
        const tmp_obj = new FibonacciResult();
        binary_read_recursive_FibonacciResult(meta, binary_data, tmp_obj, base_off + 20);
        js_obj.body = tmp_obj;
    }
    
    return js_obj;
}

/**
 * Serializes a FibonacciActionResponse object into a binary PDU.
 * @param { FibonacciActionResponse } js_obj
 * @returns {ArrayBuffer}
 */
export function jsToPdu_FibonacciActionResponse(js_obj) {
    const base_allocator = new PduUtils.DynamicAllocator();
    const bw_container = new PduUtils.BinaryWriterContainer(new PduUtils.PduMetaData());

    binary_write_recursive_FibonacciActionResponse(0, bw_container, base_allocator, js_obj);

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

export function binary_write_recursive_FibonacciActionResponse(parent_off, bw_container, allocator, js_obj) {
    const littleEndian = true;
    // member: header, type: hako_action_msgs/ActionResponseHeader (struct)

    {
        binary_write_recursive_ActionResponseHeader(parent_off + 0, bw_container, allocator, js_obj.header);
    }
    
    // member: body, type: FibonacciResult (struct)

    {
        binary_write_recursive_FibonacciResult(parent_off + 20, bw_container, allocator, js_obj.body);
    }
    
}

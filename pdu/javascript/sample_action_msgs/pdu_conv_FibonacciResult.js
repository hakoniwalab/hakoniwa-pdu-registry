import * as PduUtils from '../pdu_utils.js';
import { FibonacciResult } from './pdu_jstype_FibonacciResult.js';


/**
 * Deserializes a binary PDU into a FibonacciResult object.
 * @param {ArrayBuffer} binary_data
 * @returns { FibonacciResult }
 */
export function pduToJs_FibonacciResult(binary_data) {
    const js_obj = new FibonacciResult();
    const meta_parser = new PduUtils.PduMetaDataParser();
    const meta = meta_parser.load_pdu_meta(binary_data);
    if (meta === null) {
        throw new Error("Invalid PDU binary data: MetaData not found or corrupted");
    }
    binary_read_recursive_FibonacciResult(meta, binary_data, js_obj, meta.base_off);
    return js_obj;
}

export function binary_read_recursive_FibonacciResult(meta, binary_data, js_obj, base_off) {
    const view = new DataView(binary_data);
    const littleEndian = true;
    // member: sequence, type: int32 (primitive)

    { // varray
        const array_size = view.getInt32(base_off + 0, littleEndian);
        const offset_from_heap = view.getInt32(base_off + 0 + 4, littleEndian);
        const one_elm_size = 4;
        const array_bin = PduUtils.readBinary(binary_data, meta.heap_off + offset_from_heap, one_elm_size * array_size);
        
        if ("int32" === 'string') {
            js_obj.sequence = PduUtils.binToArrayValues("string", array_bin, array_size, one_elm_size);
        } else {
            js_obj.sequence = PduUtils.binToArrayValues("int32", array_bin, array_size);
        }
    }
    
    return js_obj;
}

/**
 * Serializes a FibonacciResult object into a binary PDU.
 * @param { FibonacciResult } js_obj
 * @returns {ArrayBuffer}
 */
export function jsToPdu_FibonacciResult(js_obj) {
    const base_allocator = new PduUtils.DynamicAllocator();
    const bw_container = new PduUtils.BinaryWriterContainer(new PduUtils.PduMetaData());

    binary_write_recursive_FibonacciResult(0, bw_container, base_allocator, js_obj);

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

export function binary_write_recursive_FibonacciResult(parent_off, bw_container, allocator, js_obj) {
    const littleEndian = true;
    // member: sequence, type: int32 (primitive)

    { // varray
        const offset_from_heap = bw_container.heap_allocator.size();
        let data_buffer;
        let array_size;
        if ("int32" === 'string') {
            data_buffer = PduUtils.typesToBin("string", js_obj.sequence, 4);
            array_size = js_obj.sequence.length;
        } else {
            data_buffer = PduUtils.typesToBin("int32", js_obj.sequence);
            array_size = js_obj.sequence.length;
        }
        bw_container.heap_allocator.add(data_buffer);

        const ref_buffer = new ArrayBuffer(8);
        const ref_view = new DataView(ref_buffer);
        ref_view.setInt32(0, array_size, littleEndian);
        ref_view.setInt32(4, offset_from_heap, littleEndian);
        allocator.add(ref_buffer, parent_off + 0);
    }
    
}

import * as PduUtils from '../pdu_utils.js';
import { ContactEvent } from './pdu_jstype_ContactEvent.js';
import { Time } from '../builtin_interfaces/pdu_jstype_Time.js';
import { binary_read_recursive_Time, binary_write_recursive_Time } from '../builtin_interfaces/pdu_conv_Time.js';
import { Point } from '../geometry_msgs/pdu_jstype_Point.js';
import { binary_read_recursive_Point, binary_write_recursive_Point } from '../geometry_msgs/pdu_conv_Point.js';


/**
 * Deserializes a binary PDU into a ContactEvent object.
 * @param {ArrayBuffer} binary_data
 * @returns { ContactEvent }
 */
export function pduToJs_ContactEvent(binary_data) {
    const js_obj = new ContactEvent();
    const meta_parser = new PduUtils.PduMetaDataParser();
    const meta = meta_parser.load_pdu_meta(binary_data);
    if (meta === null) {
        throw new Error("Invalid PDU binary data: MetaData not found or corrupted");
    }
    binary_read_recursive_ContactEvent(meta, binary_data, js_obj, meta.base_off);
    return js_obj;
}

export function binary_read_recursive_ContactEvent(meta, binary_data, js_obj, base_off) {
    const view = new DataView(binary_data);
    const littleEndian = true;
    // member: stamp, type: builtin_interfaces/Time (struct)

    {
        const tmp_obj = new Time();
        binary_read_recursive_Time(meta, binary_data, tmp_obj, base_off + 0);
        js_obj.stamp = tmp_obj;
    }
    
    // member: self_name, type: string (primitive)

    
    {
        const bin = PduUtils.readBinary(binary_data, base_off + 8, 128);
        js_obj.self_name = PduUtils.binToValue("string", bin);
    }
    
    // member: other_name, type: string (primitive)

    
    {
        const bin = PduUtils.readBinary(binary_data, base_off + 136, 128);
        js_obj.other_name = PduUtils.binToValue("string", bin);
    }
    
    // member: other_kind, type: string (primitive)

    
    {
        const bin = PduUtils.readBinary(binary_data, base_off + 264, 128);
        js_obj.other_kind = PduUtils.binToValue("string", bin);
    }
    
    // member: position, type: geometry_msgs/Point (struct)

    {
        const tmp_obj = new Point();
        binary_read_recursive_Point(meta, binary_data, tmp_obj, base_off + 392);
        js_obj.position = tmp_obj;
    }
    
    // member: relative_speed, type: float64 (primitive)

    
    {
        const bin = PduUtils.readBinary(binary_data, base_off + 416, 8);
        js_obj.relative_speed = PduUtils.binToValue("float64", bin);
    }
    
    // member: started, type: bool (primitive)

    
    {
        const bin = PduUtils.readBinary(binary_data, base_off + 424, 4);
        js_obj.started = PduUtils.binToValue("bool", bin);
    }
    
    return js_obj;
}

/**
 * Serializes a ContactEvent object into a binary PDU.
 * @param { ContactEvent } js_obj
 * @returns {ArrayBuffer}
 */
export function jsToPdu_ContactEvent(js_obj) {
    const base_allocator = new PduUtils.DynamicAllocator();
    const bw_container = new PduUtils.BinaryWriterContainer(new PduUtils.PduMetaData());

    binary_write_recursive_ContactEvent(0, bw_container, base_allocator, js_obj);

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

export function binary_write_recursive_ContactEvent(parent_off, bw_container, allocator, js_obj) {
    const littleEndian = true;
    // member: stamp, type: builtin_interfaces/Time (struct)

    {
        binary_write_recursive_Time(parent_off + 0, bw_container, allocator, js_obj.stamp);
    }
    
    // member: self_name, type: string (primitive)

    
    {
        const bin = PduUtils.typeToBin("string", js_obj.self_name, 128);
        allocator.add(bin, parent_off + 8);
    }
    
    // member: other_name, type: string (primitive)

    
    {
        const bin = PduUtils.typeToBin("string", js_obj.other_name, 128);
        allocator.add(bin, parent_off + 136);
    }
    
    // member: other_kind, type: string (primitive)

    
    {
        const bin = PduUtils.typeToBin("string", js_obj.other_kind, 128);
        allocator.add(bin, parent_off + 264);
    }
    
    // member: position, type: geometry_msgs/Point (struct)

    {
        binary_write_recursive_Point(parent_off + 392, bw_container, allocator, js_obj.position);
    }
    
    // member: relative_speed, type: float64 (primitive)

    
    {
        const bin = PduUtils.typeToBin("float64", js_obj.relative_speed, 8);
        allocator.add(bin, parent_off + 416);
    }
    
    // member: started, type: bool (primitive)

    
    {
        const bin = PduUtils.typeToBin("bool", js_obj.started, 4);
        allocator.add(bin, parent_off + 424);
    }
    
}

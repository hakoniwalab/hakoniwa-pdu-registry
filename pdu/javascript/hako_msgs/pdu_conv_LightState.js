import * as PduUtils from '../pdu_utils.js';
import { LightState } from './pdu_jstype_LightState.js';


/**
 * Deserializes a binary PDU into a LightState object.
 * @param {ArrayBuffer} binary_data
 * @returns { LightState }
 */
export function pduToJs_LightState(binary_data) {
    const js_obj = new LightState();
    const meta_parser = new PduUtils.PduMetaDataParser();
    const meta = meta_parser.load_pdu_meta(binary_data);
    if (meta === null) {
        throw new Error("Invalid PDU binary data: MetaData not found or corrupted");
    }
    binary_read_recursive_LightState(meta, binary_data, js_obj, meta.base_off);
    return js_obj;
}

export function binary_read_recursive_LightState(meta, binary_data, js_obj, base_off) {
    const view = new DataView(binary_data);
    const littleEndian = true;
    // member: source, type: string (primitive)

    
    {
        const bin = PduUtils.readBinary(binary_data, base_off + 0, 128);
        js_obj.source = PduUtils.binToValue("string", bin);
    }
    
    // member: mode, type: uint8 (primitive)

    
    {
        const bin = PduUtils.readBinary(binary_data, base_off + 128, 1);
        js_obj.mode = PduUtils.binToValue("uint8", bin);
    }
    
    // member: luminous_intensity_scale, type: float64 (primitive)

    
    {
        const bin = PduUtils.readBinary(binary_data, base_off + 136, 8);
        js_obj.luminous_intensity_scale = PduUtils.binToValue("float64", bin);
    }
    
    // member: is_lit, type: bool (primitive)

    
    {
        const bin = PduUtils.readBinary(binary_data, base_off + 144, 4);
        js_obj.is_lit = PduUtils.binToValue("bool", bin);
    }
    
    return js_obj;
}

/**
 * Serializes a LightState object into a binary PDU.
 * @param { LightState } js_obj
 * @returns {ArrayBuffer}
 */
export function jsToPdu_LightState(js_obj) {
    const base_allocator = new PduUtils.DynamicAllocator();
    const bw_container = new PduUtils.BinaryWriterContainer(new PduUtils.PduMetaData());

    binary_write_recursive_LightState(0, bw_container, base_allocator, js_obj);

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

export function binary_write_recursive_LightState(parent_off, bw_container, allocator, js_obj) {
    const littleEndian = true;
    // member: source, type: string (primitive)

    
    {
        const bin = PduUtils.typeToBin("string", js_obj.source, 128);
        allocator.add(bin, parent_off + 0);
    }
    
    // member: mode, type: uint8 (primitive)

    
    {
        const bin = PduUtils.typeToBin("uint8", js_obj.mode, 1);
        allocator.add(bin, parent_off + 128);
    }
    
    // member: luminous_intensity_scale, type: float64 (primitive)

    
    {
        const bin = PduUtils.typeToBin("float64", js_obj.luminous_intensity_scale, 8);
        allocator.add(bin, parent_off + 136);
    }
    
    // member: is_lit, type: bool (primitive)

    
    {
        const bin = PduUtils.typeToBin("bool", js_obj.is_lit, 4);
        allocator.add(bin, parent_off + 144);
    }
    
}

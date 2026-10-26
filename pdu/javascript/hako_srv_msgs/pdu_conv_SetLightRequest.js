import * as PduUtils from '../pdu_utils.js';
import { SetLightRequest } from './pdu_jstype_SetLightRequest.js';


/**
 * Deserializes a binary PDU into a SetLightRequest object.
 * @param {ArrayBuffer} binary_data
 * @returns { SetLightRequest }
 */
export function pduToJs_SetLightRequest(binary_data) {
    const js_obj = new SetLightRequest();
    const meta_parser = new PduUtils.PduMetaDataParser();
    const meta = meta_parser.load_pdu_meta(binary_data);
    if (meta === null) {
        throw new Error("Invalid PDU binary data: MetaData not found or corrupted");
    }
    binary_read_recursive_SetLightRequest(meta, binary_data, js_obj, meta.base_off);
    return js_obj;
}

export function binary_read_recursive_SetLightRequest(meta, binary_data, js_obj, base_off) {
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
    
    // member: flashing_on_s, type: float64 (primitive)

    
    {
        const bin = PduUtils.readBinary(binary_data, base_off + 144, 8);
        js_obj.flashing_on_s = PduUtils.binToValue("float64", bin);
    }
    
    // member: flashing_off_s, type: float64 (primitive)

    
    {
        const bin = PduUtils.readBinary(binary_data, base_off + 152, 8);
        js_obj.flashing_off_s = PduUtils.binToValue("float64", bin);
    }
    
    // member: transition_s, type: float64 (primitive)

    
    {
        const bin = PduUtils.readBinary(binary_data, base_off + 160, 8);
        js_obj.transition_s = PduUtils.binToValue("float64", bin);
    }
    
    return js_obj;
}

/**
 * Serializes a SetLightRequest object into a binary PDU.
 * @param { SetLightRequest } js_obj
 * @returns {ArrayBuffer}
 */
export function jsToPdu_SetLightRequest(js_obj) {
    const base_allocator = new PduUtils.DynamicAllocator();
    const bw_container = new PduUtils.BinaryWriterContainer(new PduUtils.PduMetaData());

    binary_write_recursive_SetLightRequest(0, bw_container, base_allocator, js_obj);

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

export function binary_write_recursive_SetLightRequest(parent_off, bw_container, allocator, js_obj) {
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
    
    // member: flashing_on_s, type: float64 (primitive)

    
    {
        const bin = PduUtils.typeToBin("float64", js_obj.flashing_on_s, 8);
        allocator.add(bin, parent_off + 144);
    }
    
    // member: flashing_off_s, type: float64 (primitive)

    
    {
        const bin = PduUtils.typeToBin("float64", js_obj.flashing_off_s, 8);
        allocator.add(bin, parent_off + 152);
    }
    
    // member: transition_s, type: float64 (primitive)

    
    {
        const bin = PduUtils.typeToBin("float64", js_obj.transition_s, 8);
        allocator.add(bin, parent_off + 160);
    }
    
}

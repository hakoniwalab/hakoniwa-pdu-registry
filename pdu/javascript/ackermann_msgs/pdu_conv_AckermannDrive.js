import * as PduUtils from '../pdu_utils.js';
import { AckermannDrive } from './pdu_jstype_AckermannDrive.js';


/**
 * Deserializes a binary PDU into a AckermannDrive object.
 * @param {ArrayBuffer} binary_data
 * @returns { AckermannDrive }
 */
export function pduToJs_AckermannDrive(binary_data) {
    const js_obj = new AckermannDrive();
    const meta_parser = new PduUtils.PduMetaDataParser();
    const meta = meta_parser.load_pdu_meta(binary_data);
    if (meta === null) {
        throw new Error("Invalid PDU binary data: MetaData not found or corrupted");
    }
    binary_read_recursive_AckermannDrive(meta, binary_data, js_obj, meta.base_off);
    return js_obj;
}

export function binary_read_recursive_AckermannDrive(meta, binary_data, js_obj, base_off) {
    const view = new DataView(binary_data);
    const littleEndian = true;
    // member: steering_angle, type: float32 (primitive)


    {
        const bin = PduUtils.readBinary(binary_data, base_off + 0, 4);
        js_obj.steering_angle = PduUtils.binToValue("float32", bin);
    }

    // member: steering_angle_velocity, type: float32 (primitive)


    {
        const bin = PduUtils.readBinary(binary_data, base_off + 4, 4);
        js_obj.steering_angle_velocity = PduUtils.binToValue("float32", bin);
    }

    // member: speed, type: float32 (primitive)


    {
        const bin = PduUtils.readBinary(binary_data, base_off + 8, 4);
        js_obj.speed = PduUtils.binToValue("float32", bin);
    }

    // member: acceleration, type: float32 (primitive)


    {
        const bin = PduUtils.readBinary(binary_data, base_off + 12, 4);
        js_obj.acceleration = PduUtils.binToValue("float32", bin);
    }

    // member: jerk, type: float32 (primitive)


    {
        const bin = PduUtils.readBinary(binary_data, base_off + 16, 4);
        js_obj.jerk = PduUtils.binToValue("float32", bin);
    }

    return js_obj;
}

/**
 * Serializes a AckermannDrive object into a binary PDU.
 * @param { AckermannDrive } js_obj
 * @returns {ArrayBuffer}
 */
export function jsToPdu_AckermannDrive(js_obj) {
    const base_allocator = new PduUtils.DynamicAllocator();
    const bw_container = new PduUtils.BinaryWriterContainer(new PduUtils.PduMetaData());

    binary_write_recursive_AckermannDrive(0, bw_container, base_allocator, js_obj);

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

export function binary_write_recursive_AckermannDrive(parent_off, bw_container, allocator, js_obj) {
    const littleEndian = true;
    // member: steering_angle, type: float32 (primitive)


    {
        const bin = PduUtils.typeToBin("float32", js_obj.steering_angle, 4);
        allocator.add(bin, parent_off + 0);
    }

    // member: steering_angle_velocity, type: float32 (primitive)


    {
        const bin = PduUtils.typeToBin("float32", js_obj.steering_angle_velocity, 4);
        allocator.add(bin, parent_off + 4);
    }

    // member: speed, type: float32 (primitive)


    {
        const bin = PduUtils.typeToBin("float32", js_obj.speed, 4);
        allocator.add(bin, parent_off + 8);
    }

    // member: acceleration, type: float32 (primitive)


    {
        const bin = PduUtils.typeToBin("float32", js_obj.acceleration, 4);
        allocator.add(bin, parent_off + 12);
    }

    // member: jerk, type: float32 (primitive)


    {
        const bin = PduUtils.typeToBin("float32", js_obj.jerk, 4);
        allocator.add(bin, parent_off + 16);
    }

}

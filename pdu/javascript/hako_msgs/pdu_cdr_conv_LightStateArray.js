import { LightStateArray } from './pdu_jstype_LightStateArray.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { LightState } from '../hako_msgs/pdu_jstype_LightState.js';
import { PduLightStateConverter } from '../hako_msgs/pdu_cdr_conv_LightState.js';


export class PduLightStateArrayConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { LightStateArray } src
     */
    static to_cdr_body(writer, src) {
        writer.write_uint64(src.stamp_usec);
        writer.write_string(src.carrier);
        writer.write_sequence_length(src.lights);
        for (const elem of src.lights) {
            PduLightStateConverter.to_cdr_body(writer, elem);
        }
    }

    /**
     * @param {PduCdrReader} reader
     * @param { LightStateArray } dst
     * @returns { LightStateArray }
     */
    static cdr_body_to_js(reader, dst) {
        dst.stamp_usec = reader.read_uint64();
        dst.carrier = reader.read_string();
        dst.lights = [];
        for (let i = 0, len = reader.read_uint32(); i < len; i++) {
            dst.lights.push(PduLightStateConverter.cdr_body_to_js(reader, new LightState()));
        }
        return dst;
    }

    /**
     * @param { LightStateArray } src
     * @returns {ArrayBuffer}
     */
    static to_cdr(src) {
        const writer = new PduCdrWriter();
        writer.write_encapsulation();
        this.to_cdr_body(writer, src);
        return writer.get_buf();
    }

    /**
     * @param {ArrayBuffer|ArrayBufferView} cdrPayload
     * @returns { LightStateArray }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new LightStateArray());
    }
}

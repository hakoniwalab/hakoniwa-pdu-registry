import { LightState } from './pdu_jstype_LightState.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';


export class PduLightStateConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { LightState } src
     */
    static to_cdr_body(writer, src) {
        writer.write_string(src.source);
        writer.write_uint8(src.mode);
        writer.write_float64(src.luminous_intensity_scale);
        writer.write_bool(src.is_lit);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { LightState } dst
     * @returns { LightState }
     */
    static cdr_body_to_js(reader, dst) {
        dst.source = reader.read_string();
        dst.mode = reader.read_uint8();
        dst.luminous_intensity_scale = reader.read_float64();
        dst.is_lit = reader.read_bool();
        return dst;
    }

    /**
     * @param { LightState } src
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
     * @returns { LightState }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new LightState());
    }
}

import { SetLightRequest } from './pdu_jstype_SetLightRequest.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';


export class PduSetLightRequestConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { SetLightRequest } src
     */
    static to_cdr_body(writer, src) {
        writer.write_string(src.source);
        writer.write_uint8(src.mode);
        writer.write_float64(src.luminous_intensity_scale);
        writer.write_float64(src.flashing_on_s);
        writer.write_float64(src.flashing_off_s);
        writer.write_float64(src.transition_s);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { SetLightRequest } dst
     * @returns { SetLightRequest }
     */
    static cdr_body_to_js(reader, dst) {
        dst.source = reader.read_string();
        dst.mode = reader.read_uint8();
        dst.luminous_intensity_scale = reader.read_float64();
        dst.flashing_on_s = reader.read_float64();
        dst.flashing_off_s = reader.read_float64();
        dst.transition_s = reader.read_float64();
        return dst;
    }

    /**
     * @param { SetLightRequest } src
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
     * @returns { SetLightRequest }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new SetLightRequest());
    }
}

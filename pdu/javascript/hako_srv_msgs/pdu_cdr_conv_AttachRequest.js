import { AttachRequest } from './pdu_jstype_AttachRequest.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';


export class PduAttachRequestConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { AttachRequest } src
     */
    static to_cdr_body(writer, src) {
        writer.write_string(src.asset_name);
        writer.write_uint64(src.delta_asset_tick);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { AttachRequest } dst
     * @returns { AttachRequest }
     */
    static cdr_body_to_js(reader, dst) {
        dst.asset_name = reader.read_string();
        dst.delta_asset_tick = reader.read_uint64();
        return dst;
    }

    /**
     * @param { AttachRequest } src
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
     * @returns { AttachRequest }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new AttachRequest());
    }
}

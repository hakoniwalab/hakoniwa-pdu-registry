import { DetachRequest } from './pdu_jstype_DetachRequest.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';


export class PduDetachRequestConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { DetachRequest } src
     */
    static to_cdr_body(writer, src) {
        writer.write_uint64(src.session_id);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { DetachRequest } dst
     * @returns { DetachRequest }
     */
    static cdr_body_to_js(reader, dst) {
        dst.session_id = reader.read_uint64();
        return dst;
    }

    /**
     * @param { DetachRequest } src
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
     * @returns { DetachRequest }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new DetachRequest());
    }
}

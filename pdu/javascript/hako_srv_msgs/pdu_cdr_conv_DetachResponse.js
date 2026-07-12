import { DetachResponse } from './pdu_jstype_DetachResponse.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';


export class PduDetachResponseConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { DetachResponse } src
     */
    static to_cdr_body(writer, src) {
        writer.write_uint32(src.result_code);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { DetachResponse } dst
     * @returns { DetachResponse }
     */
    static cdr_body_to_js(reader, dst) {
        dst.result_code = reader.read_uint32();
        return dst;
    }

    /**
     * @param { DetachResponse } src
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
     * @returns { DetachResponse }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new DetachResponse());
    }
}

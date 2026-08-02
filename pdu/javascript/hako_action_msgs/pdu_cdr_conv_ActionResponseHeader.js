import { ActionResponseHeader } from './pdu_jstype_ActionResponseHeader.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';


export class PduActionResponseHeaderConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { ActionResponseHeader } src
     */
    static to_cdr_body(writer, src) {
        writer.write_uint8(src.version);
        writer.write_uint8(src.response_kind);
        writer.write_uint8(src.status);
        writer.write_uint8(src.reserved);
        {
            const values = src.goal_id;
            for (let i = 0; i < 16; i++) {
                writer.write_uint8(i < values.length ? values[i] : 0);
            }
        }
    }

    /**
     * @param {PduCdrReader} reader
     * @param { ActionResponseHeader } dst
     * @returns { ActionResponseHeader }
     */
    static cdr_body_to_js(reader, dst) {
        dst.version = reader.read_uint8();
        dst.response_kind = reader.read_uint8();
        dst.status = reader.read_uint8();
        dst.reserved = reader.read_uint8();
        dst.goal_id = Array.from({ length: 16 }, () => reader.read_uint8());
        return dst;
    }

    /**
     * @param { ActionResponseHeader } src
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
     * @returns { ActionResponseHeader }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new ActionResponseHeader());
    }
}

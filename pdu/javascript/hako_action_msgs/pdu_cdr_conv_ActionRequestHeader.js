import { ActionRequestHeader } from './pdu_jstype_ActionRequestHeader.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';


export class PduActionRequestHeaderConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { ActionRequestHeader } src
     */
    static to_cdr_body(writer, src) {
        writer.write_uint8(src.version);
        writer.write_uint8(src.request_kind);
        {
            const values = src.reserved;
            for (let i = 0; i < 2; i++) {
                writer.write_uint8(i < values.length ? values[i] : 0);
            }
        }
        {
            const values = src.goal_id;
            for (let i = 0; i < 16; i++) {
                writer.write_uint8(i < values.length ? values[i] : 0);
            }
        }
    }

    /**
     * @param {PduCdrReader} reader
     * @param { ActionRequestHeader } dst
     * @returns { ActionRequestHeader }
     */
    static cdr_body_to_js(reader, dst) {
        dst.version = reader.read_uint8();
        dst.request_kind = reader.read_uint8();
        dst.reserved = Array.from({ length: 2 }, () => reader.read_uint8());
        dst.goal_id = Array.from({ length: 16 }, () => reader.read_uint8());
        return dst;
    }

    /**
     * @param { ActionRequestHeader } src
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
     * @returns { ActionRequestHeader }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new ActionRequestHeader());
    }
}

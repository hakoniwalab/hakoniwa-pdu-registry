import { ActionFeedbackHeader } from './pdu_jstype_ActionFeedbackHeader.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';


export class PduActionFeedbackHeaderConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { ActionFeedbackHeader } src
     */
    static to_cdr_body(writer, src) {
        writer.write_uint8(src.version);
        {
            const values = src.reserved;
            for (let i = 0; i < 3; i++) {
                writer.write_uint8(i < values.length ? values[i] : 0);
            }
        }
        {
            const values = src.goal_id;
            for (let i = 0; i < 16; i++) {
                writer.write_uint8(i < values.length ? values[i] : 0);
            }
        }
        writer.write_uint32(src.sequence_no);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { ActionFeedbackHeader } dst
     * @returns { ActionFeedbackHeader }
     */
    static cdr_body_to_js(reader, dst) {
        dst.version = reader.read_uint8();
        dst.reserved = Array.from({ length: 3 }, () => reader.read_uint8());
        dst.goal_id = Array.from({ length: 16 }, () => reader.read_uint8());
        dst.sequence_no = reader.read_uint32();
        return dst;
    }

    /**
     * @param { ActionFeedbackHeader } src
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
     * @returns { ActionFeedbackHeader }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new ActionFeedbackHeader());
    }
}

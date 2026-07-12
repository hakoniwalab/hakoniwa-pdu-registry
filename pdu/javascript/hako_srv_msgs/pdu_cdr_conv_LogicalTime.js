import { LogicalTime } from './pdu_jstype_LogicalTime.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';


export class PduLogicalTimeConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { LogicalTime } src
     */
    static to_cdr_body(writer, src) {
        writer.write_uint64(src.generation);
        writer.write_uint64(src.offset_tick);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { LogicalTime } dst
     * @returns { LogicalTime }
     */
    static cdr_body_to_js(reader, dst) {
        dst.generation = reader.read_uint64();
        dst.offset_tick = reader.read_uint64();
        return dst;
    }

    /**
     * @param { LogicalTime } src
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
     * @returns { LogicalTime }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new LogicalTime());
    }
}

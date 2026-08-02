import { FibonacciFeedback } from './pdu_jstype_FibonacciFeedback.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';


export class PduFibonacciFeedbackConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { FibonacciFeedback } src
     */
    static to_cdr_body(writer, src) {
        writer.write_sequence_length(src.partial_sequence);
        for (const elem of src.partial_sequence) {
            writer.write_int32(elem);
        }
    }

    /**
     * @param {PduCdrReader} reader
     * @param { FibonacciFeedback } dst
     * @returns { FibonacciFeedback }
     */
    static cdr_body_to_js(reader, dst) {
        dst.partial_sequence = Array.from({ length: reader.read_uint32() }, () => reader.read_int32());
        return dst;
    }

    /**
     * @param { FibonacciFeedback } src
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
     * @returns { FibonacciFeedback }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new FibonacciFeedback());
    }
}

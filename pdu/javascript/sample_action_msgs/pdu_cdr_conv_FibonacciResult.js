import { FibonacciResult } from './pdu_jstype_FibonacciResult.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';


export class PduFibonacciResultConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { FibonacciResult } src
     */
    static to_cdr_body(writer, src) {
        writer.write_sequence_length(src.sequence);
        for (const elem of src.sequence) {
            writer.write_int32(elem);
        }
    }

    /**
     * @param {PduCdrReader} reader
     * @param { FibonacciResult } dst
     * @returns { FibonacciResult }
     */
    static cdr_body_to_js(reader, dst) {
        dst.sequence = Array.from({ length: reader.read_uint32() }, () => reader.read_int32());
        return dst;
    }

    /**
     * @param { FibonacciResult } src
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
     * @returns { FibonacciResult }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new FibonacciResult());
    }
}

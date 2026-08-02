import { FibonacciGoal } from './pdu_jstype_FibonacciGoal.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';


export class PduFibonacciGoalConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { FibonacciGoal } src
     */
    static to_cdr_body(writer, src) {
        writer.write_int32(src.order);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { FibonacciGoal } dst
     * @returns { FibonacciGoal }
     */
    static cdr_body_to_js(reader, dst) {
        dst.order = reader.read_int32();
        return dst;
    }

    /**
     * @param { FibonacciGoal } src
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
     * @returns { FibonacciGoal }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new FibonacciGoal());
    }
}

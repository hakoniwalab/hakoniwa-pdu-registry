import { FibonacciActionRequest } from './pdu_jstype_FibonacciActionRequest.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { ActionRequestHeader } from '../hako_action_msgs/pdu_jstype_ActionRequestHeader.js';
import { PduActionRequestHeaderConverter } from '../hako_action_msgs/pdu_cdr_conv_ActionRequestHeader.js';
import { FibonacciGoal } from '../sample_action_msgs/pdu_jstype_FibonacciGoal.js';
import { PduFibonacciGoalConverter } from '../sample_action_msgs/pdu_cdr_conv_FibonacciGoal.js';


export class PduFibonacciActionRequestConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { FibonacciActionRequest } src
     */
    static to_cdr_body(writer, src) {
        PduActionRequestHeaderConverter.to_cdr_body(writer, src.header);
        PduFibonacciGoalConverter.to_cdr_body(writer, src.body);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { FibonacciActionRequest } dst
     * @returns { FibonacciActionRequest }
     */
    static cdr_body_to_js(reader, dst) {
        PduActionRequestHeaderConverter.cdr_body_to_js(reader, dst.header);
        PduFibonacciGoalConverter.cdr_body_to_js(reader, dst.body);
        return dst;
    }

    /**
     * @param { FibonacciActionRequest } src
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
     * @returns { FibonacciActionRequest }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new FibonacciActionRequest());
    }
}

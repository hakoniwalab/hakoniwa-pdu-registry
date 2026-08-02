import { FibonacciActionFeedback } from './pdu_jstype_FibonacciActionFeedback.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { ActionFeedbackHeader } from '../hako_action_msgs/pdu_jstype_ActionFeedbackHeader.js';
import { PduActionFeedbackHeaderConverter } from '../hako_action_msgs/pdu_cdr_conv_ActionFeedbackHeader.js';
import { FibonacciFeedback } from '../sample_action_msgs/pdu_jstype_FibonacciFeedback.js';
import { PduFibonacciFeedbackConverter } from '../sample_action_msgs/pdu_cdr_conv_FibonacciFeedback.js';


export class PduFibonacciActionFeedbackConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { FibonacciActionFeedback } src
     */
    static to_cdr_body(writer, src) {
        PduActionFeedbackHeaderConverter.to_cdr_body(writer, src.header);
        PduFibonacciFeedbackConverter.to_cdr_body(writer, src.body);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { FibonacciActionFeedback } dst
     * @returns { FibonacciActionFeedback }
     */
    static cdr_body_to_js(reader, dst) {
        PduActionFeedbackHeaderConverter.cdr_body_to_js(reader, dst.header);
        PduFibonacciFeedbackConverter.cdr_body_to_js(reader, dst.body);
        return dst;
    }

    /**
     * @param { FibonacciActionFeedback } src
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
     * @returns { FibonacciActionFeedback }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new FibonacciActionFeedback());
    }
}

import { FibonacciActionResponse } from './pdu_jstype_FibonacciActionResponse.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { ActionResponseHeader } from '../hako_action_msgs/pdu_jstype_ActionResponseHeader.js';
import { PduActionResponseHeaderConverter } from '../hako_action_msgs/pdu_cdr_conv_ActionResponseHeader.js';
import { FibonacciResult } from '../sample_action_msgs/pdu_jstype_FibonacciResult.js';
import { PduFibonacciResultConverter } from '../sample_action_msgs/pdu_cdr_conv_FibonacciResult.js';


export class PduFibonacciActionResponseConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { FibonacciActionResponse } src
     */
    static to_cdr_body(writer, src) {
        PduActionResponseHeaderConverter.to_cdr_body(writer, src.header);
        PduFibonacciResultConverter.to_cdr_body(writer, src.body);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { FibonacciActionResponse } dst
     * @returns { FibonacciActionResponse }
     */
    static cdr_body_to_js(reader, dst) {
        PduActionResponseHeaderConverter.cdr_body_to_js(reader, dst.header);
        PduFibonacciResultConverter.cdr_body_to_js(reader, dst.body);
        return dst;
    }

    /**
     * @param { FibonacciActionResponse } src
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
     * @returns { FibonacciActionResponse }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new FibonacciActionResponse());
    }
}

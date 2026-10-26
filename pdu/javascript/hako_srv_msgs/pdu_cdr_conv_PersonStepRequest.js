import { PersonStepRequest } from './pdu_jstype_PersonStepRequest.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { Twist } from '../geometry_msgs/pdu_jstype_Twist.js';
import { PduTwistConverter } from '../geometry_msgs/pdu_cdr_conv_Twist.js';
import { Vector3 } from '../geometry_msgs/pdu_jstype_Vector3.js';
import { PduVector3Converter } from '../geometry_msgs/pdu_cdr_conv_Vector3.js';


export class PduPersonStepRequestConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { PersonStepRequest } src
     */
    static to_cdr_body(writer, src) {
        writer.write_uint64(src.step);
        PduTwistConverter.to_cdr_body(writer, src.cmd_vel);
        writer.write_string(src.animation);
        writer.write_string(src.ride);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { PersonStepRequest } dst
     * @returns { PersonStepRequest }
     */
    static cdr_body_to_js(reader, dst) {
        dst.step = reader.read_uint64();
        PduTwistConverter.cdr_body_to_js(reader, dst.cmd_vel);
        dst.animation = reader.read_string();
        dst.ride = reader.read_string();
        return dst;
    }

    /**
     * @param { PersonStepRequest } src
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
     * @returns { PersonStepRequest }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new PersonStepRequest());
    }
}

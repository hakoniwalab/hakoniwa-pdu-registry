import { AckermannStepResponse } from './pdu_jstype_AckermannStepResponse.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { Quaternion } from '../geometry_msgs/pdu_jstype_Quaternion.js';
import { PduQuaternionConverter } from '../geometry_msgs/pdu_cdr_conv_Quaternion.js';
import { Transform } from '../geometry_msgs/pdu_jstype_Transform.js';
import { PduTransformConverter } from '../geometry_msgs/pdu_cdr_conv_Transform.js';
import { Twist } from '../geometry_msgs/pdu_jstype_Twist.js';
import { PduTwistConverter } from '../geometry_msgs/pdu_cdr_conv_Twist.js';
import { Vector3 } from '../geometry_msgs/pdu_jstype_Vector3.js';
import { PduVector3Converter } from '../geometry_msgs/pdu_cdr_conv_Vector3.js';


export class PduAckermannStepResponseConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { AckermannStepResponse } src
     */
    static to_cdr_body(writer, src) {
        writer.write_uint64(src.step);
        writer.write_uint32(src.result_code);
        writer.write_uint64(src.sim_time_usec);
        PduTransformConverter.to_cdr_body(writer, src.pose);
        PduTwistConverter.to_cdr_body(writer, src.twist);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { AckermannStepResponse } dst
     * @returns { AckermannStepResponse }
     */
    static cdr_body_to_js(reader, dst) {
        dst.step = reader.read_uint64();
        dst.result_code = reader.read_uint32();
        dst.sim_time_usec = reader.read_uint64();
        PduTransformConverter.cdr_body_to_js(reader, dst.pose);
        PduTwistConverter.cdr_body_to_js(reader, dst.twist);
        return dst;
    }

    /**
     * @param { AckermannStepResponse } src
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
     * @returns { AckermannStepResponse }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new AckermannStepResponse());
    }
}

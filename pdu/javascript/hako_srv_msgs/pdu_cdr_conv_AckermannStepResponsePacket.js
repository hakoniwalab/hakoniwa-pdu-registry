import { AckermannStepResponsePacket } from './pdu_jstype_AckermannStepResponsePacket.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { AckermannStepResponse } from '../hako_srv_msgs/pdu_jstype_AckermannStepResponse.js';
import { PduAckermannStepResponseConverter } from '../hako_srv_msgs/pdu_cdr_conv_AckermannStepResponse.js';
import { Quaternion } from '../geometry_msgs/pdu_jstype_Quaternion.js';
import { PduQuaternionConverter } from '../geometry_msgs/pdu_cdr_conv_Quaternion.js';
import { ServiceResponseHeader } from '../hako_srv_msgs/pdu_jstype_ServiceResponseHeader.js';
import { PduServiceResponseHeaderConverter } from '../hako_srv_msgs/pdu_cdr_conv_ServiceResponseHeader.js';
import { Transform } from '../geometry_msgs/pdu_jstype_Transform.js';
import { PduTransformConverter } from '../geometry_msgs/pdu_cdr_conv_Transform.js';
import { Twist } from '../geometry_msgs/pdu_jstype_Twist.js';
import { PduTwistConverter } from '../geometry_msgs/pdu_cdr_conv_Twist.js';
import { Vector3 } from '../geometry_msgs/pdu_jstype_Vector3.js';
import { PduVector3Converter } from '../geometry_msgs/pdu_cdr_conv_Vector3.js';


export class PduAckermannStepResponsePacketConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { AckermannStepResponsePacket } src
     */
    static to_cdr_body(writer, src) {
        PduServiceResponseHeaderConverter.to_cdr_body(writer, src.header);
        PduAckermannStepResponseConverter.to_cdr_body(writer, src.body);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { AckermannStepResponsePacket } dst
     * @returns { AckermannStepResponsePacket }
     */
    static cdr_body_to_js(reader, dst) {
        PduServiceResponseHeaderConverter.cdr_body_to_js(reader, dst.header);
        PduAckermannStepResponseConverter.cdr_body_to_js(reader, dst.body);
        return dst;
    }

    /**
     * @param { AckermannStepResponsePacket } src
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
     * @returns { AckermannStepResponsePacket }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new AckermannStepResponsePacket());
    }
}

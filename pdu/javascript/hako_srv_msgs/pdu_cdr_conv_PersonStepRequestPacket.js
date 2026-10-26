import { PersonStepRequestPacket } from './pdu_jstype_PersonStepRequestPacket.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { PersonStepRequest } from '../hako_srv_msgs/pdu_jstype_PersonStepRequest.js';
import { PduPersonStepRequestConverter } from '../hako_srv_msgs/pdu_cdr_conv_PersonStepRequest.js';
import { ServiceRequestHeader } from '../hako_srv_msgs/pdu_jstype_ServiceRequestHeader.js';
import { PduServiceRequestHeaderConverter } from '../hako_srv_msgs/pdu_cdr_conv_ServiceRequestHeader.js';
import { Twist } from '../geometry_msgs/pdu_jstype_Twist.js';
import { PduTwistConverter } from '../geometry_msgs/pdu_cdr_conv_Twist.js';
import { Vector3 } from '../geometry_msgs/pdu_jstype_Vector3.js';
import { PduVector3Converter } from '../geometry_msgs/pdu_cdr_conv_Vector3.js';


export class PduPersonStepRequestPacketConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { PersonStepRequestPacket } src
     */
    static to_cdr_body(writer, src) {
        PduServiceRequestHeaderConverter.to_cdr_body(writer, src.header);
        PduPersonStepRequestConverter.to_cdr_body(writer, src.body);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { PersonStepRequestPacket } dst
     * @returns { PersonStepRequestPacket }
     */
    static cdr_body_to_js(reader, dst) {
        PduServiceRequestHeaderConverter.cdr_body_to_js(reader, dst.header);
        PduPersonStepRequestConverter.cdr_body_to_js(reader, dst.body);
        return dst;
    }

    /**
     * @param { PersonStepRequestPacket } src
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
     * @returns { PersonStepRequestPacket }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new PersonStepRequestPacket());
    }
}

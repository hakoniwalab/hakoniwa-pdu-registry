import { AckermannStepRequestPacket } from './pdu_jstype_AckermannStepRequestPacket.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { AckermannDrive } from '../ackermann_msgs/pdu_jstype_AckermannDrive.js';
import { PduAckermannDriveConverter } from '../ackermann_msgs/pdu_cdr_conv_AckermannDrive.js';
import { AckermannStepRequest } from '../hako_srv_msgs/pdu_jstype_AckermannStepRequest.js';
import { PduAckermannStepRequestConverter } from '../hako_srv_msgs/pdu_cdr_conv_AckermannStepRequest.js';
import { ServiceRequestHeader } from '../hako_srv_msgs/pdu_jstype_ServiceRequestHeader.js';
import { PduServiceRequestHeaderConverter } from '../hako_srv_msgs/pdu_cdr_conv_ServiceRequestHeader.js';


export class PduAckermannStepRequestPacketConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { AckermannStepRequestPacket } src
     */
    static to_cdr_body(writer, src) {
        PduServiceRequestHeaderConverter.to_cdr_body(writer, src.header);
        PduAckermannStepRequestConverter.to_cdr_body(writer, src.body);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { AckermannStepRequestPacket } dst
     * @returns { AckermannStepRequestPacket }
     */
    static cdr_body_to_js(reader, dst) {
        PduServiceRequestHeaderConverter.cdr_body_to_js(reader, dst.header);
        PduAckermannStepRequestConverter.cdr_body_to_js(reader, dst.body);
        return dst;
    }

    /**
     * @param { AckermannStepRequestPacket } src
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
     * @returns { AckermannStepRequestPacket }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new AckermannStepRequestPacket());
    }
}

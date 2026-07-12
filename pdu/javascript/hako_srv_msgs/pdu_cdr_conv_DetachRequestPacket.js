import { DetachRequestPacket } from './pdu_jstype_DetachRequestPacket.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { DetachRequest } from '../hako_srv_msgs/pdu_jstype_DetachRequest.js';
import { PduDetachRequestConverter } from '../hako_srv_msgs/pdu_cdr_conv_DetachRequest.js';
import { ServiceRequestHeader } from '../hako_srv_msgs/pdu_jstype_ServiceRequestHeader.js';
import { PduServiceRequestHeaderConverter } from '../hako_srv_msgs/pdu_cdr_conv_ServiceRequestHeader.js';


export class PduDetachRequestPacketConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { DetachRequestPacket } src
     */
    static to_cdr_body(writer, src) {
        PduServiceRequestHeaderConverter.to_cdr_body(writer, src.header);
        PduDetachRequestConverter.to_cdr_body(writer, src.body);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { DetachRequestPacket } dst
     * @returns { DetachRequestPacket }
     */
    static cdr_body_to_js(reader, dst) {
        PduServiceRequestHeaderConverter.cdr_body_to_js(reader, dst.header);
        PduDetachRequestConverter.cdr_body_to_js(reader, dst.body);
        return dst;
    }

    /**
     * @param { DetachRequestPacket } src
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
     * @returns { DetachRequestPacket }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new DetachRequestPacket());
    }
}

import { AttachRequestPacket } from './pdu_jstype_AttachRequestPacket.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { AttachRequest } from '../hako_srv_msgs/pdu_jstype_AttachRequest.js';
import { PduAttachRequestConverter } from '../hako_srv_msgs/pdu_cdr_conv_AttachRequest.js';
import { ServiceRequestHeader } from '../hako_srv_msgs/pdu_jstype_ServiceRequestHeader.js';
import { PduServiceRequestHeaderConverter } from '../hako_srv_msgs/pdu_cdr_conv_ServiceRequestHeader.js';


export class PduAttachRequestPacketConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { AttachRequestPacket } src
     */
    static to_cdr_body(writer, src) {
        PduServiceRequestHeaderConverter.to_cdr_body(writer, src.header);
        PduAttachRequestConverter.to_cdr_body(writer, src.body);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { AttachRequestPacket } dst
     * @returns { AttachRequestPacket }
     */
    static cdr_body_to_js(reader, dst) {
        PduServiceRequestHeaderConverter.cdr_body_to_js(reader, dst.header);
        PduAttachRequestConverter.cdr_body_to_js(reader, dst.body);
        return dst;
    }

    /**
     * @param { AttachRequestPacket } src
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
     * @returns { AttachRequestPacket }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new AttachRequestPacket());
    }
}

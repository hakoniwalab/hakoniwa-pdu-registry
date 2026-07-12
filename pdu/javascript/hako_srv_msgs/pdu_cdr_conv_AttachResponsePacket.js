import { AttachResponsePacket } from './pdu_jstype_AttachResponsePacket.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { AttachResponse } from '../hako_srv_msgs/pdu_jstype_AttachResponse.js';
import { PduAttachResponseConverter } from '../hako_srv_msgs/pdu_cdr_conv_AttachResponse.js';
import { LogicalTime } from '../hako_srv_msgs/pdu_jstype_LogicalTime.js';
import { PduLogicalTimeConverter } from '../hako_srv_msgs/pdu_cdr_conv_LogicalTime.js';
import { ServiceResponseHeader } from '../hako_srv_msgs/pdu_jstype_ServiceResponseHeader.js';
import { PduServiceResponseHeaderConverter } from '../hako_srv_msgs/pdu_cdr_conv_ServiceResponseHeader.js';


export class PduAttachResponsePacketConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { AttachResponsePacket } src
     */
    static to_cdr_body(writer, src) {
        PduServiceResponseHeaderConverter.to_cdr_body(writer, src.header);
        PduAttachResponseConverter.to_cdr_body(writer, src.body);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { AttachResponsePacket } dst
     * @returns { AttachResponsePacket }
     */
    static cdr_body_to_js(reader, dst) {
        PduServiceResponseHeaderConverter.cdr_body_to_js(reader, dst.header);
        PduAttachResponseConverter.cdr_body_to_js(reader, dst.body);
        return dst;
    }

    /**
     * @param { AttachResponsePacket } src
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
     * @returns { AttachResponsePacket }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new AttachResponsePacket());
    }
}

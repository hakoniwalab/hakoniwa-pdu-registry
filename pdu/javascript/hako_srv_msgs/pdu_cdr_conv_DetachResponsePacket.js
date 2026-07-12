import { DetachResponsePacket } from './pdu_jstype_DetachResponsePacket.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { DetachResponse } from '../hako_srv_msgs/pdu_jstype_DetachResponse.js';
import { PduDetachResponseConverter } from '../hako_srv_msgs/pdu_cdr_conv_DetachResponse.js';
import { ServiceResponseHeader } from '../hako_srv_msgs/pdu_jstype_ServiceResponseHeader.js';
import { PduServiceResponseHeaderConverter } from '../hako_srv_msgs/pdu_cdr_conv_ServiceResponseHeader.js';


export class PduDetachResponsePacketConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { DetachResponsePacket } src
     */
    static to_cdr_body(writer, src) {
        PduServiceResponseHeaderConverter.to_cdr_body(writer, src.header);
        PduDetachResponseConverter.to_cdr_body(writer, src.body);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { DetachResponsePacket } dst
     * @returns { DetachResponsePacket }
     */
    static cdr_body_to_js(reader, dst) {
        PduServiceResponseHeaderConverter.cdr_body_to_js(reader, dst.header);
        PduDetachResponseConverter.cdr_body_to_js(reader, dst.body);
        return dst;
    }

    /**
     * @param { DetachResponsePacket } src
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
     * @returns { DetachResponsePacket }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new DetachResponsePacket());
    }
}

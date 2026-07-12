import { GetWorldTimeRequestPacket } from './pdu_jstype_GetWorldTimeRequestPacket.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { GetWorldTimeRequest } from '../hako_srv_msgs/pdu_jstype_GetWorldTimeRequest.js';
import { PduGetWorldTimeRequestConverter } from '../hako_srv_msgs/pdu_cdr_conv_GetWorldTimeRequest.js';
import { ServiceRequestHeader } from '../hako_srv_msgs/pdu_jstype_ServiceRequestHeader.js';
import { PduServiceRequestHeaderConverter } from '../hako_srv_msgs/pdu_cdr_conv_ServiceRequestHeader.js';


export class PduGetWorldTimeRequestPacketConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { GetWorldTimeRequestPacket } src
     */
    static to_cdr_body(writer, src) {
        PduServiceRequestHeaderConverter.to_cdr_body(writer, src.header);
        PduGetWorldTimeRequestConverter.to_cdr_body(writer, src.body);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { GetWorldTimeRequestPacket } dst
     * @returns { GetWorldTimeRequestPacket }
     */
    static cdr_body_to_js(reader, dst) {
        PduServiceRequestHeaderConverter.cdr_body_to_js(reader, dst.header);
        PduGetWorldTimeRequestConverter.cdr_body_to_js(reader, dst.body);
        return dst;
    }

    /**
     * @param { GetWorldTimeRequestPacket } src
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
     * @returns { GetWorldTimeRequestPacket }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new GetWorldTimeRequestPacket());
    }
}

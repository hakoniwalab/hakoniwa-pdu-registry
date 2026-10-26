import { SetLightRequestPacket } from './pdu_jstype_SetLightRequestPacket.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { ServiceRequestHeader } from '../hako_srv_msgs/pdu_jstype_ServiceRequestHeader.js';
import { PduServiceRequestHeaderConverter } from '../hako_srv_msgs/pdu_cdr_conv_ServiceRequestHeader.js';
import { SetLightRequest } from '../hako_srv_msgs/pdu_jstype_SetLightRequest.js';
import { PduSetLightRequestConverter } from '../hako_srv_msgs/pdu_cdr_conv_SetLightRequest.js';


export class PduSetLightRequestPacketConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { SetLightRequestPacket } src
     */
    static to_cdr_body(writer, src) {
        PduServiceRequestHeaderConverter.to_cdr_body(writer, src.header);
        PduSetLightRequestConverter.to_cdr_body(writer, src.body);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { SetLightRequestPacket } dst
     * @returns { SetLightRequestPacket }
     */
    static cdr_body_to_js(reader, dst) {
        PduServiceRequestHeaderConverter.cdr_body_to_js(reader, dst.header);
        PduSetLightRequestConverter.cdr_body_to_js(reader, dst.body);
        return dst;
    }

    /**
     * @param { SetLightRequestPacket } src
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
     * @returns { SetLightRequestPacket }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new SetLightRequestPacket());
    }
}

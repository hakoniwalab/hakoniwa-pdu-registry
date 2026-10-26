import { SetLightResponsePacket } from './pdu_jstype_SetLightResponsePacket.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { ServiceResponseHeader } from '../hako_srv_msgs/pdu_jstype_ServiceResponseHeader.js';
import { PduServiceResponseHeaderConverter } from '../hako_srv_msgs/pdu_cdr_conv_ServiceResponseHeader.js';
import { SetLightResponse } from '../hako_srv_msgs/pdu_jstype_SetLightResponse.js';
import { PduSetLightResponseConverter } from '../hako_srv_msgs/pdu_cdr_conv_SetLightResponse.js';


export class PduSetLightResponsePacketConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { SetLightResponsePacket } src
     */
    static to_cdr_body(writer, src) {
        PduServiceResponseHeaderConverter.to_cdr_body(writer, src.header);
        PduSetLightResponseConverter.to_cdr_body(writer, src.body);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { SetLightResponsePacket } dst
     * @returns { SetLightResponsePacket }
     */
    static cdr_body_to_js(reader, dst) {
        PduServiceResponseHeaderConverter.cdr_body_to_js(reader, dst.header);
        PduSetLightResponseConverter.cdr_body_to_js(reader, dst.body);
        return dst;
    }

    /**
     * @param { SetLightResponsePacket } src
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
     * @returns { SetLightResponsePacket }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new SetLightResponsePacket());
    }
}

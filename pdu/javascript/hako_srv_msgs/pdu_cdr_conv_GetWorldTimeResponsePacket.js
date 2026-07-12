import { GetWorldTimeResponsePacket } from './pdu_jstype_GetWorldTimeResponsePacket.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { GetWorldTimeResponse } from '../hako_srv_msgs/pdu_jstype_GetWorldTimeResponse.js';
import { PduGetWorldTimeResponseConverter } from '../hako_srv_msgs/pdu_cdr_conv_GetWorldTimeResponse.js';
import { LogicalTime } from '../hako_srv_msgs/pdu_jstype_LogicalTime.js';
import { PduLogicalTimeConverter } from '../hako_srv_msgs/pdu_cdr_conv_LogicalTime.js';
import { ServiceResponseHeader } from '../hako_srv_msgs/pdu_jstype_ServiceResponseHeader.js';
import { PduServiceResponseHeaderConverter } from '../hako_srv_msgs/pdu_cdr_conv_ServiceResponseHeader.js';


export class PduGetWorldTimeResponsePacketConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { GetWorldTimeResponsePacket } src
     */
    static to_cdr_body(writer, src) {
        PduServiceResponseHeaderConverter.to_cdr_body(writer, src.header);
        PduGetWorldTimeResponseConverter.to_cdr_body(writer, src.body);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { GetWorldTimeResponsePacket } dst
     * @returns { GetWorldTimeResponsePacket }
     */
    static cdr_body_to_js(reader, dst) {
        PduServiceResponseHeaderConverter.cdr_body_to_js(reader, dst.header);
        PduGetWorldTimeResponseConverter.cdr_body_to_js(reader, dst.body);
        return dst;
    }

    /**
     * @param { GetWorldTimeResponsePacket } src
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
     * @returns { GetWorldTimeResponsePacket }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new GetWorldTimeResponsePacket());
    }
}

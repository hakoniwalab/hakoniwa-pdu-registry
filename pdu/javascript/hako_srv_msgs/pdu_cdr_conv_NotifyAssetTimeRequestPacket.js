import { NotifyAssetTimeRequestPacket } from './pdu_jstype_NotifyAssetTimeRequestPacket.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { LogicalTime } from '../hako_srv_msgs/pdu_jstype_LogicalTime.js';
import { PduLogicalTimeConverter } from '../hako_srv_msgs/pdu_cdr_conv_LogicalTime.js';
import { NotifyAssetTimeRequest } from '../hako_srv_msgs/pdu_jstype_NotifyAssetTimeRequest.js';
import { PduNotifyAssetTimeRequestConverter } from '../hako_srv_msgs/pdu_cdr_conv_NotifyAssetTimeRequest.js';
import { ServiceRequestHeader } from '../hako_srv_msgs/pdu_jstype_ServiceRequestHeader.js';
import { PduServiceRequestHeaderConverter } from '../hako_srv_msgs/pdu_cdr_conv_ServiceRequestHeader.js';


export class PduNotifyAssetTimeRequestPacketConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { NotifyAssetTimeRequestPacket } src
     */
    static to_cdr_body(writer, src) {
        PduServiceRequestHeaderConverter.to_cdr_body(writer, src.header);
        PduNotifyAssetTimeRequestConverter.to_cdr_body(writer, src.body);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { NotifyAssetTimeRequestPacket } dst
     * @returns { NotifyAssetTimeRequestPacket }
     */
    static cdr_body_to_js(reader, dst) {
        PduServiceRequestHeaderConverter.cdr_body_to_js(reader, dst.header);
        PduNotifyAssetTimeRequestConverter.cdr_body_to_js(reader, dst.body);
        return dst;
    }

    /**
     * @param { NotifyAssetTimeRequestPacket } src
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
     * @returns { NotifyAssetTimeRequestPacket }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new NotifyAssetTimeRequestPacket());
    }
}

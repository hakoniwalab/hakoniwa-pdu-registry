import { NotifyAssetTimeResponsePacket } from './pdu_jstype_NotifyAssetTimeResponsePacket.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { NotifyAssetTimeResponse } from '../hako_srv_msgs/pdu_jstype_NotifyAssetTimeResponse.js';
import { PduNotifyAssetTimeResponseConverter } from '../hako_srv_msgs/pdu_cdr_conv_NotifyAssetTimeResponse.js';
import { ServiceResponseHeader } from '../hako_srv_msgs/pdu_jstype_ServiceResponseHeader.js';
import { PduServiceResponseHeaderConverter } from '../hako_srv_msgs/pdu_cdr_conv_ServiceResponseHeader.js';


export class PduNotifyAssetTimeResponsePacketConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { NotifyAssetTimeResponsePacket } src
     */
    static to_cdr_body(writer, src) {
        PduServiceResponseHeaderConverter.to_cdr_body(writer, src.header);
        PduNotifyAssetTimeResponseConverter.to_cdr_body(writer, src.body);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { NotifyAssetTimeResponsePacket } dst
     * @returns { NotifyAssetTimeResponsePacket }
     */
    static cdr_body_to_js(reader, dst) {
        PduServiceResponseHeaderConverter.cdr_body_to_js(reader, dst.header);
        PduNotifyAssetTimeResponseConverter.cdr_body_to_js(reader, dst.body);
        return dst;
    }

    /**
     * @param { NotifyAssetTimeResponsePacket } src
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
     * @returns { NotifyAssetTimeResponsePacket }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new NotifyAssetTimeResponsePacket());
    }
}

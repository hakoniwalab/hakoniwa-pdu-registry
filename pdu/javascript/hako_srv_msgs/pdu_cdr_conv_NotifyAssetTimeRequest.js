import { NotifyAssetTimeRequest } from './pdu_jstype_NotifyAssetTimeRequest.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { LogicalTime } from '../hako_srv_msgs/pdu_jstype_LogicalTime.js';
import { PduLogicalTimeConverter } from '../hako_srv_msgs/pdu_cdr_conv_LogicalTime.js';


export class PduNotifyAssetTimeRequestConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { NotifyAssetTimeRequest } src
     */
    static to_cdr_body(writer, src) {
        writer.write_uint64(src.session_id);
        PduLogicalTimeConverter.to_cdr_body(writer, src.asset_time);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { NotifyAssetTimeRequest } dst
     * @returns { NotifyAssetTimeRequest }
     */
    static cdr_body_to_js(reader, dst) {
        dst.session_id = reader.read_uint64();
        PduLogicalTimeConverter.cdr_body_to_js(reader, dst.asset_time);
        return dst;
    }

    /**
     * @param { NotifyAssetTimeRequest } src
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
     * @returns { NotifyAssetTimeRequest }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new NotifyAssetTimeRequest());
    }
}

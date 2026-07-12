import { AttachResponse } from './pdu_jstype_AttachResponse.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { LogicalTime } from '../hako_srv_msgs/pdu_jstype_LogicalTime.js';
import { PduLogicalTimeConverter } from '../hako_srv_msgs/pdu_cdr_conv_LogicalTime.js';


export class PduAttachResponseConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { AttachResponse } src
     */
    static to_cdr_body(writer, src) {
        writer.write_uint32(src.result_code);
        writer.write_uint64(src.session_id);
        PduLogicalTimeConverter.to_cdr_body(writer, src.world_time);
        writer.write_uint64(src.delta_asset_tick);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { AttachResponse } dst
     * @returns { AttachResponse }
     */
    static cdr_body_to_js(reader, dst) {
        dst.result_code = reader.read_uint32();
        dst.session_id = reader.read_uint64();
        PduLogicalTimeConverter.cdr_body_to_js(reader, dst.world_time);
        dst.delta_asset_tick = reader.read_uint64();
        return dst;
    }

    /**
     * @param { AttachResponse } src
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
     * @returns { AttachResponse }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new AttachResponse());
    }
}

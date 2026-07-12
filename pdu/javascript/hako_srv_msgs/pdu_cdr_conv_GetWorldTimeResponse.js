import { GetWorldTimeResponse } from './pdu_jstype_GetWorldTimeResponse.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { LogicalTime } from '../hako_srv_msgs/pdu_jstype_LogicalTime.js';
import { PduLogicalTimeConverter } from '../hako_srv_msgs/pdu_cdr_conv_LogicalTime.js';


export class PduGetWorldTimeResponseConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { GetWorldTimeResponse } src
     */
    static to_cdr_body(writer, src) {
        writer.write_uint32(src.result_code);
        PduLogicalTimeConverter.to_cdr_body(writer, src.world_time);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { GetWorldTimeResponse } dst
     * @returns { GetWorldTimeResponse }
     */
    static cdr_body_to_js(reader, dst) {
        dst.result_code = reader.read_uint32();
        PduLogicalTimeConverter.cdr_body_to_js(reader, dst.world_time);
        return dst;
    }

    /**
     * @param { GetWorldTimeResponse } src
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
     * @returns { GetWorldTimeResponse }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new GetWorldTimeResponse());
    }
}

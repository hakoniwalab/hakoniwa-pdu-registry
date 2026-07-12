import { NotifyAssetTimeResponse } from './pdu_jstype_NotifyAssetTimeResponse.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';


export class PduNotifyAssetTimeResponseConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { NotifyAssetTimeResponse } src
     */
    static to_cdr_body(writer, src) {
        writer.write_uint32(src.result_code);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { NotifyAssetTimeResponse } dst
     * @returns { NotifyAssetTimeResponse }
     */
    static cdr_body_to_js(reader, dst) {
        dst.result_code = reader.read_uint32();
        return dst;
    }

    /**
     * @param { NotifyAssetTimeResponse } src
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
     * @returns { NotifyAssetTimeResponse }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new NotifyAssetTimeResponse());
    }
}

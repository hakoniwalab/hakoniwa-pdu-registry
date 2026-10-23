import { RenderCameraFrameResponse } from './pdu_jstype_RenderCameraFrameResponse.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { Header } from '../std_msgs/pdu_jstype_Header.js';
import { PduHeaderConverter } from '../std_msgs/pdu_cdr_conv_Header.js';
import { Image } from '../sensor_msgs/pdu_jstype_Image.js';
import { PduImageConverter } from '../sensor_msgs/pdu_cdr_conv_Image.js';
import { Time } from '../builtin_interfaces/pdu_jstype_Time.js';
import { PduTimeConverter } from '../builtin_interfaces/pdu_cdr_conv_Time.js';


export class PduRenderCameraFrameResponseConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { RenderCameraFrameResponse } src
     */
    static to_cdr_body(writer, src) {
        writer.write_uint32(src.result_code);
        writer.write_uint64(src.sim_time_usec);
        PduImageConverter.to_cdr_body(writer, src.rgb);
        PduImageConverter.to_cdr_body(writer, src.depth);
        PduImageConverter.to_cdr_body(writer, src.segmentation);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { RenderCameraFrameResponse } dst
     * @returns { RenderCameraFrameResponse }
     */
    static cdr_body_to_js(reader, dst) {
        dst.result_code = reader.read_uint32();
        dst.sim_time_usec = reader.read_uint64();
        PduImageConverter.cdr_body_to_js(reader, dst.rgb);
        PduImageConverter.cdr_body_to_js(reader, dst.depth);
        PduImageConverter.cdr_body_to_js(reader, dst.segmentation);
        return dst;
    }

    /**
     * @param { RenderCameraFrameResponse } src
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
     * @returns { RenderCameraFrameResponse }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new RenderCameraFrameResponse());
    }
}

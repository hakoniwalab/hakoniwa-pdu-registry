import { RenderCameraFrameResponsePacket } from './pdu_jstype_RenderCameraFrameResponsePacket.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { Header } from '../std_msgs/pdu_jstype_Header.js';
import { PduHeaderConverter } from '../std_msgs/pdu_cdr_conv_Header.js';
import { Image } from '../sensor_msgs/pdu_jstype_Image.js';
import { PduImageConverter } from '../sensor_msgs/pdu_cdr_conv_Image.js';
import { RenderCameraFrameResponse } from '../hako_srv_msgs/pdu_jstype_RenderCameraFrameResponse.js';
import { PduRenderCameraFrameResponseConverter } from '../hako_srv_msgs/pdu_cdr_conv_RenderCameraFrameResponse.js';
import { ServiceResponseHeader } from '../hako_srv_msgs/pdu_jstype_ServiceResponseHeader.js';
import { PduServiceResponseHeaderConverter } from '../hako_srv_msgs/pdu_cdr_conv_ServiceResponseHeader.js';
import { Time } from '../builtin_interfaces/pdu_jstype_Time.js';
import { PduTimeConverter } from '../builtin_interfaces/pdu_cdr_conv_Time.js';


export class PduRenderCameraFrameResponsePacketConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { RenderCameraFrameResponsePacket } src
     */
    static to_cdr_body(writer, src) {
        PduServiceResponseHeaderConverter.to_cdr_body(writer, src.header);
        PduRenderCameraFrameResponseConverter.to_cdr_body(writer, src.body);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { RenderCameraFrameResponsePacket } dst
     * @returns { RenderCameraFrameResponsePacket }
     */
    static cdr_body_to_js(reader, dst) {
        PduServiceResponseHeaderConverter.cdr_body_to_js(reader, dst.header);
        PduRenderCameraFrameResponseConverter.cdr_body_to_js(reader, dst.body);
        return dst;
    }

    /**
     * @param { RenderCameraFrameResponsePacket } src
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
     * @returns { RenderCameraFrameResponsePacket }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new RenderCameraFrameResponsePacket());
    }
}

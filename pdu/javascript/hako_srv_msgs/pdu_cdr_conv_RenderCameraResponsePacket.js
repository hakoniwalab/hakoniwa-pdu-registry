import { RenderCameraResponsePacket } from './pdu_jstype_RenderCameraResponsePacket.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { Header } from '../std_msgs/pdu_jstype_Header.js';
import { PduHeaderConverter } from '../std_msgs/pdu_cdr_conv_Header.js';
import { Image } from '../sensor_msgs/pdu_jstype_Image.js';
import { PduImageConverter } from '../sensor_msgs/pdu_cdr_conv_Image.js';
import { RenderCameraResponse } from '../hako_srv_msgs/pdu_jstype_RenderCameraResponse.js';
import { PduRenderCameraResponseConverter } from '../hako_srv_msgs/pdu_cdr_conv_RenderCameraResponse.js';
import { ServiceResponseHeader } from '../hako_srv_msgs/pdu_jstype_ServiceResponseHeader.js';
import { PduServiceResponseHeaderConverter } from '../hako_srv_msgs/pdu_cdr_conv_ServiceResponseHeader.js';
import { Time } from '../builtin_interfaces/pdu_jstype_Time.js';
import { PduTimeConverter } from '../builtin_interfaces/pdu_cdr_conv_Time.js';


export class PduRenderCameraResponsePacketConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { RenderCameraResponsePacket } src
     */
    static to_cdr_body(writer, src) {
        PduServiceResponseHeaderConverter.to_cdr_body(writer, src.header);
        PduRenderCameraResponseConverter.to_cdr_body(writer, src.body);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { RenderCameraResponsePacket } dst
     * @returns { RenderCameraResponsePacket }
     */
    static cdr_body_to_js(reader, dst) {
        PduServiceResponseHeaderConverter.cdr_body_to_js(reader, dst.header);
        PduRenderCameraResponseConverter.cdr_body_to_js(reader, dst.body);
        return dst;
    }

    /**
     * @param { RenderCameraResponsePacket } src
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
     * @returns { RenderCameraResponsePacket }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new RenderCameraResponsePacket());
    }
}

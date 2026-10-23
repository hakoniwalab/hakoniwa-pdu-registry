import { RenderCameraFrameRequestPacket } from './pdu_jstype_RenderCameraFrameRequestPacket.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { Point } from '../geometry_msgs/pdu_jstype_Point.js';
import { PduPointConverter } from '../geometry_msgs/pdu_cdr_conv_Point.js';
import { Pose } from '../geometry_msgs/pdu_jstype_Pose.js';
import { PduPoseConverter } from '../geometry_msgs/pdu_cdr_conv_Pose.js';
import { Quaternion } from '../geometry_msgs/pdu_jstype_Quaternion.js';
import { PduQuaternionConverter } from '../geometry_msgs/pdu_cdr_conv_Quaternion.js';
import { RenderCameraFrameRequest } from '../hako_srv_msgs/pdu_jstype_RenderCameraFrameRequest.js';
import { PduRenderCameraFrameRequestConverter } from '../hako_srv_msgs/pdu_cdr_conv_RenderCameraFrameRequest.js';
import { ServiceRequestHeader } from '../hako_srv_msgs/pdu_jstype_ServiceRequestHeader.js';
import { PduServiceRequestHeaderConverter } from '../hako_srv_msgs/pdu_cdr_conv_ServiceRequestHeader.js';


export class PduRenderCameraFrameRequestPacketConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { RenderCameraFrameRequestPacket } src
     */
    static to_cdr_body(writer, src) {
        PduServiceRequestHeaderConverter.to_cdr_body(writer, src.header);
        PduRenderCameraFrameRequestConverter.to_cdr_body(writer, src.body);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { RenderCameraFrameRequestPacket } dst
     * @returns { RenderCameraFrameRequestPacket }
     */
    static cdr_body_to_js(reader, dst) {
        PduServiceRequestHeaderConverter.cdr_body_to_js(reader, dst.header);
        PduRenderCameraFrameRequestConverter.cdr_body_to_js(reader, dst.body);
        return dst;
    }

    /**
     * @param { RenderCameraFrameRequestPacket } src
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
     * @returns { RenderCameraFrameRequestPacket }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new RenderCameraFrameRequestPacket());
    }
}

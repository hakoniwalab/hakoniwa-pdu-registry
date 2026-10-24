import { RenderCameraFrameRequest } from './pdu_jstype_RenderCameraFrameRequest.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { Point } from '../geometry_msgs/pdu_jstype_Point.js';
import { PduPointConverter } from '../geometry_msgs/pdu_cdr_conv_Point.js';
import { Pose } from '../geometry_msgs/pdu_jstype_Pose.js';
import { PduPoseConverter } from '../geometry_msgs/pdu_cdr_conv_Pose.js';
import { Quaternion } from '../geometry_msgs/pdu_jstype_Quaternion.js';
import { PduQuaternionConverter } from '../geometry_msgs/pdu_cdr_conv_Quaternion.js';
import { RenderObject } from '../hako_srv_msgs/pdu_jstype_RenderObject.js';
import { PduRenderObjectConverter } from '../hako_srv_msgs/pdu_cdr_conv_RenderObject.js';


export class PduRenderCameraFrameRequestConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { RenderCameraFrameRequest } src
     */
    static to_cdr_body(writer, src) {
        writer.write_string(src.camera_name);
        writer.write_uint64(src.sim_time_usec);
        PduPoseConverter.to_cdr_body(writer, src.camera_pose);
        writer.write_uint8(src.outputs);
        writer.write_sequence_length(src.objects);
        for (const elem of src.objects) {
            PduRenderObjectConverter.to_cdr_body(writer, elem);
        }
    }

    /**
     * @param {PduCdrReader} reader
     * @param { RenderCameraFrameRequest } dst
     * @returns { RenderCameraFrameRequest }
     */
    static cdr_body_to_js(reader, dst) {
        dst.camera_name = reader.read_string();
        dst.sim_time_usec = reader.read_uint64();
        PduPoseConverter.cdr_body_to_js(reader, dst.camera_pose);
        dst.outputs = reader.read_uint8();
        dst.objects = [];
        for (let i = 0, len = reader.read_uint32(); i < len; i++) {
            dst.objects.push(PduRenderObjectConverter.cdr_body_to_js(reader, new RenderObject()));
        }
        return dst;
    }

    /**
     * @param { RenderCameraFrameRequest } src
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
     * @returns { RenderCameraFrameRequest }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new RenderCameraFrameRequest());
    }
}

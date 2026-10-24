import { RenderObject } from './pdu_jstype_RenderObject.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { Point } from '../geometry_msgs/pdu_jstype_Point.js';
import { PduPointConverter } from '../geometry_msgs/pdu_cdr_conv_Point.js';
import { Pose } from '../geometry_msgs/pdu_jstype_Pose.js';
import { PduPoseConverter } from '../geometry_msgs/pdu_cdr_conv_Pose.js';
import { Quaternion } from '../geometry_msgs/pdu_jstype_Quaternion.js';
import { PduQuaternionConverter } from '../geometry_msgs/pdu_cdr_conv_Quaternion.js';


export class PduRenderObjectConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { RenderObject } src
     */
    static to_cdr_body(writer, src) {
        writer.write_string(src.name);
        writer.write_string(src.model);
        PduPoseConverter.to_cdr_body(writer, src.pose);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { RenderObject } dst
     * @returns { RenderObject }
     */
    static cdr_body_to_js(reader, dst) {
        dst.name = reader.read_string();
        dst.model = reader.read_string();
        PduPoseConverter.cdr_body_to_js(reader, dst.pose);
        return dst;
    }

    /**
     * @param { RenderObject } src
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
     * @returns { RenderObject }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new RenderObject());
    }
}

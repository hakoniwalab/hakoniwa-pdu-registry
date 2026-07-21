import { MultiDOFJointTrajectoryPoint } from './pdu_jstype_MultiDOFJointTrajectoryPoint.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { Duration } from '../builtin_interfaces/pdu_jstype_Duration.js';
import { PduDurationConverter } from '../builtin_interfaces/pdu_cdr_conv_Duration.js';
import { Quaternion } from '../geometry_msgs/pdu_jstype_Quaternion.js';
import { PduQuaternionConverter } from '../geometry_msgs/pdu_cdr_conv_Quaternion.js';
import { Transform } from '../geometry_msgs/pdu_jstype_Transform.js';
import { PduTransformConverter } from '../geometry_msgs/pdu_cdr_conv_Transform.js';
import { Twist } from '../geometry_msgs/pdu_jstype_Twist.js';
import { PduTwistConverter } from '../geometry_msgs/pdu_cdr_conv_Twist.js';
import { Vector3 } from '../geometry_msgs/pdu_jstype_Vector3.js';
import { PduVector3Converter } from '../geometry_msgs/pdu_cdr_conv_Vector3.js';


export class PduMultiDOFJointTrajectoryPointConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { MultiDOFJointTrajectoryPoint } src
     */
    static to_cdr_body(writer, src) {
        writer.write_sequence_length(src.transforms);
        for (const elem of src.transforms) {
            PduTransformConverter.to_cdr_body(writer, elem);
        }
        writer.write_sequence_length(src.velocities);
        for (const elem of src.velocities) {
            PduTwistConverter.to_cdr_body(writer, elem);
        }
        writer.write_sequence_length(src.accelerations);
        for (const elem of src.accelerations) {
            PduTwistConverter.to_cdr_body(writer, elem);
        }
        PduDurationConverter.to_cdr_body(writer, src.time_from_start);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { MultiDOFJointTrajectoryPoint } dst
     * @returns { MultiDOFJointTrajectoryPoint }
     */
    static cdr_body_to_js(reader, dst) {
        dst.transforms = [];
        for (let i = 0, len = reader.read_uint32(); i < len; i++) {
            dst.transforms.push(PduTransformConverter.cdr_body_to_js(reader, new Transform()));
        }
        dst.velocities = [];
        for (let i = 0, len = reader.read_uint32(); i < len; i++) {
            dst.velocities.push(PduTwistConverter.cdr_body_to_js(reader, new Twist()));
        }
        dst.accelerations = [];
        for (let i = 0, len = reader.read_uint32(); i < len; i++) {
            dst.accelerations.push(PduTwistConverter.cdr_body_to_js(reader, new Twist()));
        }
        PduDurationConverter.cdr_body_to_js(reader, dst.time_from_start);
        return dst;
    }

    /**
     * @param { MultiDOFJointTrajectoryPoint } src
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
     * @returns { MultiDOFJointTrajectoryPoint }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new MultiDOFJointTrajectoryPoint());
    }
}

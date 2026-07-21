import { MultiDOFJointTrajectory } from './pdu_jstype_MultiDOFJointTrajectory.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { Duration } from '../builtin_interfaces/pdu_jstype_Duration.js';
import { PduDurationConverter } from '../builtin_interfaces/pdu_cdr_conv_Duration.js';
import { Header } from '../std_msgs/pdu_jstype_Header.js';
import { PduHeaderConverter } from '../std_msgs/pdu_cdr_conv_Header.js';
import { MultiDOFJointTrajectoryPoint } from '../trajectory_msgs/pdu_jstype_MultiDOFJointTrajectoryPoint.js';
import { PduMultiDOFJointTrajectoryPointConverter } from '../trajectory_msgs/pdu_cdr_conv_MultiDOFJointTrajectoryPoint.js';
import { Quaternion } from '../geometry_msgs/pdu_jstype_Quaternion.js';
import { PduQuaternionConverter } from '../geometry_msgs/pdu_cdr_conv_Quaternion.js';
import { Time } from '../builtin_interfaces/pdu_jstype_Time.js';
import { PduTimeConverter } from '../builtin_interfaces/pdu_cdr_conv_Time.js';
import { Transform } from '../geometry_msgs/pdu_jstype_Transform.js';
import { PduTransformConverter } from '../geometry_msgs/pdu_cdr_conv_Transform.js';
import { Twist } from '../geometry_msgs/pdu_jstype_Twist.js';
import { PduTwistConverter } from '../geometry_msgs/pdu_cdr_conv_Twist.js';
import { Vector3 } from '../geometry_msgs/pdu_jstype_Vector3.js';
import { PduVector3Converter } from '../geometry_msgs/pdu_cdr_conv_Vector3.js';


export class PduMultiDOFJointTrajectoryConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { MultiDOFJointTrajectory } src
     */
    static to_cdr_body(writer, src) {
        PduHeaderConverter.to_cdr_body(writer, src.header);
        writer.write_sequence_length(src.joint_names);
        for (const elem of src.joint_names) {
            writer.write_string(elem);
        }
        writer.write_sequence_length(src.points);
        for (const elem of src.points) {
            PduMultiDOFJointTrajectoryPointConverter.to_cdr_body(writer, elem);
        }
    }

    /**
     * @param {PduCdrReader} reader
     * @param { MultiDOFJointTrajectory } dst
     * @returns { MultiDOFJointTrajectory }
     */
    static cdr_body_to_js(reader, dst) {
        PduHeaderConverter.cdr_body_to_js(reader, dst.header);
        dst.joint_names = Array.from({ length: reader.read_uint32() }, () => reader.read_string());
        dst.points = [];
        for (let i = 0, len = reader.read_uint32(); i < len; i++) {
            dst.points.push(PduMultiDOFJointTrajectoryPointConverter.cdr_body_to_js(reader, new MultiDOFJointTrajectoryPoint()));
        }
        return dst;
    }

    /**
     * @param { MultiDOFJointTrajectory } src
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
     * @returns { MultiDOFJointTrajectory }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new MultiDOFJointTrajectory());
    }
}

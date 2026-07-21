import { JointTrajectory } from './pdu_jstype_JointTrajectory.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { Duration } from '../builtin_interfaces/pdu_jstype_Duration.js';
import { PduDurationConverter } from '../builtin_interfaces/pdu_cdr_conv_Duration.js';
import { Header } from '../std_msgs/pdu_jstype_Header.js';
import { PduHeaderConverter } from '../std_msgs/pdu_cdr_conv_Header.js';
import { JointTrajectoryPoint } from '../trajectory_msgs/pdu_jstype_JointTrajectoryPoint.js';
import { PduJointTrajectoryPointConverter } from '../trajectory_msgs/pdu_cdr_conv_JointTrajectoryPoint.js';
import { Time } from '../builtin_interfaces/pdu_jstype_Time.js';
import { PduTimeConverter } from '../builtin_interfaces/pdu_cdr_conv_Time.js';


export class PduJointTrajectoryConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { JointTrajectory } src
     */
    static to_cdr_body(writer, src) {
        PduHeaderConverter.to_cdr_body(writer, src.header);
        writer.write_sequence_length(src.joint_names);
        for (const elem of src.joint_names) {
            writer.write_string(elem);
        }
        writer.write_sequence_length(src.points);
        for (const elem of src.points) {
            PduJointTrajectoryPointConverter.to_cdr_body(writer, elem);
        }
    }

    /**
     * @param {PduCdrReader} reader
     * @param { JointTrajectory } dst
     * @returns { JointTrajectory }
     */
    static cdr_body_to_js(reader, dst) {
        PduHeaderConverter.cdr_body_to_js(reader, dst.header);
        dst.joint_names = Array.from({ length: reader.read_uint32() }, () => reader.read_string());
        dst.points = [];
        for (let i = 0, len = reader.read_uint32(); i < len; i++) {
            dst.points.push(PduJointTrajectoryPointConverter.cdr_body_to_js(reader, new JointTrajectoryPoint()));
        }
        return dst;
    }

    /**
     * @param { JointTrajectory } src
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
     * @returns { JointTrajectory }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new JointTrajectory());
    }
}

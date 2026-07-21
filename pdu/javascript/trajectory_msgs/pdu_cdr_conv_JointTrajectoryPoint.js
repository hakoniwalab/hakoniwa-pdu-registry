import { JointTrajectoryPoint } from './pdu_jstype_JointTrajectoryPoint.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { Duration } from '../builtin_interfaces/pdu_jstype_Duration.js';
import { PduDurationConverter } from '../builtin_interfaces/pdu_cdr_conv_Duration.js';


export class PduJointTrajectoryPointConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { JointTrajectoryPoint } src
     */
    static to_cdr_body(writer, src) {
        writer.write_sequence_length(src.positions);
        for (const elem of src.positions) {
            writer.write_float64(elem);
        }
        writer.write_sequence_length(src.velocities);
        for (const elem of src.velocities) {
            writer.write_float64(elem);
        }
        writer.write_sequence_length(src.accelerations);
        for (const elem of src.accelerations) {
            writer.write_float64(elem);
        }
        writer.write_sequence_length(src.effort);
        for (const elem of src.effort) {
            writer.write_float64(elem);
        }
        PduDurationConverter.to_cdr_body(writer, src.time_from_start);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { JointTrajectoryPoint } dst
     * @returns { JointTrajectoryPoint }
     */
    static cdr_body_to_js(reader, dst) {
        dst.positions = Array.from({ length: reader.read_uint32() }, () => reader.read_float64());
        dst.velocities = Array.from({ length: reader.read_uint32() }, () => reader.read_float64());
        dst.accelerations = Array.from({ length: reader.read_uint32() }, () => reader.read_float64());
        dst.effort = Array.from({ length: reader.read_uint32() }, () => reader.read_float64());
        PduDurationConverter.cdr_body_to_js(reader, dst.time_from_start);
        return dst;
    }

    /**
     * @param { JointTrajectoryPoint } src
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
     * @returns { JointTrajectoryPoint }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new JointTrajectoryPoint());
    }
}

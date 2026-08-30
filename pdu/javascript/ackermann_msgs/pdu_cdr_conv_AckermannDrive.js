import { AckermannDrive } from './pdu_jstype_AckermannDrive.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';


export class PduAckermannDriveConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { AckermannDrive } src
     */
    static to_cdr_body(writer, src) {
        writer.write_float32(src.steering_angle);
        writer.write_float32(src.steering_angle_velocity);
        writer.write_float32(src.speed);
        writer.write_float32(src.acceleration);
        writer.write_float32(src.jerk);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { AckermannDrive } dst
     * @returns { AckermannDrive }
     */
    static cdr_body_to_js(reader, dst) {
        dst.steering_angle = reader.read_float32();
        dst.steering_angle_velocity = reader.read_float32();
        dst.speed = reader.read_float32();
        dst.acceleration = reader.read_float32();
        dst.jerk = reader.read_float32();
        return dst;
    }

    /**
     * @param { AckermannDrive } src
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
     * @returns { AckermannDrive }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new AckermannDrive());
    }
}

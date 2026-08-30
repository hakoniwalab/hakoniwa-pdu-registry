import { AckermannDriveStamped } from './pdu_jstype_AckermannDriveStamped.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { AckermannDrive } from '../ackermann_msgs/pdu_jstype_AckermannDrive.js';
import { PduAckermannDriveConverter } from '../ackermann_msgs/pdu_cdr_conv_AckermannDrive.js';
import { Header } from '../std_msgs/pdu_jstype_Header.js';
import { PduHeaderConverter } from '../std_msgs/pdu_cdr_conv_Header.js';
import { Time } from '../builtin_interfaces/pdu_jstype_Time.js';
import { PduTimeConverter } from '../builtin_interfaces/pdu_cdr_conv_Time.js';


export class PduAckermannDriveStampedConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { AckermannDriveStamped } src
     */
    static to_cdr_body(writer, src) {
        PduHeaderConverter.to_cdr_body(writer, src.header);
        PduAckermannDriveConverter.to_cdr_body(writer, src.drive);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { AckermannDriveStamped } dst
     * @returns { AckermannDriveStamped }
     */
    static cdr_body_to_js(reader, dst) {
        PduHeaderConverter.cdr_body_to_js(reader, dst.header);
        PduAckermannDriveConverter.cdr_body_to_js(reader, dst.drive);
        return dst;
    }

    /**
     * @param { AckermannDriveStamped } src
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
     * @returns { AckermannDriveStamped }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new AckermannDriveStamped());
    }
}

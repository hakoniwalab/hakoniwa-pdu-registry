import { AckermannStepRequest } from './pdu_jstype_AckermannStepRequest.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { AckermannDrive } from '../ackermann_msgs/pdu_jstype_AckermannDrive.js';
import { PduAckermannDriveConverter } from '../ackermann_msgs/pdu_cdr_conv_AckermannDrive.js';


export class PduAckermannStepRequestConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { AckermannStepRequest } src
     */
    static to_cdr_body(writer, src) {
        writer.write_uint64(src.step);
        PduAckermannDriveConverter.to_cdr_body(writer, src.drive);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { AckermannStepRequest } dst
     * @returns { AckermannStepRequest }
     */
    static cdr_body_to_js(reader, dst) {
        dst.step = reader.read_uint64();
        PduAckermannDriveConverter.cdr_body_to_js(reader, dst.drive);
        return dst;
    }

    /**
     * @param { AckermannStepRequest } src
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
     * @returns { AckermannStepRequest }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new AckermannStepRequest());
    }
}

import { ContactEvent } from './pdu_jstype_ContactEvent.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { Point } from '../geometry_msgs/pdu_jstype_Point.js';
import { PduPointConverter } from '../geometry_msgs/pdu_cdr_conv_Point.js';
import { Time } from '../builtin_interfaces/pdu_jstype_Time.js';
import { PduTimeConverter } from '../builtin_interfaces/pdu_cdr_conv_Time.js';


export class PduContactEventConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { ContactEvent } src
     */
    static to_cdr_body(writer, src) {
        PduTimeConverter.to_cdr_body(writer, src.stamp);
        writer.write_string(src.self_name);
        writer.write_string(src.other_name);
        writer.write_string(src.other_kind);
        PduPointConverter.to_cdr_body(writer, src.position);
        writer.write_float64(src.relative_speed);
        writer.write_bool(src.started);
    }

    /**
     * @param {PduCdrReader} reader
     * @param { ContactEvent } dst
     * @returns { ContactEvent }
     */
    static cdr_body_to_js(reader, dst) {
        PduTimeConverter.cdr_body_to_js(reader, dst.stamp);
        dst.self_name = reader.read_string();
        dst.other_name = reader.read_string();
        dst.other_kind = reader.read_string();
        PduPointConverter.cdr_body_to_js(reader, dst.position);
        dst.relative_speed = reader.read_float64();
        dst.started = reader.read_bool();
        return dst;
    }

    /**
     * @param { ContactEvent } src
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
     * @returns { ContactEvent }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new ContactEvent());
    }
}

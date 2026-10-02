import { ContactEventArray } from './pdu_jstype_ContactEventArray.js';
import { PduCdrWriter, PduCdrReader } from '../pdu_cdr_runtime.js';
import { ContactEvent } from '../hako_msgs/pdu_jstype_ContactEvent.js';
import { PduContactEventConverter } from '../hako_msgs/pdu_cdr_conv_ContactEvent.js';
import { Point } from '../geometry_msgs/pdu_jstype_Point.js';
import { PduPointConverter } from '../geometry_msgs/pdu_cdr_conv_Point.js';
import { Time } from '../builtin_interfaces/pdu_jstype_Time.js';
import { PduTimeConverter } from '../builtin_interfaces/pdu_cdr_conv_Time.js';


export class PduContactEventArrayConverter {
    /**
     * @param {PduCdrWriter} writer
     * @param { ContactEventArray } src
     */
    static to_cdr_body(writer, src) {
        writer.write_sequence_length(src.events);
        for (const elem of src.events) {
            PduContactEventConverter.to_cdr_body(writer, elem);
        }
    }

    /**
     * @param {PduCdrReader} reader
     * @param { ContactEventArray } dst
     * @returns { ContactEventArray }
     */
    static cdr_body_to_js(reader, dst) {
        dst.events = [];
        for (let i = 0, len = reader.read_uint32(); i < len; i++) {
            dst.events.push(PduContactEventConverter.cdr_body_to_js(reader, new ContactEvent()));
        }
        return dst;
    }

    /**
     * @param { ContactEventArray } src
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
     * @returns { ContactEventArray }
     */
    static from_cdr(cdrPayload) {
        const reader = new PduCdrReader(cdrPayload);
        reader.read_encapsulation();
        return this.cdr_body_to_js(reader, new ContactEventArray());
    }
}

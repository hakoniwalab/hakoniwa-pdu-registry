# Action common header contract

This document defines the fixed common headers used by Hakoniwa Action PDU packets.

The Action protocol is independent from the existing Service request/response binary contract. A 128-bit `goal_id` identifies one Action execution session. The headers intentionally do not contain `client_name`, `client_id`, or a Service `request_id`.

## IDL constraint

Hakoniwa PDU IDL does not support ROS-style constant declarations such as:

```text
uint8 PROTOCOL_VERSION=1
```

Therefore, the `.msg` files contain fields only. Protocol numeric values are defined by this document and must be represented by runtime/library constants outside the PDU IDL.

## Protocol version

All three headers currently use:

```text
PROTOCOL_VERSION = 1
```

Senders set `version` to this value. Receivers must reject unsupported versions rather than guessing the layout.

## ActionRequestHeader

```text
uint8 version
uint8 request_kind
uint8[2] reserved
uint8[16] goal_id
```

`request_kind` values:

| Name | Value | Meaning |
| --- | ---: | --- |
| `REQUEST_KIND_GOAL` | 1 | Start a Goal using the packet body. |
| `REQUEST_KIND_CANCEL` | 2 | Request cancellation of the identified Goal. The packet body is ignored. |

## ActionResponseHeader

```text
uint8 version
uint8 response_kind
uint8 status
uint8 reserved
uint8[16] goal_id
```

`response_kind` values:

| Name | Value | Meaning |
| --- | ---: | --- |
| `RESPONSE_KIND_GOAL_RESPONSE` | 1 | Accept or reject a Goal. |
| `RESPONSE_KIND_CANCEL_RESPONSE` | 2 | Accept or reject a Cancel request. |
| `RESPONSE_KIND_RESULT` | 3 | Deliver the terminal result. |
| `RESPONSE_KIND_ERROR` | 255 | Report a protocol-level error. |

`status` values:

| Name | Value | Valid use |
| --- | ---: | --- |
| `STATUS_ACCEPTED` | 1 | Goal or Cancel response. |
| `STATUS_REJECTED` | 2 | Goal or Cancel response. |
| `STATUS_SUCCEEDED` | 3 | Terminal Result. |
| `STATUS_CANCELED` | 4 | Terminal Result. |
| `STATUS_ABORTED` | 5 | Terminal Result. |
| `STATUS_ERROR` | 255 | Protocol-level error. |

The `response_kind` and `status` combination defines the response meaning. For example, `GOAL_RESPONSE + ACCEPTED` acknowledges a Goal, while `RESULT + SUCCEEDED` carries a successful terminal result.

## ActionFeedbackHeader

```text
uint8 version
uint8[3] reserved
uint8[16] goal_id
uint32 sequence_no
```

`sequence_no` is monotonically increased per Goal. It allows consumers to detect repeated reads or skipped Feedback updates when the underlying PDU transport exposes the latest value rather than a durable queue.

## Reserved fields

All reserved bytes must be written as zero by senders and ignored by version-1 receivers. They are retained for future compatible extensions.

## Payload ownership

The common headers contain only protocol metadata. Action-specific Goal, Result, Feedback, and progress data belong in the generated packet body derived from the user-defined `.action` file.

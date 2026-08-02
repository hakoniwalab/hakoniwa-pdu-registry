import argparse

from generators.generate_hako_action_msgs.action_context import ActionContext
from generators.generate_hako_action_msgs.action_parser import ActionParser
from generators.generate_hako_action_msgs.msg_generator import MsgGenerator
from generators.generate_hako_action_msgs.msg_writer import MsgWriter


def main():
    parser = argparse.ArgumentParser(
        description="Generate Hakoniwa Action .msg files from a ROS 2 .action file"
    )
    parser.add_argument("action_file", help="Path to the input .action file")
    parser.add_argument("--out", required=True, help="Base output directory")
    args = parser.parse_args()

    context = ActionContext(args.action_file)
    goal_fields, result_fields, feedback_fields = ActionParser(context).parse()
    generator = MsgGenerator(context)
    writer = MsgWriter(context, args.out)
    name = context.action_name

    writer.write(f"{name}Goal.msg", generator.generate_data_msg(goal_fields))
    writer.write(f"{name}Result.msg", generator.generate_data_msg(result_fields))
    writer.write(f"{name}Feedback.msg", generator.generate_data_msg(feedback_fields))
    writer.write(f"{name}ActionRequest.msg", generator.generate_request_msg())
    writer.write(f"{name}ActionResponse.msg", generator.generate_response_msg())
    writer.write(f"{name}ActionFeedback.msg", generator.generate_feedback_msg())


if __name__ == "__main__":
    main()

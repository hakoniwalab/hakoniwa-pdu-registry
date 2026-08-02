import os


class ActionContext:
    def __init__(self, action_file_path, header_package_name=None):
        if not os.path.isfile(action_file_path):
            raise ValueError(
                f"Error: '{action_file_path}' is not a valid .action file "
                "(file does not exist or is not a regular file)."
            )
        if not action_file_path.endswith(".action"):
            raise ValueError(f"Error: '{action_file_path}' must have a .action extension.")

        self.action_file_path = action_file_path
        self.action_name = os.path.splitext(os.path.basename(action_file_path))[0]
        self.action_package_name = os.path.basename(os.path.dirname(action_file_path))
        # Keep generated Action bodies and packets in an Action-specific ROS
        # package.  The shared protocol headers remain in hako_action_msgs and
        # are referenced with an explicit package qualifier by MsgGenerator.
        self.msg_package_name = f"{self.action_package_name}_action_msgs"
        self.header_package_name = header_package_name or os.getenv(
            "HAKO_ACTION_HEADER_PKG", "hako_action_msgs"
        )

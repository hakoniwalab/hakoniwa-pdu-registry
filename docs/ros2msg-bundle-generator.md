# ROS 2 `.msg` schema bundle generator

`hakoniwa-pdu-registry` can generate a self-contained `ros2msg` schema bundle directly from ROS 2 `.msg` source files.

The generated format is suitable for schema-aware consumers such as Foxglove and MCAP. The top-level `.msg` definition is followed by all transitive message dependencies using the standard delimiter form:

```text
================================================================================
MSG: package/Type
```

The dependency label intentionally uses the same two-part `package/Type` form that appears inside ROS 2 `.msg` field definitions. For example, a field declared as `std_msgs/Header header` is paired with `MSG: std_msgs/Header`. The internal resolver may normalize types to `package/msg/Type`, but that canonical lookup form is not written into the concatenated schema bundle.

The generator is intentionally source-based:

- no ROS 2 Python message bindings are imported;
- no interface package is compiled;
- no PDU offset calculation or C/C++ compilation is run;
- unresolved dependencies are errors rather than silently producing a partial bundle.

## Recommended: run from any host directory through Docker

The host-side wrapper uses the pinned `hakoniwa-pdu-registry` Docker image and exits after generating the file. You do not need to open an interactive shell in the container.

For example, from a sibling `hakoniwa-pdu-foxglove` checkout:

```bash
bash ../hakoniwa-pdu-registry/tools/generate_ros2msg_bundle.bash \
  sensor_msgs/JointState \
  -o ./work/schemas/ros2_jazzy/sensor_msgs/msg/JointState.bundle.msg
```

The wrapper:

1. locates the registry Docker image from `docker/image_name.txt` and `docker/latest_version.txt`;
2. pulls the image automatically when it is not available locally;
3. mounts the registry read-only;
4. mounts the requested output directory;
5. searches the ROS 2 message packages installed in the image plus the registry `idl/` tree;
6. runs `tools/generate_ros2msg_bundle.py` inside the container;
7. writes the generated bundle directly to the host path supplied with `-o`.

On Apple Silicon macOS, the wrapper uses `linux/amd64`, matching the existing registry Docker workflow.

## Custom message packages

Additional host-side message roots can be mounted with repeatable `--search-path` options. A search root must contain paths such as `<package>/msg/<Type>.msg`.

```bash
bash ../hakoniwa-pdu-registry/tools/generate_ros2msg_bundle.bash \
  my_msgs/msg/MyMessage \
  --search-path ../my_ros_interfaces/install/share \
  -o ./work/schemas/MyMessage.bundle.msg
```

The default search order is:

1. `/opt/ros/<ROS_VERSION>/share` inside the registry Docker image;
2. `hakoniwa-pdu-registry/idl`;
3. any extra `--search-path` directories in command-line order.

## Direct Python use

The underlying generator is standard-library-only and can also be run directly when the required `.msg` source trees already exist on the host:

```bash
python3 tools/generate_ros2msg_bundle.py \
  sensor_msgs/JointState \
  --search-path /path/to/ros/share \
  --search-path ./idl \
  -o JointState.bundle.msg
```

Accepted top-level type names are both:

```text
sensor_msgs/JointState
sensor_msgs/msg/JointState
```

The resolver handles transitive dependencies, same-package message references, arrays, bounded arrays, strings, and bounded strings. Each dependency is emitted once in deterministic dependency-discovery order.

## Responsibility boundary

This tool belongs in `hakoniwa-pdu-registry` because the registry already owns ROS 2 `.msg` inputs and dependency resolution. Consumers such as `hakoniwa-pdu-foxglove` should stage the generated schema bundle in their local work area rather than hand-maintaining concatenated message definitions.

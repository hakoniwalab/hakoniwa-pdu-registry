builtin_interfaces/Time stamp     # 箱庭の時刻
string self_name                  # "Person-3"
string other_name                 # "Car-1"、建物なら "static"
string other_kind                 # "vehicle" | "person" | "static"
geometry_msgs/Point position      # 接触の位置（City World の座標）
float64 relative_speed            # 接触したときの相対速度 m/s
bool started                      # true: 接触の始まり、false: 離れた

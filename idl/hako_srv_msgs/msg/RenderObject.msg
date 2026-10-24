# 描画サーバーが描く動く物 1 つ（hako_srv RenderCameraFrame の頼みに付ける）
# name: 物の名前。同じ物は頼みをまたいで同じ名前（物ごとのモーションブラーで前の姿勢とつなぐ）
# model: 描く形の名前（描画サーバーがモデルを引く名前。例：車の型）
# pose: 頼みの時刻の姿勢。camera_pose と同じ世界座標（ROS の決まり：右手系、m）。原点は描画サーバーのモデルの定義による
string name
string model
geometry_msgs/Pose pose

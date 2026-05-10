class_name HakoPdu_nav_msgs_GridCells
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const PointScript = preload("../geometry_msgs/Point.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var cell_width: float = 0.0
var cell_height: float = 0.0
var cells: Array = []

static func from_dict(d: Dictionary) -> HakoPdu_nav_msgs_GridCells:
    var obj := HakoPdu_nav_msgs_GridCells.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("cell_width"):
        obj.cell_width = d["cell_width"]
    if d.has("cell_height"):
        obj.cell_height = d["cell_height"]
    if d.has("cells"):
        obj.cells = []
        for item in d["cells"]:
            obj.cells.append(PointScript.from_dict(item))
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["cell_width"] = cell_width
    d["cell_height"] = cell_height
    var cells_array: Array = []
    for item in cells:
        cells_array.append(item.to_dict())
    d["cells"] = cells_array
    return d

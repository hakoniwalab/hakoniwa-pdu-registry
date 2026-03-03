using Hakoniwa.Pdu.CSharpV2.hako_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;

namespace CSharpV2Smoke;

internal static class Program
{
    private static void Main()
    {
        RunGameControllerOperationRoundtrip();
        RunDisturbanceUserCustomRoundtrip();
        RunDisturbanceRoundtrip();
        RunSimpleStructVarrayRoundtrip();
        RunJointStateRoundtrip();
        RunPointCloud2Roundtrip();
    }

    private static void RunGameControllerOperationRoundtrip()
    {
        var src = new GameControllerOperation
        {
            axis = new List<double> { 1.25, -2.5, 3.75, -4.0, 5.5, 6.25 },
            button = new List<bool>
            {
                true, false, true, false, true,
                false, true, false, true, false,
                true, false, true, false, true
            }
        };

        var binary = GameControllerOperationConverter.MsgToPdu(src);
        var dst = GameControllerOperationConverter.PduToMsg(binary);

        AssertEqual(src.axis.Count, dst.axis.Count, "GameControllerOperation.axis.Count");
        for (var i = 0; i < src.axis.Count; i++) {
            AssertNearlyEqual(src.axis[i], dst.axis[i], $"GameControllerOperation.axis[{i}]");
        }

        AssertEqual(src.button.Count, dst.button.Count, "GameControllerOperation.button.Count");
        for (var i = 0; i < src.button.Count; i++) {
            AssertEqual(src.button[i], dst.button[i], $"GameControllerOperation.button[{i}]");
        }
    }

    private static void RunDisturbanceUserCustomRoundtrip()
    {
        var cases = new[]
        {
            new DisturbanceUserCustom { data = new List<double>() },
            new DisturbanceUserCustom { data = new List<double> { 3.75 } },
            new DisturbanceUserCustom { data = new List<double> { 1.25, 2.5 } },
        };

        for (var caseIndex = 0; caseIndex < cases.Length; caseIndex++) {
            var src = cases[caseIndex];
            var binary = DisturbanceUserCustomConverter.MsgToPdu(src);
            var dst = DisturbanceUserCustomConverter.PduToMsg(binary);

            AssertEqual(src.data.Count, dst.data.Count, $"DisturbanceUserCustom[{caseIndex}].data.Count");
            for (var i = 0; i < src.data.Count; i++) {
                AssertNearlyEqual(src.data[i], dst.data[i], $"DisturbanceUserCustom[{caseIndex}].data[{i}]");
            }
        }
    }

    private static void RunDisturbanceRoundtrip()
    {
        var cases = new[]
        {
            new Disturbance
            {
                d_temp = new DisturbanceTemperature { value = 10.5 },
                d_wind = new DisturbanceWind { value = new Vector3 { x = 1.0, y = -2.0, z = 3.5 } },
                d_atm = new DisturbanceAtm { sea_level_atm = 1008.25 },
                d_boundary = new DisturbanceBoundary
                {
                    boundary_point = new Point { x = 4.0, y = 5.0, z = 6.0 },
                    boundary_normal = new Vector3 { x = -1.0, y = 0.5, z = 0.25 }
                },
                d_user_custom = new List<DisturbanceUserCustom>()
            },
            new Disturbance
            {
                d_temp = new DisturbanceTemperature { value = 11.5 },
                d_wind = new DisturbanceWind { value = new Vector3 { x = 2.0, y = -3.0, z = 4.5 } },
                d_atm = new DisturbanceAtm { sea_level_atm = 1009.25 },
                d_boundary = new DisturbanceBoundary
                {
                    boundary_point = new Point { x = 7.0, y = 8.0, z = 9.0 },
                    boundary_normal = new Vector3 { x = -0.5, y = 1.5, z = 2.25 }
                },
                d_user_custom = new List<DisturbanceUserCustom>
                {
                    new DisturbanceUserCustom { data = new List<double> { 3.75 } }
                }
            },
            new Disturbance
            {
                d_temp = new DisturbanceTemperature { value = 12.5 },
                d_wind = new DisturbanceWind { value = new Vector3 { x = 3.0, y = -4.0, z = 5.5 } },
                d_atm = new DisturbanceAtm { sea_level_atm = 1010.25 },
                d_boundary = new DisturbanceBoundary
                {
                    boundary_point = new Point { x = 10.0, y = 11.0, z = 12.0 },
                    boundary_normal = new Vector3 { x = -2.0, y = 2.5, z = 3.25 }
                },
                d_user_custom = new List<DisturbanceUserCustom>
                {
                    new DisturbanceUserCustom { data = new List<double> { 1.25, 2.5 } },
                    new DisturbanceUserCustom { data = new List<double> { 3.75 } }
                }
            }
        };

        for (var caseIndex = 0; caseIndex < cases.Length; caseIndex++) {
            var src = cases[caseIndex];
            var binary = DisturbanceConverter.MsgToPdu(src);
            var dst = DisturbanceConverter.PduToMsg(binary);

            AssertNearlyEqual(src.d_temp.value, dst.d_temp.value, $"Disturbance[{caseIndex}].d_temp.value");
            AssertVector3(src.d_wind.value, dst.d_wind.value, $"Disturbance[{caseIndex}].d_wind.value");
            AssertNearlyEqual(src.d_atm.sea_level_atm, dst.d_atm.sea_level_atm, $"Disturbance[{caseIndex}].d_atm.sea_level_atm");
            AssertPoint(src.d_boundary.boundary_point, dst.d_boundary.boundary_point, $"Disturbance[{caseIndex}].d_boundary.boundary_point");
            AssertVector3(src.d_boundary.boundary_normal, dst.d_boundary.boundary_normal, $"Disturbance[{caseIndex}].d_boundary.boundary_normal");
            AssertEqual(src.d_user_custom.Count, dst.d_user_custom.Count, $"Disturbance[{caseIndex}].d_user_custom.Count");
            for (var i = 0; i < src.d_user_custom.Count; i++) {
                AssertEqual(src.d_user_custom[i].data.Count, dst.d_user_custom[i].data.Count, $"Disturbance[{caseIndex}].d_user_custom[{i}].data.Count");
                for (var j = 0; j < src.d_user_custom[i].data.Count; j++) {
                    AssertNearlyEqual(src.d_user_custom[i].data[j], dst.d_user_custom[i].data[j], $"Disturbance[{caseIndex}].d_user_custom[{i}].data[{j}]");
                }
            }
        }
    }

    private static void RunSimpleStructVarrayRoundtrip()
    {
        var cases = new[]
        {
            new SimpleStructVarray
            {
                aaa = 10,
                fixed_str = new List<string> { "alpha", "beta" },
                varray_str = new List<string>(),
                fixed_array = new List<SimpleVarray>
                {
                    CreateSimpleVarray(new sbyte[] {}, new sbyte[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }, 100),
                    CreateSimpleVarray(new sbyte[] { 1 }, new sbyte[] { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 }, 101),
                    CreateSimpleVarray(new sbyte[] { 1, 2 }, new sbyte[] { 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 }, 102),
                    CreateSimpleVarray(new sbyte[] {}, new sbyte[] { 31, 32, 33, 34, 35, 36, 37, 38, 39, 40 }, 103),
                    CreateSimpleVarray(new sbyte[] { 3 }, new sbyte[] { 41, 42, 43, 44, 45, 46, 47, 48, 49, 50 }, 104),
                },
                data = new List<SimpleVarray>()
            },
            new SimpleStructVarray
            {
                aaa = 20,
                fixed_str = new List<string> { "gamma", "delta" },
                varray_str = new List<string> { "one" },
                fixed_array = new List<SimpleVarray>
                {
                    CreateSimpleVarray(new sbyte[] { 1 }, new sbyte[] { 51, 52, 53, 54, 55, 56, 57, 58, 59, 60 }, 200),
                    CreateSimpleVarray(new sbyte[] {}, new sbyte[] { 61, 62, 63, 64, 65, 66, 67, 68, 69, 70 }, 201),
                    CreateSimpleVarray(new sbyte[] { 2 }, new sbyte[] { 71, 72, 73, 74, 75, 76, 77, 78, 79, 80 }, 202),
                    CreateSimpleVarray(new sbyte[] { 3, 4 }, new sbyte[] { 81, 82, 83, 84, 85, 86, 87, 88, 89, 90 }, 203),
                    CreateSimpleVarray(new sbyte[] {}, new sbyte[] { 91, 92, 93, 94, 95, 96, 97, 98, 99, 100 }, 204),
                },
                data = new List<SimpleVarray>
                {
                    CreateSimpleVarray(new sbyte[] { 5 }, new sbyte[] { 101, 102, 103, 104, 105, 106, 107, 108, 109, 110 }, 300),
                }
            },
            new SimpleStructVarray
            {
                aaa = 30,
                fixed_str = new List<string> { "epsilon", "zeta" },
                varray_str = new List<string> { "first", "second" },
                fixed_array = new List<SimpleVarray>
                {
                    CreateSimpleVarray(new sbyte[] {}, new sbyte[] { 111, 112, 113, 114, 115, 116, 117, 118, 119, 120 }, 400),
                    CreateSimpleVarray(new sbyte[] { 6 }, new sbyte[] { 121, 122, 123, 124, 125, 126, 127, -128, -127, -126 }, 401),
                    CreateSimpleVarray(new sbyte[] { 7, 8 }, new sbyte[] { -125, -124, -123, -122, -121, -120, -119, -118, -117, -116 }, 402),
                    CreateSimpleVarray(new sbyte[] {}, new sbyte[] { -115, -114, -113, -112, -111, -110, -109, -108, -107, -106 }, 403),
                    CreateSimpleVarray(new sbyte[] { 9 }, new sbyte[] { -105, -104, -103, -102, -101, -100, -99, -98, -97, -96 }, 404),
                },
                data = new List<SimpleVarray>
                {
                    CreateSimpleVarray(new sbyte[] {}, new sbyte[] { -95, -94, -93, -92, -91, -90, -89, -88, -87, -86 }, 500),
                    CreateSimpleVarray(new sbyte[] { 10, 11 }, new sbyte[] { -85, -84, -83, -82, -81, -80, -79, -78, -77, -76 }, 501),
                }
            }
        };

        for (var caseIndex = 0; caseIndex < cases.Length; caseIndex++) {
            var src = cases[caseIndex];
            var binary = SimpleStructVarrayConverter.MsgToPdu(src);
            var dst = SimpleStructVarrayConverter.PduToMsg(binary);

            AssertEqual(src.aaa, dst.aaa, $"SimpleStructVarray[{caseIndex}].aaa");
            AssertStringList(src.fixed_str, dst.fixed_str, $"SimpleStructVarray[{caseIndex}].fixed_str");
            AssertStringList(src.varray_str, dst.varray_str, $"SimpleStructVarray[{caseIndex}].varray_str");
            AssertEqual(src.fixed_array.Count, dst.fixed_array.Count, $"SimpleStructVarray[{caseIndex}].fixed_array.Count");
            for (var i = 0; i < src.fixed_array.Count; i++) {
                AssertSimpleVarray(src.fixed_array[i], dst.fixed_array[i], $"SimpleStructVarray[{caseIndex}].fixed_array[{i}]");
            }
            AssertEqual(src.data.Count, dst.data.Count, $"SimpleStructVarray[{caseIndex}].data.Count");
            for (var i = 0; i < src.data.Count; i++) {
                AssertSimpleVarray(src.data[i], dst.data[i], $"SimpleStructVarray[{caseIndex}].data[{i}]");
            }
        }
    }

    private static void RunJointStateRoundtrip()
    {
        var cases = new[]
        {
            new JointState
            {
                header = CreateHeader(1, 100, "joint-0"),
                name = new List<string>(),
                position = new List<double>(),
                velocity = new List<double>(),
                effort = new List<double>()
            },
            new JointState
            {
                header = CreateHeader(2, 200, "joint-1"),
                name = new List<string> { "shoulder" },
                position = new List<double> { 1.25 },
                velocity = new List<double> { -0.5 },
                effort = new List<double> { 3.0 }
            },
            new JointState
            {
                header = CreateHeader(3, 300, "joint-2"),
                name = new List<string> { "shoulder", "elbow" },
                position = new List<double> { 1.25, -2.5 },
                velocity = new List<double> { -0.5, 0.75 },
                effort = new List<double> { 3.0, -4.25 }
            }
        };

        for (var caseIndex = 0; caseIndex < cases.Length; caseIndex++) {
            var src = cases[caseIndex];
            var binary = JointStateConverter.MsgToPdu(src);
            var dst = JointStateConverter.PduToMsg(binary);

            AssertHeader(src.header, dst.header, $"JointState[{caseIndex}].header");
            AssertStringList(src.name, dst.name, $"JointState[{caseIndex}].name");
            AssertDoubleList(src.position, dst.position, $"JointState[{caseIndex}].position");
            AssertDoubleList(src.velocity, dst.velocity, $"JointState[{caseIndex}].velocity");
            AssertDoubleList(src.effort, dst.effort, $"JointState[{caseIndex}].effort");
        }
    }

    private static void RunPointCloud2Roundtrip()
    {
        var cases = new[]
        {
            new PointCloud2
            {
                header = CreateHeader(10, 1000, "pc2-0"),
                height = 1,
                width = 0,
                fields = new List<PointField>(),
                is_bigendian = false,
                point_step = 16,
                row_step = 0,
                data = new List<byte>(),
                is_dense = true
            },
            new PointCloud2
            {
                header = CreateHeader(11, 1100, "pc2-1"),
                height = 1,
                width = 1,
                fields = new List<PointField>
                {
                    CreatePointField("x", 0, 7, 1)
                },
                is_bigendian = false,
                point_step = 16,
                row_step = 16,
                data = new List<byte> { 1 },
                is_dense = true
            },
            new PointCloud2
            {
                header = CreateHeader(12, 1200, "pc2-2"),
                height = 1,
                width = 2,
                fields = new List<PointField>
                {
                    CreatePointField("x", 0, 7, 1),
                    CreatePointField("intensity", 4, 7, 1)
                },
                is_bigendian = false,
                point_step = 16,
                row_step = 32,
                data = new List<byte> { 1, 2 },
                is_dense = false
            }
        };

        for (var caseIndex = 0; caseIndex < cases.Length; caseIndex++) {
            var src = cases[caseIndex];
            var binary = PointCloud2Converter.MsgToPdu(src);
            var dst = PointCloud2Converter.PduToMsg(binary);

            AssertHeader(src.header, dst.header, $"PointCloud2[{caseIndex}].header");
            AssertEqual(src.height, dst.height, $"PointCloud2[{caseIndex}].height");
            AssertEqual(src.width, dst.width, $"PointCloud2[{caseIndex}].width");
            AssertEqual(src.fields.Count, dst.fields.Count, $"PointCloud2[{caseIndex}].fields.Count");
            for (var i = 0; i < src.fields.Count; i++) {
                AssertPointField(src.fields[i], dst.fields[i], $"PointCloud2[{caseIndex}].fields[{i}]");
            }
            AssertEqual(src.is_bigendian, dst.is_bigendian, $"PointCloud2[{caseIndex}].is_bigendian");
            AssertEqual(src.point_step, dst.point_step, $"PointCloud2[{caseIndex}].point_step");
            AssertEqual(src.row_step, dst.row_step, $"PointCloud2[{caseIndex}].row_step");
            AssertByteList(src.data, dst.data, $"PointCloud2[{caseIndex}].data");
            AssertEqual(src.is_dense, dst.is_dense, $"PointCloud2[{caseIndex}].is_dense");
        }
    }

    private static SimpleVarray CreateSimpleVarray(IEnumerable<sbyte> data, IEnumerable<sbyte> fixedArray, int pMem1)
    {
        return new SimpleVarray
        {
            data = new List<sbyte>(data),
            fixed_array = new List<sbyte>(fixedArray),
            p_mem1 = pMem1
        };
    }

    private static Header CreateHeader(int sec, uint nanosec, string frameId)
    {
        return new Header
        {
            stamp = new Time { sec = sec, nanosec = nanosec },
            frame_id = frameId
        };
    }

    private static PointField CreatePointField(string name, uint offset, byte datatype, uint count)
    {
        return new PointField
        {
            name = name,
            offset = offset,
            datatype = datatype,
            count = count
        };
    }

    private static void AssertEqual<T>(T expected, T actual, string label)
    {
        if (!EqualityComparer<T>.Default.Equals(expected, actual)) {
            throw new InvalidOperationException($"{label}: expected={expected} actual={actual}");
        }
    }

    private static void AssertNearlyEqual(double expected, double actual, string label)
    {
        if (Math.Abs(expected - actual) > 1e-9) {
            throw new InvalidOperationException($"{label}: expected={expected} actual={actual}");
        }
    }

    private static void AssertPoint(Point expected, Point actual, string label)
    {
        AssertNearlyEqual(expected.x, actual.x, $"{label}.x");
        AssertNearlyEqual(expected.y, actual.y, $"{label}.y");
        AssertNearlyEqual(expected.z, actual.z, $"{label}.z");
    }

    private static void AssertVector3(Vector3 expected, Vector3 actual, string label)
    {
        AssertNearlyEqual(expected.x, actual.x, $"{label}.x");
        AssertNearlyEqual(expected.y, actual.y, $"{label}.y");
        AssertNearlyEqual(expected.z, actual.z, $"{label}.z");
    }

    private static void AssertStringList(IReadOnlyList<string> expected, IReadOnlyList<string> actual, string label)
    {
        AssertEqual(expected.Count, actual.Count, $"{label}.Count");
        for (var i = 0; i < expected.Count; i++) {
            AssertEqual(expected[i], actual[i], $"{label}[{i}]");
        }
    }

    private static void AssertDoubleList(IReadOnlyList<double> expected, IReadOnlyList<double> actual, string label)
    {
        AssertEqual(expected.Count, actual.Count, $"{label}.Count");
        for (var i = 0; i < expected.Count; i++) {
            AssertNearlyEqual(expected[i], actual[i], $"{label}[{i}]");
        }
    }

    private static void AssertByteList(IReadOnlyList<byte> expected, IReadOnlyList<byte> actual, string label)
    {
        AssertEqual(expected.Count, actual.Count, $"{label}.Count");
        for (var i = 0; i < expected.Count; i++) {
            AssertEqual(expected[i], actual[i], $"{label}[{i}]");
        }
    }

    private static void AssertSByteList(IReadOnlyList<sbyte> expected, IReadOnlyList<sbyte> actual, string label)
    {
        AssertEqual(expected.Count, actual.Count, $"{label}.Count");
        for (var i = 0; i < expected.Count; i++) {
            AssertEqual(expected[i], actual[i], $"{label}[{i}]");
        }
    }

    private static void AssertSimpleVarray(SimpleVarray expected, SimpleVarray actual, string label)
    {
        AssertSByteList(expected.data, actual.data, $"{label}.data");
        AssertSByteList(expected.fixed_array, actual.fixed_array, $"{label}.fixed_array");
        AssertEqual(expected.p_mem1, actual.p_mem1, $"{label}.p_mem1");
    }

    private static void AssertHeader(Header expected, Header actual, string label)
    {
        AssertEqual(expected.stamp.sec, actual.stamp.sec, $"{label}.stamp.sec");
        AssertEqual(expected.stamp.nanosec, actual.stamp.nanosec, $"{label}.stamp.nanosec");
        AssertEqual(expected.frame_id, actual.frame_id, $"{label}.frame_id");
    }

    private static void AssertPointField(PointField expected, PointField actual, string label)
    {
        AssertEqual(expected.name, actual.name, $"{label}.name");
        AssertEqual(expected.offset, actual.offset, $"{label}.offset");
        AssertEqual(expected.datatype, actual.datatype, $"{label}.datatype");
        AssertEqual(expected.count, actual.count, $"{label}.count");
    }
}

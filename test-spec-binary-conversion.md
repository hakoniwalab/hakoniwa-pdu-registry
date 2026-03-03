# バイナリ変換テスト仕様

## 目的

PDU バイナリ変換について、少なくとも以下を継続的に保証する。

1. C++ 実装が正解バイナリを生成していること
2. Python / JavaScript が C++ バイナリを正しく読めること
3. Python / JavaScript が生成したバイナリを読んだとき、C++ と同じメンバ値になること

ここでいう「仕様どおり」とは、以下を含む。

- field offset
- field size
- alignment / padding
- `varray` の `{len, off}`
- heap 配置
- primitive 型の byte 表現

加えて、`varray` を持つ型では `size=0` を必須テストケースとする。

`C++` を正とする heap 配置規則として、`struct varray` は次を満たすものとする。

- 要素固定部を `array_size * one_elm_size` で先に連続確保する
- 各要素の固定部は heap 上で連続配置する
- 各要素が保持する可変 payload は、その固定部領域の後ろに積む
- 各要素内の `{len, off}` は heap 先頭基準の offset とする

## 前提

本仕様では、以下の 3 者を扱う。

- C++
- Python
- JavaScript

加えて、`C# v2` は `offset` を実行時解釈しない generated converter 方式として別系統で検証する。

ただし、テストの正解系は C++ とする。

つまり、

- C++ が canonical input から正解 PDU を生成する
- Python / JavaScript はその C++ 生成バイナリを正しく decode できることを求める
- Python / JavaScript の encode 結果は、byte 完全一致ではなく decode 後のメンバ値一致を基準にする
- decode も C++ バイナリを読めることを基準にする

補足:

- fixed string の未使用領域や未定義 padding は、ゼロクリアを前提にしない
- そのため、言語間の判定は原則として「意味のあるメンバ値」で行う
- byte 完全一致は、未定義領域を含まないケースに限って任意で追加する
- `struct varray` の正解レイアウトは `C++` の `dynamic_memory.allocate(...)` による連続配置を基準とする

まずは既存メッセージを使ってテストを構成し、新規 fixture message の追加は後回しにする。

## 現在の実装状況

現時点で以下は実装済み。

### C++ オラクル比較

- `hako_msgs/GameControllerOperation`
- `hako_msgs/DisturbanceUserCustom`
- `hako_msgs/Disturbance`
- `sensor_msgs/JointState`
- `hako_msgs/SimpleStructVarray`
- `sensor_msgs/PointCloud2`

### `varray size=0 / 1 / 2` ケース

- `hako_msgs/DisturbanceUserCustom`
- `hako_msgs/Disturbance`
- `sensor_msgs/JointState`
- `hako_msgs/SimpleStructVarray`
- `sensor_msgs/PointCloud2`
- `sensor_msgs/LaserScan`
- `sensor_msgs/CameraInfo`
- `std_msgs/MultiArrayLayout`
- `std_msgs/Float64MultiArray`

### 現在の全体結果

- `python3 -m unittest tests.test_generated_artifacts`
- `41 tests`
- `OK`

### C# v2 実行 smoke

- `hako_msgs/GameControllerOperation`
- `hako_msgs/DisturbanceUserCustom`
- `hako_msgs/Disturbance`
- `hako_msgs/SimpleStructVarray`
- `sensor_msgs/JointState`
- `sensor_msgs/PointCloud2`

確認内容:

- generated type / converter のコンパイル
- `dotnet run` による encode/decode roundtrip
- `size=0 / 1 / 2`
- fixed array / `string[]` / struct `varray` / nested `varray`

## テストの基本構造

各テストカテゴリで、可能な限り以下の 5 種類を確認する。

### 1. C++ 仕様一致

対象:

- `cpp2pdu`
- `pdu2cpp`

確認内容:

- 期待バイト列
- `.offset` どおりの配置
- `heap_off`
- `total_size`
- `varray` の `{len, off}`
- heap payload

役割:

- C++ を正解実装として固定する

### 2. C++ -> Python decode

対象:

- C++ が生成した PDU を Python が読む

確認内容:

- 値が期待値と一致すること

### 3. C++ -> JavaScript decode

対象:

- C++ が生成した PDU を JavaScript が読む

確認内容:

- 値が期待値と一致すること

### 4. Python encode semantic match

対象:

- 同一 canonical input から Python が生成した PDU

確認内容:

- Python が生成した PDU を decode した結果が期待メンバ値と一致すること
- 必要に応じて C++ decode でも同じメンバ値になること

### 5. JavaScript encode semantic match

対象:

- 同一 canonical input から JavaScript が生成した PDU

確認内容:

- JavaScript が生成した PDU を decode した結果が期待メンバ値と一致すること
- 必要に応じて C++ decode でも同じメンバ値になること

### 6. 任意追加: 他言語 -> C++ decode

対象:

- Python / JavaScript が生成した PDU を C++ が読む

確認内容:

- 値が期待値と一致すること

備考:

- 初期フェーズでは必須ではない
- 必要になった段階で追加する
- このカテゴリが入ると、他言語 encode の semantic match を C++ 基準で直接確認できる

## テストカテゴリ

以下を基本カテゴリとする。

### A. primitive 型だけの構造体

狙い:

- primitive 型の byte 表現
- 基本 offset
- 基本 alignment

見るもの:

- `bool`
- `int8`, `uint8`
- `int16`, `uint16`
- `int32`, `uint32`
- `int64`, `uint64`
- `float32`, `float64`
- `string`

### B. 固定長配列を含む構造体

狙い:

- fixed array の配置
- 要素サイズ
- 後続 field の offset が壊れないこと

対象例:

- primitive fixed array
- fixed string array
- fixed struct array

### C. パディングが入る構造体

狙い:

- alignment / padding
- struct 全体サイズ
- 後続 field offset

### D. 階層的な構造体

狙い:

- struct 再帰変換
- 親子 struct の offset

### E. 構造体の fixed array / varray

狙い:

- struct array の要素境界
- struct varray の `{len, off}`
- heap 配置

### F. 構造体の中に primitive `varray`

狙い:

- primitive `varray` payload
- `{len, off}`
- heap 配置
- `size=0` のときに長さと offset が破綻しないこと

### G. 構造体の中に struct `varray`

狙い:

- heap 上の struct 配置
- struct 要素境界
- 再帰 read/write
- `size=0` のときに長さと offset が破綻しないこと

### H. 構造体の中に `string[]`

狙い:

- 固定幅 string 要素
- null terminator
- padding
- truncate 規則

対象:

- fixed `string[]`
- `varray string`

### I. nested `varray`

最重要カテゴリ。

狙い:

- `struct varray` の各要素がさらに `varray` を持つケース
- heap 内 struct の内部参照
- 言語間相互運用
- 外側または内側 `varray` が `size=0` のときに破綻しないこと

## `varray` の必須異常系

`varray` を持つすべての対象型で、少なくとも以下を確認する。

- `size=0`
- `size=1`
- 複数要素

`size=0` では少なくとも以下を確認する。

- `len == 0`
- decode 結果が空配列になる
- 後続 field や他の `varray` の offset を壊さない
- `total_size` / `heap_off` が不正にならない

## 既存メッセージへの割り当て

まずは以下の既存メッセージでテストする。

### Tier 1

- `hako_msgs/GameControllerOperation`
  - primitive fixed array
  - `bool[]`

- `hako_msgs/DisturbanceUserCustom`
  - primitive `varray`

- `hako_msgs/Disturbance`
  - nested `varray`
  - struct `varray`

- `sensor_msgs/JointState`
  - `string[] varray`
  - primitive `varray`

- `hako_msgs/SimpleStructVarray`
  - fixed `string[]`
  - `string[] varray`
  - fixed struct array
  - struct `varray`
  - nested `varray`

### Tier 2

- `sensor_msgs/PointCloud2`
  - struct `varray`
  - primitive `varray`

- `sensor_msgs/LaserScan`
  - primitive `varray`

- `sensor_msgs/CameraInfo`
  - fixed primitive array
  - primitive `varray`

- `std_msgs/Float64MultiArray`
  - primitive `varray`

- `std_msgs/MultiArrayLayout`
  - struct `varray`

## 各カテゴリで最低限見る項目

### primitive

- expected bytes
- read/write 一致
- Python / JavaScript 一致

### fixed array

- 配列長
- 総 byte 数
- 後続 field offset

### padding

- field 間 padding
- struct end の alignment

### `varray`

- `len`
- `off`
- heap payload
- empty / 1 要素 / 複数要素

### string

- null terminator
- 固定幅
- 0 埋め
- truncate

### nested `varray`

- 親の `off`
- 子要素の base 領域
- 子要素内 `varray` の `off`
- Python / JavaScript encode semantic match

## テストデータ方針

テスト値は各ケースで以下を優先する。

- 0
- 正値
- 負値
- 複数要素
- 空配列
- 1 要素配列
- 長さの異なる複数文字列
- 文字列長が固定幅未満 / 近傍

特に `varray` 系は必ず以下を含める。

- empty
- 1 要素
- 2 要素以上

## 異常系

正常系が固まった後に、以下を追加する。

- 不正 magic number
- 不正 version
- 不正 `heap_off`
- 不正 `total_size`
- 範囲外 offset
- 期待固定長を超える string
- `fromDict()` / `fromJSON()` の不正入力

## 実装方針

各メッセージについて、以下の形で実装する。

### C++ 側

- `tests/cpp/<msg>_cpp_interop_test.cpp`
  - GoogleTest
  - C++ 単独で layout/spec を固定する

- `tests/cpp/<msg>_cpp_dump.cpp`
  - canonical input を C++ で構築する
  - PDU バイナリを出力する

### Python 側ハブ

- `generators/generate_hako_pdu_msgs/validate_generated_artifacts.py`
  - C++ dump ツールを呼ぶ
  - Python decode
  - JavaScript decode
  - Python encode
  - JavaScript encode
  - C++ 基準のメンバ比較

- `tests/test_generated_artifacts.py`
  - unittest として pass/fail を固定する

## テスト実行手順

基本的な確認は以下の順で行う。

### 1. Python / JavaScript ハブテスト

```bash
python3 -m unittest tests.test_generated_artifacts
```

役割:

- `C++ -> Python / JavaScript` decode
- `Python / JavaScript` encode semantic match
- `varray size=0 / 1 / 2` ケース

### 2. C++ オラクルテスト

```bash
cmake -S tests/cpp -B /tmp/hako-pdu-cpp-tests
cmake --build /tmp/hako-pdu-cpp-tests -j4
ctest --test-dir /tmp/hako-pdu-cpp-tests --output-on-failure
```

役割:

- C++ 単独の layout/spec 固定
- `cpp2pdu`
- `pdu2cpp`

### 3. C# v2 実行 smoke

```bash
python3 -m unittest tests.test_csharp_v2_generator
python3 -m unittest tests.test_csharp_v2_runtime
dotnet run --no-restore --project tests/csharp_v2_smoke/CSharpV2Smoke.csproj
```

役割:

- `csharp_v2` generated converter の静的生成確認
- `C# v2` の実行 roundtrip
- `size=0 / 1 / 2`
- fixed / string / struct / nested `varray`

### 4. 個別メッセージの確認

必要に応じて、対象メッセージの unittest だけを抜き出して確認する。

例:

```bash
python3 -m unittest \
  tests.test_generated_artifacts.GeneratedArtifactsTest.test_simple_struct_varray_cpp_oracle_interop \
  tests.test_generated_artifacts.GeneratedArtifactsTest.test_simple_struct_varray_python_encode_size_0_case \
  tests.test_generated_artifacts.GeneratedArtifactsTest.test_simple_struct_varray_python_encode_size_1_case \
  tests.test_generated_artifacts.GeneratedArtifactsTest.test_simple_struct_varray_python_encode_size_2_case
```

```bash
ctest --test-dir /tmp/hako-pdu-cpp-tests --output-on-failure -R SimpleStructVarrayCppInteropTest
```

### 5. 再生成後の確認順

テンプレートや generator を修正して再生成した場合は、次の順で確認する。

1. 変更対象メッセージの個別 unittest
2. 対応する C++ oracle test
3. `python3 -m unittest tests.test_generated_artifacts`
4. `python3 -m unittest tests.test_csharp_v2_generator tests.test_csharp_v2_runtime`

## 実装順

初期計画は次の順だった。

### Phase 1

- `Disturbance`

### Phase 2

- `JointState`
- `SimpleStructVarray`

### Phase 3

- `GameControllerOperation`
- `DisturbanceUserCustom`
- `PointCloud2`
- `LaserScan`
- `CameraInfo`
- `Float64MultiArray`
- `MultiArrayLayout`

現在は Phase 3 まで実装済み。

## C# v2 補足

- `C# v2` は `pdu/csharp_v2` に生成する
- `offset` ファイルを runtime で解釈せず、message ごとの generated converter を使う
- 既存 `pdu/csharp` とは別系統で並行運用する
- 現在の残課題は、生成 converter の重複 `using` warning を減らすこと

## 完了条件

以下を満たしたら、最初のテスト仕様として成立とみなす。

1. Tier 1 メッセージすべてに C++ layout/spec テストがある
2. Tier 1 メッセージすべてに `C++ -> Python` / `C++ -> JavaScript` decode テストがある
3. Tier 1 メッセージすべてに `C++ -> Python/JavaScript decode` と `Python/JavaScript encode semantic match` テストがある
4. `primitive`, `fixed array`, `padding`, `string`, `varray`, `nested varray` を既存メッセージで網羅している
5. 失敗時に少なくとも対象 field と実際の値差分を追える

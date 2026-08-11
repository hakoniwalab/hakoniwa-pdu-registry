import json
import shutil
import subprocess
import tempfile
import unittest
from pathlib import Path

from pdu.python.binary_io import PduMetaDataState, classify_pdu_metadata


class PduMetaDataClassifierTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.repo_root = Path(__file__).resolve().parents[1]
        contract_path = cls.repo_root / "tests/fixtures/pdu_metadata_classifier.json"
        cls.contract = json.loads(contract_path.read_text())
        cls.states = cls.contract["states"]

    @staticmethod
    def data_for(case):
        value = case["bytes_hex"]
        return None if value is None else bytes.fromhex(value)

    def test_python_classifier_matches_shared_vectors(self):
        for case in self.contract["cases"]:
            with self.subTest(case=case["name"]):
                actual = classify_pdu_metadata(self.data_for(case))
                self.assertEqual(int(actual), self.states[case["expected"]])

        self.assertEqual(int(PduMetaDataState.INVALID), 0)
        self.assertEqual(int(PduMetaDataState.UNINITIALIZED), 1)
        self.assertEqual(int(PduMetaDataState.VALID), 2)

    def test_javascript_classifier_matches_shared_vectors(self):
        if shutil.which("node") is None:
            self.skipTest("node is not available")
        script = r"""
import { classifyPduMetadata } from './pdu/javascript/pdu_utils.js';
const value = process.argv[1] === 'null' ? null : Uint8Array.from(Buffer.from(process.argv[1], 'hex'));
console.log(classifyPduMetadata(value));
"""
        for case in self.contract["cases"]:
            value = "null" if case["bytes_hex"] is None else case["bytes_hex"]
            result = subprocess.run(
                ["node", "--input-type=module", "-e", script, value],
                cwd=self.repo_root,
                check=True,
                capture_output=True,
                text=True,
            )
            self.assertEqual(int(result.stdout.strip()), self.states[case["expected"]], case["name"])

    def test_ruby_classifier_matches_shared_vectors(self):
        if shutil.which("ruby") is None:
            self.skipTest("ruby is not available")
        script = r"""
require 'pdu_runtime'
value = ARGV[0] == 'null' ? nil : [ARGV[0]].pack('H*')
puts HakoPdu::Runtime.classify_pdu_metadata(value)
"""
        for case in self.contract["cases"]:
            value = "null" if case["bytes_hex"] is None else case["bytes_hex"]
            result = subprocess.run(
                ["ruby", "-I./pdu/ruby", "-e", script, value],
                cwd=self.repo_root,
                check=True,
                capture_output=True,
                text=True,
            )
            self.assertEqual(int(result.stdout.strip()), self.states[case["expected"]], case["name"])

    def test_elixir_classifier_matches_shared_vectors(self):
        if shutil.which("elixir") is None:
            self.skipTest("elixir is not available")
        script = r"""
value = case List.first(System.argv()) do
  "null" -> nil
  hex -> Base.decode16!(hex, case: :mixed)
end
IO.puts(HakoPdu.Runtime.classify_pdu_metadata(value))
"""
        for case in self.contract["cases"]:
            value = "null" if case["bytes_hex"] is None else case["bytes_hex"]
            result = subprocess.run(
                ["elixir", "-r", "pdu/elixir/pdu_runtime.ex", "-e", script, value],
                cwd=self.repo_root,
                check=True,
                capture_output=True,
                text=True,
            )
            self.assertEqual(int(result.stdout.strip()), self.states[case["expected"]], case["name"])

    def test_c_classifier_matches_shared_vectors(self):
        compiler = shutil.which("cc") or shutil.which("clang") or shutil.which("gcc")
        if compiler is None:
            self.skipTest("C compiler is not available")
        source = r'''
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pdu/types/pdu_primitive_ctypes.h"

static unsigned char from_hex(char value) {
    if (value >= '0' && value <= '9') return (unsigned char)(value - '0');
    if (value >= 'a' && value <= 'f') return (unsigned char)(value - 'a' + 10);
    return (unsigned char)(value - 'A' + 10);
}

int main(int argc, char **argv) {
    unsigned char *data = NULL;
    size_t size = 0;
    size_t index;
    if (argc != 2) return 2;
    if (strcmp(argv[1], "null") != 0) {
        size = strlen(argv[1]) / 2;
        data = (unsigned char*)malloc(size == 0 ? 1 : size);
        if (data == NULL) return 3;
        for (index = 0; index < size; ++index) {
            data[index] = (unsigned char)((from_hex(argv[1][index * 2]) << 4) | from_hex(argv[1][index * 2 + 1]));
        }
    }
    printf("%d\n", (int)hako_pdu_classify_metadata(data, size));
    free(data);
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as tmp:
            source_path = Path(tmp) / "classifier.c"
            executable = Path(tmp) / "classifier"
            source_path.write_text(source)
            subprocess.run(
                [compiler, "-std=c11", "-I", str(self.repo_root), str(source_path), "-o", str(executable)],
                check=True,
                capture_output=True,
                text=True,
            )
            for case in self.contract["cases"]:
                value = "null" if case["bytes_hex"] is None else case["bytes_hex"]
                result = subprocess.run([str(executable), value], check=True, capture_output=True, text=True)
                self.assertEqual(int(result.stdout.strip()), self.states[case["expected"]], case["name"])


if __name__ == "__main__":
    unittest.main()

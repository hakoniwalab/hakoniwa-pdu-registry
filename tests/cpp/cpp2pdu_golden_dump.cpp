// Writes the cpp2pdu golden files: cpp2pdu_golden_dump <dir> writes
// <dir>/<case>.bin for every case of cpp2pdu_cases.hpp.
//
// The files in tests/fixtures/cpp2pdu_golden were made with the converters
// before the PDU was built straight into the caller's buffer (commit a76bd47),
// so cpp2pdu_golden_test.cpp checks the new converters against the old ones.
// The old converters left some bytes unset (struct padding from an
// uninitialized stack struct; malloc'd heap blocks such as the rest of a
// fixed-size string), which differ from run to run. To make those zero, as the
// new converters write them, the old build (headers of commit a76bd47) was
//   g++ -O2 -std=c++17 -ftrivial-auto-var-init=zero \
//       -include tests/cpp/cpp2pdu_golden_zero_malloc.h -I<old pdu/types> \
//       tests/cpp/cpp2pdu_golden_dump.cpp -o dump_old
// (stack variables zeroed; every malloc of the old converters made a calloc).
// Three runs gave the same files, and the new converters match them all.
#include <cstdio>
#include <string>

#include "cpp2pdu_cases.hpp"

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::fprintf(stderr, "usage: cpp2pdu_golden_dump <dir>\n");
        return 2;
    }
    for (const auto& c : cpp2pdu_cases::All()) {
        const std::vector<char> pdu = c.make();
        if (pdu.empty()) {
            std::fprintf(stderr, "%s: cpp2pdu failed\n", c.name.c_str());
            return 1;
        }
        const std::string path = std::string(argv[1]) + "/" + c.name + ".bin";
        std::FILE* f = std::fopen(path.c_str(), "wb");
        if (f == nullptr || std::fwrite(pdu.data(), 1, pdu.size(), f) != pdu.size()) {
            std::fprintf(stderr, "%s: cannot write\n", path.c_str());
            return 1;
        }
        std::fclose(f);
        std::printf("%s %zu\n", c.name.c_str(), pdu.size());
    }
    return 0;
}

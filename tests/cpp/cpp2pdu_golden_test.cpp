// The converters must keep producing, byte for byte, the PDUs the converters
// made before the PDU was built straight into the caller's buffer (the golden
// files, see cpp2pdu_golden_dump.cpp for how they were made). Strictly, the
// match is with the old converters whose unset bytes (struct padding, the rest
// of a fixed string) are made zero: those bytes were never defined before.
#include <gtest/gtest.h>

#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include "cpp2pdu_cases.hpp"

#ifndef CPP2PDU_GOLDEN_DIR
#error "CPP2PDU_GOLDEN_DIR must name tests/fixtures/cpp2pdu_golden"
#endif

namespace {

std::vector<char> ReadFile(const std::string& path)
{
    std::ifstream in(path, std::ios::binary);
    return std::vector<char>(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
}

TEST(Cpp2PduGoldenTest, SameBytesAsBeforeTheDirectWrite)
{
    const auto cases = cpp2pdu_cases::All();
    ASSERT_FALSE(cases.empty());
    for (const auto& c : cases) {
        const std::vector<char> golden = ReadFile(std::string(CPP2PDU_GOLDEN_DIR) + "/" + c.name + ".bin");
        ASSERT_FALSE(golden.empty()) << c.name << ": no golden file";
        const std::vector<char> pdu = c.make();
        ASSERT_EQ(pdu.size(), golden.size()) << c.name;
        EXPECT_TRUE(pdu == golden) << c.name;
    }
}

}  // namespace

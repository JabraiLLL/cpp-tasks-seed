#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "base85ed.h"

static std::vector<uint8_t> cstr2v(const char* s)
{
    return std::vector<uint8_t>(s, s + std::string(s).length());
}

TEST(Base85Extended, EncodeDecodeEmptyString)
{
    std::vector<uint8_t> empty;
    EXPECT_EQ(base85::encode(empty), empty);
    EXPECT_EQ(base85::decode(empty), empty);
}

TEST(Base85Extended, EncodeDecodeSingleChar)
{
    for (char c = 'a'; c <= 'z'; ++c)
    {
        std::string s(1, c);
        auto encoded = base85::encode(cstr2v(s.c_str()));
        auto decoded = base85::decode(encoded);
        EXPECT_EQ(cstr2v(s.c_str()), decoded);
    }
}

TEST(Base85Extended, EncodeDecodeTwoChars)
{
    std::vector<std::string> cases = { "ab", "cd", "12", "xy", "!!" };
    for (const auto& s : cases)
    {
        auto encoded = base85::encode(cstr2v(s.c_str()));
        auto decoded = base85::decode(encoded);
        EXPECT_EQ(cstr2v(s.c_str()), decoded);
    }
}

TEST(Base85Extended, EncodeDecodeThreeChars)
{
    std::vector<std::string> cases = { "abc", "123", "xyz", "!@#" };
    for (const auto& s : cases)
    {
        auto encoded = base85::encode(cstr2v(s.c_str()));
        auto decoded = base85::decode(encoded);
        EXPECT_EQ(cstr2v(s.c_str()), decoded);
    }
}

TEST(Base85Extended, EncodeDecodeFourChars)
{
    std::vector<std::string> cases = { "abcd", "1234", "wxyz", "!@#$" };
    for (const auto& s : cases)
    {
        auto encoded = base85::encode(cstr2v(s.c_str()));
        auto decoded = base85::decode(encoded);
        EXPECT_EQ(cstr2v(s.c_str()), decoded);
    }
}

TEST(Base85Extended, EncodeDecodeVariousLengths)
{
    std::vector<std::string> test_strings =
    {
        "Hello",
        "Hello, World!",
        "The quick brown fox jumps over the lazy dog",
        "1234567890",
        std::string(10, 'a'),
        std::string(20, 'b'),
        std::string(50, 'c'),
        std::string(100, 'd'),
        std::string(200, 'e'),
        std::string(500, 'f'),
        std::string(1000, 'g')
    };
    for (const auto& test_str : test_strings)
    {
        std::vector<uint8_t> original(test_str.begin(), test_str.end());
        auto encoded = base85::encode(original);
        auto decoded = base85::decode(encoded);
        EXPECT_EQ(original, decoded) << "Failed for string of length " << test_str.length();
    }
}

TEST(Base85Extended, EncodeOutputSize)
{
    EXPECT_EQ(base85::encode(cstr2v("")).size(), 0);
    EXPECT_EQ(base85::encode(cstr2v("1")).size(), 2);
    EXPECT_EQ(base85::encode(cstr2v("12")).size(), 3);
    EXPECT_EQ(base85::encode(cstr2v("123")).size(), 4);
    EXPECT_EQ(base85::encode(cstr2v("1234")).size(), 5);
    EXPECT_EQ(base85::encode(cstr2v("12345")).size(), 7);
}

TEST(Base85Extended, EncodeDecodeBinaryData)
{
    std::vector<uint8_t> binary;
    for (int i = 0; i < 256; ++i)
    {
        binary.push_back(static_cast<uint8_t>(i));
    }
    auto encoded = base85::encode(binary);
    auto decoded = base85::decode(encoded);
    EXPECT_EQ(binary, decoded);
}

TEST(Base85Extended, EncodeDecodeRepeatedPatterns)
{
    for (int len = 1; len <= 20; ++len)
    {
        std::vector<uint8_t> pattern;
        for (int i = 0; i < len; ++i)
        {
            pattern.push_back(i % 256);
        }
        auto encoded = base85::encode(pattern);
        auto decoded = base85::decode(encoded);
        EXPECT_EQ(pattern, decoded) << "Failed for pattern length " << len;
    }
}

TEST(Base85Extended, DecodeLongRandomData)
{
    std::string data(10000, 'x');
    for (size_t i = 0; i < data.size(); ++i)
    {
        data[i] = 'a' + (i % 26);
    }
    std::vector<uint8_t> original(data.begin(), data.end());
    auto encoded = base85::encode(original);
    auto decoded = base85::decode(encoded);
    EXPECT_EQ(original, decoded);
}

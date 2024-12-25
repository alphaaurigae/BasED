#!/bin/bash


BOLD='\033[1m'
BRIGHT_WHITE='\033[1;37m'
RED='\033[0;31m'
GREEN='\033[0;32m'
RESET='\033[0m'

local test_name="$1"
local expected="$2"
local output="$3"

debug_assert_equals() {
  if [ "$output" != "$expected" ]; then
    echo "${RED}TEST FAILED: $test_name${RESET}"
    echo "DEBUG: Expected:"
    echo "$expected"
    echo "DEBUG: Got:"
    echo "$output"
    assertEquals "Test '$test_name' failed." "$expected" "$output"
  else
    echo "${GREEN}TEST PASSED: $test_name${RESET}"
    echo "DEBUG: Expected:"
    echo "$expected"
    echo "DEBUG: Got:"
    echo "$output"
    assertEquals "Test '$test_name' passed." "$expected" "$output"
  fi
}


# Test Hex Encode and Decoding
test_HexEncode() {
    output=$(bin/hex --hex --encode -i "test!")
    expected="Encoded: 7465737421"
    assertEquals "Hex Encode Test Failed" "$expected" "$output"
  debug_assert_equals "test_print005" "$expected" "$output"
}
test_HexDecode() {
    output=$(bin/hex --hex --decode -i "7465737421")
    expected="Decoded: test!"
    assertEquals "Hex Decoding Test Failed" "$expected" "$output"
}

# Test Binary Encode and Decoding
test_BinaryEncode() {
    output=$(bin/binary --binary --encode -i "421VDSV§$")
    expected="Encoded: 00110100001100100011000101010110010001000101001101010110110000101010011100100100"
    assertEquals "Binary Encode Test Failed" "$expected" "$output"
}
test_BinaryDecode() {
    output=$(bin/binary --binary --decode -i "00110100001100100011000101010110010001000101001101010110110000101010011100100100")
    expected="Decoded: 421VDSV§$"
    assertEquals "Binary Decoding Test Failed" "$expected" "$output"
}

# Test Morse Code Encode and Decoding
test_MorseEncode() {
    output=$(bin/morse -m --encode -i "testTEST2345$")
    expected="Encoded: - . ... - - . ... - ..--- ...-- ....- ..... "
    assertEquals "Morse Encode Test Failed" "$expected" "$output"
}
test_MorseDecode() {
    output=$(bin/morse -m --decode -i "- . ... - - . ... - ..--- ...-- ....- .....")
    expected="Decoded: TESTTEST2345"
    assertEquals "Morse Decoding Test Failed" "$expected" "$output"
}

# Test Caesar Shift Encode and Decoding (digit mode)
test_CaesarShiftDigitEncode() {
    output=$(bin/caesarshift --encode --caesarshift 5 --mode digit -i "test1234%&ABC")
    expected="Encoded: test2345%&ABC"
    assertEquals "Caesar Shift Encode (digit mode) Test Failed" "$expected" "$output"
}
test_CaesarShiftDigitDecode() {
    output=$(bin/caesarshift --decode --caesarshift 5 --mode digit -i "test1234%&ABC")
    expected="Decoded: test0123%&ABC"
    assertEquals "Caesar Shift Decoding (digit mode) Test Failed" "$expected" "$output"
}

# Test Caesar Shift Encode and Decoding (alpha mode)
test_CaesarShiftAlphaEncode() {
    output=$(bin/caesarshift --encode --caesarshift 5 --mode alpha -i "test1234%&ABC")
    expected="Encoded: uftu1234%&BCD"
    assertEquals "Caesar Shift Encode (alpha mode) Test Failed" "$expected" "$output"
}
test_CaesarShiftAlphaDecode() {
    output=$(bin/caesarshift --decode --caesarshift 5 --mode alpha -i "test1234%&ABC")
    expected="Decoded: sdrs1234%&@AB"
    assertEquals "Caesar Shift Decoding (alpha mode) Test Failed" "$expected" "$output"
}

# Test Base16 Encode and Decoding
test_Base16Encode() {
    output=$(bin/base --base16 --encode -i "Test1234%")
    expected="Encoded: 546573743132333425"
    assertEquals "Base16 Encode Test Failed" "$expected" "$output"
}
test_Base16Decode() {
    output=$(bin/base --base16 --decode -i "546573743132333425")
    expected="Decoded: Test1234%"
    assertEquals "Base16 Decoding Test Failed" "$expected" "$output"
}
#include <iostream>
#include "Trim.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"



TEST_CASE("Trimming whitespace from string works correctly", "[trim_string]") {
    std::string text = "  hello world   ";
    std::string expected_result = "hello world";
    REQUIRE(trim_string(text, is_whitespace, is_whitespace) == expected_result);
}

TEST_CASE("Trimming digits from string works correctly", "[trim_string]") {
    std::string text = "123hello456world789";
    std::string expected_result = "hello456world";
    REQUIRE(trim_string(text, is_number, is_number) == expected_result);
}

TEST_CASE("Trimming uppercase letters from string works correctly", "[trim_string]") {
    std::string text = "hELLO wORLD";
    std::string expected_result = "hELLO w";
    REQUIRE(trim_string(text, is_uppercase, is_uppercase) == expected_result);
}

TEST_CASE("Trimming lowercase letters from string works correctly", "[trim_string]") {
    std::string text = "hELLO wORLD";
    std::string expected_result = "ELLO wORLD";
    REQUIRE(trim_string(text, is_lowercase, is_lowercase) == expected_result);
}

TEST_CASE("Trimming combination of left and right predicates from string works correctly", "[trim_string]") {
    std::string text = "123heLLO wORLD456A";
    std::string expected_result = "heLLO wORLD456";
    REQUIRE(trim_string(text, is_number, is_uppercase) == expected_result);
}

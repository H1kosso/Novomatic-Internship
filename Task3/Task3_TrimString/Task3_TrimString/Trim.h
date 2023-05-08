#pragma once
#include <string>
#include <cctype>


bool is_whitespace(char c) {
	return std::isspace(c);
}

bool is_number(char c) {
	return std::isdigit(c);
}

bool is_uppercase(char c){
	return std::isupper(c);
}

bool is_lowercase(char c){
	return std::islower(c);
}

template <typename leftPredicate, typename rightPredicate>
std::string trim_string(const std::string& text, leftPredicate l_predicate, rightPredicate r_predicate) {
	if (!text.length()) return "";

	std::size_t left_index = 0;
	std::size_t right_index = text.size() - 1;

	//Left trimming
	while (left_index < text.size() && l_predicate(text[left_index]))
		left_index++;

	//Right trimming
	while (right_index > left_index && r_predicate(text[right_index]))
		right_index--;

	return text.substr(left_index, right_index - left_index + 1);
}

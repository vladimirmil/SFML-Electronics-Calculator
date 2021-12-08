#ifndef HANDLE_INPUT_H
#define HANDLE_INPUT_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <stdexcept>

class HandleInput
{
private:
	std::vector<std::string> input_vector, prefix;
	std::string input, p;
	double result;
	bool error;
public:
	HandleInput();
	virtual ~HandleInput();

	double set_prefix_values(int prefix);
	int char_count(std::string s, char c);
	int index_of_last_character_found(std::string s, char c);
	bool string_contains(std::string s1, std::string s2);
	bool decimal_check(std::vector<std::string> &input, std::string s);
	void replaceAll(std::string& str, const std::string &from, const std::string &to);

	double logic(std::vector<std::string> &list, std::vector<std::string> prefix, std::string &p);
	double divisionException(double num, double den);
	std::string toString(double num);
	void stringToVectorFloat(std::vector<float> &inputvector, std::string s, std::string delimiter);
	std::string getString(std::string input);
	double getDouble(std::string input);

};

#endif // !HANDLE_INPUT_H
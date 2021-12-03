#include "HandleInput.h"

HandleInput::HandleInput()
{
	this->input_vector.clear();
	this->prefix = { "G", "M", "K", "m", "u", "n", "p" };
	this->p = "";
	this->result = -1;
	this->error = false;
}

HandleInput::~HandleInput()
{
}

int HandleInput::char_count(std::string s, char c)
{
	// returns how many characters c does string s contain
	int count = 0;
	for (unsigned int i = 0; i < s.size(); i++)
	{
		if (s[i] == c)
			count++;
	}
	return count;
}

int HandleInput::index_of_last_character_found(std::string s, char c)
{
	// returns index of last found character c in string s
	int index;
	for (unsigned int i = 0; i < s.size(); i++)
	{
		if (s[i] == c)
			index = i;
	}
	return index;
}

double HandleInput::set_prefix_values(int prefix)
{
	double value = 0;
	switch (prefix) {
	case 0:
		value = 1000000000;
		break;
	case 1:
		value = 1000000;
		break;
	case 2:
		value = 1000;
		break;
	case 3:
		value = 0.001;
		break;
	case 4:
		value = 0.000001;
		break;
	case 5:
		value = 0.000000001;
		break;
	case 6:
		value = 0.000000000001;
		break;
	default:
		value = 1;
		break;
	}
	return value;
}

bool HandleInput::string_contains(std::string s1, std::string s2)
{
	// returns true if string s1 contains string s2
	if (s1.find(s2) != std::string::npos)
		return true;
	return false;
}

bool HandleInput::decimal_check(std::vector<std::string>& input, std::string s)
{
	std::string delimiter = ".";
	size_t pos = 0;
	std::string token;

	std::replace(s.begin(), s.end(), ',', '.');

	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		input.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	input.push_back(s);

	//std::cout << "vector size: " << input.size() << std::endl;

	if (input.size() > 2) {
		return false;
	}
	return true;
}

void HandleInput::replaceAll(std::string & str, const std::string & from, const std::string & to)
{
	// in string str, replaces every string "from" with string "to"
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos)
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}

double HandleInput::logic(std::vector<std::string>& list, std::vector<std::string> prefix, std::string & p)
{
	int index = 0;
	int prefixInt = -1;
	double result, value = 0;
	std::string s = "";
	p = "X";

	if (list.size() == 1) {
		index = 0;                                  //ako nema, lista se sastoji od 1 �lana
	}
	else if (list.size() == 2) {
		index = 1;                                  //ako ima, lista se sastoji od dva �lana i prefiks se uvek nalazi u drugom
	}
	else
	{
		this->error = true;
		std::cout << "Error: Something went wrong" << std::endl;
		return -1;
	}

	//pro�i kroz listu prefiksa i prona�i koji se nalazi u listi unosa
	for (unsigned int x = 0; x < prefix.size(); x++) {
		if (this->string_contains(list[index], prefix[x])) {
			p = prefix[x];                          //podesi se prefix npr p = "M"
			prefixInt = x;                          //ovo je za switch u set_values(), pamti se na kojem se indeksu
			break;                                  //nalazi prona�eni prefiks jer c++ nema switch za stringove
		}
	}

	for (unsigned int i = 0; i < list.size(); i++)	// spajanje vektora u string
	{
		if (i == 1)
			s.append(".");
		s.append(list[i]);
	}

	if (index == 1)
	{
		this->replaceAll(s, p, "");                            //prefiks se nalazi na kraju pa se zamenjuje sa "" npr 0.1u -> 0.1
		std::replace(s.begin(), s.end(), ',', '.');
	}
	else if (index == 0)
	{
		this->replaceAll(s, p, ".");							//prefiks se nalazi u sredini pa se zamenjuje sa "." npr 4K7 -> 4.7

		int num_of_dots = this->char_count(s, '.');             //ako je unos "1ppp" tada je s="1..."
		for (int x = 1; x < num_of_dots; x++) {			 //petlja brise sve tacke sem prve npr: 4KKKK7 -> 4....7 -> 4.7
			int index = this->index_of_last_character_found(s, '.');
			s.erase(s.begin() + index);
		}
	}
	else
	{
		this->error = true;
		std::cerr << "ERROR: Something went wrong" << std::endl;
		return -1;
	}

	//pretvaranje u double
	try
	{
		std::size_t pos;
		result = std::stod(s, &pos);
		if (pos < s.size())
			throw std::string("ERROR: Input contains not supported letter");
	}
	catch (const std::string&a) {
		std::cerr << a << std::endl;
		this->error = true;
	}
	catch (const std::invalid_argument&) {
		std::cerr << "ERROR: Argument is invalid" << std::endl;
		this->error = true;
	}
	catch (const std::out_of_range&) {
		std::cerr << "ERROR: Argument is out of range for a double" << std::endl;
		this->error = true;
	}

	if (!this->error)
	{
		value = this->set_prefix_values(prefixInt);			//zamena prefiksa sa broj�anom vredno��u K -> 1000
		result = result * value;				//kona�an rezultat 4.7 * 1000 -> 4700
		//std::cout << "Result:" << result << std::endl;
		return result;
	}

	return -1;
}

double HandleInput::divisionException(double num, double den)
{
	if (den == 0)
		throw std::invalid_argument("Divide by zero exception");
	return num / den;
}

std::string HandleInput::toString(double num)
{
	std::stringstream ss;
	ss << num;
	return ss.str();
}

void HandleInput::stringToVectorFloat(std::vector<float> &inputvector, std::string s, std::string delimiter)
{
	// finds strings seperated by delimiter, converts it to float and adds it to vecotor
	std::string token;
	bool error = false;
	size_t pos = 0;
	std::replace(s.begin(), s.end(), ',', '.');

	while ((pos = s.find(delimiter)) != std::string::npos)
	{
		token = s.substr(0, pos);
		// if token is space, skip it. if it contains any letter, skip it.
		if (token != "")
		{
			for (unsigned int i = 0; i < token.size(); i++)
			{
				if (!(((int)token[i] >= 48 && (int)token[i] <= 57) || (int)token[i] == 46 || (int)token[i] == 45))
					error = true;
			}
			if (!error)
				inputvector.push_back(std::stof(token));
			error = false;
		}
		s.erase(0, pos + delimiter.length());
	}
	// adds last part which was not deleted
	if (s != "")
	{
		for (unsigned int i = 0; i < s.size(); i++)
		{
			if (!(((int)s[i] >= 48 && (int)s[i] <= 57) || (int)s[i] == 46 || (int)s[i] == 45))
				error = true;
		}
		if (!error)
			inputvector.push_back(std::stof(s));
	}
}

std::string HandleInput::getString(std::string input)
{
	std::stringstream ss;
	this->input_vector.clear();
	this->p = "";
	this->result = -1;
	this->error = false;

	if (this->decimal_check(this->input_vector, input))
	{
		result = logic(this->input_vector, this->prefix, this->p);
	}
	else
	{
		std::cout << "ERROR: Input contains multiple decimal places" << std::endl;
	}
	ss << result;
	return ss.str();
}

double HandleInput::getDouble(std::string input)
{
	this->input_vector.clear();
	this->p = "";
	this->result = -1;
	this->error = false;

	if (this->decimal_check(this->input_vector, input))
	{
		result = logic(this->input_vector, this->prefix, this->p);
	}
	else
	{
		std::cout << "ERROR: Input contains multiple decimal places" << std::endl;
	}

	return result;
}
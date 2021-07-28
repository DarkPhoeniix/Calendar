#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Date.h"

enum class TokenType
{
	DATE,
	EVENT,
	COLUMN,
	LOGICAL_OP,
	COMPARE_OP,
	PARENT_LEFT,
	PARENT_RIGHT
};

// CLASS Token
class Token
{
public:
	// Key word for token
	std::string value;
	// TYpe of key word
	TokenType type;
};

// Divide input condition into tokens {word, type}
// Return all tokens from input
std::vector<Token> tokenize(std::istream & in);

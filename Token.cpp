#include "Token.h"

// Divide input condition into tokens {word, type}
// Return all tokens from input
std::vector<Token> tokenize(std::istream& in)
{
    std::vector<Token> tokens;
    char c;
    auto isDigit = [](char c) {return c >= '0' && c <= '9'; };

    while (!in.eof()) {
        c = in.get();
        if (c == 'd') {
            if (in.get() == 'a' && in.get() == 't' && in.get() == 'e') {
                tokens.push_back({ "date", TokenType::COLUMN });
            } else {
                throw std::logic_error("Unknown token");
            }
        } else if (c == 'e') {
            if (in.get() == 'v' && in.get() == 'e' && in.get() == 'n' && 
                in.get() == 't') {
                tokens.push_back({ "event", TokenType::COLUMN });
            } else {
                throw std::logic_error("Unknown token");
            }
        } else if (isDigit(in.peek())) {
            Date date;
            std::stringstream ss;
            ss >> date;
            tokens.push_back({ ss.str(), TokenType::DATE });
        } else if (in.get() == '(') {
            tokens.push_back({ "(", TokenType::PARENT_LEFT });
        } else if (in.get() == ')') {
            tokens.push_back({ ")", TokenType::PARENT_RIGHT });
        } else if (in.get() == '<') {
            if (in.get() == '=') {
                tokens.push_back({ "<=", TokenType::COMPARE_OP });
            } else {
                tokens.push_back({ "<", TokenType::COMPARE_OP });
            }
        } else if (in.get() == '>') {
            if (in.get() == '=') {
                tokens.push_back({ ">=", TokenType::COMPARE_OP });
            } else {
                tokens.push_back({ ">", TokenType::COMPARE_OP });
            }
        } else if (in.get() == '=') {
            if (in.get() == '=') {
                tokens.push_back({ "==", TokenType::COMPARE_OP });
            } else {
                throw std::logic_error("Unknown token");
            }
        } else if (in.get() == '!') {
            if (in.get() == '=') {
                tokens.push_back({ "!=", TokenType::COMPARE_OP });
            } else {
                throw std::logic_error("Unknown token");
            }
        } else if (in.get() == 'A') {
            if (in.get() == 'N' && in.get() == 'D') {
                tokens.push_back({ "AND", TokenType::LOGICAL_OP });
            } else {
                throw std::logic_error("Unknown token");
            }
        } else if (in.get() == 'O') {
            if (in.get() == 'R') {
                tokens.push_back({ "OR", TokenType::LOGICAL_OP });
            } else {
                throw std::logic_error("Unknown token");
            }
        }
    }

    return tokens;
}

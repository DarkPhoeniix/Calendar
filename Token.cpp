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
        } else if (isDigit(c)) {
            std::string s;
            in >> s;
            tokens.push_back({ c + s, TokenType::DATE });
        } else if (c == '(') {
            tokens.push_back({ "(", TokenType::PARENT_LEFT });
        } else if (c == ')') {
            tokens.push_back({ ")", TokenType::PARENT_RIGHT });
        } else if (c == '<') {
            if (in.get() == '=') {
                tokens.push_back({ "<=", TokenType::COMPARE_OP });
            } else {
                tokens.push_back({ "<", TokenType::COMPARE_OP });
            }
        } else if (c == '>') {
            if (in.get() == '=') {
                tokens.push_back({ ">=", TokenType::COMPARE_OP });
            } else {
                tokens.push_back({ ">", TokenType::COMPARE_OP });
            }
        } else if (c == '=') {
            if (in.get() == '=') {
                tokens.push_back({ "==", TokenType::COMPARE_OP });
            } else {
                throw std::logic_error("Unknown token");
            }
        } else if (c == '!') {
            if (in.get() == '=') {
                tokens.push_back({ "!=", TokenType::COMPARE_OP });
            } else {
                throw std::logic_error("Unknown token");
            }
        } else if (c == 'A') {
            if (in.get() == 'N' && in.get() == 'D') {
                tokens.push_back({ "AND", TokenType::LOGICAL_OP });
            } else {
                throw std::logic_error("Unknown token");
            }
        } else if (c == 'O') {
            if (in.get() == 'R') {
                tokens.push_back({ "OR", TokenType::LOGICAL_OP });
            } else {
                throw std::logic_error("Unknown token");
            }
        } else if (c == '"') {
            std::string eventName;
            std::getline(in, eventName, '"');
            tokens.push_back({ eventName, TokenType::EVENT });
        } else if (c == ' ') {
            continue;
        }
    }

    return tokens;
}

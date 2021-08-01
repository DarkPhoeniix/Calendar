#include "Condition_Parser.h"



template<class Iterator>
std::shared_ptr<Node> parseComparison(Iterator& begin, const Iterator& end)
{
    if (begin == end) {
        throw std::logic_error("Unexcpected end of condition");
    }

    auto& current = begin;

    if (current->type != TokenType::COLUMN) {
        throw std::logic_error("Failed while reading tokens. Expected column");
    }

    Token& column = *current;
    current++;

    if (current == end) {
        throw std::logic_error("Unexcpected end of condition");
    } else if (current->type != TokenType::COMPARE_OP) {
        throw std::logic_error("Failed while reading tokens. Expected comparison operator");
    }

    Comparison cmp;
    if (current->value == "<") {
        cmp = Comparison::Less;
    } else if (current->value == "<=") {
        cmp = Comparison::LessOrEqual;
    } else if (current->value == ">") {
        cmp = Comparison::Greater;
    } else if (current->value == ">=") {
        cmp = Comparison::GreaterOrEqual;
    } else if (current->value == "==") {
        cmp = Comparison::Equal;
    } else if (current->value == "!=") {
        cmp = Comparison::NotEqual;
    }

    current++;

    if (current == end) {
        throw std::logic_error("Unexpected end of file");
    } else if(current->type != TokenType::EVENT &&
              current->type != TokenType::DATE) {
        throw std::logic_error("Failed while reading tokens. Expected date or event");
    }

    std::string& value = current->value;
    current++;

    if (column.value == "date") {
        std::istringstream iss(value);
        Date date;
        iss >> date;
        return std::make_shared<DateComparisonNode>(date, cmp);
    } else if (column.value == "event") {
        return std::make_shared<EventComparisonNode>(value, cmp);
    }
}



template<class Iterator>
std::shared_ptr<Node> parseExpression(Iterator& begin, const Iterator& end, int precedence)
{
    auto& current = begin;

    if (current == end) {
        return std::shared_ptr<EmptyNode>();
    }

    std::shared_ptr<Node> leftSubtree;

    if (current->type == TokenType::PARENT_LEFT) {
        current++;
        leftSubtree = parseExpression(current, end, 0);
        if (current == end || current->type != TokenType::PARENT_RIGHT) {
            throw std::logic_error("Failed while reading tokens");
        }
        current++;
    } else {
        leftSubtree = parseComparison(current, end);
    }

    std::map<LogicalOperation, int> precendences = {
        {LogicalOperation::OR, 1},
        {LogicalOperation::AND, 2}
    };
    while (current != end && current->type != TokenType::PARENT_RIGHT) {
        if (current->type != TokenType::LOGICAL_OP) {
            throw std::logic_error("Failed while reading tokens");
        }
        LogicalOperation logicalOp = (current->value == "AND") ? 
            LogicalOperation::AND : 
            LogicalOperation::OR;
        if (precendences[logicalOp] <= precedence) {
            break;
        }
        current++;
        leftSubtree = std::make_shared<LogicalOperationNode>(
            logicalOp, 
            leftSubtree, 
            parseExpression(current, end, precendences[logicalOp])
            );
    }

    return leftSubtree;
}



std::shared_ptr<Node> parseCondition(std::istream& in)
{
    std::vector<Token> tokens = tokenize(in);
    auto current = tokens.begin();
    std::shared_ptr<Node> rootNode = 
        parseExpression(current, tokens.end(), 0);

    if (rootNode == nullptr) {
        rootNode = std::make_shared<EmptyNode>();
    }

    if (current != tokens.end()) {
        throw std::logic_error("Failed while reading tokens");
    }

    return rootNode;
}

#pragma once
#include <iostream>
#include <memory>

#include "Date.h"



// Enum of comparison operations
enum class Comparison
{
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

// Enum of logical operations
enum class LogicalOperation
{
	OR = 1,
	AND = 2
};



// CLASS Node
// Parent abstract class for polymorph evaluating all types of nodes
class Node
{
public:
	// Virtual method for recursive node evaluating
	virtual bool evaluate(const Date& date, 
						  const std::string& eventName) const = 0;
};



// CLASS LogicalOperationNode
// Subclass for nodes with logical operations and child nodes.
// Inner vertex of tree
class LogicalOperationNode : public Node
{
private:
	std::shared_ptr<Node> left_;	// left subtree
	std::shared_ptr<Node> right_;	// right subtree
	LogicalOperation logicalOp_;

public:
	// Constructor
	// Takes logical operation and pointers to left and right subtrees
	LogicalOperationNode(const LogicalOperation& logicalOp, 
						 std::shared_ptr<Node> left, 
						 std::shared_ptr<Node> right);
	// Virtual method for recursive node evaluating
	// Recursively evaluate left and right subtrees and return result
	// with specified logical operation
	virtual bool evaluate(const Date& date, 
						  const std::string& eventName) const override;
};



// CLASS DateComparisonNode
// Subclass for nodes with date comparison. Outer vertex of tree
class DateComparisonNode : public Node
{
private:
	Date date_;
	Comparison cmp_;

public:
	// Constructor
	// Takes comparison operator and a date to compare with
	DateComparisonNode(const Date& date, const Comparison& cmp);
	// Return result of comparing input date to specified date
	virtual bool evaluate(const Date& date, 
						  const std::string& eventName) const override;
};



// CLASS EventComparisonNode
// Subclass for nodes with event comparison. Outer vertex of tree
class EventComparisonNode : public Node
{
private:
	std::string eventName_;
	Comparison cmp_;

public:
	// Constructor
	// Takes comparison operator and an event to compare with
	EventComparisonNode(const std::string& eventName, const Comparison& cmp);
	// Return result of comparing input event to specified event
	virtual bool evaluate(const Date& date, 
						  const std::string& eventName) const override;
};



// CLASS EmptyNode
// Subclass for empty nodes with event comparison
// Creates if conditions is empty
class EmptyNode : public Node
{
public:
	// Return true while evaluating
	virtual bool evaluate(const Date& date, 
						  const std::string& eventName) const override;
};

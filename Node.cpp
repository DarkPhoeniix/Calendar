#include "Node.h"

// Constructor
// Takes logical operation and pointers to left and right subtrees
LogicalOperationNode::LogicalOperationNode(const LogicalOperation& logicalOp, 
										   std::shared_ptr<Node> left, 
										   std::shared_ptr<Node> right)
	: logicalOp_(logicalOp), left_(left), right_(right)
{	}

// Virtual method for recursive node evaluating
// Recursively evaluate left and right subtrees and return result
// with specified logical operation
bool LogicalOperationNode::evaluate(const Date& date, 
									const std::string& eventName) const
{
	if (logicalOp_ == LogicalOperation::AND) {
		return	left_->evaluate(date, eventName) && 
				right_->evaluate(date, eventName);
	} else if (logicalOp_ == LogicalOperation::OR) {
		return	left_->evaluate(date, eventName) ||
				right_->evaluate(date, eventName);
	}
}



// Constructor
// Takes comparison operator and a date to compare with
DateComparisonNode::DateComparisonNode(const Date& date, 
									   const Comparison& cmp)
	: date_(date), cmp_(cmp)
{	}

// Return result of comparing input date to specified date
bool DateComparisonNode::evaluate(const Date& date, 
								  const std::string& eventName) const
{
	if (cmp_ == Comparison::Less) {
		return date < date_;
	} else if (cmp_ == Comparison::LessOrEqual) {
		return date <= date_;
	} else if (cmp_ == Comparison::Greater) {
		return date > date_;
	} else if (cmp_ == Comparison::GreaterOrEqual) {
		return date >= date_;
	} else if (cmp_ == Comparison::Equal) {
		return date == date_;
	} else if (cmp_ == Comparison::NotEqual) {
		return date != date_;
	}
}

// Constructor
// Takes comparison operator and an event to compare with
EventComparisonNode::EventComparisonNode(const std::string& eventName, 
										 const Comparison& cmp)
	: eventName_(eventName), cmp_(cmp)
{	}

// Return result of comparing input event to specified event
bool EventComparisonNode::evaluate(const Date& date, 
								   const std::string& eventName) const
{
	if (cmp_ == Comparison::Equal) {
		return eventName_ == eventName;
	} if (cmp_ == Comparison::NotEqual) {
		return eventName_ != eventName;
	}
}



bool EmptyNode::evaluate(const Date& date, 
						 const std::string& eventName) const
{
	return true;
}

#include "Date.h"

// Checks month and day ranges
// valid fields: month_(1-12), day_(1-31)
void Date::dateValidator_() const
{
	if (month_ <= 0 || month_ >= 13) {
		throw std::invalid_argument(
			"Month value is invalid: " + std::to_string(month_)
		);
	} else if (day_ <= 0 || day_ >= 32) {
		throw std::invalid_argument(
			"Day value is invalid: " + std::to_string(day_)
		);
	}
}



// Default constructor
Date::Date()
	: year_(0), month_(0), day_(0)
{	}

// Constructor with parameters
// Also validates data (valid parameters: month(1-12), day(1-31))
Date::Date(int year, int month, int day)
	: year_(year), month_(month), day_(day)
{
	dateValidator_();
}

// Copy constructor
Date::Date(const Date& copy)
	: year_(copy.year_), month_(copy.month_), day_(copy.day_)
{	}

// Destructor
Date::~Date()
{	}



// Copy assignment operator
Date& Date::operator=(const Date& copy)
{
	year_ = copy.year_;
	month_ = copy.month_;
	day_ = copy.day_;

	return *this;
}



// Input operator
// Returns std::istream reference
// Gets std::istream refenece and Date object reference
// Throws std::invalid_argument if date format is wrong or date 
// range is wrong
std::istream& operator>>(std::istream& in, Date& date)
{
	std::string fullDate;
	in >> fullDate;
	std::stringstream ss(fullDate);
	auto symbolValidator = [fullDate](char symbol) {
		if (symbol != '-') {
			throw std::invalid_argument("Wrong gate format: " + fullDate);
		}
	};

	ss >> date.year_;
	symbolValidator(ss.get());
	ss >> date.month_;
	symbolValidator(ss.get());
	ss >> date.day_;
	
	date.dateValidator_();

	return in;
}

// Output operator
// Returns std::ostream reference
// Gets std::istream refenece and constant Date object reference
std::ostream& operator<<(std::ostream& out, const Date& date)
{
	return out	<< std::setw(4) << std::setfill('0') << date.year_	<< '-' 
				<< std::setw(2) << std::setfill('0') << date.month_ << '-'
				<< std::setw(2) << std::setfill('0') << date.day_;
}

// Comparison operator<
// Returns is left object less than right object
// Gets two constant Date object references
bool operator<(const Date& lhs, const Date& rhs)
{
	return	std::tie(lhs.year_, lhs.month_, lhs.day_) < 
			std::tie(rhs.year_, rhs.month_, rhs.day_);
}

// Comparison operator>
// Returns is left object greater than right object
// Gets two constant Date object references
bool operator>(const Date& lhs, const Date& rhs)
{
	return	std::tie(lhs.year_, lhs.month_, lhs.day_) >
			std::tie(rhs.year_, rhs.month_, rhs.day_);
}

// Comparison operator<=
// Returns is left object less or equal to the right object
// Gets two constant Date object references
bool operator<=(const Date& lhs, const Date& rhs)
{
	return	std::tie(lhs.year_, lhs.month_, lhs.day_) <=
			std::tie(rhs.year_, rhs.month_, rhs.day_);
}

// Comparison operator>=
// Returns is left object greater or equal to the right object
// Gets two constant Date object references
bool operator>=(const Date& lhs, const Date& rhs)
{
	return	std::tie(lhs.year_, lhs.month_, lhs.day_) >=
			std::tie(rhs.year_, rhs.month_, rhs.day_);
}

// Comparison operator==
// Returns is left object equal to the right object
// Gets two constant Date object references
bool operator==(const Date& lhs, const Date& rhs)
{
	return	std::tie(lhs.year_, lhs.month_, lhs.day_) ==
			std::tie(rhs.year_, rhs.month_, rhs.day_);
}

// Comparison operator!=
// Returns is left object not equal to the right object
// Gets two constant Date object references
bool operator!=(const Date& lhs, const Date& rhs)
{
	return	std::tie(lhs.year_, lhs.month_, lhs.day_) !=
			std::tie(rhs.year_, rhs.month_, rhs.day_);
}
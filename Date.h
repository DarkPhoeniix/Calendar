
#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <tuple>

// CLASS Date
// Date format: yyyy-mm-dd
// Saves date and validate it while inputting
class Date
{
private:
	int year_;
	int month_;
	int day_;

	// Checks month and day ranges
	void dateValidator_() const;

public:
	// Default constructor
	Date();
	// Constructor with parameters
	Date(int year, int month, int day);
	// Copy constructor
	Date(const Date& copy);
	// Destructor
	~Date();

	// Copy assignment operator
	Date& operator=(const Date& copy);

	friend std::istream& operator>>(std::istream& in, Date& date);
	friend std::ostream& operator<<(std::ostream& out, const Date& date);
	friend bool operator<(const Date& lhs, const Date& rhs);
};


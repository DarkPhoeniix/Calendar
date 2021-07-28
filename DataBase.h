
#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <set>

#include "Date.h"



// CLASS DataBase
// Contains pairs <Date, Event> and provide an interface to interact 
// with database
class DataBase
{
private:
	std::map<Date, std::set<std::string>> dataBase_;

public:
	// Default constructor
	DataBase();
	// Destructor
	~DataBase();

	// Insert pair <date, eventName> in database
	void add(const Date& date, const std::string& eventName);
	// Delete pair <date, eventName> from database
	// Return 1 if deleted successfully, else 0
	int remove(const Date& date, const std::string& eventName);
	// Delete all pairs <Date, Event> with specific date
	// Return number of deleted elements from database
	int remove(const Date& date);
	// Return all events on specific date
	std::set<std::string> find(const Date& date) const;
	// Print all pairs <Date, Event>
	void print() const;
};


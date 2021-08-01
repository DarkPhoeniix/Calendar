
#pragma once
#include <algorithm>
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
	std::map<Date, std::vector<std::string>> dataBase_;

public:
	// Default constructor
	DataBase();
	// Destructor
	~DataBase();

	// Insert pair <date, eventName> in database
	void add(const Date& date, const std::string& eventName);
	// Delete pairs <date, eventName> if they satisfy the predicate
	// Return number of deleted elements from database
	template<class Predicate>
	int removeIf(Predicate predicate);
	// Find pairs <date, eventName> if they satusfy the predicate
	// Return copies of specified pairs from dataBase
	template<class Predicate>
	std::map<Date, std::vector<std::string>> findIf(Predicate predicate);
	// Print all pairs <Date, Event>
	void print() const;
};



// Delete pairs <date, eventName> if they satisfy the predicate
// Return number of deleted elements from database
template<class Predicate>
inline int DataBase::removeIf(Predicate predicate)
{
	int numOfDeleted = 0;

	for (auto& [date, events] : dataBase_) {
		auto toDelete = [predicate, date, &numOfDeleted](std::string eventName)
		{
			if (predicate(date, eventName)) {
				numOfDeleted++;
				return true;
			}
			return false;
		};
		events.erase(std::remove_if(events.begin(), events.end(), toDelete), events.end());
	}

	return numOfDeleted;
}

// Find pairs <date, eventName> if they satusfy the predicate
// Return copies of specified pairs from dataBase
template<class Predicate>
inline std::map<Date, std::vector<std::string>> DataBase::findIf(Predicate predicate)
{
	std::map<Date, std::vector<std::string>> result;

	for (auto& [date, events] : dataBase_) {
		for (auto& eventName : events) {
			if (predicate(date, eventName)) {
				result[date].push_back(eventName);
			}
		}
	}

	return result;
}

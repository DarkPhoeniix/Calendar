
#pragma once
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

#include "Date.h"



// CLASS Database
// Contains pairs <Date, Event> and provide an interface to interact 
// with Database
class Database
{
private:
	std::map<Date, std::vector<std::string>> database_;

public:
	// Default constructor
	Database();
	// Destructor
	~Database();

	// Insert pair <date, eventName> in Database
	void add(const Date& date, const std::string& eventName);
	// Delete pairs <date, eventName> if they satisfy the predicate
	// Return number of deleted elements from Database
	template<class Predicate>
	int removeIf(Predicate predicate);
	// Find pairs <date, eventName> if they satusfy the predicate
	// Return copies of specified pairs from Database
	template<class Predicate>
	std::map<Date, std::vector<std::string>> findIf(Predicate predicate);
	// Print all pairs <date, eventName>
	void print() const;
	// Save all pairs <date, eventName> from database to specified file
	void saveDatabaseToFile(const std::string& fileName = "data.txt") const;
	// Read and save all pairs <date, eventName> from specidied file to 
	// current database
	void readDatabaseFromFile(const std::string& fileName = "data.txt");
};



// Delete pairs <date, eventName> if they satisfy the predicate
// Return number of deleted elements from Database
template<class Predicate>
inline int Database::removeIf(Predicate predicate)
{
	int numOfDeleted = 0;

	for (auto& [date, events] : database_) {
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
// Return copies of specified pairs from Database
template<class Predicate>
inline std::map<Date, std::vector<std::string>> Database::findIf(Predicate predicate)
{
	std::map<Date, std::vector<std::string>> result;

	for (auto& [date, events] : database_) {
		for (auto& eventName : events) {
			if (predicate(date, eventName)) {
				result[date].push_back(eventName);
			}
		}
	}

	return result;
}

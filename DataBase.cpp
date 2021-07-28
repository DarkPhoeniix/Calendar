#include "DataBase.h"

// Default constructor
DataBase::DataBase()
{	}

// Destructor
DataBase::~DataBase()
{	}



// Insert pair <date, eventName> in database
void DataBase::add(const Date& date, const std::string& eventName)
{
	dataBase_[date].insert(eventName);
}

// Delete pair <date, eventName> from database
// Return 1 if deleted successfully, else 0
int DataBase::remove(const Date& date, const std::string& eventName)
{
	if (dataBase_.find(date) == dataBase_.end() || 
		dataBase_.at(date).erase(eventName) == 0) {
		return 0;
	} else {
		return 1;
	}
}

// Delete all pairs <Date, Event> with specific date
// Return number of deleted elements from database
int DataBase::remove(const Date& date)
{
	int deletedEventsNum = dataBase_[date].size();
	dataBase_[date].clear();
	return deletedEventsNum;
}

// Return all events on specific date
std::set<std::string> DataBase::find(const Date& date) const
{
	// if database doesn't contain such date, returns empty set
	if (dataBase_.find(date) == dataBase_.end()) {
		return std::set<std::string>{};
	}
	return dataBase_.at(date);
}

// Print all pairs <Date, Event>
void DataBase::print() const
{
	for (const auto& [date, events] : dataBase_) {
		for (const auto& eventName : events) {
			std::cout << date << ' ' << eventName << std::endl;
		}
	}
}

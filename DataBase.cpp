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
	dataBase_[date].push_back(eventName);
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

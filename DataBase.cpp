#include "Database.h"

// Default constructor
Database::Database()
{	}

// Destructor
Database::~Database()
{	}



// Insert pair <date, eventName> in Database
void Database::add(const Date& date, const std::string& eventName)
{
	database_[date].push_back(eventName);
}

// Print all pairs <Date, Event>
void Database::print() const
{
	for (const auto& [date, events] : database_) {
		for (const auto& eventName : events) {
			std::cout << date << ' ' << eventName << std::endl;
		}
	}
}

// Save all pairs <date, eventName> from database to specified file
void Database::saveDatabaseToFile(const std::string& fileName) const
{
	std::ofstream fout(fileName);
	for (const auto& [date, events] : database_) {
		for (auto it = events.begin(); it != events.end(); ++it) {
			fout << date << ' ' << *it;
			if (it != std::prev(events.end())) {
				fout << std::endl;
			}
		}
	}
	fout.close();
}

// Read and save all pairs <date, eventName> from specidied file to 
// current database
void Database::readDatabaseFromFile(const std::string& fileName)
{
	std::ifstream fin(fileName);
	Date date;
	std::string eventName;

	database_.clear();
	char ch;
	while (!fin.eof() && fin.peek() != std::ifstream::traits_type::eof()) {
		fin >> date >> eventName;
		database_[date].push_back(eventName);
	}

	fin.close();
}

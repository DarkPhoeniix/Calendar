
#include <iostream>
#include <numeric>

#include "Condition_Parser.h"
#include "Database.h"
#include "Node.h"

int main()
{
	Date date;
	Database database;
	std::string command;
	std::string eventName;

	database.readDatabaseFromFile();

	for (std::string line; getline(std::cin, line); ) {
		std::istringstream iss(line);
		try {
			iss >> command;
			if (command == "Add") {
				iss >> date >> eventName;
				while (!iss.eof()) {
					eventName += iss.get();
				}
				database.add(date, eventName);
			}
			else if (command == "Del") {
				std::shared_ptr<Node> root = parseCondition(iss);
				auto pred = [root](const Date& date, const std::string& eventName) 
					{ 
						return root->evaluate(date, eventName); 
					};
				std::cout << "Deleted " << database.removeIf(pred) << " events" 
						  << std::endl;
			}
			else if (command == "Find") {
				std::shared_ptr<Node> root = parseCondition(iss);
				auto pred = [root](const Date& date, const std::string& eventName)
				{
					return root->evaluate(date, eventName);
				};
				auto foundEvents = database.findIf(pred);
				int num = 0;
				std::for_each(foundEvents.begin(), 
							  foundEvents.end(), 
							  [&num](auto& p) { num += p.second.size(); }
				);
				std::cout << "Found " << num << " events" << std::endl;
				for (const auto& [date, events] : foundEvents) {
					for (const auto& eventName : events) {
						std::cout << date << ' ' << eventName << std::endl;
					}
				}
			}
			else if (command == "Print") {
				database.print();
			}
			else if (command == "Exit") {
				break;
			}
			else {
				throw std::invalid_argument("Unknown command: " + command);
			}
		} catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
		command = "";
	}

	database.saveDatabaseToFile();

	return 0;
}



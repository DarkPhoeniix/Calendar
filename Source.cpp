
#include <iostream>

#include "DataBase.h"

int main()
{
	Date date;
	DataBase dataBase;
	std::string command;
	std::string eventName;

	while(true) {
		try {
			std::cin >> command;
			if (command == "Add") {
				std::cin >> date >> eventName;
				dataBase.add(date, eventName);
			}
			else if (command == "Del") {
				std::cin >> date;
				if (std::cin.get() == ' ') {
					std::cin >> eventName;
					(dataBase.remove(date, eventName)) ? 
						std::cout << "Deleted successfully" << std::endl :
						std::cout << "Event not found" << std::endl;
				} else {
					std::cout << "Deleted " << dataBase.remove(date) << " events" << std::endl;
				}
			}
			else if (command == "Find") {
				std::cin >> date;
				for (const auto& item : dataBase.find(date)) {
					std::cout << date << ' ' << item << std::endl;
				}
			}
			else if (command == "Print") {
				dataBase.print();
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
	}

	return 0;
}



#include <iostream>
#include <string>
#include "ContainmentSystem.h"

int main() {
	ContainmentSystem system;

	std::string input;

	while (true) {
		std::cout << "> ";
		std::cin >> input;

		if (input == "motion") {
			system.handleEvent(ContainmentSystem::Event::MotionDetected);
		}
		if (input == "lockdown") {
			system.handleEvent(ContainmentSystem::Event::ManualLockdown);
		}
		if (input == "fail") {
			system.handleEvent(ContainmentSystem::Event::SystemFailure);
		}
		if (input == "reset") {
			system.handleEvent(ContainmentSystem::Event::SystemReset);
		}
		if (input == "exit") {
			break;
		}
	}

	return 0;
}
#include <iostream>
#include "ContainmentSystem.h"

int main() {
	ContainmentSystem system;

	system.handleEvent(ContainmentSystem::Event::MotionDetected);
	system.handleEvent(ContainmentSystem::Event::ManualLockdown);
	system.handleEvent(ContainmentSystem::Event::SystemFailure);
	system.handleEvent(ContainmentSystem::Event::SystemReset);
	system.handleEvent(ContainmentSystem::Event::SystemFailure);
	system.handleEvent(ContainmentSystem::Event::ManualLockdown);
	system.handleEvent(ContainmentSystem::Event::SystemReset);
	return 0;
}
#include <iostream>
#include <string>
#include "ContainmentSystem.h"

ContainmentSystem::ContainmentSystem() : currentState(State::CONTAINED) {
	log("System initialized. State: " + stateToString(currentState));
}

ContainmentSystem::State ContainmentSystem::getState() const {
	return currentState;
}

void ContainmentSystem::handleEvent(Event e) {
	log("Event received (" + eventToString(e) + ")");
	State previousState = currentState;
	
	if (e == Event::SystemReset) {
		currentState = State::CONTAINED;
	}
	else {

		switch (currentState) {
		case State::CONTAINED:
			switch (e) {
			case Event::MotionDetected:
				currentState = State::RISK;
				break;
			case Event::SystemFailure:
				currentState = State::BREACHED;
				break;
			case Event::ManualLockdown:
				currentState = State::LOCKDOWN;
				break;
			default:
				escalate();
				break;
			}
			break;

		case State::RISK:
			switch (e) {
			case Event::MotionDetected:
				currentState = State::BREACHED;
				break;
			case Event::ManualLockdown:
				currentState = State::LOCKDOWN;
				break;
			default:
				escalate();
				break;
			}
			break;

		case State::BREACHED:
			switch (e) {
			case Event::ManualLockdown:
				currentState = State::LOCKDOWN;
				break;
			default:
				escalate();
				break;
			}
			break;

		case State::LOCKDOWN:
			switch (e) {
			default:
				escalate();
				break;
			}
			break;
		}
	}

	if (previousState != currentState) {
		log("State changed from " + stateToString(previousState) + " to " + stateToString(currentState));
	}
}

void ContainmentSystem::log(const std::string& message) {
	std::cout << "[LOG] " << message << std::endl;
}

void ContainmentSystem::escalate() {
	switch (currentState) {
	case State::CONTAINED:
		currentState = State::RISK;
		break;
	case State::RISK:
		currentState = State::BREACHED;
		break;
	case State::BREACHED:
		currentState = State::BREACHED;
		break;
	case State::LOCKDOWN:
		currentState = State::LOCKDOWN;
		break;
	}
}

std::string ContainmentSystem::stateToString(State s) const {
	switch (s) {
	case State::CONTAINED:
		return "CONTAINED";
		break;
	case State::RISK:
		return "RISK";
		break;
	case State::BREACHED:
		return "BREACHED";
		break;
	case State::LOCKDOWN:
		return "LOCKDOWN";
		break;
	default:
		return "UNKNOWN";
		break;
	}
}

std::string ContainmentSystem::eventToString(Event e) const {
	switch (e) {
	case Event::MotionDetected:
		return "MOTION DETECTED";
		break;
	case Event::SystemFailure:
		return "SYSTEM FAILURE";
		break;
	case Event::ManualLockdown:
		return "MANUAL LOCKDOWN";
		break;
	case Event::SystemReset:
		return "SYSTEM RESET";
		break;
	default:
		return "UNKNOWN";
		break;
	}
}
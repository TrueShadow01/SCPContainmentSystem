#include <iostream>
#include <string>
#include <gpiod.h>
#include "ContainmentSystem.h"

ContainmentSystem::ContainmentSystem() : currentState(State::CONTAINED) {
	log("System initialized. State: " + stateToString(currentState));
	if (!chip) {
		std::cerr << "Failed to open GPIO chip" << std::endl;
		exit(1);
	}
	
	chip = gpiod_chip_open("/dev/gpiochip0");
	gpiod_line_settings* settings = gpiod_line_settings_new();
	gpiod_line_settings_set_direction(settings, GPIOD_LINE_DIRECTION_OUTPUT);
	gpiod_line_config* config = gpiod_line_config_new();
	unsigned int offsets[] = {17};
	gpiod_line_config_add_line_settings(config, offsets, 1, settings);
	
	request = gpiod_chip_request_lines(chip, NULL, config);
	if (!request) {
		std::cerr << "Failed to request GPIO line" << std::endl;
		exit(1);
	}
	
	gpiod_line_request_set_value(request, 17, GPIOD_LINE_VALUE_INACTIVE);
}

ContainmentSystem::~ContainmentSystem() {
	if (request) {
		gpiod_line_request_release(request);
		std::cout << "Released GPIO Line Request" << std::endl;
	}
	
	if (chip) {
		gpiod_chip_close(chip);
		std::cout << "Released GPIO Chip" << std::endl;
	}
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
		
		if (currentState == State::CONTAINED) {
			gpiod_line_request_set_value(request, 17, GPIOD_LINE_VALUE_INACTIVE);
		} else {
			gpiod_line_request_set_value(request, 17, GPIOD_LINE_VALUE_ACTIVE);
		}
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

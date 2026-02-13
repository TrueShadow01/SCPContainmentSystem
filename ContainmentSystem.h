#pragma once

#include <string>

struct gpiod_chip;
struct gpiod_line_request;

class ContainmentSystem {
public:
	enum class State {
		CONTAINED,
		RISK,
		BREACHED,
		LOCKDOWN
	};

	enum class Event {
		MotionDetected,
		SystemFailure,
		ManualLockdown,
		SystemReset
	};

	ContainmentSystem();
	~ContainmentSystem();
	void handleEvent(Event e);
	State getState() const;

private:
	gpiod_chip* chip;
	gpiod_line_request* request;
	State currentState;
	void log(const std::string& message);
	void escalate();
	std::string stateToString(State s) const;
	std::string eventToString(Event e) const;
};

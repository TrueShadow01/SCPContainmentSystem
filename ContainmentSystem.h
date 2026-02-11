#pragma once

#include <string>

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
	void handleEvent(Event e);
	State getState() const;

private:
	State currentState;
	void log(const std::string& message);
	void escalate();
	std::string stateToString(State s) const;
	std::string eventToString(Event e) const;
};
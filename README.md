# SCP Containment System (EARLY ACCESS VERISON)

A finite state machine–based SCP containment control system written in modern C++.

This project simulates a containment control core similar to what might be used in a fictional SCP Foundation facility. It models containment states, event handling, automatic escalation logic and system overrides.

---

## Overview

The system is built around a deterministic state machine.

### States

- CONTAINED
- RISK
- BREACHED
- LOCKDOWN

### Events

- MotionDetected
- SystemFailure
- ManualLockdown
- SystemReset

---

## State Transition Logic

The system uses:

- Explicit transitions for defined events
- Automatic escalation for undefined transitions
- A global reset override

### Escalation Rules

CONTAINED → RISK<br>
RISK → BREACHED<br>
BREACHED → BREACHED<br>
LOCKDOWN → LOCKDOWN<br>


`SystemReset` overrides all states and restores `CONTAINED`.

---

## Architecture

Project structure:

ContainmentSystem.h
ContainmentSystem.cpp
main.cpp


Core components:

- `ContainmentSystem` class
- Scoped enums (`enum class`) for type safety
- State transition logic using nested switches
- Console-based logging
- Automatic escalation helper

The system is designed to be extendable for:

- GPIO integration (Raspberry Pi)
- Web dashboard control
- File-based logging
- Random event simulation
- Timed escalation logic

---

## Build

Compile with:

```bash
g++ main.cpp ContainmentSystem.cpp -o scp_containment
```
Run:
```
./scp_containment
```
## Future Improvements
- Random event simulation engine
- Probability-based breach escalation
- File-based logging
- Hardware integration layer (GPIO)
- Web-based control dashboard
- Transition table refactor

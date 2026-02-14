# SCP Containment System

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

Core components:

- `ContainmentSystem` class
- Scoped enums (`enum class`) for type safety
- State transition logic using nested switches
- Console-based logging
- Hardware integration with Raspberry Pi 5 via libgpiod
- GPIO17 LED state indication

The system now supports real-time hardware feedback:

- CONTAINED → LED OFF
- Any other state → LED ON

Designed to be extendable for:

- Multi-LED status panels
- Physical buttons and motion sensors
- Web dashboard control
- File-based logging
- Random event simulation
- Timed escalation logic

---

## Hardware Requirements

- Raspberry Pi 5
- LED
- 220–330Ω resistor
- GPIO17 (BCM numbering)

---

## Build (Tested on Raspberry Pi 5)

Install dependencies:

```bash
sudo apt install build-essential libgpiod-dev
```

Compile with:

```bash
g++ main.cpp ContainmentSystem.cpp -o scp -lgpiod
```
Run:
```
./scp
```
or
```
sudo ./scp
```

## Future Improvements
- Random event simulation engine
- Probability-based breach escalation
- File-based logging
- Hardware integration layer (GPIO)
- Web-based control dashboard
- Transition table refactor

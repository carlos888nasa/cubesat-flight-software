# 🛰️ CubeSat Flight Software Suite

![Build Status](https://img.shields.io/badge/build-passing-brightgreen)
![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20WSL-blue)
![Language](https://img.shields.io/badge/language-C99%20%7C%20Python3-orange)
![License](https://img.shields.io/badge/license-MIT-green)

## 📖 Overview

This project is a high-fidelity implementation of a **CubeSat On-Board Computer (OBC)** flight software, designed to mimic the constraints and architecture of real space missions. 

Unlike standard simulations, this system utilizes a **Software-in-the-Loop (SIL)** and **Virtual Hardware-in-the-Loop (vHIL)** testing approach. The OBC runs deterministically, agnostic of whether it is communicating with a physics engine or real hardware sensors.

### 🎯 Core Objectives
- Implementation of a **deterministic scheduler** for soft-real-time task execution.
- Development of **GNC/ADCS algorithms** (Attitude Determination and Control System) for satellite detumbling.
- **Fault Detection, Isolation, and Recovery (FDIR)** mechanisms (e.g., Safe Mode transition on critical battery levels).
- **Telemetry logging and post-flight analytics** via a custom Ground Station.

---

## 🏗️ System Architecture & File Structure

The project is structured following aerospace industry standards to ensure separation of concerns between raw telemetry, processed reports, documentation, and source code.

```text
cubesat-flight-software/
├── obc/               # C99 Flight Software (Core, GNC, Comms, Storage)
├── ground_station/    # Python tools for post-flight telemetry analysis
├── logs/              # Raw data outputs (CSV blackbox files)
├── reports/           # Processed analytical outputs (PNG graphs)
├── docs/              # Static documentation (ICDs, Architecture, Manuals)
└── build/             # CMake compiled binaries
```

### 1. OBC (On-Board Computer) 🧠
* **Language:** C (C99 standard).
* **Role:** The "brain" of the satellite.
* **Key Features:**
    * Cyclic execution (10Hz deterministic control loop).
    * Storage Module: Blackbox telemetry logging to CSV.
    * Power & FDIR: Graceful degradation and Safe Mode upon battery depletion.
    * GNC: PID control algorithms for angular velocity stabilization (Detumbling).

### 2. Ground Station (Data Analytics) 📡
* **Language:** Python (`pandas`, `matplotlib`).
* **Role:** Mission control post-flight interface.
* **Key Features:**
    * Automated parsing of flight software logs.
    * High-resolution report generation for Power Systems and GNC performance.

---

## 🚀 Getting Started

### Prerequisites
* **OS:** Linux or Windows (via WSL2 - Ubuntu recommended).
* **Compiler:** GCC / CMake (3.10+).
* **Python:** 3.12+ (with `venv` module).

### Build & Run Instructions

**1. Clone the repository:**
```bash
git clone https://github.com/carlos888nasa/cubesat-flight-software.git
cd cubesat-flight-software
```

2. Build the Flight Software (OBC):
```bash
mkdir build && cd build
cmake ..
make
```

3. Execute a Flight Simulation:
```bash
# Still inside the build/ directory
./OBC
```
(This will run the flight sequence and generate a `flight_data.csv` in the `logs/` directory).

4. Generate Ground Station Reports:
Return to the project root and set up the Python environment to analyze the telemetry:

```bash
cd ..
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt

# Run the Ground Station parser
python ground_station/main.py
```
(Check the `reports/` folder for the generated telemetry graphs).

🛠️ Project Roadmap
[x] Phase 1: Core Architecture & Build System (CMake).

[x] Phase 2: Scheduler implementation (10Hz deterministic loop).

[x] Phase 3: Storage Module (CSV Blackbox Telemetry Logging).

[x] Phase 4: Power Management & FDIR Logic (Safe Mode).

[x] Phase 5: GNC - Controller implementation (Detumbling/PID).

[x] Phase 6: Ground Station Post-Flight Analytics (Python).

[ ] Phase 7: Comms Interface (Socket-based TM/TC uplink/downlink).

[ ] Phase 8: Hardware Abstraction Layer (HAL) for real Microcontroller Porting (ESP32/FreeRTOS).

👨‍💻 Author
Carlos - Aerospace Enthusiast & Embedded Developer
GitHub Profile

This project is developed for educational and portfolio purposes, demonstrating full-cycle embedded software development for aerospace applications.
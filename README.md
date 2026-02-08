# 🛰️ CubeSat Flight Software Suite

![Build Status](https://img.shields.io/badge/build-passing-brightgreen)
![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20WSL-blue)
![Language](https://img.shields.io/badge/language-C99%20%7C%20Python3-orange)
![License](https://img.shields.io/badge/license-MIT-green)

## 📖 Overview

This project is a high-fidelity implementation of a **CubeSat On-Board Computer (OBC)** flight software, designed to mimic the constraints and architecture of real space missions. 

Unlike standard simulations, this system decouples the **flight software** (firmware) from the **environment simulation** (physics), allowing for a **Virtual Hardware-in-the-Loop (vHIL)** testing approach. The OBC runs deterministically, agnostic of whether it is communicating with a physics engine or real hardware sensors.

### 🎯 Core Objectives
- Implementation of a **deterministic scheduler** for soft-real-time task execution.
- Development of **GNC/ADCS algorithms** (Attitude Determination and Control System).
- **Fault Detection, Isolation, and Recovery (FDIR)** mechanisms.
- Full **Telemetry and Telecommand (TM/TC)** pipeline via TCP sockets (simulating radio links).

---

## 🏗️ System Architecture

The system is distributed into three independent modules communicating over local network sockets, simulating the interfaces between hardware components.

```mermaid
graph TD;
    A[Physics Simulator] -- Sensor Data (I2C/SPI sim) --> B(OBC Firmware);
    B -- Actuator Cmds (PWM sim) --> A;
    B -- Telemetry (Downlink) --> C[Ground Station];
    C -- Commands (Uplink) --> B;

 ```
    
### 1. OBC (On-Board Computer) 🧠
* **Language:** C (C99 standard).
* **Role:** The "brain" of the satellite. It runs the flight logic.
* **Key Features:**
    * Cyclic execution (10Hz control loop).
    * Mode management (Safe, Detumble, Nominal).
    * Sensor fusion (Kalman Filter implementation planned).

### 2. Physics Simulator 🌌
* **Language:** Python.
* **Role:** Simulates the orbital environment and hardware interfaces.
* **Key Features:**
    * Orbital mechanics & magnetic field modeling.
    * Sensor noise injection (Gyro/Mag).
    * Rotational dynamics integration.

### 3. Ground Station 📡
* **Language:** Python (GUI).
* **Role:** Mission control interface.
* **Key Features:**
    * Real-time 3D attitude visualization.
    * Telecommand dispatching.
    * Health & Status monitoring.

---

## 🚀 Getting Started

### Prerequisites
* **OS:** Linux or Windows (via WSL2 - Ubuntu recommended).
* **Compiler:** GCC / CMake (3.10+).
* **Python:** 3.8+ (for Simulation & Ground Station).

### Build & Run

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/carlos888nasa/cubesat-flight-software.git](https://github.com/carlos888nasa/cubesat-flight-software.git)
    cd cubesat-flight-software
    ```

2.  **Build the Flight Software (OBC):**
    ```bash
    mkdir build && cd build
    cmake ..
    make
    ```

3.  **Run the System (In separate terminals):**
    * *Terminal 1 (Simulator):* `python3 simulator/main.py`
    * *Terminal 2 (OBC):* `./obc_main`
    * *Terminal 3 (Ground Station):* `python3 ground_station/main.py`

---

## 🛠️ Project Roadmap

- [x] **Phase 1:** Core Architecture & Build System (CMake).
- [x] **Phase 2:** Scheduler implementation (10Hz deterministic loop).
- [ ] **Phase 3:** Comms Interface (Socket-based TM/TC).
- [ ] **Phase 4:** GNC - B-Dot Controller (Detumbling).
- [ ] **Phase 5:** GNC - Attitude Determination (MEKF).
- [ ] **Phase 6:** Fault Injection & Recovery testing.

---

## 👨‍💻 Author

**Carlos** - *Aerospace Enthusiast & Embedded Developer*
[GitHub Profile](https://github.com/carlos888nasa)

*This project is developed for educational and portfolio purposes, demonstrating full-cycle embedded software development for aerospace applications.*
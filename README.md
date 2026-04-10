# 🛰️ CubeSat Flight Software Suite

<div align="center">

![Build Status](https://img.shields.io/badge/build-passing-brightgreen?style=flat-square)
![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20WSL2-blue?style=flat-square)
![Language](https://img.shields.io/badge/language-C99%20%7C%20Python3-orange?style=flat-square)
![License](https://img.shields.io/badge/license-MIT-green?style=flat-square)
![Status](https://img.shields.io/badge/status-active%20development-yellow?style=flat-square)

**A full-cycle embedded flight software stack for a 1U CubeSat — from attitude control to post-flight telemetry analytics.**

*Built to the constraints of real space missions: deterministic scheduling, graceful fault recovery, and hardware-agnostic design.*

</div>

---

## 📖 What Is This?

Most satellite simulations are monolithic scripts. This project takes a different approach: it **separates the flight firmware from the simulation environment**, mirroring how real missions are tested before launch.

The OBC (On-Board Computer) firmware runs in C99 as if it were on real hardware. A Python-based Ground Station parses its telemetry logs and generates analytical reports — the same post-flight analysis pipeline used in real mission operations.

**Core capabilities implemented:**
- Deterministic 10 Hz control loop with cyclic task scheduling
- PID-based detumbling controller (B-dot variant) for angular velocity stabilization
- Battery-aware FDIR with automatic Safe Mode transitions
- Blackbox telemetry logging to CSV (flight recorder)
- Post-flight analytics with automated report generation

---

## 🏗️ Architecture

The system is split into three independent layers, reflecting real spacecraft software architecture:

```
┌─────────────────────────────────────────────────────┐
│                  GROUND SEGMENT                     │
│  ground_station/     Python · pandas · matplotlib   │
│  Post-flight telemetry parsing & report generation  │
└──────────────────────┬──────────────────────────────┘
                       │  logs/flight_data.csv
┌──────────────────────▼──────────────────────────────┐
│                  FLIGHT SEGMENT                     │
│  obc/                C99 · CMake · GCC              │
│  ├── core/       Scheduler, main loop (10 Hz)       │
│  ├── gnc/        PID Detumbling Controller          │
│  ├── power/      Battery monitor & FDIR logic       │
│  └── storage/    CSV Blackbox telemetry writer      │
└─────────────────────────────────────────────────────┘
```

### OBC — Flight Software (C99) 🧠

The firmware follows a **cyclic executive** pattern (no RTOS), common in CubeSat missions due to its determinism and low overhead:

| Module | Responsibility |
|---|---|
| `core/scheduler` | Fixed 10 Hz loop, task dispatch |
| `gnc/detumble` | PID angular velocity controller |
| `power/fdir` | Battery monitoring, Safe Mode trigger |
| `storage/blackbox` | CSV telemetry logging |

### Ground Station — Analytics (Python) 📡

Parses raw `flight_data.csv` output and generates:
- **Power system report** — battery voltage curve, Safe Mode trigger events
- **GNC performance report** — angular velocity convergence, controller response

> 📁 Example outputs are available in the `reports/` directory.

---

## 📊 Example Telemetry Output

After a simulated flight, the blackbox logger produces structured CSV data:

```
timestamp_ms, mode,       batt_v, omega_x,  omega_y,  omega_z,  ctrl_torque
0,            NOMINAL,    8.20,   0.8500,   -0.6200,  0.4100,   0.0000
100,          NOMINAL,    8.19,   0.7923,   -0.5841,  0.3867,   -0.0245
200,          DETUMBLE,   8.18,   0.7201,   -0.5312,  0.3510,   -0.0489
...
4200,         NOMINAL,    7.95,   0.0312,   -0.0198,  0.0089,   -0.0012
5000,         SAFE_MODE,  6.80,   0.0289,   -0.0201,  0.0091,   0.0000
```

The Ground Station then plots this data automatically into the `reports/` folder.

---

## 🚀 Getting Started

### Prerequisites

| Tool | Version |
|---|---|
| GCC | Any recent version |
| CMake | 3.10+ |
| Python | 3.12+ |
| OS | Linux or WSL2 (Ubuntu recommended) |

### 1. Clone & Build the OBC

```bash
git clone https://github.com/carlos888nasa/cubesat-flight-software.git
cd cubesat-flight-software

# Build the flight software
mkdir build && cd build
cmake ..
make
```

### 2. Run a Flight Simulation

```bash
# From inside build/
./OBC
```

This executes the full flight sequence and writes telemetry to `logs/flight_data.csv`.

**Expected console output:**
```
[OBC] System boot. Initializing subsystems...
[SCHEDULER] 10Hz loop started.
[POWER] Battery: 8.20V — Mode: NOMINAL
[GNC] Detumbling engaged. omega: [0.85, -0.62, 0.41] rad/s
...
[FDIR] Battery critical: 6.80V — Entering SAFE MODE.
[OBC] Flight sequence complete. Telemetry saved to logs/flight_data.csv
```

### 3. Analyze Telemetry with the Ground Station

```bash
# Return to project root
cd ..

# Set up Python environment
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt

# Run the analytics pipeline
python ground_station/main.py
```

Check `reports/` for the generated plots.

---

## 📁 Project Structure

```
cubesat-flight-software/
├── obc/               # C99 Flight Software
│   ├── core/          #   Scheduler & main loop
│   ├── gnc/           #   Detumbling controller (PID)
│   ├── power/         #   Battery monitor & FDIR
│   └── storage/       #   Blackbox telemetry logger
├── ground_station/    # Python post-flight analytics
├── logs/              # Raw telemetry outputs (CSV)
├── reports/           # Generated analytical plots (PNG)
├── docs/              # Architecture docs & ICDs
├── CMakeLists.txt
├── requirements.txt
└── README.md
```

---

## 🗺️ Roadmap

| Phase | Feature | Status |
|---|---|---|
| 1 | Core architecture & CMake build system | ✅ Done |
| 2 | Deterministic 10 Hz scheduler | ✅ Done |
| 3 | Blackbox telemetry (CSV logging) | ✅ Done |
| 4 | Power management & FDIR (Safe Mode) | ✅ Done |
| 5 | GNC — Detumbling PID controller | ✅ Done |
| 6 | Ground Station post-flight analytics | ✅ Done |
| 7 | Socket-based TM/TC uplink/downlink | 🔄 In progress |
| 8 | HAL for microcontroller porting (ESP32 / FreeRTOS) | 📋 Planned |

---

## 🧠 Technical Deep-Dives

Interested in specific design decisions? These are the most technically interesting aspects of the project:

- **Why a cyclic executive instead of an RTOS?** — Determinism and simplicity are critical in embedded space systems where task timing must be provable. A cyclic executive with a fixed 10 Hz loop avoids priority inversion and scheduler overhead at the cost of flexibility.
- **B-dot vs. full PID detumbling** — The controller targets angular velocity directly rather than attitude, which is the correct approach for detumbling from an unknown initial spin state.
- **FDIR design** — Safe Mode is triggered by a voltage threshold with hysteresis to avoid mode-chattering near the boundary.

---

## 👨‍💻 Author

**Carlos** — Telecommunications Engineering Student & Aerospace Enthusiast

Focused on embedded systems for space applications, astrodynamics, and satellite communications.

[![LinkedIn](https://img.shields.io/badge/LinkedIn-Connect-0A66C2?style=flat-square&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/carlos-ortega-5b904a23b/)
[![GitHub](https://img.shields.io/badge/GitHub-Profile-181717?style=flat-square&logo=github&logoColor=white)](https://github.com/carlos888nasa)

---

*"Per Aspera Ad Astra" — Built for educational and portfolio purposes, demonstrating full-cycle embedded software development for aerospace applications.*
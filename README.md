[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.23631889.svg)](https://doi.org/10.5281/zenodo.23631889)
[![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![Standard](https://img.shields.io/badge/C99-MISRA--Compliant-brightgreen.svg)](#)
[![Memory](https://img.shields.io/badge/RAM-Zero--Heap%20(%3C128B%20Stack)-orange.svg)](#)

A deterministic, zero-heap causal state estimation operator engineered in standard C99 for resource-constrained, safety-critical microcontrollers (ARM Cortex-M0/M3/M4, bare-metal RISC-V). 

This project addresses the critical vulnerability of classical Kalman filters and moving-average algorithms under non-Gaussian impulse corruption and sensor lockups, eliminating floating-point matrix explosion while maintaining deterministic execution time.

---

## ⚡ Key Engineering Highlights

- **Zero `libm` Linkage**: Features an embedded Padé (2,2) matrix-exponential approximator. Runs natively on low-cost MCUs lacking hardware FPUs.
- **Hard Spike Rejection**: Implements a discrete 5-state FSM with a quadratic Lyapunov envelope to isolate single-frame non-Gaussian outliers without divergence.
- **Bounded Momentum Reacquisition**: Mitigates high-frequency finite-difference snapping during recovery from long-duration dropouts using physical velocity clamping and slew filtering.
- **Strict Hard Real-Time Guarantee (WCET)**:
  - Zero dynamic heap allocation (`malloc` free).
  - Stack footprint: < 128 bytes.
  - Worst-Case Execution Time: < 1.2 µs @ 48 MHz Cortex-M0+.

---

## 🔬 Benchmark & SIL Verification

Validated via Software-in-the-Loop (SIL) numerical fault injection under extreme conditions:
- **Impulse Corruption**: Injection of +20.0 outlier at t = 2.0 s (instantly clamped and rejected).
- **15-Frame Deadlock**: Sustained sensor latch-up with seamless reacquisition and zero velocity overshoot.

```text
[SIL Fault-Injection Benchmark Summary]
Metric                    Unprotected Diff    This Architecture
Max Transient Spike       +18.2 rad/s         +1.08 rad/s (Bounded)
FSM Limit-Cycle Chattering Observed           Eliminated via Hysteresis
Matrix Inversion Failure  Occasional          Mathematically Impossible

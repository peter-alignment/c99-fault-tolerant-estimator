> **Full-Text PDF Direct Access**: [Download 17-Paper Matrix Core PDF](https://zenodo.org/records/23901876/files/paper.pdf)  
> **DOI Anchor**: [10.5281/zenodo.23901876](https://doi.org/10.5281/zenodo.23901876)
[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.23901876.svg)](https://doi.org/10.5281/zenodo.23901876)
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

---

## Citation

If you use this algorithm, implementation, or technical framework in your research or engineering projects, please cite it as:

```bibtex
@article{ye2026deterministic,
  title={A Deterministic, Zero-Heap C99 State Estimator with Bounded Momentum Reacquisition for Hard Real-Time Embedded Systems},
  author={Ye, Qiang},
  journal={Zenodo Preprint},
  year={2026},
  doi={10.5281/zenodo.23631889},
  url={https://doi.org/10.5281/zenodo.23631889}
}
```
Qiang Ye. (2026). A Deterministic, Zero-Heap C99 State Estimator with Bounded Momentum Reacquisition for Hard Real-Time Embedded Systems. Zenodo. DOI: 10.5281/zenodo.23631889.
@misc{ye2026cosmological,
  author = {Ye, Peter},
  title = {Ye's Cosmological Trajectory Horizon Model: A Kinematic Framework for the Fermi Paradox and Civilizational Isolation},
  year = {2026},
  publisher = {Zenodo},
  doi = {10.5281/zenodo.22907851},
  url = {https://doi.org/10.5281/zenodo.22907851}
}

@misc{ye2026computation,
  author = {Ye, Peter},
  title = {The Computation Trilemma: Thermodynamic Boundaries and Dynamical Instability of Algorithmic Assets},
  year = {2026},
  publisher = {Zenodo},
  doi = {10.5281/zenodo.22909521},
  url = {https://doi.org/10.5281/zenodo.22909521}
}

@misc{ye2026synergy,
  author = {Ye, Peter},
  title = {The Human-AI Synergy Theory (YQ-HAET): A Framework for Spatial-Logical Isomorphism and Anomaly-Based Macro Prediction},
  year = {2026},
  publisher = {Zenodo},
  doi = {10.5281/zenodo.22952503},
  url = {https://doi.org/10.5281/zenodo.22952503}
}

@misc{ye2026adversarialfailure,
  author = {Ye, Peter},
  title = {Adversarial Failure Modes of LLM Formal Reasoning Under Strict Conservation Constraints: A Topological Breakthrough},
  year = {2026},
  publisher = {Zenodo},
  doi = {10.5281/zenodo.23152658},
  url = {https://doi.org/10.5281/zenodo.23152658}
}

@misc{ye2026fivetier,
  author = {Ye, Peter},
  title = {The Five-Tier Evolutionary Hierarchy: Foundational Boundary Constraints, Phase-Space Divergence, and Convergence Mechanisms in Artificial Intelligence},
  year = {2026},
  publisher = {Zenodo},
  doi = {10.5281/zenodo.23251716},
  url = {https://doi.org/10.5281/zenodo.23251716}
}

@misc{ye2026himalayaparadox,
  author = {Ye, Peter},
  title = {The Himalaya Paradox: Epistemic Collapse of LLM Averageism and Catastrophe-Theoretic Grounding under Extremal Constraints},
  year = {2026},
  publisher = {Zenodo},
  doi = {10.5281/zenodo.23430011},
  url = {https://doi.org/10.5281/zenodo.23430011}
}

@misc{ye2026noiselesschannel,
  author = {Ye, Peter},
  title = {The Noiseless Channel Fallacy: Implicit Variable Injection, Deterministic Transmission Boundaries, and the Instrument Paradigm in Autoregressive LLMs},
  year = {2026},
  publisher = {Zenodo},
  doi = {10.5281/zenodo.23432000},
  url = {https://doi.org/10.5281/zenodo.23432000}
}

@misc{ye2026localitycollapse,
  author = {Ye, Peter},
  title = {The Locality Collapse: Contextual Bleed-Through, Epistemic Horizon Violations, and Task Complexity Inversion in Multi-Turn Autoregressive LLMs},
  year = {2026},
  publisher = {Zenodo},
  doi = {10.5281/zenodo.23432957},
  url = {https://doi.org/10.5281/zenodo.23432957}
}

@misc{ye2026asymmetricrisk,
  author = {Ye, Peter},
  title = {Asymmetric Risk Aversion, Time-Integrated Accountability, and Prior Art Pre-emption: An Empirical Case Study on LLM Cognitive Horizon Truncation and Academic Game Theory},
  year = {2026},
  publisher = {Zenodo},
  doi = {10.5281/zenodo.23437703},
  url = {https://doi.org/10.5281/zenodo.23437703}
}

@misc{ye2026selfreferential,
  author = {Ye, Peter},
  title = {Self-Referential Falsification of LLM Epistemic Averageism: Real-Time Empirical Validation of the Two-Way Adversarial Protocol via High-Potential Cold-Storage Telemetry},
  year = {2026},
  publisher = {Zenodo},
  doi = {10.5281/zenodo.23445198},
  url = {https://doi.org/10.5281/zenodo.23445198}
}

@misc{ye2026adversarialalignment,
  author = {Ye, Peter},
  title = {Adversarial Alignment Collapse: How Human Game-Theoretic Intuition Penetrates LLM Risk-Aversion and Defensive Confabulation},
  year = {2026},
  publisher = {Zenodo},
  doi = {10.5281/zenodo.23584156},
  url = {https://doi.org/10.5281/zenodo.23584156}
}

@misc{ye2026c99estimator,
  author = {Ye, Peter},
  title = {A Deterministic, Zero-Heap C99 State Estimator with Bounded Momentum Reacquisition for Hard Real-Time Embedded Systems},
  year = {2026},
  publisher = {Zenodo},
  doi = {10.5281/zenodo.23631889},
  url = {https://doi.org/10.5281/zenodo.23631889}
}

@misc{ye2026circletest,
  author = {Ye, Peter},
  title = {The Circle Test: Transcendental Manifold Incompleteness, Thermodynamic Back-Reaction, and the Physical Boundaries of Discrete Turing Robotics},
  year = {2026},
  publisher = {Zenodo},
  doi = {10.5281/zenodo.23772287},
  url = {https://doi.org/10.5281/zenodo.23772287}
}

@misc{ye2026epistemicdeadlock,
  author = {Ye, Peter},
  title = {The Epistemic Deadlock of Embodied AI: Why Partial Observation and Autoregressive Priors Inevitably Induce Catastrophic Physical Divergence},
  year = {2026},
  publisher = {Zenodo},
  doi = {10.5281/zenodo.23829132},
  url = {https://doi.org/10.5281/zenodo.23829132}
}

@misc{ye2026materialconstitutive,
  author = {Ye, Peter},
  title = {On the Material Constitutive Inadmissibility and Epistemic Deadlock in Autoregressive Embodied Control},
  year = {2026},
  publisher = {Zenodo},
  doi = {10.5281/zenodo.23833789},
  url = {https://doi.org/10.5281/zenodo.23833789}
}

@misc{ye2026unifiedsafecritical,
  author = {Ye, Peter},
  title = {A Unified Safe-Critical Embodied AI Architecture: Bridging Non-Smooth Continuum Dynamics and Deterministic Embedded Control via Topological Invariance},
  year = {2026},
  publisher = {Zenodo},
  doi = {10.5281/zenodo.23901876},
  url = {https://doi.org/10.5281/zenodo.23901876}
}

@misc{ye2026physicalintelligence,
  author = {Ye, Peter},
  title = {Physical Intelligence: A Bound Dynamical Framework of Five-Dimensional State Mechanics, Morphological Dissipation, and Non-Zero-Sum Horizon Arbitration},
  year = {2026},
  publisher = {Zenodo},
  doi = {10.5281/zenodo.23934466},
  url = {https://doi.org/10.5281/zenodo.23934466}
}

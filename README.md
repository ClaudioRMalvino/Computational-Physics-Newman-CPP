# Computational Physics in Modern C++

Solutions to the exercises in Mark Newman's *Computational Physics*, written in C++23.

The book teaches numerical methods in Python. This project works through the same exercises
in C++, focusing on correct numerics, clean and idiomatic modern C++, and performance. I first wrote the project in C++20 while learning to write scientific code. I am now rewriting it in C++23 using techniques I learned in the University of Cambridge's MPhil in Scientific Computing. I work on it in my free time, so progress is sporadic.

## Approach

- **Modern C++23:** `std::print`/`std::println`, `constexpr` physical constants and maths helpers,
  `std::optional`, ranges, and strong const-correctness.
- **Shared code:** physical constants, unit conversions, numerical routines and I/O helpers live
  in reusable headers instead of being duplicated across exercises.
- **Parallelism:** OpenMP for expensive loops. For example, Exercise 2.9 computes the Madelung
  constant over roughly 8 x 10^9 lattice sites.
- **C++ for computation, Python for plots:** the C++ programs write their results to files, and
  Python scripts (matplotlib, NumPy, pandas, managed with [pixi](https://pixi.sh)) read those files
  and make the figures. This replaces the earlier `matplotlib-cpp` setup.
- **Documentation:** every exercise and header has Doxygen comments, and you can generate HTML
  documentation from them.

## Project layout

```
.
├── src/
│   └── Chapter_N/          # One executable per exercise (exercise_N_M.cpp)
├── include/
│   ├── common/             # Constants, unit conversions, numerical methods
│   ├── io/                 # Input/output helpers
│   └── Chapter_N/          # Types specific to one chapter
├── data/                   # Input data sets supplied with the textbook
├── legacy/                 # Original C++20 solutions waiting to be ported (not built)
├── CMakeLists.txt
├── Doxyfile
└── pixi.toml               # Python environment for plotting and Doxygen
```

## Building

You need CMake 3.25 or newer, a compiler with C++23 support (for example GCC 14 or newer), and OpenMP.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
./build/exercise_2_9
```

CMake builds every `.cpp` file under `src/` as its own executable, named after the file.

## Python environment and documentation

```sh
pixi install            # Set up Python, NumPy, pandas, matplotlib and Doxygen
pixi run doxygen        # Generate HTML documentation in html/
```

## Progress

A ticked box means the exercise has been rewritten in C++23 under `src/`. Unticked exercises
either have an older solution in `legacy/` waiting to be ported, or have not been started yet.

| Chapter | Topic                                       | Status      |
|---------|---------------------------------------------|-------------|
| 2       | Python Programming for Physicists           | In progress |
| 3       | Graphics and Visualization                  | Legacy only |
| 4       | Accuracy and Speed                          | Legacy only |
| 5       | Integrals and Derivatives                   | Legacy only |
| 6       | Solution of Linear and Nonlinear Equations  | Not started |
| 7       | Fourier Transforms                          | Not started |
| 8       | Ordinary Differential Equations             | Not started |
| 9       | Partial Differential Equations              | Not started |
| 10      | Random Processes and Monte Carlo Methods    | Not started |

### Chapter 2: Python Programming for Physicists

- [x] 2.1: Another ball dropped from a tower
- [x] 2.2: Altitude of a satellite
- [x] 2.3: Cartesian to polar coordinates
- [x] 2.4: Relativistic spaceship travel
- [x] 2.5: Quantum potential step
- [x] 2.6: Planetary orbits
- [x] 2.8: Skipped
- [x] 2.7: Catalan numbers
- [x] 2.9: The Madelung constant (OpenMP)
- [x] 2.10 (a-c): The semi-empirical mass formula
- [ ] 2.10 (d): The semi-empirical mass formula (legacy)
- [ ] 2.11: Binomial coefficients (legacy)
- [ ] 2.12: Prime numbers (legacy)
- [ ] 2.13: Recursion (legacy)

### Chapter 3: Graphics and Visualization

- [ ] 3.1: Plotting experimental data (legacy)
- [ ] 3.2: Plotting curves (legacy)
- [ ] 3.3: Curve plotting (legacy)
- [ ] 3.6: Feigenbaum plot (legacy)
- [ ] 3.8: Least-squares fitting and the photoelectric effect (legacy)

### Chapter 4: Accuracy and Speed

- [ ] 4.2: Quadratic equations (legacy)
- [ ] 4.4: Calculating integrals (legacy)

### Chapter 5: Integrals and Derivatives

- [ ] 5.1: The trapezoidal rule (legacy)
- [ ] 5.2: The extended Simpson's rule (legacy)
- [ ] 5.3: Integrating e^(-t^2) (legacy)
- [ ] 5.4 (a): The diffraction limit of a telescope (legacy)
- [ ] 5.6: Error on Simpson's rule (legacy)
- [ ] 5.7: Integrating sin^2(sqrt(100x)) (legacy)

## Reference

Mark Newman, *Computational Physics*, revised and expanded edition, CreateSpace, 2013.

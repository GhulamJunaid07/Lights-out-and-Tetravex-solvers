# Lights-out-and-Tetravex-solvers

This repository contains algorithmic solvers for two classic combinatorial puzzles:

- **Lights Out (5×5)** — solved optimally using full-state Breadth-First Search (BFS)
- **Tetravex** — solved as a Constraint Satisfaction Problem (CSP) using Depth-First Search (DFS), backtracking, constraint propagation, and heuristics

These implementations accompany an analytical paper studying the modeling, complexity, and optimization strategies behind both solutions.

## Contents
lights_out.cpp # Optimal BFS solver for 5×5 Lights Out

tetravex.cpp # Heuristic DFS-based Tetravex solver

---

## Lights Out Solver

### Problem
Given a 5×5 grid of lights, clicking a cell toggles that cell and its four orthogonal neighbors.  
The goal is to turn all lights off using the minimum number of moves.

### Approach
- Board encoded as a **25-bit integer**
- Each click is a **bitwise XOR transition**
- Full **Breadth-First Search** over all \(2^{25}\) states
- Precomputes shortest distance and parent pointers for solution reconstruction

### Properties
- ✔ Guarantees **optimal solutions**
- ✔ Detects **unsolvable configurations**
- ✖ High memory usage (stores all states)

---

## Tetravex Solver

### Problem
Given \(n^2\) square tiles, each with numbers on its four sides, place them in an \(n \times n\) grid such that all adjacent edges match.

### Approach
- Modeled as a **Constraint Satisfaction Problem**
- Uses **DFS with backtracking**
- Enforces **local edge constraints** at every placement
- Heuristic placement order (center-first expansion)
- Aggressive pruning via candidate filtering

### Notes
- This solver is heuristic-based
- Designed for correctness and strong pruning, not guaranteed polynomial time
- Performs well for small to moderate grid sizes

---

## How to Compile and Run

### Requirements
- C++17 compatible compiler (e.g., `g++`)

### Compile
```bash
g++ -std=gnu++17 lights_out.cpp -O2 -o lights_out
g++ -std=gnu++17 tetravex.cpp -O2 -o tetravex
```

Run
Lights Out
```
./lights_out
```

Input: 
5 lines of 5 integers (0 or 1) with space separated characters, representing the initial grid.

Tetravex
```
./tetravex
```

Input:

Integer n

Then n^2 lines, each containing 4 integers representing tile edges (top, right, bottom, left), space separated.

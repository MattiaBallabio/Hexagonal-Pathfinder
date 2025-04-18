# Hexagonal Pathfinder

![Finished](https://img.shields.io/badge/status-finished-brightgreen?style=for-the-badge&logo=checkmarx&logoColor=white)

A C++ project developed for the **Data Structures and Objects** course at **Youngstown State University (YSU)**. This program generates a hexagonal maze of up to 50×50 in size, computes the optimal path from origin to destination, and exports the final result as a `.ps` (PostScript) file for graphical representation.

## 📌 Features

- **Procedural generation** of fully connected hexagonal mazes using a randomized spanning tree algorithm
- **Customizable maze size** (up to 50x50) with optional removable walls
- **Efficient pathfinding** from start to goal using BFS
- **PostScript output** for graphical representation

## 🧠 Core Concepts

This project demonstrates practical application of core data structures and algorithms, including:

- **2D Arrays** to represent maze walls using bit masking
- **Disjoint Set Union (DSU)** to ensure maze connectivity (Kruskal-style spanning tree)
- **Queues and BFS traversal** for pathfinding
- **Sampler** for randomized wall and edge selection

## ⚙️ Technologies Used

- **C++** for all implementation
- **GNU Make** for building the project
- **Custom data structures** including `DisjointSet`, `Queue`, and `Sampler`
- **PostScript** for graphical output rendering

## 🛠️ Build Instructions

### Prerequisites
- A C++ compiler (G++ recommended)
- `make` utility

### To build the project:
```bash
make
```

### To clean build artifacts:
```bash
make clean
```

## 🗂️ Output

### To run the program:
```bash
./pathfinder <rows> <columns> <additionalRemovableWalls>
```
Both rows and columns go up to **50**. The number of additional walls the user needs removed is optional and can be left blank.

The program generates a `.ps` file that visually represents:
- The hexagonal maze layout
- The shortest path from origin (top left) to end (bottom right)

Compatible with PostScript viewers such as Ghostscript, Evince, or Okular.

## Notes
- Maze generation uses 6-bit masks per cell to represent walls in six directions
- Each direction follow even-q layout for hex grids
- The pathfinding starts from the bottom-right corner and works back to the starts

## 🧪 Status
This project is a functional prototype and primarily serves educational and testing purposes.

### 📄 License
Feel free to use and adapt this code for non-commercial or learning use cases.
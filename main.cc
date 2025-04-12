#include <iostream>
#include "hexpathfinder.h"
#include "disjointSet.h"
#include "sampler.h"
#include "queue.h"

using namespace std;

uint8_t maze[MAX_ROWS][MAX_COLS];
Queue<int> q;

// Function used once to generate a nR * nC hexagonal maze
// which then removes a minimum amount of (nR * nC) - 1 walls
// to make it possible to reach the end.
void generateTreeMaze(int nR, int nC) {
    for (int r = 0; r < nR; r++) {
        for (int c = 0; c < nC; c++) {
            maze[r][c] = 0x3F;
        }
    }

    DisjointSet ds(nR * nC);
    Sampler sampler(3 * nR * nC);

    int i = 0;
    while (i < nR * nC - 1) {
        uint32_t e = sampler.getSample();
        int c1 = e % nC;
        e = e / nC;
        int r1 = e % nR;
        int dir = e /nR;
        int r2 = r1;
        int c2 = c1;

        // Calculate adjacent cell based on direction
        switch(dir) {
            case 0:
                r2 = r1 - 1;
                break;
            case 1:
                r2 = r1 - 1 + (c1 % 2);
                c2 = c1 + 1;
                break;
            case 2:
                r2 = r1 + (c1 % 2);
                c2 = c1 + 1;
                break;
            case 3:
                r2 = r1 + 1;
                break;
            case 4:
                r2 = r1 + (c1 % 2);
                c2 = c1 - 1;
                break;
            case 5:
                r2 = r1 - 1 + (c1 % 2);
                c2 = c1 - 1;
                break;
        }

        // Check if adjacent cell is on map
        if (r2 < 0 || r2 >= nR || c2 < 0 || c2 >= nC) {
            continue;
        }

        int cell1 = r1 * nC + c1;
        int cell2 = r2 * nC + c2;

        if (ds.find(cell1) != ds.find(cell2)) {
            // Remove walls between cells
            maze[r1][c1] &= ~(1 << dir);
            maze[r2][c2] &= ~(1 << ((dir + 3) % 6));
            
            ds.join(cell1, cell2);
            i++;
        }
    }
}

// Function used once to remove any additional walls.
// This is technically optional since it is already possible
// to find a solution right after the maze is generated.
void removeAdditionalWalls(int nR, int nC, int w) {
    Sampler walls(3 * nR * nC);

    for (int i = 0; i < w-1; i++) {
        bool haveWall = false;
        uint32_t e;
        int r1, c1, dir, r2, c2;
        while (!haveWall) {
            e = walls.getSample();
            c1 = e % nC;
            e = e / nC;
            r1 = e % nR;
            dir = e / nR;
            // Set (r2, c2) to the coordinates of the cell adjacent to (r1, c1)
            r2 = r1;
            c2 = c1;
            // Calculate adjacent cell based on direction
            switch(dir) {
                case 0:
                    r2 = r1 - 1;
                    break;
                case 1:
                    r2 = r1 - 1 + (c1 % 2);
                    c2 = c1 + 1;
                    break;
                case 2:
                    r2 = r1 + (c1 % 2);
                    c2 = c1 + 1;
                    break;
                case 3:
                    r2 = r1 + 1;
                    break;
                case 4:
                    r2 = r1 + (c1 % 2);
                    c2 = c1 - 1;
                    break;
                case 5:
                    r2 = r1 - 1 + (c1 % 2);
                    c2 = c1 - 1;
                    break;
            }

            // Check if adjacent cell is valid
            if (r2 < 0 || r2 >= nR || c2 < 0 || c2 >= nC) {
                continue;
            }

            // Check if wall exists
            if (maze[r1][c1] & (1 << dir)) {
                haveWall = true;
            }
        }

        // Remove the walls
        maze[r1][c1] &= ~(1 << dir);
        maze[r2][c2] &= ~(1 << ((dir + 3) % 6));
    }
}

// Function that finds the shortest path to the end of the maze
// perfoming a Breadth-first search.
void findPath(uint8_t maze[MAX_ROWS][MAX_COLS], int nR, int nC) {
    int count[MAX_ROWS][MAX_COLS];

    for (int row = 0; row < nR; row++) {
        for (int col = 0; col < nC; col++) {
            count[row][col] = -1;
        }
    }

    int e = (nR - 1) * nC + (nC - 1);
    q.enqueue(e);
    count[nR - 1][nC - 1] = 0;

    // BFS Loop
    while (!q.isEmpty()) {
        e = q.dequeue();
        int row = e / nC;
        int col = e % nC;

        // Check all 6 directions
        for (int dir = 0; dir < 6; dir++) {
            int newRow = row, newCol = col;
            
            // Calculate neighbor coordinates
            switch (dir) {
                case 0: newRow = row - 1; break;
                case 1: newRow = row - 1 + (col % 2); newCol++; break;
                case 2: newRow = row + (col % 2);     newCol++; break;
                case 3: newRow = row + 1; break;
                case 4: newRow = row + (col % 2);     newCol--; break;
                case 5: newRow = row - 1 + (col % 2); newCol--; break;
            }

            // Check if neighbor is valid and accessible
            if (newRow >= 0 && newRow < nR && newCol >= 0 && newCol < nC) {
                if (!(maze[row][col] & (1 << dir))) {  // Wall check
                    if (count[newRow][newCol] == -1) { // Unvisited check
                        count[newRow][newCol] = count[row][col] + 1;
                        q.enqueue(newRow * nC + newCol);
                    }
                }
            }
        }
    }

    // Mark solution path (from start to exit)
    int row = 0, col = 0;
    maze[row][col] |= VISITED;

    while (count[row][col] != 0) {
        bool moved = false;
        
        for (int dir = 0; dir < 6; dir++) {
            int newRow = row, newCol = col;
            
            // Calculate neighbor coordinates
            switch (dir) {
                case 0: newRow--; break;
                case 1: newRow = row - 1 + (col % 2); newCol++; break;
                case 2: newRow = row + (col % 2);     newCol++; break;
                case 3: newRow++; break;
                case 4: newRow = row + (col % 2);     newCol--; break;
                case 5: newRow = row - 1 + (col % 2); newCol--; break;
            }

            // Check if neighbor is valid and closer to exit
            if (newRow >= 0 && newRow < nR && newCol >= 0 && newCol < nC) {
                if (!(maze[row][col] & (1 << dir))) {  // No wall
                    if (count[newRow][newCol] == count[row][col] - 1) {
                        row = newRow;
                        col = newCol;
                        maze[row][col] |= VISITED;
                        moved = true;
                        break;
                    }
                }
            }
        }
    }
}

// Main function. It checks for 3 numbers, no. of rows, no. of columns,
// and no. of additional walls to be removed.
int main(int argc, char *argv[]) {
    // This does not check if the user has entered the no. of walls to remove
    // since it is optional.
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <rows> <columns> <removeWalls (Optional)>" << endl;
        return 1;
    }

    int nR = atoi(argv[1]);
    int nC = atoi(argv[2]);
    int w = atoi(argv[3]); // If the no. of walls has not been entered, it will automatically be 0.

    if (nR <= 0 || nR > MAX_ROWS || nC <= 0 || nC > MAX_COLS) {
        cerr << "Maze dimensions must be between 1 and " << MAX_ROWS << endl;
        return 1;
    }

    cout << "Generating " << nR << "x" << nC << " maze..." << endl;
    generateTreeMaze(nR, nC);
    cout << "Maze generated. Removing " << w << " walls..." << endl;
    removeAdditionalWalls(nR, nC, w);
    cout << "Finding path..." << endl;
    findPath(maze, nR, nC);
    cout << "Writing to maze.ps..." << endl;
    printMaze(maze, nR, nC);
    cout << "Done!" << endl;

    return 0;
}
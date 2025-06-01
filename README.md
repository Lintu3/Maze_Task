# Maze Task Solver

## Overview

**Maze Task Solver** is an interactive C program that finds the shortest path from a start point (`^`) to the nearest exit (`E`) in a maze using Breadth-First Search (BFS).

The program reads a maze from a text file, marks the shortest path with `+`, and allows you to set a maximum number of moves for the solution.

Example files are in the repository.
---

## Maze File Format

- `#` : Wall  
- ` ` : Open space  
- `^` : Start position (exactly one required)  
- `E` : Exit position (one or more allowed)  
- `+` : Path (marked by the program)

**Example:**
```
#######
#    E#
# #####
#     #
#^#####
```

---

## How to Use

1. **Compile the Program**

   Open a terminal in the project directory and run:
   ```
   gcc -o Maze_task Maze_task.c
   ```
 
  If there are problems with compiling the file with windows. Check this link: https://code.visualstudio.com/docs/cpp/config-mingw
   for Visual Studio Code C/C++ compiler

3. **Prepare Your Maze File**

   - Create a text file (e.g., `maze.txt`) in the same directory.
   - Follow the maze format above.

4. **Run the Program**

   ```
   ./Maze_task
   ```
   or on Windows:
   ```
   Maze_task.exe
   ```

5. **Follow the Prompts**

   - Enter the maze file name (e.g., `maze.txt`).
   - Enter the maximum number of moves (or press Enter for no limit).
   - The program will display the maze with the shortest path marked.
   - If no solution is found or the path exceeds the move limit, you will be notified.
   - You can solve another maze or type `exit` at any prompt to quit.

---

## Features

- **Shortest Path:** Finds the shortest path to the nearest exit using BFS.
- **Multiple Exits:** Automatically finds the closest exit if there are several.
- **Move Limit:** Optionally restricts the solution to a maximum number of moves.
- **Interactive:** Prompts for file name and move limit; allows repeated use.
- **Clear Output:** Prints the maze with the path marked and the path length.

---

## Example Session

```
Maze Task Solver
Enter maze file name (or type 'exit' to quit): maze.txt
Enter max moves (or press Enter for no limit, or type 'exit' to quit): 20
Searching for exit...

#######
#++++E#
#+#####
#+    #
#^#####

Path length = 6 moves

---
You can solve another maze or type 'exit' at any prompt to quit.
```

---

## Notes

- The maze must contain exactly one `^` (start).
- The maze can contain one or more `E` (exits).
- The program supports mazes up to 100x100 in size.
- If no solution is found, or the path is longer than the move limit, you can try another maze or exit.

---

## License

This project is for educational and personal use.

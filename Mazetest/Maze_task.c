// Maze_task.c
// Interactive maze solver that prompts for maze file and max moves.
//
// Maze file format:
//   '#' = wall
//   ' ' = open space
//   '^' = start (exactly one)
//   'E' = exit  (one or more)
//   '+' = path (marked by the program)
//
// The program finds the shortest path (in steps) using BFS (Breadth-first search).
// It marks the path (excluding start '^' and exit 'E') with '+'
// If you supply max_moves and the shortest path exceeds it,
// the program reports “No solution within X moves.”
// If no exit is found, it prompts for another maze or exit command.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Constants for maximum maze size
#define MAX_ROWS 100
#define MAX_COLS 100

// Node structure to represent a position in the maze
typedef struct { int r, c; } Node;

// Directions for moving in the maze: up, down, left, right
static const int DR[4] = {-1, +1,  0,  0};
static const int DC[4] = { 0,  0, -1, +1};

int main() {
    // Main loop for the maze solver
    while (1) {
        //Variables for maze file and max moves
        char maze_file[256];
        char max_moves_str[32];
        int max_moves = -1;

        //Command prompt interface
        printf("Maze Task Solver\n");
        printf("Enter maze file name (or type 'exit' to quit): ");
        if (!fgets(maze_file, sizeof(maze_file), stdin)) {
            fprintf(stderr, "Error reading file name.\n");
            continue;
        }
        //Remove newline character from input
        maze_file[strcspn(maze_file, "\r\n")] = 0;
        //Exit condition
        if (strcmp(maze_file, "exit") == 0) {
            printf("Exiting program.\n");
            break;
        }

        //Prompt for max moves
        printf("Enter max moves (or press Enter for no limit, or type 'exit' to quit): ");
        if (!fgets(max_moves_str, sizeof(max_moves_str), stdin)) {
            fprintf(stderr, "Error reading max moves.\n");
            continue;
        }
        //Exit condition
        if (strncmp(max_moves_str, "exit", 4) == 0) {
            printf("Exiting program.\n");
            break;
        }
        //Parse max_moves if provided
        if (max_moves_str[0] != '\n' && max_moves_str[0] != '\0') {
            max_moves = atoi(max_moves_str);
            if (max_moves <= 0) {
                fprintf(stderr, "max_moves must be positive\n");
                continue;
            }
        }

        //Open maze file
        FILE *fp = fopen(maze_file, "r");
        if (!fp) {
            perror("fopen");
            continue;
        }

        //Initialize maze and find start
        char maze[MAX_ROWS][MAX_COLS+1];
        int rows = 0, cols = 0;
        Node start = {-1, -1};

        //Read maze from file and locate start
        while (fgets(maze[rows], sizeof(maze[rows]), fp) && rows < MAX_ROWS) {
            int len = strlen(maze[rows]);
            if (maze[rows][len-1] == '\n') maze[rows][--len] = 0;
            if (len > cols) cols = len;
            for (int c = 0; c < len; c++) {
                if (maze[rows][c] == '^') start = (Node){rows, c};
            }
            rows++;
        }
        fclose(fp);

        //must have a start
        if (start.r < 0) {
            fprintf(stderr, "Maze must have a '^' start.\n");
            continue;
        }

        //BFS setup (Breadth-first search)
        bool visited[MAX_ROWS][MAX_COLS] = {0};
        Node parent[MAX_ROWS][MAX_COLS];
        Node queue[MAX_ROWS*MAX_COLS];
        int head = 0, tail = 0;

        //BFS initialization
        queue[tail++] = start;
        visited[start.r][start.c] = true;
        parent[start.r][start.c] = (Node){-1, -1};

        //BFS loop to find the nearest exit
        printf("Searching for exit...\n");
        bool found = false;
        Node exit_found = {-1, -1};
        while (head < tail) {
            Node cur = queue[head++];
            // If reach any exit 'E'  stop
            if (maze[cur.r][cur.c] == 'E') {
                found = true;
                exit_found = cur;
                break;
            }
            //Explore neighbors
            for (int d = 0; d < 4; d++) {
                int nr = cur.r + DR[d], nc = cur.c + DC[d];
                if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
                char ch = maze[nr][nc];
                if (visited[nr][nc]) continue;
                if (ch == '#' || ch == 0) continue;
                visited[nr][nc] = true;
                parent[nr][nc] = cur;
                queue[tail++] = (Node){nr, nc};
            }
        }

        //If no exit found ask again
        if (!found) {
            puts("No solution found. Try another maze or type 'exit' to quit.");
            continue;
        }

        //Reconstruct path from start to found exit
        Node path[MAX_ROWS*MAX_COLS];
        int path_len = 0;
        Node cur = exit_found;
        //Backtrack from exit to start using parent pointers
        while (!(cur.r == start.r && cur.c == start.c)) {
            path[path_len++] = cur;
            cur = parent[cur.r][cur.c];
        }
        //Add start to path
        path[path_len++] = start;
        int moves = path_len - 1;

        //Check move limit
        if (max_moves > 0 && moves > max_moves) {
            printf("No solution within %d moves (shortest is %d).\n", max_moves, moves);
            continue;
        }

        //Mark path in maze excluding start and exit
        for (int i = 1; i < path_len-1; i++) {
            int r = path[i].r, c = path[i].c;
            if (maze[r][c] == ' ') maze[r][c] = '+';
        }

        //Print the maze with the path
        for (int r = 0; r < rows; r++) puts(maze[r]);
        printf("\nPath length = %d moves\n", moves);

        printf("\n---\nYou can solve another maze or type 'exit' at any prompt to quit.\n\n");
    }
    printf("Thank you for using the Maze Task Solver!\n");
    return 0;
}

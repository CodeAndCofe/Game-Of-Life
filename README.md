# Game of Life

A small C implementation of Conway's Game of Life created as a 42 exam-style exercise.

This program:
- builds an initial grid from stdin keystrokes,
- runs the simulation for a fixed number of generations,
- prints the final grid to stdout.

## Rules used

Each cell is either dead (`0`) or alive (`1`). For every generation:

1. A live cell with fewer than 2 live neighbors dies.
2. A live cell with 2 live neighbors survives.
3. A live cell with 3 live neighbors survives.
4. A live cell with more than 3 live neighbors dies.
5. A dead cell with exactly 3 live neighbors becomes alive.

Neighbors are the 8 surrounding cells. Out-of-bounds neighbors are ignored.

## Build

From the repository root:

```bash
gcc -Wall -Wextra -Werror /home/runner/work/Game-Of-Life/Game-Of-Life/gameoflife/main.c -o /home/runner/work/Game-Of-Life/Game-Of-Life/gameoflife/gameoflife
```

## Run

```bash
/home/runner/work/Game-Of-Life/Game-Of-Life/gameoflife/gameoflife <width> <height> <iterations>
```

Example:

```bash
printf 'xdddsss' | /home/runner/work/Game-Of-Life/Game-Of-Life/gameoflife/gameoflife 10 6 5
```

## Input behavior (stdin)

The program reads stdin one byte at a time before simulation starts.

- `w` move cursor up
- `s` move cursor down
- `a` move cursor left
- `d` move cursor right
- `x` toggle pen mode on/off

Details:
- Cursor starts at `(0, 0)`.
- Movement is clamped to grid bounds.
- While pen mode is ON, the current cursor cell is set alive after each processed input character.

This means stdin is used to "draw" the initial live cells.

## Output behavior

After running all iterations, the program prints only the final generation:

- live cell: `o`
- dead cell: space (` `)
- one newline per row

## Implementation notes

- Uses variable-length arrays sized from CLI arguments:
  - `int map[height][width]`
  - `int temp[height][width]`
- Uses a second grid (`temp`) so each generation is computed from the previous state.
- Neighbor counting is done by scanning relative offsets `[-1..1]` for row/column and skipping `(0, 0)`.

## Current limitations

- No argument validation beyond requiring 3 arguments.
- Non-numeric or invalid sizes/iteration values are not handled explicitly.
- Very large dimensions can cause stack issues because grids are stack-allocated.
- The program does not display intermediate generations; only the final state is printed.

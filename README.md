# Game of Life

This project is an implementation of **Conway's Game of Life**, a cellular automaton that simulates how a population of cells evolves over time.

It was part of a **42 exam**. I liked this exercise because it is a simple but interesting concept: with only a few rules, a small grid can create complex and unexpected patterns.

## How the Game Works

The game is played on a grid. Each position on the grid contains either:

- `.` — a dead cell
- `O` — a live cell

For every generation, the program checks the eight neighboring positions around each cell and applies these rules:

1. A live cell with fewer than two live neighbors dies from underpopulation.
2. A live cell with two or three live neighbors survives.
3. A live cell with more than three live neighbors dies from overpopulation.
4. A dead cell with exactly three live neighbors becomes alive.

All cells are evaluated for the next generation based on the previous generation. This is important because changing cells immediately while scanning the grid can produce incorrect results.

## How I Wrote the Code

The implementation is organized around the main steps of the simulation:

1. Read or create the initial grid.
2. Store the current state of every cell.
3. Count the live neighbors for each cell.
4. Apply the Game of Life rules.
5. Build the next generation.
6. Display the updated grid.
7. Repeat the process for the required number of generations.

The most important part is the neighbor-counting logic. For each cell, the code checks the surrounding positions using row and column offsets:

```text
(-1, -1)  (-1, 0)  (-1, 1)
( 0, -1)  current  ( 0, 1)
( 1, -1)  ( 1, 0)  ( 1, 1)
```

When a neighboring position is outside the grid, it is ignored. This allows the program to safely handle cells on the borders.

A separate next grid is useful because every decision must use the old generation. After all cells have been processed, the next grid becomes the current grid.

## Example Patterns

### Still Life: Block

This pattern does not change because each live cell has exactly three neighbors and each dead cell around it has fewer than three neighbors:

```text
....
.OO.
.OO.
....
```

### Oscillator: Blinker

A blinker changes between a horizontal and vertical line:

```text
.O.
.O.
.O.
```

After one generation:

```text
...
OOO
...
```

After another generation, it returns to the vertical form.

### A Few Lines of Code

The core decision for a cell can be represented with logic like this:

```c
if (cell_is_alive && (neighbors == 2 || neighbors == 3))
    next_cell = ALIVE;
else if (!cell_is_alive && neighbors == 3)
    next_cell = ALIVE;
else
    next_cell = DEAD;
```

The neighbor counter follows the surrounding positions and only counts cells that are alive:

```c
for (int row_offset = -1; row_offset <= 1; row_offset++)
{
    for (int col_offset = -1; col_offset <= 1; col_offset++)
    {
        if (row_offset == 0 && col_offset == 0)
            continue;

        /* Check the neighboring position and count live cells. */
    }
}
```

## What I Learned

This exam exercise helped me practice:

- Working with two-dimensional grids.
- Handling boundaries safely.
- Separating the current state from the next state.
- Breaking a problem into small functions.
- Testing a program with simple patterns.
- Understanding how simple rules can produce complex behavior.

The Game of Life was a nice concept for a 42 exam because the rules are easy to understand, but implementing them correctly requires careful thinking about memory, indexing, and the order in which the simulation is updated.

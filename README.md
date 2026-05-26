# Boxed In

Boxed In is a C console puzzle game inspired by Sokoban. The player moves through a grid-based room, pushes boxes onto targets, and completes the puzzle when every box is correctly placed.

This project was built as an academic project and is a small portfolio example of C programming, grid-based game logic, state management, and undo functionality.

## Features

- Renders a grid-based room using console characters
- Moves the player with `w`, `a`, `s`, and `d`
- Handles box pushing around walls and onto targets
- Tracks boxes, targets, player position, and completed target states
- Supports undoing moves with `z`
- Detects when the puzzle has been solved

## Tech Stack

- C
- Console-based input/output
- GCC-compatible build command

## Build

```bash
gcc boxed_in.c -o boxed_in
```

## Run

On Windows:

```powershell
.\boxed_in.exe
```

On macOS/Linux:

```bash
./boxed_in
```

## Repository Contents

This public version includes the final source file, README, and `.gitignore`. Compiled binaries, temporary editor files, scratch files, and personal notes are excluded from the repository.

## License

No open-source license is currently provided for this repository.

This project is shared publicly for portfolio and educational viewing purposes only. It includes academic project structure, so please do not copy, redistribute, or reuse the code without permission.

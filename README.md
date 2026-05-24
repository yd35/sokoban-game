# Boxed In

Boxed In is a C console Sokoban-style puzzle game. The player moves around a grid-based room, pushes boxes onto targets, and completes the puzzle when every box is correctly placed.

This was built as an academic project and is intended as a small portfolio example of C programming, grid-based game logic, and state management.

## Features

- Render a room using console characters.
- Move the player with `w`, `a`, `s`, and `d`.
- Push boxes around walls and onto targets.
- Track boxes, targets, player position, and completed target states.
- Undo moves with `z`.
- Detect when the puzzle has been solved.

## Build

```bash
gcc boxed_in.c -o boxed_in
```

## Run

Windows:

```powershell
.\boxed_in.exe
```

macOS/Linux:

```bash
./boxed_in
```

## Public Repo Contents

The public version of this repository should include the final source file, this README, and `.gitignore`. Compiled binaries, temporary editor files, scratch files, and personal notes should be excluded.

## License

No license is currently provided.

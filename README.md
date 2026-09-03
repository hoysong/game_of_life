# Game of Life

[English](./README.md) | [한국어](./README.ko.md)

A Conway's Game of Life simulator implemented in C with MiniLibX.  
Each next generation is calculated sequentially, while POSIX threads are used to render the background, grid, and cells. Cells and color palettes can be changed while the program is running.

![Game of Life demo](./video.gif)

## 1. Features

- Generation updates based on Conway's Game of Life rules
- Background, grid, and cell rendering with 8 threads
- Random initial map generation
- Custom initial map loading from a `.gol` file
- Real-time cell insertion with the mouse
- Switching between 12 color palettes

## 2. Project Background

This project builds on the graphics, map parsing, and multithreading experience gained from the following projects:

- [hoysong/cub3d](https://github.com/hoysong/cub3d) — Graphics rendering and event handling with MiniLibX
- [hoysong/fdf_fil_de_fer](https://github.com/hoysong/fdf_fil_de_fer) — Map-file parsing and visualization
- [hoysong/philo](https://github.com/hoysong/philo) — Concurrency control using POSIX threads and mutexes

## 3. Environment

This project targets Linux and X11.

Required tools and libraries:

- A C compiler (`cc`)
- `make`
- POSIX Threads
- X11 and Xext development libraries
- zlib and a BSD compatibility library

On Ubuntu or Debian-based systems, install the dependencies with:

```bash
sudo apt update
sudo apt install build-essential xorg libx11-dev libxext-dev zlib1g-dev libbsd-dev
```

## 4. Build

Clone the repository, then build the static libraries and executable in order:

```bash
cd my_game_of_life
make -C my_libft
make -C minilibx-linux
sh compile.sh
```

After the build completes, an `a.out` executable is created in the current directory.

## 5. Run

### 5.1 Random map

Run without arguments to generate a random map sized to the screen:

```bash
./a.out
```

### 5.2 Map file

Pass the path to a `.gol` file containing an initial state:

```bash
./a.out test.gol
```

The repository includes `test.gol`, `test2.gol`, and `tornado.gol` as examples.

## 6. Controls

| Input | Action |
| --- | --- |
| Mouse movement | Add live cells around the pointer |
| `←` / `→` | Select the previous or next color palette |
| `Esc` | Exit the program |
| Window close button | Exit the program |

## 7. Map File Format

A map file contains equal-length strings, one row per line.

- `0`: dead cell
- `1`: live cell
- Every row must have the same length.

Example glider:

```text
00000
01000
00100
11100
00000
```

The window dimensions are calculated by multiplying the map width and height by the pixel size of one cell.

## 8. Key Settings

The following values can be changed in the header files:

| Setting | Location | Default | Description |
| --- | --- | ---: | --- |
| `PIX_SIZE` | `gol_defs.h` | `5` | Pixel size of one cell |
| `NUM_OF_THREADS` | `gol_defs.h` | `8` | Number of rendering threads |
| `PALLETTE_COUNT` | `color_defs.h` | `12` | Number of available color palettes |

Rebuild with `sh compile.sh` after changing these settings.

## 9. Project Structure

```text
.
├── README.md
├── README.ko.md
├── video.gif
└── my_game_of_life
    ├── main.c             # Entry point and input events
    ├── set_next_map.c     # Next-generation calculation
    ├── thread_setup.c     # Rendering-thread setup
    ├── img_hdlers.c       # MiniLibX-based rendering
    ├── gen_map.c          # Map-file loading
    ├── no_arg_logics.c    # Random map generation
    ├── color_defs.h       # Color palettes
    ├── my_libft           # Shared C utility library
    └── minilibx-linux     # MiniLibX
```

## 10. Game of Life Rules

The next state of each cell is determined by its eight neighbors.

1. A live cell dies if it has fewer than two live neighbors.
2. A live cell survives if it has two or three live neighbors.
3. A live cell dies if it has more than three live neighbors.
4. A dead cell becomes alive if it has exactly three live neighbors.

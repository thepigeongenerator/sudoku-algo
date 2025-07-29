// Copyright (c) 2025 Quinn
// Licensed under the MIT Licence. See LICENSE for details
#pragma once

#include "util/intdef.h"

#define SUDOKU_DEPTH_SQRT 3
#define SUDOKU_DEPTH      (SUDOKU_DEPTH_SQRT * SUDOKU_DEPTH_SQRT)
#define SUDOKU_DEPTH_2    (SUDOKU_DEPTH * SUDOKU_DEPTH)

/* bitmask  */
enum sudoku_bitmask {
	SUDOKU_1 = 0x001,
	SUDOKU_2 = 0x002,
	SUDOKU_3 = 0x004,
	SUDOKU_4 = 0x008,
	SUDOKU_5 = 0x010,
	SUDOKU_6 = 0x020,
	SUDOKU_7 = 0x040,
	SUDOKU_8 = 0x080,
	SUDOKU_9 = 0x100,
	SUDOKU_ALL = 0x01FF,
};

/* initialises the sudoku board to `SUDOKU_ALL`. (if the tile is empty) */
void sudoku_init(u16 *board);

/* places `val` at `idx` in `board`, and removes `val` from the possibilities in neighbouring tiles */
void sudoku_place(u16 *board, u16 val, uint idx);

/* TODO: write documentation */
void sudoku_solve_step(u16 *board);

/* TODO: write documentation */
void sudoku_print(const u16 *board);

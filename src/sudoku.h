// Copyright (c) 2025 Quinn
// Licensed under the MIT Licence. See LICENSE for details
#pragma once

#include "util/intdef.h"

#define SUDOKU_BOXLEN     3
#define SUDOKU_DPT        9
#define SUDOKU_LEN        (SUDOKU_DPT * SUDOKU_DPT)

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

/* places `val` at `idx` in `board`, and removes `val` from the possibilities in neighbouring tiles */
void sudoku_place(u16 *board, u16 val, uint idx);

/* loops through the board, updating all places that only have a single possibility set. */
void sudoku_solve_step(u16 *board);

/* prints the sudoku board to `stdout` */
void sudoku_print(const u16 *board);

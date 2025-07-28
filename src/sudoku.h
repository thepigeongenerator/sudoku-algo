// Copyright (c) 2025 Quinn
// Licensed under the MIT Licence. See LICENSE for details
#pragma once

#include "util/intdef.h"

#define SUDOKU_DEPTH   9                             // defines the "depth" of the puzzle.
#define SUDOKU_DEPTH_2 (SUDOKU_DEPTH * SUDOKU_DEPTH) // computes how many squares there are

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
};

/* TODO: write documentation */
void sudoku_solve_step(u16 *board);

/* TODO: write documentation */
void sudoku_print(const u16 *board);

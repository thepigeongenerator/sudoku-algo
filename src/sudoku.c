// Copyright (c) 2025 Quinn
// Licensed under the MIT Licence. See LICENSE for details
#include "sudoku.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util/intdef.h"

void sudoku_init(u16 *board) {
	for (uint i = 0; i < SUDOKU_DEPTH_2; i++) {
		board[i] |= SUDOKU_ALL & -!board[i];
	}
}

void sudoku_place(u16 *board, u16 val, uint idx) {
	uint icol = idx % SUDOKU_DEPTH;
	uint irow = idx - icol;
	uint ibox = idx - (idx % SUDOKU_DEPTH_SQRT);
	for (uint i = 0; i < SUDOKU_DEPTH; i++) {
		board[irow + i] &= ~val;
		board[icol + (i * SUDOKU_DEPTH)] &= ~val;
		board[ibox + (i / SUDOKU_DEPTH_SQRT * SUDOKU_DEPTH) + (i % SUDOKU_DEPTH_SQRT)] &= ~val;
	}
}

void sudoku_solve_step(u16 *board) {
	u16 bmask[SUDOKU_DEPTH_2]; // board mask
	memcpy(bmask, board, SUDOKU_DEPTH_2 * 2);
	// TODO: first, we must somehow loop through the columns
	// TODO: then, we must write to the bmask or do *magic* for the bits designating to 1-9 to be unset if ONLY one of them is set
}

void sudoku_print(const u16 *board) {
	for (uint i = 0; i < SUDOKU_DEPTH_2; i++) {
		char tile;
		switch (board[i]) {
		case SUDOKU_1: tile = '1'; break;
		case SUDOKU_2: tile = '2'; break;
		case SUDOKU_3: tile = '3'; break;
		case SUDOKU_4: tile = '4'; break;
		case SUDOKU_5: tile = '5'; break;
		case SUDOKU_6: tile = '6'; break;
		case SUDOKU_7: tile = '7'; break;
		case SUDOKU_8: tile = '8'; break;
		case SUDOKU_9: tile = '9'; break;
		default:       tile = ' '; break;
		};

		printf("|%c ", tile);
		if (i % 9 == 8) printf("|\n");
	}
}

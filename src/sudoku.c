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

/* removes `val` from `*brd`, if `*brd` is not equal to `val` */
static inline void setbrdpos(u16 *brd, u16 val) {
	*brd &= ~(val & -(*brd != val));
}

void sudoku_place(u16 *brd, u16 val, uint idx) {
	uint icol = idx % SUDOKU_DEPTH;
	uint irow = idx - icol;
	uint ibox = idx - (idx % SUDOKU_DEPTH_SQRT);
	for (uint i = 0; i < SUDOKU_DEPTH; i++) {
		setbrdpos(&brd[irow + i], val);
		setbrdpos(&brd[icol + (i * SUDOKU_DEPTH)], val);
		setbrdpos(&brd[ibox + (i / SUDOKU_DEPTH_SQRT * SUDOKU_DEPTH) + (i % SUDOKU_DEPTH_SQRT)], val);
	}
}

void sudoku_solve_step(u16 *board) {
	for (uint i = 0; i < SUDOKU_DEPTH_2; i++) {
		switch (board[i]) {
		case SUDOKU_1:
		case SUDOKU_2:
		case SUDOKU_3:
		case SUDOKU_4:
		case SUDOKU_5:
		case SUDOKU_6:
		case SUDOKU_7:
		case SUDOKU_8:
		case SUDOKU_9:
			sudoku_place(board, board[i], i);
		}
	}
}

void sudoku_print(const u16 *board) {
	printf("+———-———-———-———-———-———-———-———-———+\n");
	for (uint i = 0; i < SUDOKU_DEPTH_2; i++) {
		char tile;
		switch (board[i]) {
		case 0:        tile = 'x'; break;
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

		printf("| %c ", tile);
		// printf("|%3i", board[i]);
		if (i % 9 == 8) printf("|\n");
	}
	printf("+———-———-———-———-———-———-———-———-———+\n");
}

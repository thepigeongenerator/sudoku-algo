// Copyright (c) 2025 Quinn
// Licensed under the MIT Licence. See LICENSE for details
#include "sudoku.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util/intdef.h"

void sudoku_init(u16 *board) {
	for (uint i = 0; i < SUDOKU_LEN; i++) {
		board[i] |= SUDOKU_ALL & -!board[i];
	}
}

/* removes `val` from `*brd`, if `*brd` is not equal to `val` */
static inline void setbrdpos(u16 *brd, u16 val) {
	*brd &= ~(val & -(*brd != val));
}

void sudoku_place(u16 *brd, u16 val, uint idx) {
	uint x = idx % SUDOKU_DPT;
	uint y = idx / SUDOKU_DPT;

	uint irow = idx - x;
	uint ibox = SUDOKU_DPT * (y % SUDOKU_BOXLEN) + SUDOKU_BOXLEN * (x % SUDOKU_BOXLEN);

	for (uint i = 0; i < SUDOKU_DPT; i++) {
		setbrdpos(&brd[irow + i], val);
		setbrdpos(&brd[x + (i * SUDOKU_DPT)], val);
		setbrdpos(&brd[ibox + (SUDOKU_DPT * (i % SUDOKU_BOXLEN))], val);
	}
}

void sudoku_solve_step(u16 *board) {
	for (uint i = 0; i < SUDOKU_LEN; i++) {
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
			// printf("%i,%i\n", i % SUDOKU_DPT, i / SUDOKU_DPT);
		}
	}
}

void sudoku_print(const u16 *board) {
	printf("+———-———-———-———-———-———-———-———-———+\n");
	for (uint i = 0; i < SUDOKU_LEN; i++) {
		char tile;
		switch (board[i]) {
		// case 0:        tile = 'x'; break;
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
		// printf("|%3X", board[i]);
		if (i % 9 == 8) printf("|\n");
	}
	printf("+———-———-———-———-———-———-———-———-———+\n");
}

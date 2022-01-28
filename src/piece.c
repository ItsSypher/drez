#include "piece.h"
#include <stdlib.h>

position coords_to_pos(short rank, short file) {
  position p = {rank, file};
  return p;
}

position *rook_valid (position pos, cell game[SIZE_STD][SIZE_STD]) {
  const int max_length = SIZE_STD - 1; /* a rook can move ( not counting other pieces ) a total of
							   size of one side - 1 (to exclude current position) */
  position *valid_moves = malloc(sizeof(position)*max_length*2+sizeof(position)); /* allocate vertical + horizontal moves,
																				   intentionally left the + sizeof(position) to
																				  clarify that's reserved for the sentinel */
  int move_idx = 0;
  /* Line up */
  for (int row = pos.rank + 1; row<SIZE_STD; row++) {
	valid_moves[move_idx++] = coords_to_pos(row, pos.file);
	if (game[row][pos.file].piece != NULL) break;
  }
  /* Line down */
  for (int row = pos.rank - 1; row>=0; row--) {
	valid_moves[move_idx++] = coords_to_pos(row, pos.file);
	if (game[row][pos.file].piece != NULL) break;
  }
  /* Line left */
  for (int col = pos.file - 1; col>=0; col--) {
	valid_moves[move_idx++] = coords_to_pos(pos.rank, col);
	if (game[pos.rank][col].piece != NULL) break;
  }
  for (int col = pos.file + 1; col<SIZE_STD; col++) {
	valid_moves[move_idx++] = coords_to_pos(pos.rank, col);
	if (game[pos.rank][col].piece != NULL) break;
  }
  valid_moves[move_idx] = SENTINEL;
  return valid_moves;
}

position *knight_valid(position pos, cell game[SIZE_STD][SIZE_STD]) {
  const int max_length = 8;
  position *valid_moves = malloc(sizeof(position)*max_length+sizeof(position));
  int i, j, move_idx = 0;
  for (i = -2; i <= 2; i += 4)
  {
    for (j = -1; j <= 1; j += 2)
    {
      position coords_v = coords_to_pos(pos.rank + i, pos.file + j);
      position coords_h = coords_to_pos(pos.rank + j, pos.file + i);
      if (!(coords_v.file < 0 || coords_v.rank < 0 ||
			coords_v.file > SIZE_STD || coords_v.rank > SIZE_STD)) {
		valid_moves[move_idx++] = coords_v;
		  }
	  if (!(coords_h.file < 0 || coords_h.rank < 0 ||
			coords_h.file > SIZE_STD || coords_h.rank > SIZE_STD)) {
		valid_moves[move_idx++] = coords_h;
		  }
    }
  }
  valid_moves[move_idx] = SENTINEL;
  return valid_moves;
}

position *bishop_valid (position pos, cell game[SIZE_STD][SIZE_STD]) {
  /* we can approximate, in the worst case the bishop will take (board's diagonal length * 2) - 3 */
  const int max_length = SIZE_STD;
  position *valid_moves = malloc(sizeof(position)*max_length+sizeof(position)); /* allocate vertical + horizontal moves + sentinel */
  int i = 0;
  int min = (pos.file < pos.rank) ? pos.file : pos.rank;
  position lower_left = {pos.rank - min, pos.file - min};
  /* now we start crawling diagonally up right */
  int n = 0;
  while (lower_left.rank+i < SIZE_STD && lower_left.file+i < SIZE_STD) {
	if (pos.rank == lower_left.rank+i && pos.file == lower_left.file+i) continue;
	valid_moves[n++] = coords_to_pos(lower_left.rank+i, lower_left.file+i);
	i++;
  }
  /* TODO: other diagonal */
  valid_moves[n] = coords_to_pos(-1, -1);
  return valid_moves;
  //  rank_dif *= ((rank_dif>0) - (rank_dif<0)); /* get abs value */
}

position *queen_valid (position pos, cell game[SIZE_STD][SIZE_STD]) {
  return NULL;
}

position *king_valid(position pos, cell game[SIZE_STD][SIZE_STD]) {
  return NULL;
}

position *pawn_valid (position pos, cell game[SIZE_STD][SIZE_STD]) {
  position *valid_moves = malloc(sizeof(position)*3+sizeof(position)); /* three possible moves: forwards, twice forwards (at start), en passant */
  // TODO
  return valid_moves;
}

position *moves(piece *piece, position pos, cell game[SIZE_STD][SIZE_STD]) {
  switch (piece->ident) {
  case 'r':
	return rook_valid(pos, game);
	break;
  case 'b':
	return bishop_valid(pos, game);
	break;
  case 'n':
	return knight_valid(pos, game);
	break;
  case 'q':
	return queen_valid(pos, game);
	break;
  case 'k':
	return king_valid(pos, game);
	break;
  case 'p':
	return pawn_valid(pos, game);
	break;
  default:
	return NULL;
  }
}

piece rook = {'r'};
piece knight = {'n'};
piece bishop = {'b'};
piece queen = {'q'};
piece king = {'k'};
piece pawn = {'p'};
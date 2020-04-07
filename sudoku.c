/*
 * This program is meant to be a sudoku solver using recursive backtracking.
 * The functions is_val_in_row and is_val_in_col both use a single for loop
 * which compares a value that is put into a previously blank cell with those
 * values that are in the same row or column, respectively. The function
 * is_val_in_3x3_zone first uses the element's row and column to determine
 * the upper left corner of the 3x3 box the element is in. It then uses
 * nested for loops to check the entire 3x3 box. These 3 functions each
 * return a 1 if the given number val has already been used. The function
 * is_val_valid calls all 3 functions, and if they are all 0, returns a 1.
 * This comes in handy in the solve_sudoku function, which is where the
 * recursion takes place. This function first has a base case which checks
 * if all 81 spaces have been filled up with nonzero numbers, and returns
 * a 1 if so. If this fails, we used the given algorithm to increment
 * through each space, find an unfilled space, and then try digits 1-9
 * into it. The function is_val_valid is called here as a preliminary check
 * to see which value is compatible, and then recursion is used to see if
 * this value can remain in this spot and complete the board. If this does
 * not eventually complete the board, the value in the spot is reset to 0.
 *
 * Partner: psaboo2
 */

#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  int j;
  for(j=0; j<9; j++){				//loop to go through each column of the row
  	if(val == sudoku[i][j]){ //compares each value of row to val
      return 1;				// returns 1 if val is already in row
    }
  }
  return 0;          // returns 0 if val is not in row
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO

  int i;
  for(i=0; i<9; i++){         // loop to go through each row of the column
  	if(val == sudoku[i][j]){	// compares each value of column to val
      return 1;					// returns 1 if val is already in column
    }
  }
  return 0;					// returns 0 if val is not in column
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9);
  // BEG TODO
  int start_r = (i/3) * 3;			//gets the starting value of the row index for the 3x3 cell
  int start_c = (j/3) * 3;			// gets the starting value of the column index for the 3x3 cell
  int x;
  int y;
  for(x=start_r; x<start_r+3; x++) {      // row iterations up to 3 iterations
    for(y=start_c; y<start_c+3; y++) {    // column iterations up to 3 iterations
      if(sudoku[x][y] == val) {           // compares val to all values in the 3x3
        return 1;
      }
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO need to call all 3 functions, if all of them return 0, we return 1 in this function.
  int f1, f2, f3, sum;
  f1 = is_val_in_row(val, i, sudoku);		//stores return value of is_val_in_row
  f2 = is_val_in_col(val, j, sudoku);		//stores return value of is_val_in_col
  f3 = is_val_in_3x3_zone(val, i, j, sudoku);		//stores return value of is_val_in_3x3_zone
  sum = f1+f2+f3;		// sum should be zero for it to be valid
  if (sum == 0) {   //checks if sum is 0 and returns 1 if it is otherwise return 0
    return 1;
  }
    return 0;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int r;
  int c;
  int val;
  int temp = 0;
  for(r=0;r<9;r++){			//iterates through rows
    for(c=0;c<9;c++){		//iterates through columns
      if (sudoku[r][c] > 0) {	//checks to see if each value is not 0
        temp++;
      }
    }
  }
  if (temp == 81) {		//if 81 values are not 0 then the sudoku is solved
    return 1;
  }
  for(r=0;r<9;r++){			//iterates through each row
    for(c=0;c<9;c++){		//iterates through each column
      if (sudoku[r][c] == 0) {		//checks to see if it is an empty spot
        for(val = 1; val <= 9; val++) {		//iterates through 1 to 9
      		if (is_val_valid(val, r, c, sudoku) == 1) {  //checks to see first number that is valid from 1 to 9
          	sudoku[r][c] = val;			//sets valid number into the empty spot
            if (solve_sudoku(sudoku) == 1) {  //calls sudoku again to see if it is solved and puts in next number
              return 1;     // solved
            }
            sudoku[r][c] = 0;   //was not solved and had to be backtracked so putting it back to empty state
          }
        }
      return 0;    // got stuck and needs to backtrack
      }
    }
  }
  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}

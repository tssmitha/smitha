#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 10

bool isSafe(int row, int col, char board[MAX_SIZE][MAX_SIZE], int size) {
    int i, j;

    for (i = 0; i < col; i++) {
        if (board[row][i] == 'Q') {
            return false;
        }
    }

    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }

    for (i = row, j = col; i < size && j >= 0; i++, j--) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }

    return true;
}

void printBoard(char board[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void solveNQueens(char board[MAX_SIZE][MAX_SIZE], int col, int size) {
    if (col >= size) {
        printBoard(board, size);
        printf("\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        if (isSafe(i, col, board, size)) {
            board[i][col] = 'Q';
            solveNQueens(board, col + 1, size);
            board[i][col] = '.';
        }
    }
}

int main() {
    int n;
    printf("Enter the size of the board: ");
    scanf("%d", &n);

    char board[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = '.';
        }
    }

    solveNQueens(board, 0, n);

    return 0;
}
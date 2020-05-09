#include "Piezas.h"
#include <vector>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/

/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
    //Resizing the board to default size
    board.resize(3, std::vector<Piece>(4, Blank));
    // Set the turn as X's turn to start
    turn = X;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
    //Loop through game board to reset it to blank
    for (int i = 0; i < (int)board.size(); i++)
        for (int j = 0; j < (int)board[i].size(); j++)
            board[i][j] = Blank;
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/
Piece Piezas::dropPiece(int column)
{
    //Error testing the parameter
    if (column > 3 || column < 0)
    {
        if (turn == X)
            turn = O;
        else
            turn = X;

        return Invalid;
    }

    //Loop across the rows of the board
    for (int i = 0; i < (int)board.size(); i++)
    {
        //If the spot is open
        if (board[i][column] == Blank)
        {
            //Place the piece there
            board[i][column] = turn;
            Piece thing = turn;
            if (turn == X)
                turn = O;
            else
                turn = X;
            return thing;
        }
    }
    if (turn == X)
        turn = O;
    else
        turn = X;
    //If the whole column is filled return Blank
    return Blank;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
    //Testing for invalid coordinates
    if (row > 2 || row < 0)
        return Invalid;
    if (column > 3 || column < 0)
        return Invalid;

    //Loop through game board
    for (int i = 0; i < (int)board.size(); i++)
    {
        for (int j = 0; j < (int)board[i].size(); j++)
        {
            //If no piece in that spot
            if (board[i][j] == Blank)
                return Blank;
            //If there is a piece there return what the piece is
            else
                return board[i][j];
        }
    }
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
    int winX = 0, winO = 0;
    int rowCount = 0;
    Piece temp = board[0][0];

    //Count horizontal lines
    for (int i = 0; i < (int)board.size(); i++)
    {
        for (int j = 0; j < (int)board[i].size(); j++)
        {
            //If the board isn't filled
            if (board[i][j] == Blank)
                return Invalid;
            else if (board[i][j] == temp)
            {
                //increment the count since it is a continued Piece
                rowCount++;
                //If it's x and worthy of score
                if (board[i][j] == X && winX < rowCount)
                    winX = rowCount;
                else if (board[i][j] == O && winO < rowCount)
                    winO = rowCount;
            }
            else
            {
                //Change the temp to count the other piece list
                temp = board[i][j];
                rowCount = 0;
            }
        }
        rowCount = 0;
    }

    //since the size is static we can set size vars
    int rowSize = board.size();
    int columnSize = board[0].size();

    for (int i = 0; i < columnSize; i++)
    {
        for (int j = 0; j < rowSize; j++)
        {
            if (board[j][i] == temp)
            {
                //increment the count since it is a continued Piece
                rowCount++;
                //If it's x and worthy of score
                if (board[j][i] == X && winX < rowCount)
                    winX = rowCount;
                else if (board[j][i] == O && winO < rowCount)
                    winO = rowCount;
            }
            else
            {
                //Change the temp to count the other piece list
                temp = board[j][i];
                rowCount = 0;
            }
        }
        rowCount = 0;
    }

    if (winX > winO)
        return X;
    else if (winX < winO)
        return O;
    else
        return Blank;
}
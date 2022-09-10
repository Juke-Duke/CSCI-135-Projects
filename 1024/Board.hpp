#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <conio.h>
using std::vector;

class Board
{
private:
    int** panel;
    int numRows, numCols, target, max;

    void AllocatePanel();
    void Print() const;
    void Print(int& row, int& col) const;
    bool IsFull() const;
    bool NoMoves() const;
    void FindEmptyCell();
    void PressUp();
    void PressDown();
    void PressLeft();
    void PressRight();

public:
    Board();
    Board(int square);
    Board(int rows, int cols);

    void Start();

    ~Board();
};

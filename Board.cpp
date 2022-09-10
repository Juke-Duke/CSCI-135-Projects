#include "Board.hpp"

Board::Board() : numRows(3), numCols(3), max(0), target(32) { AllocatePanel(); }

Board::Board(int square) : numRows(3), numCols(3), max(0), target(32)
{
    if (square >= 1)
    {
        numRows = square;
        numCols = square;
    }

    AllocatePanel();
}

Board::Board(int rows, int cols) : numRows(3), numCols(3), max(0), target(32) 
{
    if (rows >= 1)
        numRows = rows;

    if (cols >= 1)
        numCols = cols;

    AllocatePanel();
}

void Board::AllocatePanel()
{
    panel = new int*[numRows];
    for (int i = 0; i < numRows; ++i)
    {
        panel[i] = new int[numCols];
        for (int j = 0; j < numCols; ++j)
            panel[i][j] = 0;    
    }
}

void Board::Start()
{
    int goal = 0;
    std::cout << "What is the desired target?: ";
    std::cin >> goal;
    if (goal > 0)
        target = goal;
    
    int round = 1;
    FindEmptyCell();
    FindEmptyCell();
    
    while (true)
    {
        if (max == target)
        {
            std::cout << "Congratulation!";
            break;
        }

        switch(getchar()) 
        {
        case 'w':
            PressUp();
            std::cout << "Round " << std::setw(4) << round << ": ";
            std::cout << "Pressed UP. " << std::endl;
            round++;
            break;

        case 's':
            PressDown();
            std::cout << "Round " << std::setw(4) << round << ": ";
            std::cout << "Pressed DOWN. " << std::endl;
            round++;
            break;

        case 'd':
            PressRight();
            std::cout << "Round " << std::setw(4) << round << ": ";
            std::cout << "Pressed RIGHT. " << std::endl;
            round++;
            break;

        case 'a':
            PressLeft();
            std::cout << "Round " << std::setw(4) << round << ": ";
            std::cout << "Pressed LEFT. " << std::endl;
            round++;
            break;
        }
    }
}

void Board::Print() const
{
    std::cout << "\033[2J\033[1;1H";
    for (int i = 0; i < numRows; ++i)
    {
        std::cout << "+";
        for (int j = 0; j < numCols; ++j)
            std::cout << "----+";
        std::cout << std::endl;

        std::cout << "|";
        for (int j = 0; j < numCols; ++j)
        {
            if (panel[i][j] == 0)
                std::cout << "    |";
            else
                std::cout << std::setw(4) << panel[i][j] << "|";
        }
        std::cout << std::endl;
    }

    std::cout << "+";
    for (int j = 0; j < numCols; ++j)
        std::cout << "----+";
    std::cout << std::endl;
}

void Board::Print(int& row, int& col) const
{
    std::cout << "\033[2J\033[1;1H";
    for (int i = 0; i < numRows; ++i)
    {
        std::cout << "+";
        for (int j = 0; j < numCols; ++j)
            std::cout << "----+";
        std::cout << std::endl;

        std::cout << "|";
        for (int j = 0; j < numCols; ++j)
        {
            if (panel[i][j] == 0)
                std::cout << "    |";
            else if (i == row && j == col)
                std::cout << "\x1B[31m" << std::setw(4) << panel[i][j] << "\033[0m" << "|";
            else
                std::cout << std::setw(4) << panel[i][j] << "|";
        }
        std::cout << std::endl;
    }

    std::cout << "+";
    for (int j = 0; j < numCols; ++j)
        std::cout << "----+";
    std::cout << std::endl;
}

bool Board::IsFull() const
{
    for (int i = 0; i < numRows; ++i)
        for (int j = 0; j < numCols; ++j)
            if (panel[i][j] == 0)
                return false;
    
    return true;
}

bool Board::NoMoves() const
{
    for (int i = 0; i < numRows; ++i)
        for (int j = 0; j < numCols - 1; ++j)
        {
            if (panel[i][j] == panel[i][j + 1])
                return false;
            
            if (i != 0 && panel[i][j] == panel[i - 1][j])
                return false;
        }
    
    return true;
}

void Board::FindEmptyCell()
{
    if (IsFull() && NoMoves() && max < target)
    {
        std::cout << "Game Over! Try again." << std::endl;
        exit(0);
    }
    else if (!IsFull())
    {
        vector<int> emptyCells;
        int position = 0;

        for (int i = 0; i < numRows; ++i)
            for (int j = 0; j < numCols; ++j)
            {
                if (panel[i][j] == 0)
                    emptyCells.push_back(position);
                ++position;
            }
        
        srand(time(NULL));
        int random = rand() % emptyCells.size();
        int row = emptyCells[random] / numRows;
        int col = emptyCells[random] % numCols;
        panel[row][col] = 1;
        Print(row, col);
        return;
    }

    Print();
}

void Board::PressUp()
{
    for (int i = 1; i < numRows; ++i)
        for (int j = 0; j < numCols; ++j)
        {
            if (panel[i - 1][j] == 0)
            {
                panel[i - 1][j] = panel[i][j];
                panel[i][j] = 0;
            }
            else if (panel[i - 1][j] == panel[i][j])
            {
                panel[i - 1][j] *= 2;
                panel[i][j] = 0;
                
                if (panel[i - 1][j] > max)
                    max = panel[i - 1][j];
            }
        }
    
    FindEmptyCell();
}

void Board::PressDown()
{
    for (int i = numRows - 2; i >= 0; --i)
        for (int j = 0; j < numCols; ++j)
        {
            if (panel[i + 1][j] == 0)
            {
                panel[i + 1][j] = panel[i][j];
                panel[i][j] = 0;
            }
            else if (panel[i + 1][j] == panel[i][j])
            {
                panel[i + 1][j] *= 2;
                panel[i][j] = 0;

                if (panel[i + 1][j] > max)
                    max = panel[i + 1][j];
            }
        }
    
    FindEmptyCell();
}

void Board::PressRight()
{
    for (int i = 0; i < numRows; ++i)
        for (int j = numCols - 2; j >= 0; --j)
        {
            if (panel[i][j + 1] == 0)
            {
                panel[i][j + 1] = panel[i][j];
                panel[i][j] = 0;
            }
            else if (panel[i][j] == panel[i][j + 1])
            {
                panel[i][j + 1] *= 2;
                panel[i][j] = 0;

                if (panel[i][j + 1] > max)
                    max = panel[i][j + 1];
            }
        }
    
    FindEmptyCell();
}

void Board::PressLeft()
{
    for (int i = 0; i < numRows; ++i)
        for (int j = 1; j < numCols; ++j)
        {
            if (panel[i][j - 1] == 0)
            {
                panel[i][j - 1] = panel[i][j];
                panel[i][j] = 0;
            }
            else if (panel[i][j] == panel[i][j - 1])
            {
                panel[i][j - 1] *= 2;
                panel[i][j] = 0;

                if (panel[i][j - 1] > max)
                    max = panel[i][j - 1];
            }
        }
    
    FindEmptyCell();
}

Board::~Board()
{
    for (int i = 0; i < numRows; ++i)
    {
        delete[] panel[i];
        panel[i] = nullptr;
    }

    delete[] panel;
    panel = nullptr;
}

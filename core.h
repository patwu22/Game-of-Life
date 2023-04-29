#pragma once
#include <SFML/Graphics.hpp>
#include <string>

struct core
{
    unsigned int rows;
    unsigned int columns;
    unsigned int cell;
    bool *cells = nullptr;

    core(unsigned int width, unsigned int height, unsigned int c)
    {
        rows = height / c;
        columns = width / c;
        cell = c;
        cells = new bool[rows * columns];
        for (int i = 0; i < rows * columns; i++)
            cells[i] = false;
    }

    void listen(sf::Event::MouseButtonEvent b)
    {
        if (b.button == sf::Mouse::Left)
        {
            unsigned int row = b.y / cell;
            unsigned int column = b.x / cell;
            cells[column + row * columns] = true;
        }
    }

    void next()
    {
        bool *new_cells = new bool[rows * columns];

        for (int i = 0; i < rows * columns; i++)
        {
            new_cells[i] = false;
            unsigned int CellsAround = getCellsAround(i);
            if (cells[i])
            {
                if (CellsAround == 2 || CellsAround == 3)
                    new_cells[i] = true;
            }
            else
            {
                if (CellsAround == 3)
                    new_cells[i] = true;
            }
        }

        delete cells;
        cells = new_cells;
    }

    unsigned int getCellsAround(int coordinate)
    {
        int x = coordinate % columns;
        int y = coordinate / columns;
        unsigned int count = 0;
        if (x != 0)
            if (cells[coordinate - 1])
                count++;
        if (x != columns - 1)
            if (cells[coordinate + 1])
                count++;
        if (y != 0)
            if (cells[coordinate - columns])
                count++;
        if (y != rows - 1)
            if (cells[coordinate + columns])
                count++;
        if (x != 0 && y != 0)
            if (cells[coordinate - columns - 1])
                count++;
        if (x != 0 && y != rows - 1)
            if (cells[coordinate + columns - 1])
                count++;
        if (x != columns - 1 && y != 0)
            if (cells[coordinate - columns + 1])
                count++;
        if (x != columns - 1 && y != rows - 1)
            if (cells[coordinate + columns + 1])
                count++;
        return count;
    }

    ~core()
    {
        delete cells;
        cells = nullptr;
    }
};

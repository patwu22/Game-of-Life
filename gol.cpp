#include "core.h"
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
    string path = "";
    if (argc > 1)
        path = argv[1];

    // Get config
    ifstream fin;
    string tmp;
    unsigned int width;
    unsigned int height;
    unsigned int cell;
    unsigned int freq;

    fin.open(path + "gol.conf");
    if (!fin.is_open())
        throw exception();
    getline(fin, tmp);
    width = stoi(tmp);
    getline(fin, tmp);
    height = stoi(tmp);
    getline(fin, tmp);
    cell = stoi(tmp);
    getline(fin, tmp);
    freq = stoi(tmp);

    // Main window
    sf::RenderWindow w(sf::VideoMode(width / cell * cell, height / cell * cell), "Game of Life");

    // Tiles
    sf::RectangleShape *cells;
    cells = new sf::RectangleShape[(width / cell) * (height / cell)];
    for (int i = 0; i < (width / cell) * (height / cell); i++)
    {
        cells[i].setSize(sf::Vector2f(cell, cell));
        cells[i].setPosition(i % (width / cell) * cell, i / (width / cell) * cell);
        cells[i].setFillColor(sf::Color::White);
        cells[i].setOutlineThickness(1);
        cells[i].setOutlineColor(sf::Color::Black);
    }

    core _core(width, height, cell);

    // Main loop
    w.setFramerateLimit(freq);
    bool pause = true;
    while (w.isOpen())
    {
        sf::Event e;
        sf::String inp;
        while (w.pollEvent(e))
        {
            switch (e.type)
            {
            case sf::Event::Closed:
                w.close();
                break;
            case sf::Event::MouseButtonReleased:
                _core.listen(e.mouseButton);
                break;
            case sf::Event::TextEntered:
                inp += e.text.unicode;
                if (inp == " ")
                {
                    if (pause)
                        pause = false;
                    else
                        pause = true;
                }
                break;
            default:
                break;
            }
        }

        // Automaton
        if (!pause)
            _core.next();

        // Main window
        w.clear();
        for (int i = 0; i < (width / cell) * (height / cell); i++)
        {
            if (_core.cells[i])
                cells[i].setFillColor(sf::Color::Black);
            else
                cells[i].setFillColor(sf::Color::White);
            w.draw(cells[i]);
        }

        w.display();
    }
    return 1;
}
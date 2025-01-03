#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include "Sudoku.cpp" 

using namespace std;

// Function to draw the grid
void drawGrid(sf::RenderWindow& window) {
    sf::VertexArray lines(sf::Lines, 40);  // 40 lines (10 horizontal + 10 vertical)

    for (int i = 0; i < 10; ++i) {  
        // Horizontal lines
        lines[2 * i].position = sf::Vector2f(50.f, 50.f + i * 50.f);  // Left side of the grid
        lines[2 * i + 1].position = sf::Vector2f(550.f, 50.f + i * 50.f);  // Right side of the grid

        // Set color for horizontal lines
        lines[2 * i].color = sf::Color::Black;
        lines[2 * i + 1].color = sf::Color::Black;

        // Vertical lines
        lines[2 * (i + 10)].position = sf::Vector2f(50.f + i * 50.f, 50.f);  // Top side of the grid
        lines[2 * (i + 10) + 1].position = sf::Vector2f(50.f + i * 50.f, 550.f);  // Bottom side of the grid

        // Set color for vertical lines
        lines[2 * (i + 10)].color = sf::Color::Black;
        lines[2 * (i + 10) + 1].color = sf::Color::Black;
    }

    window.draw(lines); 
}

// Function to draw numbers on the grid
void drawNumbers(sf::RenderWindow& window, const vector<vector<int>>& board) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Failed to load font!" << endl;
        return;
    }

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] != 0) {
                sf::Text text;
                text.setFont(font);
                text.setString(to_string(board[i][j]));
                text.setCharacterSize(24);
                text.setFillColor(sf::Color::Black);

           
                float xPosition = 50.f + j * 50.f + 13.f; 
                float yPosition = 50.f + i * 50.f + 10.f;  
                text.setPosition(xPosition, yPosition);

                window.draw(text);
            }
        }
    }
}

// Function to handle mouse events for the button click
bool isButtonClicked(sf::Vector2i mousePos) {
    // Define the button area 
    sf::FloatRect buttonArea(50.f, 550.f, 100.f, 50.f);
    
    return buttonArea.contains(sf::Vector2f(mousePos));
}

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "Sudoku Solver");
    window.setVerticalSyncEnabled(false);

    vector<vector<int>> board(9, vector<int>(9, 0)); 

    // Read the board from user input
    cout << "Enter the Sudoku grid row by row, using 0 for empty cells:" << endl;
    for (int i = 0; i < 9; ++i) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        for (int j = 0; j < 9; ++j) {
            ss >> board[i][j];  // Fill the board with numbers
        }
    }

    // Create a button solve
    sf::RectangleShape button(sf::Vector2f(100.f, 50.f));  
    button.setFillColor(sf::Color::Green);
    button.setPosition(50.f, 550.f);  

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Failed to load font!" << endl;
        return -1;
    }

    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setString("Solve");
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(button.getPosition().x + 15.f, button.getPosition().y + 10.f);

    // Instantiate the Sudoku solver
    Sudoku sudokuSolver;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Check if the mouse is clicked inside the button
            if (event.type == sf::Event::MouseButtonPressed) {
                if (isButtonClicked(sf::Mouse::getPosition(window))) {
                    if (sudokuSolver.SolveSudoku(board)) {
                        cout << "Sudoku solved!" << endl;
                    } else {
                        cout << "No solution found!" << endl;
                    }
                }
            }
        }

        window.clear(sf::Color::White);

        drawGrid(window);  
        drawNumbers(window, board);  
        window.draw(button);  
        window.draw(buttonText);  

        window.display();
    }

    return 0;
}

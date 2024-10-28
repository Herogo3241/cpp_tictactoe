#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>

enum class Player { None, X, O };
const int gridSize = 3;
const int cellSize = 200;
const int windowSize = cellSize * gridSize;

class TicTacToe {
public:
    TicTacToe() : currentPlayer(Player::X), board{}, gameWon(false) {}

    void run() {
        sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Tic-Tac-Toe");

        while (window.isOpen()) {
            handleEvents(window);
            window.clear(sf::Color::White);
            drawBoard(window);
            window.display();

            if (gameWon) {
                std::cout << "Player " << (currentPlayer == Player::O ? "X" : "O") << " wins!\n";
                break;
            }
        }
    }

private:
    Player currentPlayer;
    std::array<std::array<Player, gridSize>, gridSize> board;
    bool gameWon;

    void handleEvents(sf::RenderWindow &window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && !gameWon) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int row = event.mouseButton.y / cellSize;
                    int col = event.mouseButton.x / cellSize;

                    if (board[row][col] == Player::None) {
                        board[row][col] = currentPlayer;
                        if (checkWin(row, col)) {
                            gameWon = true;
                        } else {
                            currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
                        }
                    }
                }
            }
        }
    }

    void drawBoard(sf::RenderWindow &window) {
        for (int i = 0; i <= gridSize; ++i) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(i * cellSize, 0), sf::Color::Black),
                sf::Vertex(sf::Vector2f(i * cellSize, windowSize), sf::Color::Black)
            };
            window.draw(line, 2, sf::Lines);

            line[0] = sf::Vertex(sf::Vector2f(0, i * cellSize), sf::Color::Black);
            line[1] = sf::Vertex(sf::Vector2f(windowSize, i * cellSize), sf::Color::Black);
            window.draw(line, 2, sf::Lines);
        }

        for (int row = 0; row < gridSize; ++row) {
            for (int col = 0; col < gridSize; ++col) {
                if (board[row][col] != Player::None) {
                    sf::Text text;
                    sf::Font font;
                    font.loadFromFile("arial.ttf");

                    text.setFont(font);
                    text.setString(board[row][col] == Player::X ? "X" : "O");
                    text.setCharacterSize(150);
                    text.setFillColor(sf::Color::Black);
                    text.setPosition(col * cellSize + 50, row * cellSize - 15);

                    window.draw(text);
                }
            }
        }
    }

    bool checkWin(int row, int col) {
        Player p = board[row][col];
        bool winRow = true, winCol = true, winDiag1 = true, winDiag2 = true;

        for (int i = 0; i < gridSize; ++i) {
            if (board[row][i] != p) winRow = false;
            if (board[i][col] != p) winCol = false;
            if (board[i][i] != p) winDiag1 = false;
            if (board[i][gridSize - i - 1] != p) winDiag2 = false;
        }
        return winRow || winCol || winDiag1 || winDiag2;
    }
};

int main() {
    TicTacToe game;
    game.run();
    return 0;
}


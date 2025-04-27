// #include <SFML/Graphics.hpp>
// #include <iostream>

// // Constants
// const int ROWS = 6;
// const int COLS = 7;
// const int CELL_SIZE = 80;
// const int BOARD_WIDTH = COLS * CELL_SIZE;
// const int BOARD_HEIGHT = (ROWS + 1) * CELL_SIZE; // Extra row for dropping pieces
// const sf::Color BOARD_COLOR = sf::Color(0, 0, 255); // Blue
// const sf::Color EMPTY_COLOR = sf::Color(255, 255, 255); // White
// const sf::Color PLAYER1_COLOR = sf::Color(255, 0, 0); // Red
// const sf::Color PLAYER2_COLOR = sf::Color(255, 255, 0); // Yellow

// // Forward declarations
// class Board;
// class Game;
// class GUI;

// // Board class to manage the game state
// class Board {
// private:
//     int grid[ROWS][COLS];

// public:
//     Board() {
//         // Initialize empty board
//         for (int i = 0; i < ROWS; i++) {
//             for (int j = 0; j < COLS; j++) {
//                 grid[i][j] = 0;
//             }
//         }
//     }

//     bool isColumnFull(int col) const {
//         return grid[0][col] != 0;
//     }

//     int getCell(int row, int col) const {
//         return grid[row][col];
//     }

//     bool dropPiece(int col, int player) {
//         if (col < 0 || col >= COLS || isColumnFull(col)) {
//             return false;
//         }

//         // Find the lowest empty cell in the column
//         int row = ROWS - 1;
//         while (row >= 0 && grid[row][col] != 0) {
//             row--;
//         }

//         if (row >= 0) {
//             grid[row][col] = player;
//             return true;
//         }

//         return false;
//     }

//     bool checkWin(int player) const {
//         // Check horizontal
//         for (int row = 0; row < ROWS; row++) {
//             for (int col = 0; col <= COLS - 4; col++) {
//                 if (grid[row][col] == player && 
//                     grid[row][col+1] == player && 
//                     grid[row][col+2] == player && 
//                     grid[row][col+3] == player) {
//                     return true;
//                 }
//             }
//         }

//         // Check vertical
//         for (int row = 0; row <= ROWS - 4; row++) {
//             for (int col = 0; col < COLS; col++) {
//                 if (grid[row][col] == player && 
//                     grid[row+1][col] == player && 
//                     grid[row+2][col] == player && 
//                     grid[row+3][col] == player) {
//                     return true;
//                 }
//             }
//         }

//         // Check diagonal (down-right)
//         for (int row = 0; row <= ROWS - 4; row++) {
//             for (int col = 0; col <= COLS - 4; col++) {
//                 if (grid[row][col] == player && 
//                     grid[row+1][col+1] == player && 
//                     grid[row+2][col+2] == player && 
//                     grid[row+3][col+3] == player) {
//                     return true;
//                 }
//             }
//         }

//         // Check diagonal (up-right)
//         for (int row = 3; row < ROWS; row++) {
//             for (int col = 0; col <= COLS - 4; col++) {
//                 if (grid[row][col] == player && 
//                     grid[row-1][col+1] == player && 
//                     grid[row-2][col+2] == player && 
//                     grid[row-3][col+3] == player) {
//                     return true;
//                 }
//             }
//         }

//         return false;
//     }

//     bool isBoardFull() const {
//         for (int col = 0; col < COLS; col++) {
//             if (!isColumnFull(col)) {
//                 return false;
//             }
//         }
//         return true;
//     }

//     void reset() {
//         for (int i = 0; i < ROWS; i++) {
//             for (int j = 0; j < COLS; j++) {
//                 grid[i][j] = 0;
//             }
//         }
//     }
// };

// // Game class to control game flow and logic
// class Game {
// private:
//     Board board;
//     int currentPlayer;
//     bool gameOver;
//     int winner;

// public:
//     Game() : currentPlayer(1), gameOver(false), winner(0) {}

//     void reset() {
//         board.reset();
//         currentPlayer = 1;
//         gameOver = false;
//         winner = 0;
//     }

//     bool isGameOver() const {
//         return gameOver;
//     }

//     int getWinner() const {
//         return winner;
//     }

//     int getCurrentPlayer() const {
//         return currentPlayer;
//     }

//     bool makeMove(int col) {
//         if (gameOver) {
//             return false;
//         }

//         if (board.dropPiece(col, currentPlayer)) {
//             // Check for win
//             if (board.checkWin(currentPlayer)) {
//                 gameOver = true;
//                 winner = currentPlayer;
//             } 
//             // Check for draw
//             else if (board.isBoardFull()) {
//                 gameOver = true;
//                 winner = 0; // 0 indicates a draw
//             } 
//             // Switch player
//             else {
//                 currentPlayer = (currentPlayer == 1) ? 2 : 1;
//             }
//             return true;
//         }
//         return false;
//     }

//     const Board& getBoard() const {
//         return board;
//     }
// };

// // GUI class to handle rendering and user input
// class GUI {
// private:
//     sf::RenderWindow window;
//     Game& game;
//     sf::Font font;
//     int hoverColumn;

//     void drawBoard() {
//         // Draw the board background
//         sf::RectangleShape boardBackground(sf::Vector2f(BOARD_WIDTH, BOARD_HEIGHT));
//         boardBackground.setFillColor(BOARD_COLOR);
//         window.draw(boardBackground);

//         // Draw the cells
//         const Board& board = game.getBoard();
//         for (int row = 0; row < ROWS; row++) {
//             for (int col = 0; col < COLS; col++) {
//                 sf::CircleShape cell(CELL_SIZE / 2 - 5);
//                 cell.setPosition(col * CELL_SIZE + 5, (row + 1) * CELL_SIZE + 5);
                
//                 int cellValue = board.getCell(row, col);
//                 if (cellValue == 0) {
//                     cell.setFillColor(EMPTY_COLOR);
//                 } else if (cellValue == 1) {
//                     cell.setFillColor(PLAYER1_COLOR);
//                 } else {
//                     cell.setFillColor(PLAYER2_COLOR);
//                 }
                
//                 window.draw(cell);
//             }
//         }

//         // Draw the hover piece if game is not over
//         if (!game.isGameOver() && hoverColumn >= 0 && hoverColumn < COLS) {
//             sf::CircleShape hoverPiece(CELL_SIZE / 2 - 5);
//             hoverPiece.setPosition(hoverColumn * CELL_SIZE + 5, 5);
            
//             if (game.getCurrentPlayer() == 1) {
//                 hoverPiece.setFillColor(PLAYER1_COLOR);
//             } else {
//                 hoverPiece.setFillColor(PLAYER2_COLOR);
//             }
            
//             window.draw(hoverPiece);
//         }

//         // Draw game over message if needed
//         if (game.isGameOver()) {
//             sf::RectangleShape overlay(sf::Vector2f(BOARD_WIDTH, BOARD_HEIGHT));
//             overlay.setFillColor(sf::Color(0, 0, 0, 128)); // Semi-transparent black
//             window.draw(overlay);

//             sf::Text gameOverText;
//             gameOverText.setFont(font);
//             gameOverText.setCharacterSize(40);
            
//             if (game.getWinner() == 0) {
//                 gameOverText.setString("Draw! Click to play again");
//             } else {
//                 gameOverText.setString("Player " + std::to_string(game.getWinner()) + " wins! Click to play again");
//             }
            
//             gameOverText.setFillColor(sf::Color::White);
            
//             // Center the text
//             sf::FloatRect textBounds = gameOverText.getLocalBounds();
//             gameOverText.setPosition(
//                 (BOARD_WIDTH - textBounds.width) / 2,
//                 (BOARD_HEIGHT - textBounds.height) / 2
//             );
            
//             window.draw(gameOverText);
//         }
//     }

// public:
//     GUI(Game& g) : game(g), hoverColumn(-1) {
//         window.create(sf::VideoMode(BOARD_WIDTH, BOARD_HEIGHT), "Connect 4");
//         window.setFramerateLimit(60);
        
//         // Load font
//         if (!font.loadFromFile("arial.ttf")) {
//             // Use default font if arial.ttf is not available
//             std::cout << "Warning: Could not load font file. Using default font." << std::endl;
//         }
//     }

//     void run() {
//         while (window.isOpen()) {
//             sf::Event event;
//             while (window.pollEvent(event)) {
//                 if (event.type == sf::Event::Closed) {
//                     window.close();
//                 } else if (event.type == sf::Event::MouseMoved) {
//                     // Update hover column
//                     int mouseX = event.mouseMove.x;
//                     hoverColumn = mouseX / CELL_SIZE;
//                 } else if (event.type == sf::Event::MouseButtonPressed) {
//                     if (event.mouseButton.button == sf::Mouse::Left) {
//                         int mouseX = event.mouseButton.x;
//                         int col = mouseX / CELL_SIZE;
                        
//                         if (game.isGameOver()) {
//                             game.reset();
//                         } else {
//                             game.makeMove(col);
//                         }
//                     }
//                 }
//             }

//             window.clear();
//             drawBoard();
//             window.display();
//         }
//     }
// };

// int main() {
//     Game game;
//     GUI gui(game);
//     gui.run();
//     return 0;
// }
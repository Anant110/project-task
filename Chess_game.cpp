#include<bits/stdc++.h>

using namespace std;

// Base class for all chess pieces
class ChessPiece {
public:
    ChessPiece(char type, bool isWhite) : type(type), isWhite(isWhite) {}
    virtual ~ChessPiece() {}
    virtual bool isValidMove(int startX, int startY, int endX, int endY, ChessPiece* board[8][8]) = 0;
    char getType() { return type; }
    bool isWhitePiece() { return isWhite; }

protected:
    char type;
    bool isWhite;
};

// Derived class for King
class King : public ChessPiece {
public:
    King(bool isWhite) : ChessPiece('K', isWhite) {}
    bool isValidMove(int startX, int startY, int endX, int endY, ChessPiece* board[8][8]) override {
        int dx = std::abs(startX - endX);
        int dy = std::abs(startY - endY);
        return (dx <= 1 && dy <= 1);
    }
};

// Board class to manage the chessboard
class Board {
public:
    Board() { initialize(); }
    ~Board() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                delete board[i][j];
                board[i][j] = nullptr; // Set to nullptr after deletion
            }
        }
    }

    void initialize() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                board[i][j] = nullptr;
            }
        }
        // Initialize the kings
        board[0][4] = new King(false); // Black king
        board[7][4] = new King(true);  // White king
    }

    void display() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] == nullptr) {
                    std::cout << ". ";
                } else {
                    std::cout << (board[i][j]->isWhitePiece() ? 'W' : 'B') << board[i][j]->getType() << " ";
                }
            }
            std::cout << std::endl;
        }
    }

    bool movePiece(int startX, int startY, int endX, int endY) {
        if (startX < 0 || startX >= 8 || startY < 0 || startY >= 8 ||
            endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
            return false;
        }
        ChessPiece* piece = board[startX][startY];
        if (piece == nullptr || !piece->isValidMove(startX, startY, endX, endY, board)) {
            return false;
        }
        // Check if the destination has a piece of the same color
        if (board[endX][endY] != nullptr && board[endX][endY]->isWhitePiece() == piece->isWhitePiece()) {
            return false;
        }
        delete board[endX][endY];  // Capture the piece if present
        board[endX][endY] = piece;
        board[startX][startY] = nullptr;
        return true;
    }

    bool isGameOver() {
        // Check for the presence of both kings
        bool whiteKingPresent = false, blackKingPresent = false;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] != nullptr) {
                    if (board[i][j]->getType() == 'K') {
                        if (board[i][j]->isWhitePiece()) whiteKingPresent = true;
                        else blackKingPresent = true;
                    }
                }
            }
        }
        return !(whiteKingPresent && blackKingPresent);
    }

    bool isKingCaptured(bool isWhite) {
        // Check if the specified king is captured
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] != nullptr && board[i][j]->getType() == 'K' && board[i][j]->isWhitePiece() == isWhite) {
                    return false;
                }
            }
        }
        return true;
    }

private:
    ChessPiece* board[8][8];
};

int main() {
    Board board;
    board.display();

    while (!board.isGameOver()) {
        int startX, startY, endX, endY;
        std::cout << "Enter move (startX startY endX endY): ";
        std::cin >> startX >> startY >> endX >> endY;
        if (board.movePiece(startX, startY, endX, endY)) {
            board.display();
            if (board.isKingCaptured(true)) {
                std::cout << "Black wins! White king is captured." << std::endl;
                break;
            } else if (board.isKingCaptured(false)) {
                std::cout << "White wins! Black king is captured." << std::endl;
                break;
            }
        } else {
            std::cout << "Invalid move. Try again." << std::endl;
        }
    }

    if (board.isGameOver()) {
        std::cout << "Game over!" << std::endl;
    }

    return 0;
}

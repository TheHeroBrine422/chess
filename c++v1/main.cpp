#include <iostream>
#include <string>
#include <list>
#include <unordered_map>
#include <thread>
#include "Engine.h"
#include "senjo/UCIAdapter.h"
#include "senjo/Output.h"

using namespace std;

/*
number to piece:
0: empty
1: white pawn
2: white knight
3: white bishop
4: white rook
5: white queen
6: white king
7: black pawn
8: black knight
9: black bishop
10: black rook
11: black queen
12: black king
 */

enum class Pieces {EMPTY, WPAWN, WKNIGHT, WBISHOP, WROOK, WQUEEN, WKING, BPAWN, BKNIGHT, BBISHOP, BROOK, BQUEEN, BKING};

class Board {
public:
    Pieces board[8][8];
    bool castling[4] = {true,true,true,true}; // white left (7,0), white right (7,7), black left (0,0), black right (0,7)

    Board() {
        for (auto & rank : board) { // set whole board to empty
            for (Pieces & location : rank){
                location = Pieces::EMPTY;
            }
        }

        board[0][0] = Pieces::BROOK; // black pieces
        board[0][1] = Pieces::BKNIGHT;
        board[0][2] = Pieces::BBISHOP;
        board[0][3] = Pieces::BQUEEN;
        board[0][4] = Pieces::BKING;
        board[0][5] = Pieces::BBISHOP;
        board[0][6] = Pieces::BKNIGHT;
        board[0][7] = Pieces::BROOK;

        for (Pieces & i : board[1]) { // black pawns
            i = Pieces::BPAWN;
        }

        board[0][0] = Pieces::BROOK; // black pieces
        board[0][1] = Pieces::BKNIGHT;
        board[0][2] = Pieces::BBISHOP;
        board[0][3] = Pieces::BQUEEN;
        board[0][4] = Pieces::BKING;
        board[0][5] = Pieces::BBISHOP;
        board[0][6] = Pieces::BKNIGHT;
        board[0][7] = Pieces::BROOK;

        board[7][0] = Pieces::WROOK; // white pieces
        board[7][1] = Pieces::WKNIGHT;
        board[7][2] = Pieces::WBISHOP;
        board[7][3] = Pieces::WQUEEN;
        board[7][4] = Pieces::WKING;
        board[7][5] = Pieces::WBISHOP;
        board[7][6] = Pieces::WKNIGHT;
        board[7][7] = Pieces::WROOK;

        for (Pieces & i : board[6]) { // black pawns
            i = Pieces::BPAWN;
        }
    }

    // this is a really simple eval that just bases the eval based on the
    int eval(bool player) { // true = white, false = black
        int points = 0;
        int multiplier = player ? 1 : -1;
        for (auto & rank : board) { // set whole board to empty
            for (Pieces & location : rank) {
                if (location != Pieces::EMPTY) {
                    switch(location) {
                        // white
                        case Pieces::WPAWN:
                            points += multiplier * 1;
                            break;
                        case Pieces::WBISHOP:
                        case Pieces::WKNIGHT:
                            points += multiplier * 3;
                            break;
                        case Pieces::WROOK:
                            points += multiplier * 5;
                            break;
                        case Pieces::WQUEEN:
                            points += multiplier * 9;
                            break;
                            // black
                        case Pieces::BPAWN:
                            points += multiplier * -1;
                            break;
                        case Pieces::BBISHOP:
                        case Pieces::BKNIGHT:
                            points += multiplier * -3;
                            break;
                        case Pieces::BROOK:
                            points += multiplier * -5;
                            break;
                        case Pieces::BQUEEN:
                            points += multiplier * -9;
                            break;
                    }
                }
            }
        }
        return points;
    }

    list<Board> validMoves() {
        list<Board> moves;

        return moves;
    }

};

int main(int /*argc*/, char** /*argv*/) {
    try {
        Engine engine;
        senjo::UCIAdapter adapter(engine);

        string line;
        line.reserve(16384);

        while (getline(cin, line)) {
            if (!adapter.doCommand(line)) {
                break;
            }
        }

        return 0;
    }
    catch (const exception& e) {
        senjo::Output() << "ERROR: " << e.what();
        return 1;
    }
}
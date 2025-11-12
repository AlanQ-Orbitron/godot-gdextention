#include "chess_board.hpp"
#include <string>
#include "godot_cpp/variant/string.hpp"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;
using namespace std;

void ChessBoard::reset_board()
{
    Board.white_pieces = 0ULL;
    Board.black_pieces = 0ULL;
    Board.pawns = 0ULL;
    Board.rooks = 0ULL;
    Board.knights = 0ULL;
    Board.bishops = 0ULL;
    Board.queens = 0ULL;
    Board.kings = 0ULL;
}

ChessBoard::GameState ChessBoard::fen_to_bit(String board)
{
    
    auto process_position = [](String state, char32_t l) {
        String result;
        for (int i = 0; i < state.length(); i++) {
            char32_t c = state[i];
            result += (c == l) ? "1" : (c >= U'0' && c <= U'9') ? String("0").repeat(c - U'0') : "0";
        }
        return result;
    };

    auto convert_to_binary = [](String string_binary) {
        return stoull(string_binary.utf8().get_data(), nullptr, 2);
    };

    // Only works with standard FEN chess notation
    ChessBoard::GameState converted_state;
    Array states = board.split(" ");
    String position = String(states[0]).replace("/", "").to_lower();

    converted_state.pawns = convert_to_binary(process_position(position, U'p'));
    converted_state.rooks = convert_to_binary(process_position(position, U'r'));
    converted_state.knights = convert_to_binary(process_position(position, U'n'));
    converted_state.bishops = convert_to_binary(process_position(position, U'b'));
    converted_state.queens = convert_to_binary(process_position(position, U'q'));
    converted_state.kings = convert_to_binary(process_position(position, U'k'));

    return converted_state;
}

// String ChessBoard::bit_to_fen(ChessBoard::GameState board)
// {
    
// }

void ChessBoard::set_board(String board)
{
    ChessBoard::GameState fen_board = fen_to_bit(board);
    Board.white_pieces = fen_board.white_pieces;
    Board.black_pieces = fen_board.black_pieces;
    Board.pawns = fen_board.pawns;
    Board.rooks = fen_board.rooks;
    Board.knights = fen_board.knights;
    Board.bishops = fen_board.bishops;
    Board.queens = fen_board.queens;
    Board.kings = fen_board.kings;
}

// uint64_t ChessBoard::evaluate_board(uint64_t board)
// {
    
// }

// uint64_t ChessBoard::generate_moves(int index)
// {
    
// }

// uint64_t ChessBoard::generate_pawn_movement(int index)
// {
    
// }

// uint64_t ChessBoard::generate_rook_movement(int index)
// {
    
// }

// uint64_t ChessBoard::generate_knight_movement(int index)
// {
    
// }

// uint64_t ChessBoard::generate_bishop_movement(int index)
// {
    
// }

// uint64_t ChessBoard::generate_queen_movement(int index)
// {
    
// }

// uint64_t ChessBoard::generate_king_movement(int index)
// {
    
// }

// uint64_t ChessBoard::evaluate_pawns(int index)
// {
    
// }

// uint64_t ChessBoard::evaluate_rooks(int index)
// {
    
// }

// uint64_t ChessBoard::evaluate_knights(int index)
// {
    
// }

// uint64_t ChessBoard::evaluate_bishops(int index)
// {
    
// }

// uint64_t ChessBoard::evaluate_queens(int index)
// {
    
// }

// uint64_t ChessBoard::evaluate_kings(int index)
// {
    
// }

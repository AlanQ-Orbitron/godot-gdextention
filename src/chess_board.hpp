#pragma once

#include "godot_cpp/variant/string.hpp"
#include <cstdint>

class ChessBoard{
    public:
        void reset_board();
        void generate_board();
    private:

        struct GameState {
            // Bitboards
            uint64_t white_pieces;
            uint64_t black_pieces;
            uint64_t pawns;
            uint64_t rooks;
            uint64_t knights;
            uint64_t bishops;
            uint64_t queens;
            uint64_t kings;
            uint64_t en_passant;

            // States
            uint8_t castling;
            bool white_to_move;
            uint8_t halfmove_clock;
            uint16_t fullmove_number;

        };
        GameState Board;
        uint64_t generate_pawn_movement(int index);
        uint64_t generate_rook_movement(int index);
        uint64_t generate_knight_movement(int index);
        uint64_t generate_bishop_movement(int index);
        uint64_t generate_queen_movement(int index);
        uint64_t generate_king_movement(int index);
        uint64_t evaluate_pawns(int index);
        uint64_t evaluate_rooks(int index);
        uint64_t evaluate_knights(int index);
        uint64_t evaluate_bishops(int index);
        uint64_t evaluate_queens(int index);
        uint64_t evaluate_kings(int index);
    protected:
        GameState fen_to_bit(godot::String board);
        godot::String bit_to_fen(GameState board);
        void set_board(godot::String board);
        uint64_t evaluate_board(uint64_t board);
        uint64_t generate_moves(int index);
};

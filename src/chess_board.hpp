#pragma once

#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/variant/array.hpp"
#include "godot_cpp/variant/dictionary.hpp"
#include "godot_cpp/variant/string.hpp"
#include "godot_cpp/variant/vector2.hpp"
#include <cstdint>
#include <utility>

using namespace std;

class ChessBoard: public godot::Node{
    GDCLASS(ChessBoard, Node)
    protected:
        enum Color {
            White, Black
        };
        enum Pieces {
            Pawn, Rook, Knight, Bishop, Queen, King
        };
        const char* to_UCI[64] = {
            "h1", "g1", "f1", "e1", "d1", "c1", "b1", "a1",
            "h2", "g2", "f2", "e2", "d2", "c2", "b2", "a2",
            "h3", "g3", "f3", "e3", "d3", "c3", "b3", "a3",
            "h4", "g4", "f4", "e4", "d4", "c4", "b4", "a4",
            "h5", "g5", "f5", "e5", "d5", "c5", "b5", "a5",
            "h6", "g6", "f6", "e6", "d6", "c6", "b6", "a6",
            "h7", "g7", "f7", "e7", "d7", "c7", "b7", "a7",
            "h8", "g8", "f8", "e8", "d8", "c8", "b8", "a8"
        };
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
            uint64_t attack_boards[64][12];

            // States
            uint8_t castling;
            bool white_to_move;
            uint8_t halfmove_clock;
            uint16_t fullmove_number;

        };
        GameState Board;
        const uint64_t HORIZONTAL = 0x00000000000000FF;
        const uint64_t VERTICAL = 0x0101010101010101;
        const uint64_t DIAGONAL_L = 0x8040201008040201;
        const uint64_t DIAGONAL_R = 0x0102040810204080;
    public:
        void reset_board();
        void generate_board(godot::String board);
        godot::Array get_valid_moves();
    protected:
        static void _bind_methods();
        void generate_moves();
        GameState fen_to_bit(godot::String board);
        godot::String bit_to_fen(GameState board);
        pair<int, int> index_to_rankfile(int square_index) {return {square_index % 8, square_index / 8};}; // Rank, File
        uint64_t mirrorHorizontal (uint64_t x);
        uint64_t pop_least_significant(uint64_t* bitboard) {
            unsigned long popped_index;
            _BitScanForward64(&popped_index, *bitboard);
            *bitboard &= *bitboard -1;
            return static_cast<int>(popped_index);
        }
    private:
        void set_board(godot::Dictionary board) {
            Board.white_pieces = board["white_pieces"];
            Board.black_pieces = board["black_pieces"];
            Board.pawns = board["pawns"];
            Board.rooks = board["rooks"];
            Board.knights = board["knights"];
            Board.bishops = board["bishops"];
            Board.queens = board["queens"];
            Board.kings = board["kings"];
        };
        godot::Dictionary get_board() const {
            godot::Dictionary board;
            board["white_pieces"] = Board.white_pieces;
            board["black_pieces"] = Board.black_pieces;
            board["pawns"] = Board.pawns;
            board["rooks"] = Board.rooks;
            board["knights"] = Board.knights;
            board["bishops"] = Board.bishops;
            board["queens"] = Board.queens;
            board["kings"] = Board.kings;
            return board;
        };
        uint64_t generate_h_quintessence(int square_index, uint64_t mask);
        uint64_t generate_pawn_movement(int square_index, bool is_white);
        uint64_t generate_wpawn_movement(int square_index);
        uint64_t generate_bpawn_movement(int square_index);
        uint64_t generate_rook_movement(int square_index, bool = true);
        uint64_t generate_knight_movement(int square_index, bool = true);
        uint64_t generate_bishop_movement(int square_index, bool = true);
        uint64_t generate_queen_movement(int square_index, bool = true);
        uint64_t generate_king_movement(int square_index, bool = true);

        using MoveGenerator = uint64_t (ChessBoard::*)(int, bool);

        static MoveGenerator move_generator[12];
};

//
// Created by DELL on 07/06/2018.
//

#ifndef AT_EX4_GAMEBOARD_H
#define AT_EX4_GAMEBOARD_H

#include <memory>
#include <functional>
#include <tuple>

template<typename GAME_PIECE>
using PieceInfo = std::unique_ptr<const std::pair<int, GAME_PIECE>>;

template <int ROWS, int COLS, typename GAME_PIECE, int PLAYERS=2>
class GameBoard{
    PieceInfo<GAME_PIECE> m_mainBoard[ROWS][COLS];

public:
    PieceInfo<GAME_PIECE> getPiece(int row, int col);
    PieceInfo<GAME_PIECE> setPiece(int row, int col, GAME_PIECE piece, int player);

    class PredicateIterator{
        const GameBoard* m_board;
        int m_rows;
        int m_cols;
        std::function<bool(const PieceInfo<GAME_PIECE>&)> m_predicate;
    public:
        PredicateIterator(const GameBoard* board, std::function<bool(const PieceInfo<GAME_PIECE>&)> predicate, int rows, int cols)
                : m_board(board), m_predicate(predicate), m_rows(rows), m_cols(cols) {}

        const std::tuple<int, int, GAME_PIECE, int> operator*(){
//            PieceInfo<GAME_PIECE>& piece = m_board->m_mainBoard[m_rows][m_cols];
            int player = m_board->m_mainBoard[m_rows][m_cols]->first;
            GAME_PIECE pie = m_board->m_mainBoard[m_rows][m_cols]->second;
            return std::make_tuple(m_rows,m_cols,pie,player);
        };
        bool operator!=(const PredicateIterator& other){
            return (m_rows != other.m_rows) || (m_cols != other.m_cols) || (m_board != other.m_board);
        }
        PredicateIterator& operator++(){
            if(m_rows >= ROWS) return *this;
            do{
                m_cols++;
                if(m_cols == COLS){
                    m_cols = 0;
                    m_rows++;
                    if(m_rows >= ROWS){
                        m_cols = COLS;
                        break;
                    }
                }

            }while(!m_predicate(m_board->m_mainBoard[m_rows][m_cols]));
            return *this;
        }

    };

    PredicateIterator begin()const;
    PredicateIterator end()const;


};

template<int ROWS, int COLS, typename GAME_PIECE, int PLAYERS>
typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PredicateIterator GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::begin() const {
    return GameBoard::PredicateIterator(this, [](const PieceInfo<GAME_PIECE>& piece){ return (piece!= nullptr); }, 0, 0);
}

template<int ROWS, int COLS, typename GAME_PIECE, int PLAYERS>
typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PredicateIterator GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::end() const {
    return GameBoard::PredicateIterator(this, [](const PieceInfo<GAME_PIECE>& piece){ return false; }, ROWS, COLS);
}

template<int ROWS, int COLS, typename GAME_PIECE, int PLAYERS>
PieceInfo<GAME_PIECE>
GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::setPiece(int row, int col, GAME_PIECE piece, int player) {
    m_mainBoard[row][col] = std::make_unique<const std::pair<int, GAME_PIECE>>(std::make_pair(player, piece));
    return std::make_unique<const std::pair<int, GAME_PIECE>>(std::make_pair(player, piece));
}


#endif //AT_EX4_GAMEBOARD_H

//
// Created by DELL on 07/06/2018.
//

#include "GameBoard.h"
/*
template<int ROWS, int COLS, typename GAME_PIECE, int PLAYERS>
typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PredicateIterator &GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PredicateIterator::operator++() {
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
}*/
/*
template<int ROWS, int COLS, typename GAME_PIECE, int PLAYERS>
bool
GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PredicateIterator::operator!=(const GameBoard::PredicateIterator &other) {
    return (m_rows != other.m_rows) || (m_cols != other.m_cols) || (m_board != other.m_board);
}*/
/*
template<int ROWS, int COLS, typename GAME_PIECE, int PLAYERS>
const std::tuple<int, int, GAME_PIECE, int> GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PredicateIterator::operator*() {
    PieceInfo<GAME_PIECE>& piece = m_board->m_mainBoard[m_rows][m_cols];
    return std::make_tuple(m_rows,m_cols,piece->second,piece->first);
}*/

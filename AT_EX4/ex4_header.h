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
    PieceInfo<GAME_PIECE> getPiece(int row, int col) {
        if(row < 0 || row >= ROWS) return nullptr;
        if(col < 0 || col >= COLS) return nullptr;
        if(m_mainBoard[row][col] == nullptr) return nullptr;
        return std::make_unique<const std::pair<int, GAME_PIECE>>(
                std::make_pair(m_mainBoard[row][col]->first,m_mainBoard[row][col]->second));
    }
    PieceInfo<GAME_PIECE> setPiece(int row, int col, GAME_PIECE piece, int player){
        if(row < 0 || row >= ROWS) return nullptr;
        if(col < 0 || col >= COLS) return nullptr;
        PieceInfo<GAME_PIECE> prevVal = std::move(m_mainBoard[row][col]);
        m_mainBoard[row][col] = std::make_unique<const std::pair<int, GAME_PIECE>>(std::make_pair(player, piece));
        return prevVal;
    }


    class PredicateIterator{
        const GameBoard* m_board;
        int m_rows;
        int m_cols;
        std::function<bool(const PieceInfo<GAME_PIECE>&)> m_predicate;
    public:
        PredicateIterator(const GameBoard* board, std::function<bool(const PieceInfo<GAME_PIECE>&)> predicate, int rows, int cols)
                : m_board(board), m_rows(rows), m_cols(cols), m_predicate(predicate) {}

        const std::tuple<int, int, GAME_PIECE, int> operator*(){
            int player = m_board->m_mainBoard[m_rows][m_cols]->first;
            GAME_PIECE pie(m_board->m_mainBoard[m_rows][m_cols]->second);
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

        bool isPredicate(int row, int col) const{return m_predicate(m_board->m_mainBoard[row][col]);}

    };

    PredicateIterator begin()const{
        PredicateIterator itr(this, [](const PieceInfo<GAME_PIECE>& piece){ return (piece!= nullptr); }, 0, 0);
        if(!itr.isPredicate(0,0))
            ++itr;
        return itr;
    }
    PredicateIterator end()const{
        return PredicateIterator(this, [](const PieceInfo<GAME_PIECE>& piece){ return (piece!= nullptr); }, ROWS, COLS);
    }

    class GameBoardView{
        const GameBoard* m_board;
        std::function<bool(const PieceInfo<GAME_PIECE>&)> m_predicate;

    public:
        GameBoardView(const GameBoard* board, std::function<bool(const PieceInfo<GAME_PIECE>&)> predicate):
                m_board(board), m_predicate(predicate) {}
        PredicateIterator begin()const {
            PredicateIterator itr(this->m_board,
                                  m_predicate,
                                  0, 0);
            if(!itr.isPredicate(0,0))
                ++itr;
            return itr;
        }
        PredicateIterator end()const {
            return PredicateIterator(this->m_board,
                                     m_predicate,
                                     ROWS, COLS);
        }

    };

    GameBoardView allPiecesOfPlayer(int playerNum) const{
        return GameBoardView(this,
                             [playerNum](const PieceInfo<GAME_PIECE>& piece){
                                 return (piece!= nullptr) && (piece->first == playerNum);
                             });
    }

    GameBoardView allOccureneceOfPiece(const GAME_PIECE pieceToFind) const{
        return GameBoardView(this,
                          [pieceToFind](const PieceInfo<GAME_PIECE>& piece){
                              return (piece!= nullptr) && (piece->second == pieceToFind);
                          });
    }

    GameBoardView allOccureneceOfPieceForPlayer(const GAME_PIECE pieceToFind, int playerNum) const {
        return GameBoardView(this,
                             [pieceToFind, playerNum](const PieceInfo<GAME_PIECE>& piece){
                                 return (piece!= nullptr) && (piece->second == pieceToFind) && (piece->first == playerNum);
                             });
    }

};



#endif //AT_EX4_GAMEBOARD_H

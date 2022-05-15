#include "gamesarray.h"

GamesArray::GamesArray()
{

}

void GamesArray::generate(int count, int size, operation op)
{
    m_games.resize(count);
    for (int i = 0; i < count; ++i) {
        m_games[i] = new Game;

        m_games[i]->m_kenken = new kenken(size, op);
        m_games[i]->m_kenken->generate_game();
        m_games[i]->m_index = i;
    }
}

void GamesArray::clearSolutions()
{
    for (int i = 0; i < m_games.size(); ++i) {
        m_games[i]->m_kenken->clear_solution();
    }
}

void GamesArray::clearGames()
{
    for (int i = 0; i < m_games.size(); ++i) {
        m_games[i]->m_kenken->delete_game();
    }
    m_games.clear();
}

GamesVector& GamesArray::games()
{
    return m_games;
}

const GamesVector& GamesArray::games() const
{
    return m_games;
}

void GamesArray::setGames(const GamesVector &games)
{
    m_games = games;
}

void solveB(kenken *game)
{
    game->solve(BACKTRACKING);
}

void solveBFC(kenken *game)
{
    game->solve(BACKTRACKING_WITH_FORWARD_CHECKING);
}

void solveBFCAC(kenken *game)
{
    game->solve(BACKTRACKING_WITH_FORWARDCHECKING_AND_ARC_CONSISTENCY);
}

#ifndef GAMESARRAY_H
#define GAMESARRAY_H

#include "kenken.h"

#include <QVector>

struct Game{
    kenken *m_kenken;
    int m_index;
};

typedef QVector<Game*> GamesVector;

class GamesArray
{
public:
    GamesArray();
    ~GamesArray() {clearGames();}

    // auxiliary functions for the entire array
    void generate(int count, int size, operation op);
    void clearSolutions();
    void clearGames();

    //  getters and setters
    const GamesVector& games() const;
    GamesVector& games();
    void setGames(const GamesVector &games);

private:
    GamesVector m_games;
};


// Solvers
void solveB(kenken *game);
void solveBFC(kenken *game);
void solveBFCAC(kenken *game);

#endif // GAMESARRAY_H

#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "gamesarray.h"

#include <chrono>

#include <QVector>
#include <QFutureWatcher>

const size_t MODES_COUNT = 3;

typedef bool Mode;
typedef Mode Modes[MODES_COUNT];

typedef QVector<std::chrono::duration<double>> Durations;

class Comparator
{
public:
    Comparator();
    ~Comparator() {clear();}

    void compare(QFutureWatcher<void> &watcher);

    int size() const;
    void setSize(int size);

    operation op() const;
    void setOp(const operation &op);

    Mode* modes();
    void setModes(const Mode *modes);

    int count() const;
    void setCount(int count);

    void aggregateResults(double *results);

    void clear();

private:
    int m_count;
    int m_size;
    operation m_op;

    Modes m_modes;
    GamesArray m_games;

    size_t *m_timer;

    Durations m_durations[MODES_COUNT];
    double *m_finalDurations;

    void solve(Game *game);
};

#endif // COMPARATOR_H

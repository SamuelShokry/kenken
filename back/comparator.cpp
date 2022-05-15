#include "comparator.h"

#include <QtConcurrent/QtConcurrent>

Comparator::Comparator()
    : m_count(0),
      m_size(0),
      m_op(PLUS),
      m_timer(Q_NULLPTR),
      m_finalDurations(Q_NULLPTR)
{

}

void Comparator::compare(QFutureWatcher<void> &watcher)
{
    clear();

    m_finalDurations = new double[MODES_COUNT];
    m_games.generate(m_count, m_size, m_op);

    for (size_t i = 0; i < MODES_COUNT; ++i)
        m_durations[i].resize(m_count);

    watcher.setFuture(
        QtConcurrent::map(m_games.games(), [this] (Game* &game) {
            this->solve(game);
        }));
}

int Comparator::size() const
{
    return m_size;
}

void Comparator::setSize(int size)
{
    m_size = size;
}

operation Comparator::op() const
{
    return m_op;
}

void Comparator::setOp(const operation &op)
{
    m_op = op;
}

Mode *Comparator::modes()
{
    return m_modes;
}

void Comparator::setModes(const Mode *modes)
{
    for (size_t i = 0; i < MODES_COUNT; ++i)
        m_modes[i] = modes[i];
}

int Comparator::count() const
{
    return m_count;
}

void Comparator::setCount(int count)
{
    m_count = count;
}

void Comparator::aggregateResults(double *results)
{
    for (size_t i = 0; i < MODES_COUNT; ++i) {
        results[i] = 0;
        for (int j = 0; j < m_count; ++j) {
            results[i] += m_durations[i][j].count();
        }
    }
}

void Comparator::clear()
{
    m_games.clearGames();
    for (size_t i = 0; i < MODES_COUNT; ++i)
        m_durations[i].clear();

    if (m_finalDurations) {
        delete[] m_finalDurations;
        m_finalDurations = Q_NULLPTR;
    }
}

void Comparator::solve(Game *game)
{
    solving_technique op;
    for (size_t i = 0; i < MODES_COUNT; ++i) {
        if (m_modes[i]) {
            if (i == 0)
                op = BACKTRACKING;
            else if (i == 1)
                op = BACKTRACKING_WITH_FORWARD_CHECKING;
            else
                op = BACKTRACKING_WITH_FORWARDCHECKING_AND_ARC_CONSISTENCY;

            auto start = std::chrono::steady_clock::now();
            game->m_kenken->solve(op);
            auto end = std::chrono::steady_clock::now();

            m_durations[i][game->m_index] = end - start;

            game->m_kenken->clear_solution(); //clear the solution.
        }
    }
}

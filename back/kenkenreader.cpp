#include "kenkenreader.h"

KenkenReader::KenkenReader()
    : m_reader(nullptr)
{

}

std::string KenkenReader::read(kenken &game, const std::string &path)
{
    std::ifstream reader(path, std::ios::out | std::ios::binary);

    if (!reader) {
        return "File cannot be opened for reading";
    }

    this->m_reader = &reader;
    readKenken(game);
    this->m_reader = nullptr;

    reader.close();
    if (!reader.good()) {
        return "Error occurred at reading time!";
    }

    return "";
}

void KenkenReader::readKenken(kenken &game)
{
    readScalar(game.isSolved);

    readGrid(*game.get_game_grid_ptr());
    readOperationsCategory(*game.get_game_operation_ptr());
}

void KenkenReader::readGrid(grid &g)
{
    readScalar(g.gridSize);
    readScalar(g.numberOfCages);

    assert(g.gridSize > 0 && "g.gridSize <= 0");
    assert(g.numberOfCages > 0 && "g.numberOfCages <= 0");

    g.gridCells = new cell[g.gridSize*g.gridSize];
    readArray((char*) g.gridCells,
              sizeof(cell)*g.gridSize*g.gridSize);

    g.cages = new cage[g.numberOfCages];
    for (int i = 0; i < g.numberOfCages; ++i) {
        readCage(g.cages[i], g.gridCells);
    }
}

void KenkenReader::readCage(cage &c, cell * gridCells)
{
    readScalar(c.targetValue);
    readScalar(c.operation);
    readScalar(c.numberOfCells);
    readScalar(c.firstCellInCage);

    assert(c.numberOfCells > 0 && "c.numberOfCells <= 0");

    c.cageCells = new cell*[c.numberOfCells];
    for (int i = 0; i < c.get_number_of_cells(); ++i) {
        c.cageCells[i] = gridCells;
        int offset;
        readScalar(offset);
        c.cageCells[i] += offset;
    }
}

void KenkenReader::readOperationsCategory(operationsCategory &op)
{
    readScalar(op.categoryName);
    readScalar(op.operationsSize);

    assert(op.operationsSize > 0 && "op.operationsSize <= 0");

    op.operationsArray = new char[op.operationsSize];
    readArray(op.operationsArray,
              sizeof(char)*op.operationsSize);
}

void KenkenReader::readArray(char* data, const size_t size)
{
    assert(size > 0 && "readArray size <= 0");
    m_reader->read(data, size);
}

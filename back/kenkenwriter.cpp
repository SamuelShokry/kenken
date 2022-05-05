#include "kenkenwriter.h"

#include <fstream>

KenkenWriter::KenkenWriter()
    : m_writer(nullptr)
{

}

std::string KenkenWriter::write(const kenken &game, const std::string &path)
{
    std::ofstream writer(path, std::ios::out | std::ios::binary);

    if (!writer) {
        return "File cannot be opened for writing";
    }

    this->m_writer = &writer;
    writeKenken(game);
    this->m_writer = nullptr;

    writer.close();
    if (!writer.good()) {
        return "Error occurred at writing time!";
    }

    return "";
}

void KenkenWriter::writeKenken(const kenken &game)
{
    writeScalar(game.get_is_solved());

    writeGrid(*game.get_game_grid_ptr());
    writeOperationsCategory(*game.get_game_operation_ptr());
}

void KenkenWriter::writeGrid(const grid &g)
{
    writeScalar(g.get_grid_size());
    writeScalar(g.get_number_of_cages());

    writeArray((const char*)g.get_cells_ptr(),
               sizeof(cell)*g.get_grid_size()*g.get_grid_size());

    for (int i = 0; i < g.get_number_of_cages(); ++i) {
        writeCage(g.get_cages_ptr()[i], g.get_cells_ptr());
    }
}

void KenkenWriter::writeCage(const cage &c, const cell * const gridCells)
{
    writeScalar(c.get_target_value());
    writeScalar(c.get_operation());
    writeScalar(c.get_number_of_cells());
    writeScalar(c.get_first_cell_in_cage());

    cell **cells = c.get_cage_cells_ptr();
    for (int i = 0; i < c.get_number_of_cells(); ++i) {
        int offset = cells[i] - gridCells;
        writeScalar(offset);
    }
}

void KenkenWriter::writeOperationsCategory(const operationsCategory &op)
{
    writeScalar(op.get_category_name());
    writeScalar(op.get_operations_Size());

    writeArray(op.get_operations_array(),
               sizeof(char)*op.get_operations_Size());
}

void KenkenWriter::writeArray(const char *data, const size_t size)
{
    m_writer->write(data, size);
}

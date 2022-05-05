#ifndef KENKENWRITER_H
#define KENKENWRITER_H

#include "kenken.h"

class KenkenWriter
{
public:
    KenkenWriter();

    std::string write(const kenken &game, const std::string &path);

public:
    void writeKenken(const kenken &game);
    void writeGrid(const grid &g);
    void writeOperationsCategory(const operationsCategory &op);
    void writeCage(const cage &c, const cell * const cells);

    void writeArray(const char *data, const size_t size);

    template<class T>
    void writeScalar(const T data);

    std::ofstream *m_writer;
};

template<class T>
void KenkenWriter::writeScalar(const T data) {
    m_writer->write((char*) &data, sizeof(data));
}

#endif // KENKENWRITER_H

#ifndef KENKENREADER_H
#define KENKENREADER_H

#include "kenken.h"

class KenkenReader
{
public:
    KenkenReader();

    std::string read(kenken &game, const std::string &path);

public:
    void readKenken(kenken &game);
    void readGrid(grid &g);
    void readOperationsCategory(operationsCategory &op);
    void readCage(cage &c);

    void readArray(char *data, const size_t size);

    template<class T>
    void readScalar(T &data);

    std::ifstream *m_reader;
};

template<class T>
void KenkenReader::readScalar(T &data) {
    m_reader->read((char*) &data, sizeof(data));
}

#endif // KENKENREADER_H

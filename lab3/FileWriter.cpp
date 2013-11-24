#include "FileWriter.h"

FileWriter::FileWriter(const char* path)
{
    file = new std::ofstream(path, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
    position = 0;
}

FileWriter::~FileWriter()
{
    if (file != NULL) {
        delete file;
    }
}

int FileWriter::WriteData(char* buffer, int count)
{
    file->seekp(position);
    file->write(buffer, count);
    position = file->tellp();

    return count;
}

void FileWriter::Close()
{
    if (file != NULL) {
        file->close();
    }
}
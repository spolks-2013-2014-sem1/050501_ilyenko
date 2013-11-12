#include "FileReader.h"

FileReader::FileReader(const char* filePath)
{
    file = new std::ifstream(filePath, std::ifstream::binary);
    fileSize = SetFileSize();

    position = 0;
}

FileReader::~FileReader()
{
    if (file != NULL) {
        file->close();
        delete file;
    }
}

bool FileReader::CanRead()
{
    return file != NULL && file->good();
}

const char* FileReader::GetData(char* buffer, int& count)
{

    file->seekg(position);

    file->read(buffer, count);

    if (file->eof()) {
        // Modify :count because only gcount() bytes have been read.
        count = file->gcount();
    }

    position = file->tellg();
    return buffer;
}

int FileReader::SetFileSize()
{
    file->seekg (0, file->end);
    int length = file->tellg();
    return length;
}

const int FileReader::GetFileSize() const
{
    return fileSize;
}
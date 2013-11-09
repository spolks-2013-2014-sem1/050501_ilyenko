#ifndef __FileReader__
#define __FileReader__


#include <fstream>
#include <istream>

class FileReader
{
private:
protected:

    std::ifstream* file;

    int fileSize;

    int position;
    
    int SetFileSize();

public:
    
    FileReader(const char* filePath);

    virtual ~FileReader();

    bool CanRead();

    const char* GetData(char* buffer, int& count);

    const int GetFileSize() const;
};

#endif // __FileReader__
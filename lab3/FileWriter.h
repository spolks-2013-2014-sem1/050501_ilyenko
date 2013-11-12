#ifndef __FileWriter__
#define __FileWriter__


#include <fstream>
#include <ostream>

class FileWriter
{
private:
protected:

    std::ofstream* file;

    int position;

public:
    
    FileWriter(const char* filePath);

    virtual ~FileWriter();

    int WriteData(char* buffer, int count);

    void Close();
};

#endif // __FileWriter__
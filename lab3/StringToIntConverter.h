#ifndef __StringTointConverter__
#define __StringToIntConverter__

#include <string>
#include <sstream>

class StringToIntConverter 
{
private:
protected:
public:

    StringToIntConverter(){}

    ~StringToIntConverter(){}

    int ToInt(std::string str)
    {
        int number = -1;
        std::istringstream(str) >> number;
        return number;
    }

    std::string ToString(int number)
    {
        return dynamic_cast<std::ostringstream &>(
            (std::ostringstream() << std::dec << number )
            ).str();
    }
};

#endif // _StringToIntConverter__
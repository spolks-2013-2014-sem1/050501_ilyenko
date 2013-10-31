#ifndef __ISignalObserver__
#define __ISignalObserver__

class ISignalObserver
{
public:

    ISignalObserver(){}

    virtual ~ISignalObserver(){}
    
    virtual void SignalCallback(int signum) = 0;
};

#endif  //__ISignalObserver__
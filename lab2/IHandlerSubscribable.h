#ifndef __IHandlerSubscribable__
#define __IHandlerSubscribable__

class IHandlerSubscribable
{
public:
    IHandlerSubscribable(){}
    virtual ~IHandlerSubscribable(){}
    virtual void SignalCallback(int signum) = 0;
};

#endif  //__IHandlerSubscribable__
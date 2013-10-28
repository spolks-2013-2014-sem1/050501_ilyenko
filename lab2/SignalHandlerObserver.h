#ifndef __SignalHandlerObserver__
#define __SignalHandlerObserver__

#include "IHandlerSubscribable.h"
#include "headers.h"

class SignalHandlerObserver
{
private:
    static std::vector<IHandlerSubscribable*> observers;

    static void Notify(int signum);
public:

    static void Subscribe(IHandlerSubscribable* obj);
    
    static void Unsubscribe(IHandlerSubscribable* obj);

    static void SetupSignalHandlers();
};

#endif //__SignalHandlerObserver__
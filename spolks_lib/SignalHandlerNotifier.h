#ifndef __SignalHandlerNotifier__
#define __SignalHandlerNotifier__

#include "ISignalObserver.h"
#include "headers.h"

class SignalHandlerNotifier
{
private:
    static std::vector<ISignalObserver*> observers;

    static void Notify(int signum);
public:

    static void Subscribe(ISignalObserver* obj);
    
    static void Unsubscribe(ISignalObserver* obj);

    static void SetupSignalHandlers();
};

#endif //__SignalHandlerNotifier__
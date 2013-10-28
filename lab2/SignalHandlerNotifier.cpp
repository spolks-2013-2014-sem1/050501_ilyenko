#include "SignalHandlerNotifier.h"

std::vector<ISignalObserver*> SignalHandlerNotifier::observers = std::vector<ISignalObserver*>();

void SignalHandlerNotifier::Subscribe(ISignalObserver* obj)
{
    observers.push_back(obj);
}

void SignalHandlerNotifier::SetupSignalHandlers()
{
    signal(SIGINT, Notify);
    signal(SIGTERM, Notify);
    signal(SIGQUIT, Notify);
}

void SignalHandlerNotifier::Notify(int signum)
{
    for (unsigned int i = 0; i < observers.size(); ++i) {
        ((ISignalObserver*)observers[i])->SignalCallback(signum);
    }

    exit(signum);
}
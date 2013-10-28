#include "SignalHandlerObserver.h"

std::vector<IHandlerSubscribable*> SignalHandlerObserver::observers = std::vector<IHandlerSubscribable*>();

void SignalHandlerObserver::Subscribe(IHandlerSubscribable* obj)
{
    observers.push_back(obj);
}

void SignalHandlerObserver::SetupSignalHandlers()
{
    signal(SIGINT, Notify);
    signal(SIGTERM, Notify);
    signal(SIGQUIT, Notify);
}

void SignalHandlerObserver::Notify(int signum)
{
    for (unsigned int i = 0; i < observers.size(); ++i) {
        ((IHandlerSubscribable*)observers[i])->SignalCallback(signum);
    }

    exit(signum);
}
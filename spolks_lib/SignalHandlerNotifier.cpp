#include "SignalHandlerNotifier.h"

std::vector<ISignalObserver*> SignalHandlerNotifier::observers = std::vector<ISignalObserver*>();

void SignalHandlerNotifier::Subscribe(ISignalObserver* obj)
{
    observers.push_back(obj);
}

void SignalHandlerNotifier::SetupSignalHandlers()
{
    Signal(SIGINT);
    Signal(SIGTERM);
    Signal(SIGQUIT);
}

void SignalHandlerNotifier::Notify(int signum)
{
    for (unsigned int i = 0; i < observers.size(); ++i) {
        ((ISignalObserver*)observers[i])->SignalCallback(signum);
    }
}

void SignalHandlerNotifier::Signal(int signum)
{
    struct sigaction new_action; 
    new_action.sa_handler = Notify;
    sigemptyset (&new_action.sa_mask);
    new_action.sa_flags = 0;
    sigaction(signum, &new_action, 0);
}
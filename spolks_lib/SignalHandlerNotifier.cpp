#include "SignalHandlerNotifier.h"

std::map<int,std::vector<ISignalObserver*> > SignalHandlerNotifier::observers = 
    std::map<int,std::vector<ISignalObserver*> >();

void SignalHandlerNotifier::Subscribe(ISignalObserver* obj, int signum)
{
    observers[signum].push_back(obj);
}

void SignalHandlerNotifier::SetupSignalHandlers()
{
    Signal(SIGINT);
    Signal(SIGTERM);
    Signal(SIGQUIT);
    Signal(SIGURG);
}

void SignalHandlerNotifier::Notify(int signum)
{
    for (unsigned int i = 0; i < observers[signum].size(); ++i) {
        ((ISignalObserver*)observers[signum][i])->SignalCallback(signum);
    }
}

void SignalHandlerNotifier::Signal(int signum)
{
    struct sigaction new_action; 
    new_action.sa_handler = Notify;
    
    sigaction(signum, &new_action, 0);
}
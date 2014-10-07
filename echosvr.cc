#include <iostream>
#include <string>
#include <ace/Reactor.h>
#include <ace/Select_Reactor.h>
#include <ace/Thread_Manager.h>
#include "echoacceptor.h"
#include "echosvr.h"

class QuitHandler : public ACE_Event_Handler
{
public:
	QuitHandler(ACE_Reactor *r) : ACE_Event_Handler(r) {}

	virtual int handle_exception(ACE_HANDLE)
	{
		reactor()->end_reactor_event_loop();
		return -1;
	}

	virtual int handle_close(ACE_HANDLE, ACE_Reactor_Mask)
	{
		delete this;
		return 0;
	}

protected:
	virtual ~QuitHandler() {}
};

static ACE_THR_FUNC_RETURN event_loop(void *arg)
{
	ACE_Reactor *reactor = static_cast<ACE_Reactor *>(arg);

	reactor->owner(ACE_OS::thr_self());
	reactor->run_reactor_event_loop();
	return 0;
}

static ACE_THR_FUNC_RETURN controller(void *arg)
{
	ACE_Reactor *reactor = static_cast<ACE_Reactor *>(arg);
	QuitHandler *quitHandler = NULL;
	ACE_NEW_RETURN(quitHandler, QuitHandler(reactor), 0);

	for (;;)
	{
		std::string userInput;
		std::getline(std::cin, userInput, '\n');
		if (userInput == "quit")
		{
			reactor->notify(quitHandler);
			break;
		}
	}

	return 0;
}

int main(int argc, char *argv[])
{
	typedef EchoServer<EchoAcceptor> EchoServerDaemon;

	ACE_Select_Reactor selectReactor;
	ACE_Reactor reactor(&selectReactor);

	EchoServerDaemon *server;
	ACE_NEW_RETURN(server, EchoServerDaemon(&reactor), 1);

	ACE_Thread_Manager::instance()->spawn(event_loop, &reactor);
	ACE_Thread_Manager::instance()->spawn(controller, &reactor);

	return ACE_Thread_Manager::instance()->wait();
}

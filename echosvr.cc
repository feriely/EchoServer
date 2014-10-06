#include <ace/Reactor.h>
#include <ace/Select_Reactor.h>
#include <ace/Thread_Manager.h>
#include "echoacceptor.h"
#include "echosvr.h"

static ACE_THR_FUNC_RETURN event_loop(void *arg)
{
	ACE_Reactor *reactor = static_cast<ACE_Reactor *>(arg);

	reactor->owner(ACE_OS::thr_self());
	reactor->run_reactor_event_loop();
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

	return ACE_Thread_Manager::instance()->wait();

	return 0;
}

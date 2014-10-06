#include "echoeventhandler.h"
#include "echoacceptor.h"

int EchoAcceptor::open(const ACE_INET_Addr& local_addr)
{
	if (acceptor_.open(local_addr) == -1)
		return -1;
	return reactor()->register_handler(this, ACE_Event_Handler::ACCEPT_MASK);
}

int EchoAcceptor::handle_input(ACE_HANDLE handle)
{
	EchoEventHandler *peerHandler = NULL;
	ACE_NEW_RETURN(peerHandler, EchoEventHandler(reactor()), -1);

	if (acceptor_.accept(peerHandler->peer()) == -1)
	{
		delete peerHandler;
		return -1;
	}
	else if (peerHandler->open() == -1)
	{
		peerHandler->handle_close();
		return -1;
	}

	return 0;
}

int EchoAcceptor::handle_close(ACE_HANDLE, ACE_Reactor_Mask)
{
	acceptor_.close();
	delete this;
	return 0;
}

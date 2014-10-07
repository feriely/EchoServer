#ifndef ECHOSVR_H
#define ECHOSVR_H

#include <ace/ACE.h>
#include <ace/Reactor.h>
/*
template <typename ACCEPTOR>
class EchoServer : public ACCEPTOR
{
public:
	EchoServer(ACE_Reactor* reactor) : ACCEPTOR(reactor)
	{
		typename ACCEPTOR::PEER_ADDR serverAddr;
		int result;

		result = serverAddr.set("9877", (ACE_UINT32)INADDR_ANY);
		if (result != -1)
			result = ACCEPTOR::open(serverAddr);
		if (result == -1)
			reactor->end_reactor_event_loop();
	}
};
*/

// Acceptor as a member variable
template <typename ACCEPTOR>
class EchoServer
{
public:
	EchoServer(ACE_Reactor* reactor)
	{
		ACE_NEW_NORETURN(acceptor_, ACCEPTOR(reactor));
		typename ACCEPTOR::PEER_ADDR serverAddr;
		int result;

		result = serverAddr.set("9877", (ACE_UINT32)INADDR_ANY);
		if (result != -1)
			result = acceptor_->open(serverAddr);
		if (result == -1)
			reactor->end_reactor_event_loop();
	}
private:
	ACCEPTOR *acceptor_;
};
#endif

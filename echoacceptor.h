#ifndef ECHOSVRACCEPTOR_H
#define ECHOSVRACCEPTOR_H

#include <ace/Event_Handler.h>
#include <ace/INET_Addr.h>
#include <ace/Reactor.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/SOCK_Stream.h>

class EchoAcceptor : public ACE_Event_Handler
{
public:
	typedef ACE_INET_Addr PEER_ADDR;

	EchoAcceptor(ACE_Reactor *r) : ACE_Event_Handler(r)
	{
	}

	virtual int open(const ACE_INET_Addr& local_addr);
	virtual int handle_input(ACE_HANDLE = ACE_INVALID_HANDLE);
	virtual int handle_close(ACE_HANDLE = ACE_INVALID_HANDLE, ACE_Reactor_Mask = 0);
	virtual ACE_HANDLE get_handle() const
	{
		return acceptor_.get_handle();
	}
	ACE_SOCK_Acceptor& acceptor() { return acceptor_; }

protected:
	ACE_SOCK_Acceptor acceptor_;
};

#endif

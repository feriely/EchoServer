#ifndef ECHOEVENTHANDLER_H
#define ECHOEVENTHANDLER_H

#include <ace/Event_Handler.h>
#include <ace/Reactor.h>
#include <ace/SOCK_Stream.h>

class EchoEventHandler : public ACE_Event_Handler
{
public:
	EchoEventHandler(ACE_Reactor* r) : ACE_Event_Handler(r)
	{
	}

	virtual int open();
	virtual int handle_input(ACE_HANDLE = ACE_INVALID_HANDLE);
	virtual int handle_close(ACE_HANDLE = ACE_INVALID_HANDLE, ACE_Reactor_Mask = 0);
	virtual ACE_HANDLE get_handle() const
	{
		return stream_.get_handle();
	}

	ACE_SOCK_Stream& peer() { return stream_; }
protected:
	ACE_SOCK_Stream stream_;
};

#endif

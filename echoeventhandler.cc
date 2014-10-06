#include "echoeventhandler.h"

int EchoEventHandler::open()
{
	return reactor()->register_handler(this, ACE_Event_Handler::READ_MASK);
}

int EchoEventHandler::handle_input(ACE_HANDLE handle)
{
	int buf[1024];
	int nbytes = read(handle, buf, sizeof(buf));
	if (nbytes < 0)
		return -1;
	else if (nbytes == 0)
		handle_close();

	if (write(handle, buf, nbytes) != nbytes)
		return -1;
	else 
		return 0;
}

int EchoEventHandler::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask mask)
{
	stream_.close();
	delete this;
	return 0;
}

#pragma once
#include "Communicator.h"

class Server
{
public:
	void run();

protected:
	Communicator m_communicator;
	RequestHandlerFactory m_handlerFactory;
};
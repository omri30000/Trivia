#pragma once

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
//class RequestHandlerFactory;

class MenuRequestHandler : IRequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory* factory);
	virtual bool isRequestRelevant(RequestInfo);
	virtual RequestResult handleRequest(RequestInfo);
protected:
	RequestHandlerFactory* m_handlerFactory;
};
#include "RoomAdminRequestHandler.h"
#include "JsonResponsePacketSerializer.h"

#include "StartGameResponse.h"
#include "CloseRoomResponse.h"
#include "GetRoomStateResponse.h"
#include "LeaveRoomResponse.h"
#include "LogoutResponse.h"


#include <thread>


//-----------------constructor------------------
RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory* factory, LoggedUser connectedUser, Room connectedRoom) : RoomHandler(factory,connectedRoom,connectedUser)
{
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo req)
{
	int id = req.getId();
	return id == 48 || id == 50 || id == 52 || id == 100;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo req)
{
	if (req.getId() == 48)//getRoomState
		return getRoomState(req);

	bool actionResult = true;
	RequestResult res;
	if (req.getId() == 50) // startRoom
	{
		try
		{
			this->m_handlerFactory->getRoomManager().setRoomState(_connectedRoom.getID(),ACTIVE);
		}
		catch (std::exception e)
		{
			actionResult = false;
		}
		StartGameResponse resp((int)actionResult);
		res._buffer = JsonResponsePacketSerializer::serializeResponse((Response*)&resp);
		int gameId = this->m_handlerFactory->getGameManager().createGame(this->m_handlerFactory->getRoomManager().getRoom(this->_connectedRoom.getID()));
		res.setNewHandler((IRequestHandler*)this->m_handlerFactory->createGameRquestHandler(gameId, this->_connectedUser.getUsername()));
	}
	else if (req.getId() == 52)// close
	{
		try
		{
			this->m_handlerFactory->getRoomManager().setRoomState(_connectedRoom.getID(), CLOSED); // -1 = Inactive // after X time delete the room
			std::thread t(&RoomManager::eraseRoom, &this->m_handlerFactory->getRoomManager(), this->_connectedRoom.getID());
			t.detach();
		}
		catch (std::exception e)
		{
			actionResult = false;
		}
		CloseRoomResponse resp((int)actionResult);
		res._buffer = JsonResponsePacketSerializer::serializeResponse((Response*)&resp);
		if (actionResult)
			res.setNewHandler((IRequestHandler*)this->m_handlerFactory->createMenuRequestHandler(this->_connectedUser.getUsername()));
	}
	else if (req.getId() == 100)// logout
	{
		res = logout(req);
	}
	
	return res;  
}

RequestResult RoomAdminRequestHandler::logout(RequestInfo info)
{
	bool actionResult = true;
	RequestResult res;

	try
	{
		this->m_handlerFactory->getLoginManager().logout(this->_connectedUser.getUsername());
		this->m_handlerFactory->getRoomManager().eraseRoom(this->_connectedRoom.getID());
	}
	catch (std::exception e)
	{
		actionResult = false;
	}

	LogoutResponse response((int)actionResult);

	res._buffer = JsonResponsePacketSerializer::serializeResponse((Response*)&response);

	if (actionResult)
		res.setNewHandler((IRequestHandler*)this->m_handlerFactory->createLoginRequestHandler());

	return res;
}

bool RoomAdminRequestHandler::isAdmin()
{
	return true;
}

#pragma once
#include <event.h>
#include "ByteSteam.h"
#include "Util.h"
class Connect
{
private:
	evutil_socket_t fd;
	int megLength;
	ByteSteam headStean;
	ByteSteam contentSteam;

public:
	Connect();
	~Connect();

	Connect(evutil_socket_t fd);
	evutil_socket_t GetConnectId();

	void OnRead(char*, int);
};


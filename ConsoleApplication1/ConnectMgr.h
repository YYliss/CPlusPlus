

#ifndef __CONNECTMGR_H__
#define __CONNECTMGR_H__

#include <map>
#include <event.h>
#include "Connect.h"

class ConnectMgr
{
private:
	std::map<evutil_socket_t, Connect*> connects;

public:
	static ConnectMgr* GetInstance();

	void AddConnect(evutil_socket_t fd);
	void DelConnect(evutil_socket_t fd);
	Connect* GetConnect(evutil_socket_t fd);

	bool OnRead(evutil_socket_t fd);
	//void OnWrite(evutil_socket_t fd);

};


#endif __CONNECTMGR_H__
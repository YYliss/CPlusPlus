#pragma once
#include <event.h>
#include <map>
#include <iostream>
#include "ConnectMgr.h";

typedef void(*MainUpdate)(void);

using namespace std;

class NetMgr
{
private:
	event_base* base;
	map<evutil_socket_t, event*> readEvents;
	MainUpdate fUpdate;
private:
	static void accept_cb(evutil_socket_t fd, short bitfield, void* arg);
	static void read_cb(evutil_socket_t fd, short bitfield, void* arg);
	static void timer_cb(evutil_socket_t fd, short bitfield, void* arg);

	void OnRead(evutil_socket_t fd, short bitfield, void* arg);
	void OnAccept(evutil_socket_t fd, short bitfield, void* arg);
	void OnTimer(evutil_socket_t fd, short bitfield, void* arg);
private: 
	void InitSocket();

public:
	static NetMgr* GetPtr();


	void Start(int port, MainUpdate f);

	void Close();
};


#include "NetMgr.h"

NetMgr* NetMgr::GetPtr()
{
	static NetMgr _ins;
	return &_ins;
}

void NetMgr::InitSocket()
{
	SOCKADDR_IN sockAddr;
	int sockAddrSize = sizeof(sockAddr);
	memset(&sockAddr, 0, sockAddrSize);
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(9527);

	SOCKET serv_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (bind(serv_sock, (SOCKADDR*)&sockAddr, sockAddrSize) == SOCKET_ERROR)
	{
		printf("bind error");
		return;

	}
	if (listen(serv_sock, SOMAXCONN) == SOCKET_ERROR)
	{
		return;
	}

	event* accept_event = event_new(base, serv_sock, EV_READ | EV_PERSIST, &NetMgr::accept_cb, 0);
	timeval timeout = { 100, 0 };
	event_add(accept_event, &timeout);
}

void NetMgr::Start(int port, MainUpdate f)
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return;
	}

	fUpdate = f;

	base = event_init();

	event* cdEvent = event_new(base, -1, EV_TIMEOUT | EV_PERSIST, &NetMgr::timer_cb, 0);
	timeval cd;
	cd.tv_sec = 0;
	cd.tv_usec = 1;
	event_add(cdEvent, &cd);

	InitSocket();
	event_base_dispatch(base);
}

void NetMgr::Close() {
	event_base_free(base);
	WSACleanup();
}

void NetMgr::accept_cb(evutil_socket_t fd, short bitfield, void* arg)
{
	NetMgr::GetPtr()->OnAccept(fd, bitfield, arg);
}

void NetMgr::OnAccept(evutil_socket_t fd, short bitfield, void* arg)
{
	SOCKADDR_IN clntAddr;
	int clntAddrSize = sizeof(clntAddr);
	SOCKET clntSock = accept(fd, (SOCKADDR*)&clntAddr, &clntAddrSize);

	printf("有新连接 %d \n", clntSock);

	event* read_event = event_new(base, clntSock, EV_READ | EV_PERSIST, read_cb, 0);
	timeval timeout = { 100, 0 };
	event_add(read_event, &timeout);
	readEvents.insert(make_pair(clntSock, read_event));

	ConnectMgr::GetInstance()->AddConnect(clntSock);

}

void NetMgr::read_cb(evutil_socket_t fd, short bitfield, void* arg)
{
	NetMgr::GetPtr()->OnRead(fd, bitfield, arg);
}

void NetMgr::OnRead(evutil_socket_t fd, short bitfield, void* arg)
{
	
	printf("有可读事件%d \n", fd);
	bool result = ConnectMgr::GetInstance()->OnRead(fd);
	if (!result)
	{
		cout << (readEvents.find(fd) != readEvents.end());
		if (readEvents.find(fd) != readEvents.end())
		{
			event* ev = readEvents.at(fd);
			readEvents.erase(fd);
			event_del(ev);
		}
	}
}

void NetMgr::timer_cb(evutil_socket_t fd, short bitfield, void* arg)
{
	NetMgr::GetPtr()->OnTimer(fd, bitfield, arg);
}

void NetMgr::OnTimer(evutil_socket_t fd, short bitfield, void* arg)
{
	fUpdate();
}
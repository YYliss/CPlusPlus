#include "ConnectMgr.h"

ConnectMgr* ConnectMgr::GetInstance() {
	static ConnectMgr _instance;
	return &_instance;
}

void ConnectMgr::AddConnect(evutil_socket_t fd) {
	Connect* conn = new Connect(fd);
	connects[fd] = conn;
}

void ConnectMgr::DelConnect(evutil_socket_t fd) {
	if (connects.find(fd) != connects.end())
	{
		connects.erase(fd);
	}
}

Connect* ConnectMgr::GetConnect(evutil_socket_t fd) {
	if (connects.find(fd) != connects.end())
	{
		return connects[fd];
	}
	return nullptr;
}
bool ConnectMgr::OnRead(evutil_socket_t fd)
{
	char data[1024] = { 0 };
	int read_len = recv(fd, data, 1024, 0);
	cout << "�������ݳ���" << read_len<<endl;
	if (read_len < 0)
	{
		//��ӡ�쳣
		DelConnect(fd);
		return false;
	}
	else if (read_len == 0) 
	{
		DelConnect(fd);
		printf("�����ӶϿ�\n");
		return false;
	}
	else
	{
		Connect* conn = GetConnect(fd);
		if (conn)
		{
			conn->OnRead(data, read_len);
		}
	}
	return true;
}

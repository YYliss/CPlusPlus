#include "Connect.h"
Connect::Connect() {
	this->fd = 0;
	this->megLength = 0;
}

Connect::~Connect() {

}
Connect::Connect(evutil_socket_t fd) {
	this->fd = fd;
	this->megLength = 0;
}

evutil_socket_t Connect::GetConnectId() {
	return fd;
}

void Connect::OnRead(char* buf, int len) {

	int startIndex = 0;
	int useCount = 0;
	if (megLength == 0)
	{
		int needSize = Util::Min(4 - headStean.GetSize(), len);
		startIndex = needSize;
		useCount = needSize;
		headStean.WriteChar(buf, needSize);
		if (headStean.GetSize() < 4)
		{
			return;
		}
		megLength = headStean.ReadInt();
	}
	int readSize = Util::Min(megLength - contentSteam.GetSize(), len);
	useCount += readSize;
	contentSteam.WriteChar(buf + startIndex, readSize);
	if (contentSteam.GetSize() < megLength)
	{
		return;
	}

	send(fd, contentSteam.GetData(), contentSteam.GetSize(), 0);
	send(fd, contentSteam.GetData(), contentSteam.GetSize(), 0);

	contentSteam.Zero();
	headStean.Zero();
	megLength = 0;

	if (useCount < len)
	{
		OnRead(buf + useCount, len - useCount);
	}
}
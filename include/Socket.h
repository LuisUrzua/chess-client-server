#ifndef SOCKET_H
#define SOCKET_H

#define BYTES_PER_MESSAGE 1024

enum class SocketType
{
	Client,
	Server,
};

class Socket
{
public:
	Socket(SocketType);
	void Read();
	void Send();

private:
	void CreateSocket();
	void Connect();
	void PrintError(const int&);

private:
	SocketType socket_type;
	int socket_int;
	int socket_new;
	char read_buffer[BYTES_PER_MESSAGE] = { 0 };
	char send_buffer[BYTES_PER_MESSAGE] = { 0 };
};

#endif
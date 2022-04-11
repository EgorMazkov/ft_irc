#pragma once

#define BUFSIZ 4096

#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>
#include <iostream>
#define X(err, res, str) (x_int(err, res, str, __FILE__, __LINE__))
#define Xv(err, res, str) (x_void(err, res, str, __FILE__, __LINE__))
#define MAX(a, b) ((a > b) ? a : b)

typedef struct s_fds
{
	int type;
	void (*fctRead)();
	void (*fctWrite)();
	char buffRead[BUFSIZ + 1];
	char buffWrite[BUFSIZ + 1];
} t_fds;

class Server
{
private:
	std::string password;
	int port;
	int r;
	t_fds fds;
	fd_set fdRead;
	fd_set fdWrite;
	struct sockaddr_in sin;
	struct protoent *pe;
	struct sockaddr_in csin;
	socklen_t csin_len;
	int maxfd;
	int max;

public:
	void initial(int portMain, std::string passwordMain);
	void create(t_fds *fds);
	void mainLoop(t_fds *fds);
	int x_int(int err, int res, char *str, char *file, int line);
	void *x_void(void *err, void *res, char *str, char *file, int line);
	void srvAccept(t_fds *fds, int s);
	void cleanFD(t_fds *fds);
	void client_read(t_fds *fds, int cs);
	void client_write(t_fds *fds, int cs);
	void init_fd(t_fds *fds);
	void do_select();
	void check_fd(t_fds *fds);
};

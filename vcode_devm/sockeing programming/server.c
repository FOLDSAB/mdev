#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <WinSock2.h>


int main() {


	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in socketaddr;

	if (sock != INVALID_SOCKET) {
		printf("socket failed with error no %d\n", GetLastError());
		return -1;
	}

	socketaddr.sin_family = AF_INET;
	socketaddr.sin_port = 3313;
	


}
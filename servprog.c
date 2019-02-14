#include <sys/socket.h>		/* socket definitions	*/
#include <sys/types.h>		/* socket types			*/
#include <arpa/inet.h>		/* inet (3) functions	*/
#include <unistd.h>			/* misc. UNIX functions	*/

#include "helper.h"			/* helper functions		*/
#include <stdlib.h>
#include <stdio.h>

/* Global constants */
#define ECHO_PORT		(2005)
#define MAX_LINE		(1000)	
#define LISTENQ			(3)	

int main(int argc, char * argv[]) {
	int list_s, conn_s;
	struct sockaddr_in sockaddr;
	char buffer[MAX_LINE];

	// Sets the address of the server
	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	sockaddr.sin_port = htons(ECHO_PORT);
	// Creates socket to receive requests
	if ((list_s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Socket not created \n");
	}
	// binds socket to an address
	if (bind(list_s, (struct sockaddr *) &sockaddr, sizeof(sockaddr)) < 0) {
		printf("Socket not bound.\n");
	}
	// Listens for connection requests
	if (listen(list_s, LISTENQ) < 0) {
		printf("Socket not listening\n");
	}

	while (1) {
		// Handles connections
		if ((conn_s = accept (list_s, NULL, NULL)) < 0) {
			printf("connection not accepted");
		}
		
		Readline(conn_s, buffer, MAX_LINE - 1);
		Writeline(conn_s, buffer, strlen(buffer));

		if (close (conn_s) < 0) {
			printf("connection not closed.");
		}
	}
	return 0;
}
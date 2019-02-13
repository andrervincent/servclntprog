#include <sys/socket.h>		/* socket definitions	*/
#include <sys/types.h>		/* socket types			*/
#include <arpa/inet.h>		/* inet (3) functions	*/
#include <unistd.h>			/* misc. UNIX functions	*/

#include "helper.h"			/* helper functions		*/
#include <stdlib.h>
#include <stdio.h>

/* Global constants */
#define ECHO_PORT		(2002)
#define MAX_LINE		(1000)		

int main(int argc, char * argv[]) {
	int list_s, conn_s;
	struct sockaddr_in sockaddr;
	char buffer[MAX_LINE];

	// Sets the address of the server
	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	sockaddr.sin_port = htons(ECHO_PORT);

	

}
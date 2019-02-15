#include "helper.h"
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

ssize_t Readline(int sockd, void *vptr, size_t maxlen) {
	ssize_t n, rc;
	char c, *buffer;
	// the buffer is used to hold the strings sent
	// to the server.
	buffer = vptr;

	// target string = 'CAP'
	char CapString[] = "CAP";
	char FileString[] = "FILE";

	int CapTarget = 0;
	int FileTarget = 0;


	for ( n = 1; n < maxlen; n++ ) {
		// Reads from socket
		if ( (rc = read(sockd, &c, 1)) == 1 ) {

			// assigns found character into buffer
			*buffer++ = c;
			// When reading characters, if the character isn't a 
			// newline, increase the number of "found" characters of 
			// CAP or FILE.

			// When either target number is found, 
			// call its helper function to perform the specified task 
			if (c != '\n') {
				if (c == CapString[n-1]) CapTarget++;
				else if (c == FileString[n-1]) FileTarget++;
			}
			else {
				if (CapTarget == 3) {
				/* call cap function */ 
				CapTarget = 0;
				}
			else if (FileTarget == 3) {
				/* call file function */
				FileTarget = 0;
				}
			else break;
		}

		}
		else if ( rc == 0 ) {
			if (n == 1)
				return 0;

			else break;
		}

		else {
			if (errno == EINTR)
				continue;
		return -1;
		}	
	}
	*buffer = 0;
	return n;
}
/*void ChangeToCapital(int sockd, void *buffer2, ) {
	ssize_t rc_2;
	while (1){
		if (rc_2 = read(sockd, buffer2,))
	}
}*/
ssize_t Writeline(int sockd, const void *vptr, size_t n) {

	size_t nleft;
	ssize_t nwritten;
	const char *buffer;

	buffer = vptr;
	nleft = n;


	while (nleft > 0) {
		if ((nwritten = write(sockd, buffer, nleft)) <= 0 ) {
			if (errno == EINTR)
				nwritten = 0;
			else
				return -1;
			}
		nleft -= nwritten;
		buffer += nwritten;
		}
		
		return n;
}
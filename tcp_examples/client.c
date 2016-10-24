/*-
 * Copyright (c) 2013 Michael Tuexen
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "Socket.h"

#define BUFFER_SIZE  (1<<16) //=2^16=65536
#define MESSAGE_SIZE (9216)

int
main(int argc, char **argv)
{
	int fd=0,done=0,n=0;
	ssize_t len=0;
	socklen_t addr_len=0;
	struct sockaddr_in server_addr;
	char buf[BUFFER_SIZE];
	struct in_addr dest_addr;
	fd_set rset;
	
	fd=Socket(AF_INET,SOCK_STREAM,0);
	
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
#ifdef HAVE_SIN_LEN
	server_addr.sin_len = sizeof(struct sockaddr_in);
#endif
	Inet_pton(AF_INET,argv[1],&dest_addr);
        server_addr.sin_addr=dest_addr;
	server_addr.sin_port=htons(Atoi(argv[2]));
	
	
	Connect(fd,(const struct sockaddr *) &server_addr,sizeof(server_addr));
	
	FD_ZERO(&rset);
	while(done<2){
		if(done==0)
			FD_SET(0,&rset);
		FD_SET(fd,&rset);
		Select(fd+1,&rset,NULL,NULL,NULL);

		//user
		if(FD_ISSET(0,&rset)) {
			n=Read(0,(void*)buf,sizeof(buf));
			if(n==0){
				Shutdown(fd,SHUT_WR);
				FD_CLR(0,&rset);
				done=1;
			}else{
				Send(fd,(const void*) buf,(size_t)n,0);
			}
		}

		//server
		if (FD_ISSET(fd, &rset)) {
			n = Recv(fd, (void *) buf, sizeof(buf), 0);
			if (n == 0){
				done=2;
			}else{
				printf("%.*s", (int)n, buf);
			}
		}
	}

	Close(fd);

	return(0);
}

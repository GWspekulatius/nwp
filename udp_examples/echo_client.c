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
#include <stdlib.h>
#include "Socket.h"

#define BUFFER_SIZE  (1<<16) //=2^16=65536
#define MESSAGE_SIZE (9216)

int
main(int argc, char **argv)
{
	int fd;
	struct sockaddr_in server_addr, client_addr;
	socklen_t addr_len;
	ssize_t len;
	char buf[BUFFER_SIZE];
	struct in_addr dest_addr;
	
	fd=Socket(AF_INET,SOCK_DGRAM,0);
	
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
#ifdef HAVE_SIN_LEN
	server_addr.sin_len = sizeof(struct sockaddr_in);
#endif
	
	Inet_pton(AF_INET,argv[1],&dest_addr);
        server_addr.sin_addr=dest_addr;
	server_addr.sin_port = htons(12345);
	
	Connect(fd,(const struct sockaddr *) &server_addr,sizeof(server_addr));
	memset((void *) buf, 'A', sizeof(buf));
	//sendto(fd, (const void *) buf, (size_t) MESSAGE_SIZE, 0, (const struct sockaddr *) &server_addr, sizeof(server_addr));
	Send(fd,buf,MESSAGE_SIZE,0);
	
	addr_len = (socklen_t) sizeof(client_addr);
	memset((void *) buf, 0, sizeof(buf));
	len=Recvfrom(fd, (void *) buf, sizeof(buf), 0, (struct sockaddr *) &client_addr, &addr_len);
	printf("Received %zd bytes from %s.\n", len, inet_ntoa(client_addr.sin_addr));
	
	Close(fd);

	return(0);
}

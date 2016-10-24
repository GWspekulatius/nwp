#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int Socket(int fd, int type, int protocol){
	int n;
	if((n=socket(fd,type,protocol))<0){
		perror("socket");
		exit(-1);
	}
	return(n);
}

//TODO rückgabewert überprüfen, kann weniger sein als data_len
ssize_t Send(int socketfd, const void* data, size_t data_len,unsigned int flags){
	ssize_t n;
	if((n=send(socketfd,data,data_len,flags))<0){
		perror("send");
		exit(-1);
	}
	return n;
}
ssize_t Sendto(int socketfd, const void *data, size_t data_len, int flags, const struct sockaddr*to, socklen_t tolen){
	ssize_t n;
	if((n=sendto(socketfd, data, data_len, 0, to , tolen))<0){
		perror("sendto");
		exit(-1);
	}
	return n;
}
ssize_t Recv(int sockfd, void *buf, size_t len, int flags){
	ssize_t n;
	if((n=recv(sockfd,buf,len,flags))<0){
		perror("recv");
		exit(-1);
	}
	return n;
}

ssize_t Recvfrom(int socketfd, void*data, size_t data_len, int flags, struct sockaddr* from, socklen_t* fromlen){
	ssize_t len;
	if((len=recvfrom(socketfd, (void *) data, data_len, 0, from, fromlen)) < 0){
		perror("recvfrom");
		exit(-1);
	}
	return len;
}

int Connect(int socketfd,const struct sockaddr * addr, int addrlen){
	int n;
	if((n=connect(socketfd,addr,addrlen))<0){
		perror("connect");
		exit(-1);
	}
	 return n;
}

int Bind(int socketfd,const struct sockaddr* name, int namelen){
	int n;
	if((n=bind(socketfd, name, namelen))!=0){
		perror("bind");
		exit(-1);
	}
	return n;
}

int Listen(int socketfd, int queue_len ){
	int n;
	if((n=listen(socketfd,queue_len))<0){
		perror("listen");
		exit(-1);
	}
	return n;
}

int Accept(int socketfd, struct sockaddr * address,socklen_t * address_len){
	int n;
	if((n=accept(socketfd,address,address_len))<0){
		perror("accept");
		exit(-1);
	}  
	return n;
}

int Shutdown(int socketfd, int how){
	int n;
	if((n=shutdown(socketfd,how))<0){
		perror("shutdown");
		exit(-1);
	}
	return n;
}

int Close(int socketfd){
	int n;
	if((n=close(socketfd))<0){
		perror("socket_close");
		exit(-1);
	}
	return n;
}

int Inet_pton(int af, const char *src, void *dst){
	int n;
	if ((n=inet_pton(af,src,dst)) <= 0) {
		perror("inet_pton");
		exit(-1);
        }
        return n;
}

int Atoi(const char *str){
	int n;
	if((n=atoi(str))==0){
		perror("atoi");
		exit(-1);
	}
	return n;
}

int  Read(  int  handle,  void  *buffer,  int  nbyte ){
	int n;
	if((n=read(handle,buffer,nbyte))<0){
		perror("read");
		exit(-1);
	}
	return n;
}

int Select (int nfds, fd_set *read_fds, fd_set *write_fds, fd_set *except_fds, struct timeval *timeout){
	int n;
	if((n=select(nfds,read_fds,write_fds,except_fds,timeout))<0){
		perror("select");
		exit(-1);
	}
	return n;
}
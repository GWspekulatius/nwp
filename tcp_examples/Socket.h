#ifndef SOCKET_H
#define SOCKET_H
int Socket(int fd, int type, int protocol);
ssize_t Send(int socketfd, const void* data, size_t data_len,unsigned int flags);
ssize_t Sendto(int socketfd, const void *data, size_t data_len, int flags, const struct sockaddr*to, socklen_t tolen);
ssize_t Recv(int socketfd, void *buf, size_t len, int flags);
ssize_t Recvfrom(int socketfd, void*data, size_t data_len, int flags, struct sockaddr* from, socklen_t* fromlen);
int Connect(int socketfd,const struct sockaddr * addr, int addrlen);
int Bind(int socketfd,const struct sockaddr* name, int namelen);
int Listen(int socketfd, int queue_len );
int Accept(int socketfd, struct sockaddr * address,socklen_t * address_len);
int Shutdown(int socketfd, int how);
int Close(int socketfd);
int Inet_pton(int af, const char *src, void *dst);
int Atoi(const char *str);
int Read(  int  handle,  void  *buffer,  int  nbyte );
int Select (int nfds, fd_set *read_fds, fd_set *write_fds, fd_set *except_fds, struct timeval *timeout);
#endif
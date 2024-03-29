#include "chat.h"
#include "client.h"
#include "interface.h"

#define PORT 4000

int sockfd, thisID;

int main(int argc, char *argv[])
{
    struct sockaddr_in serv_addr;
    struct hostent *server;

    thisID = -1;

    if (argc < 2) {
		fprintf(stderr,"usage %s hostname\n", argv[0]);
		exit(0);
    }

	server = gethostbyname(argv[1]);
	if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("ERROR opening socket\n");
    }


	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr = *((struct in_addr *)server->h_addr);
	bzero(&(serv_addr.sin_zero), 8);


    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("ERROR connecting\n");
    }

    chatInterface(argc, argv, sockfd);

	close(sockfd);
    return 0;
}

int writeSocket(MSG *buffer)
{
    int n;
    buffer->userID = thisID;
    n = write(sockfd, buffer, sizeof(MSG));
    if (n < 0) {
        printf("ERROR writing to socket\n");
        return -1;
    }
    bzero(buffer, sizeof(MSG));
    return 0;
}

int readSocket(MSG *buffer)
{
    int n;
    int len = 0;
    ioctl(sockfd, FIONREAD, &len);
    printf("N: %i\n", len);
    if (len > 0) {
      n = read(sockfd, buffer, sizeof(MSG));
      if (n < 0)
        printf("ERROR reading from socket\n");
      if(thisID == -1)
        thisID = buffer->userID;
      return 1;
    }
    return 0;
}

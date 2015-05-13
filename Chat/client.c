#include "chat.h"
#include "interface.h"

#define PORT 4000

int main(int argc, char *argv[])
{
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    MSG *buffer;
  
    chatInterface(argc, argv);
    
    if (argc < 2) {
		fprintf(stderr,"usage %s hostname\n", argv[0]);
		exit(0);
    }
	
	server = gethostbyname(argv[1]);
	if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
        printf("ERROR opening socket\n");
    
    buffer = malloc(sizeof(MSG));
    
	serv_addr.sin_family = AF_INET;     
	serv_addr.sin_port = htons(PORT);    
	serv_addr.sin_addr = *((struct in_addr *)server->h_addr);
	bzero(&(serv_addr.sin_zero), 8);     
	
    
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        printf("ERROR connecting\n");

    printf("Enter the message: ");
    
    bzero(buffer, sizeof(MSG));
    fgets(buffer->message, sizeof(buffer->message), stdin);
    
	/* write in the socket */
	n = write(sockfd, buffer, sizeof(MSG));
    if (n < 0) 
		printf("ERROR writing to socket\n");

    bzero(buffer, sizeof(MSG));
	
	/* read from the socket */
    n = read(sockfd, buffer, sizeof(MSG));
    if (n < 0) 
		printf("ERROR reading from socket\n");

    printf("%s\n", buffer->message);
    
	close(sockfd);
    return 0;
}
#include "../lib/server.h"
#include "../../../../lib/encryption.h"
#include "../../../../lib/input_operations.h"
#include "../../res/connection.h"
#include "../../res/messages.h"
#include "../../../../res/keys_domain.h"
#include "../../../../res/numbers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 


char start() 
{ 
	int server;
    int client;
    int opt;

	struct sockaddr_in address; 

	int addr_len = sizeof(address); 

	static char buffer[CIPHERTEXT_MAX] = {ZERO};

    char user_action[TWO] = {ZERO};

    static char d_server[D_MAX];
    static char e_server[E_MAX];
    CommonKey *ck_server;


    printf("\n\n");


	// Creating socket file descriptor 
    server = socket(AF_INET, SOCK_STREAM, ZERO);

	if (server < ZERO) 
	{ 
		printf("socket creation failed\n\n"); 

		return EXIT_FAILURE; 
	} 


    opt = ONE;

    // Forcefully attaching socket to the port PORT
    if (setsockopt (server, SOL_SOCKET, SO_REUSEADDR, 
                &opt, sizeof(opt) )) 
    { 
        printf("setsockopt failed\n\n"); 

        return EXIT_FAILURE;
    } 


    bzero (&address, sizeof(address));

    address.sin_family = AF_INET; 

	address.sin_addr.s_addr = INADDR_ANY; 

	address.sin_port = htons( PORT ); 


	if (bind(server, (struct sockaddr *) &address, 
                sizeof(address)) < ZERO) 
	{ 
		printf("bind failed\n\n"); 

		return EXIT_FAILURE; 
	} 


	if (listen (server, ONE) < ZERO) 
	{ 
		printf("listen failed\n\n"); 
		
        return EXIT_FAILURE; 
	} 


    ck_server = malloc (sizeof(CommonKey));
        
    if (!ck_server)
    {
        printf("error when allocating memory to ck_server\n");
        
        free(ck_server);

        return EXIT_FAILURE;
    }

    // Use current time as seed for random generator 
    srand(time(ZERO));

    generateKeys (d_server, e_server, ck_server);


    printf("listening on port :  %d\n\n", PORT);

    while (strcmp(user_action, "s"))
    {
        printf("waiting for client to connect\n\n");
        
        client = accept (server, (struct sockaddr *) &address, 
                (socklen_t *) &addr_len);


        if (client < ZERO) 
        { 
            printf("accept failed\n\n"); 

            closeServer(server);
            
            free(ck_server);
        
            return EXIT_FAILURE; 
        } 


        printf("client has connected\n\n");


        if (handleConnected (client, buffer, CIPHERTEXT_MAX,
                                d_server, e_server, ck_server))
        {
            closeServer(server);
    
            free(ck_server);

            return EXIT_FAILURE;
        }

        printf ("enter 's' to stop accepting sockets or press enter to continue : ");

        if (!fgets(user_action, TWO, stdin))
        {
            printf("Error when getting input from user\n\n");

            return EXIT_FAILURE;
        }
        
        clear (user_action);
    }
    
    printf("\n\n");

    free(ck_server);

    return closeServer(server);
} 


char closeServer (int server)
{
   switch (close (server))
    {   
        case ZERO:
            
            printf ("closed server socket successfully\n\n");

            return EXIT_SUCCESS;

        case MINUS_ONE:

            printf ("error when closing server socket\n\n");

            return EXIT_FAILURE;

        default:

            printf ("error when closing server socket,"
                    "return value is not 0 or -1\n\n");

            return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}


char closeClient (int client)
{
    switch (close (client))
    {
        case ZERO:
            
            printf ("closed client socket due to disconnect message\n\n");

            return EXIT_SUCCESS;

        case MINUS_ONE:

            printf ("error when closing client socket\n\n");

            return EXIT_FAILURE;

        default:

            printf ("error when closing client socket,"
                    "return value is not 0 or -1\n\n");

            return EXIT_FAILURE;
    }            


    return EXIT_SUCCESS;
}


char handleConnected (int client, char *buffer, int size,
                        char *d_server, char *e_server, CommonKey *ck_server)
{
    char is_connected;

    static char e_client[E_MAX];
    CommonKey *ck_client;
    

    printf ("handling connection\n\n");
    
    if (handleWrite(client, CONNECTED, strlen(CONNECTED) + ONE))
    {
        return EXIT_FAILURE;
    }


    ck_client = malloc (sizeof(CommonKey));
        
    if (!ck_client)
    {
        printf("error when allocating memory to ck_client\n");
        
        free(ck_client);

        return EXIT_FAILURE;
    }

    printf ("exchanging keys\n\n");
    
    if (exchangeKeys (client, e_server, ck_server, e_client, ck_client))
    {
        printf ("error when exchanging keys\n\n");

        return EXIT_FAILURE;
    }


    is_connected = ONE;

    while (is_connected)
    {
        if (handleReadCiphertext(client, buffer, size, d_server, ck_server))
        {
            return EXIT_FAILURE;
        }

        is_connected = strcmp(buffer, DISCONNECT);

        if (handleWriteCiphertext(client, buffer, size, e_client, ck_client))
        {
            return EXIT_FAILURE;
        }
    }


    return closeClient(client);
}


char handleRead (int sock, char *buffer, int size)
{
    int total_bytes_read;

    bzero (buffer, size);
            
    total_bytes_read = read (sock, buffer, size);

    switch (total_bytes_read)
    {
        case MINUS_ONE:

            printf ("error in read\n\n");

            return EXIT_FAILURE;

        case ZERO:

            printf ("client has disconnected due to unknown reason\n\n");

            return EXIT_FAILURE;
    }

    printf("received : %s\n\n", buffer);

    return EXIT_SUCCESS;
}


char handleReadCiphertext (int sock, char *buffer, int size,
                            char *d, CommonKey *ck)
{
    static char ciphertext[CIPHERTEXT_MAX];


    if (handleRead(sock, ciphertext, size))
    {
        return EXIT_FAILURE;
    }


    bzero (buffer, size);

    decrypt (ciphertext, buffer, d, ck);

    printf("decrypt result : %s\n\n", buffer);

    
    return EXIT_SUCCESS;
}


char handleWrite (int sock, char *buffer, int size)
{
    if (write(sock, buffer , size) == MINUS_ONE)
    {
        printf("error when sending message\n\n");

        return EXIT_FAILURE;
    }

    printf("sent : %s\n\n", buffer);


    return EXIT_SUCCESS;
}


char handleWriteCiphertext (int sock, char *buffer, int size,
                            char *e, CommonKey *ck)
{
    static char ciphertext[CIPHERTEXT_MAX] = {ZERO};


    printf ("encrypting : %s\n\n", buffer);

    encrypt (buffer, ciphertext, e, ck);


    if (handleWrite(sock, ciphertext, size))
    {
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}


char exchangeKeys (int client, 
                        char *e_server, CommonKey *ck_server,
                        char *e_client, CommonKey *ck_client)
{
    char *public_key_server;
    static char public_key_client[PUBLIC_KEY_MAX];
    
    
    public_key_server = membersToPublicKey (e_server, ck_server);


    if (!public_key_server)
    {
        printf ("error when creating public key server\n\n");

        free (public_key_server);

        return EXIT_FAILURE;
    }


    if (handleWrite(client, public_key_server, PUBLIC_KEY_MAX))
    {
        free (public_key_server);

        return EXIT_FAILURE;
    }


    if (handleRead(client, public_key_client, PUBLIC_KEY_MAX))
    {
        free (public_key_server);

        return EXIT_FAILURE;
    }


    if (publicKeyToMembers (public_key_client, e_client, ck_client))
    {
        free (public_key_server);

        return EXIT_FAILURE;
    }


    if (handleWrite(client, SUCCESS, strlen(SUCCESS) + ONE))
    {
        free (public_key_server);

        return EXIT_FAILURE;
    }


    free (public_key_server);


    return EXIT_SUCCESS;
}
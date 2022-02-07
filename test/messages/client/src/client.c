#include "../lib/client.h"
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
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h>


char start ()
{
    int client;

	struct sockaddr_in server_address; 

	static char buffer[CIPHERTEXT_MAX] = {ZERO};

    char handle_connected;


    static char d_client[D_MAX];
    static char e_client[E_MAX];
    CommonKey *ck_client;

    char status;

    printf("\n\n");


    client = socket(AF_INET, SOCK_STREAM, ZERO);

    
	if (client < ZERO) 
	{ 
		printf("socket creation failed\n\n"); 

		return EXIT_FAILURE; 
	} 


    bzero( &server_address, sizeof(server_address));

    server_address.sin_family = AF_INET; 
    server_address.sin_port = htons(PORT);


    if(inet_pton(AF_INET, IP, &server_address.sin_addr) <= ZERO)  
    { 
        printf("invalid address or address not supported \n\n");

        return EXIT_FAILURE; 
    }


     if (connect(client, (struct sockaddr *) &server_address,
                    sizeof(server_address)) < ZERO) 
    { 
        printf("Connection Failed \n\n");

        return EXIT_FAILURE; 
    }


    ck_client = malloc (sizeof(CommonKey));
        
    if (!ck_client)
    {
        printf("error when allocating memory to ck_client\n");
        
        free(ck_client);

        return EXIT_FAILURE;
    }

    // Use current time as seed for random generator 
    srand(time(ZERO));
    
    generateKeys (d_client, e_client, ck_client);


    handle_connected = handleConnected (client, buffer, CIPHERTEXT_MAX,
                                        d_client, e_client, ck_client);


    status = closeSocket(client) || handle_connected;

    free(ck_client);

    return status;
}


char closeSocket (int sock)
{
    switch (close(sock))
    {   
        case ZERO:
            
            printf ("closed client socket successfully\n\n");

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
                        char *d_client, char *e_client, CommonKey *ck_client)
{
    char is_connected;

    static char e_server[E_MAX];
    CommonKey *ck_server;


    printf ("waiting for connected message\n\n");


    if (handleRead(client, buffer, strlen(CONNECTED) + ONE))
    {
        return EXIT_FAILURE;
    }

    if (strcmp(buffer, CONNECTED))
    {
        printf ("error : did not received connected message\n\n");

        return EXIT_FAILURE;

    }

    ck_server = malloc (sizeof(CommonKey));
        
    if (!ck_server)
    {
        printf("error when allocating memory to ck_server\n");
        
        free(ck_server);

        return EXIT_FAILURE;
    }

    printf ("exchanging keys\n\n");

    if (exchangeKeys (client, buffer, e_client, ck_client, e_server, ck_server))
    {
        printf ("error when exchanging keys\n\n");

        free(ck_server);

        return EXIT_FAILURE;
    }


    is_connected = ONE;

    while (is_connected)
    {
        printf ("enter your message or enter 'exit' to exit the program : ");

        if (!fgets(buffer, size, stdin))
        {
            printf("Error when getting input from user\n\n");

            free(ck_server);
            
            return EXIT_FAILURE;
        }
        
        clear (buffer);


        is_connected = strcmp(buffer, DISCONNECT);


        if (handleWriteCiphertext(client, buffer, size, e_server, ck_server))
        {
            free(ck_server);
            
            return EXIT_FAILURE;
        }


        if (handleReadCiphertext(client, buffer, size, d_client, ck_client))
        {
            free(ck_server);

            return EXIT_FAILURE;
        }
    }


    printf ("server closed connection due to disconnect message\n\n");

    free(ck_server);

    return EXIT_SUCCESS;
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

            printf ("server closed connection due to unknown reason\n\n");

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


char exchangeKeys (int client, char *buffer,
                        char *e_client, CommonKey *ck_client,
                        char *e_server, CommonKey *ck_server)
{
    char *public_key_client;
    static char public_key_server[PUBLIC_KEY_MAX];
    
    
    public_key_client = membersToPublicKey (e_client, ck_client);

    
    if (!public_key_client)
    {
        printf ("error when creating public key server\n\n");

        free (public_key_client);

        return EXIT_FAILURE;
    }


    if (handleRead(client, public_key_server, PUBLIC_KEY_MAX))
    {
        free (public_key_client);

        return EXIT_FAILURE;
    }

    if (handleWrite(client, public_key_client, PUBLIC_KEY_MAX))
    {
        free (public_key_client);

        return EXIT_FAILURE;
    }


    if (publicKeyToMembers (public_key_server, e_server, ck_server))
    {
        free (public_key_client);

        return EXIT_FAILURE;
    }


    if (handleRead(client, buffer, strlen(SUCCESS) + ONE))
    {
        free (public_key_client);

        return EXIT_FAILURE;
    }

    if (strcmp(buffer, SUCCESS))
    {
        printf ("error - server did not return SUCCESS response\n\n");

        free (public_key_client);

        return EXIT_FAILURE;
    }


    free (public_key_client);


    return EXIT_SUCCESS;
}
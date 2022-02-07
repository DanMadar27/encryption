#ifndef CLIENT_H
#define CLIENT_H

#include "../../../../lib/common_key.h"


// start connection with a server. returns 0 if success and 1 if failed
char start ();


// close socket. returns 0 if success and 1 if failed
char closeSocket (int sock);


// handle connection of client. returns 0 if success and 1 if failed
char handleConnected (int client, char *buffer, int size,
                        char *d_client, char *e_client, CommonKey *ck_client);


// handle read operation. returns 0 if success and 1 if failed
char handleRead (int sock, char *buffer, int size);


// handle read operation that reads ciphertext. 
// returns 0 if success and 1 if failed
char handleReadCiphertext (int sock, char *buffer, int size,
                            char *d, CommonKey *ck);


// handle write operation. returns 0 if success and 1 if failed
char handleWrite (int sock, char *buffer, int size);


// handle write operation that writes ciphertext. 
// returns 0 if success and 1 if failed
char handleWriteCiphertext (int sock, char *buffer, int size,
                            char *e, CommonKey *ck_client);


// exchange keys with the server. returns 0 if success and 1 if failed
char exchangeKeys (int client, char *buffer,
                        char *e_client, CommonKey *ck_client,
                        char *e_server, CommonKey *ck_server);


#endif
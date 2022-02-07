#ifndef SERVER_H
#define SERVER_H

#include "../../../../lib/common_key.h"


// starts a server. returns 0 if success and 1 if failed
char start ();


// close server. returns 0 if success and 1 if failed
char closeServer (int server);


// close client. returns 0 if success and 1 if failed
char closeClient (int client);


// handle connection of a client. returns 0 if success and 1 if failed
char handleConnected (int client, char *buffer, int size,
                        char *d_server, char *e_server, CommonKey *ck_server);


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
                            char *e, CommonKey *ck);                            


// exchange keys with the client. returns 0 if success and 1 if failed
char exchangeKeys (int client,
                        char *e_server, CommonKey *ck_server,
                        char *e_client, CommonKey *ck_client);


#endif
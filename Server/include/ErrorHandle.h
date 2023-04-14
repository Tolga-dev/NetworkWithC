//
// Created by xamblot on 4/13/23.
//

#ifndef XSERVER_ERRORHANDLE_H
#define XSERVER_ERRORHANDLE_H

#include <bits/stdc++.h>
#include <stdio.h>

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); \
        } while (0)

#define BACKLOG 8 // how many pending connections queue will hold
#define MAX_LEN 200 // server
#define MAX_BUFFER 200 // client

#define PORT 3031
#define SERVER_MESSAGE "0"
#define CLIENT_MESSAGE "1"
#define CLIENT_QUIT_MESSAGE "QUIT"


#endif //XSERVER_ERRORHANDLE_H

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


#endif //XSERVER_ERRORHANDLE_H

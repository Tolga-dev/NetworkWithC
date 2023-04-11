#include <iostream>
#include <poll.h>
#define MONITOR_NUMBER 1
int main()
{

    struct pollfd fds[MONITOR_NUMBER];

    fds[0].fd = 0;          // Standard input
    fds[0].events = POLLIN; // Tell me when ready to read
    printf("Hit RETURN or wait 2.5 seconds for timeout\n");

    int num_event = poll(fds, 1, 2500);

    if(num_event == 0)
        printf("Timeout! \n");
    else
    {
        for (auto & pfd : fds) {
            int happened = pfd.revents & POLLIN;

            if(happened)
                printf("file descriptor %d is ready to read! \n", pfd.fd);
            else
                printf("Unexpected event occurred %d \n", pfd.events);
        }

    }

    return 0;
}
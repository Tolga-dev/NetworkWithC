#include <iostream>
#include <fcntl.h>

#define BUFFER_MAX 1000
using namespace std;


int main()
{
    size_t check = 0;
    char buffer[BUFFER_MAX];

    auto fileOpen = [](const char* path, mode_t mode = O_RDONLY)
    {
        return open(path,O_CREAT|O_RDONLY|O_RDWR,mode);
    };


    if((check == fileOpen("file.txt"))==1)
    {
        cout << "File Open failed!" << endl;
        exit(0);
    }

    cout << check << " " << " SUCCESSFULLY" << endl;



}
#include "mprpcapplication.h"
#include <iostream>
#include <unistd.h>

using namespace std;

MprpcApplication& MprpcApplication::getMpracApplication()
{
    static MprpcApplication app;
    return app;
}

void ShowArgsHelp()
{
    cout<<"format: command -i <configfile>"<<endl;
}
void MprpcApplication::init(int argc,char **argv)
{
    if(argc < 2)
    {
        ShowArgsHelp();
        exit(EXIT_FAILURE);
    }

    int c = 0;
    string config_file;
    while((c = getopt(argc,argv,"i:")) != -1)
    {
        switch (c)
        {
        case 'i':
            config_file = optarg;
            break;
        case '?':
            cout<<"invalid args"<<endl;
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        case ':':
            cout<<"need <configfile>!"<<endl;
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        default:
            break;
        }
    }
}
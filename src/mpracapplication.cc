#include "mprpcapplication.h"

MprpcApplication& MprpcApplication::getMpracApplication()
{
    static MprpcApplication app;
    return app;
}
void MprpcApplicationinit(int argc,char **argv)
{

}
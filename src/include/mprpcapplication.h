#include "mprpcconfig.h"

class MprpcApplication
{
public:
    static MprpcApplication& getMpracApplication();
    static void init(int argc,char **argv);
    static MprpcConfig& GetConfig();
private:
    static MprpcConfig m_config;
    MprpcApplication(){}
    MprpcApplication(const MprpcApplication&) = delete;
    MprpcApplication(MprpcApplication&&) = delete;

    
};
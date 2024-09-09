class MprpcApplication
{
public:
    static MprpcApplication& getMpracApplication();
    static void init(int argc,char **argv);
private:
    MprpcApplication(){}
    MprpcApplication(const MprpcApplication&) = delete;
    MprpcApplication(MprpcApplication&&) = delete;
};
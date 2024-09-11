#include <iostream>
#include <string>
#include "user.pb.h"
#include "mprpcapplication.h"
#include "rpcprovider.h"
using namespace std;

class UserService : public fixbug::UserServiceRpc
{
public:
    bool Login(string name, string pwd)
    {
        cout << "doing local service:Login" << endl;
        cout << name << " " << pwd << endl;
        return true;
    }

    void Login(::google::protobuf::RpcController *controller,
               const ::fixbug::LoginRequest *request,
               ::fixbug::LoginResponse *response,
               ::google::protobuf::Closure *done)
    {
        string name = request->name();
        string pwd = request->pwd();

        bool Login_result = Login(name,pwd);

        //写response返回值
        fixbug::ResultCode* code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_sucess(Login_result);

        done->Run();
    }
};

int main(int argc,char **argv)
{
    MprpcApplication::init(argc,argv);

    RpcProvider provider;
    provider.NotifyService(new UserService());

    provider.run();

    return 0;
}
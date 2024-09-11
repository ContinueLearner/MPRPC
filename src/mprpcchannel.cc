#include "mprpcchannel.h"
#include <string>
#include "rpcheader.pb.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include "mprpcapplication.h"


/*
header_size + service_name method_name args_size + args
*/
void MprpcChannel::CallMethod(const google::protobuf::MethodDescriptor *method,
                              google::protobuf::RpcController *controller,
                              const google::protobuf::Message *request,
                              google::protobuf::Message *response,
                              google::protobuf::Closure *done)
{
    const google::protobuf::ServiceDescriptor* sd = method->service();
    std::string service_name = sd->name();
    std::string method_name = method->name();

    uint32_t args_size = 0;
    std::string args_str;
    if(request->SerializeToString(&args_str))
    {
        args_size = args_str.size();
    }
    else
    {
        cout<<"args size error"<<endl;
        return;
    }

    mprpc::RpcHeader rpcheader;
    rpcheader.set_method_name(method_name);
    rpcheader.set_service_name(service_name);
    rpcheader.set_args_size(args_size);

    uint32_t header_size = 0;
    std::string header_str;
    if(rpcheader.SerializePartialToString(&header_str))
    {
        header_size = header_str.size();
    }
    else
    {
        cout<<"header str error"<<endl;
        return;
    }

    std::string send_rpc_str;
    send_rpc_str.insert(0,std::string((char*)&header_size,4));
    send_rpc_str += header_str;
    send_rpc_str += args_str;


    // 打印调试信息
    std::cout << "============================================" << std::endl;
    std::cout << "header_size: " << header_size << std::endl; 
    std::cout << "rpc_header_str: " << header_str << std::endl; 
    std::cout << "service_name: " << service_name << std::endl; 
    std::cout << "method_name: " << method_name << std::endl; 
    std::cout << "args_str: " << args_str << std::endl; 
    std::cout << "============================================" << std::endl;

    // 使用tcp编程，完成rpc方法的远程调用
    int clientfd = socket(AF_INET,SOCK_STREAM,0);
    if(clientfd == -1)
    {
        cout<<"socket error"<<endl;
        close(clientfd);
        exit(EXIT_FAILURE);
    }

    std::string ip = MprpcApplication::getMpracApplication().GetConfig().Load("rpcserverip");
    uint16_t port = atoi(MprpcApplication::getMpracApplication().GetConfig().Load("rpcserverport").c_str());

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());

    
    // 连接rpc服务节点
    if (-1 == connect(clientfd, (struct sockaddr*)&server_addr, sizeof(server_addr)))
    {
        close(clientfd);
        char errtxt[512] = {0};
        cout<<"connect error"<<endl;
        //sprintf(errtxt, "connect error! errno:%d", errno);
        return;
    }

    // 发送rpc请求
    if (-1 == send(clientfd, send_rpc_str.c_str(), send_rpc_str.size(), 0))
    {
        close(clientfd);
        char errtxt[512] = {0};
        cout<<"send error"<<endl;
        //sprintf(errtxt, "send error! errno:%d", errno);
        //controller->SetFailed(errtxt);
        return;
    }

    // 接收rpc请求的响应值
    char recv_buf[1024] = {0};
    int recv_size = 0;
    if (-1 == (recv_size = recv(clientfd, recv_buf, 1024, 0)))
    {
        close(clientfd);
        char errtxt[512] = {0};
        cout<<"recv error"<<endl;
        //sprintf(errtxt, "recv error! errno:%d", errno);
        //controller->SetFailed(errtxt);
        return;
    }

    // 反序列化rpc调用的响应数据
    // std::string response_str(recv_buf, 0, recv_size); // bug出现问题，recv_buf中遇到\0后面的数据就存不下来了，导致反序列化失败
    // if (!response->ParseFromString(response_str))
    if (!response->ParseFromArray(recv_buf, recv_size))
    {
        close(clientfd);
        char errtxt[512] = {0};
        cout<<"ParseFromArray error"<<endl;
        //sprintf(errtxt, "parse error! response_str:%s", recv_buf);
        //controller->SetFailed(errtxt);
        return;
    }

    close(clientfd);
}
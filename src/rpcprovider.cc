#include "rpcprovider.h"
#include "mprpcapplication.h"

void RpcProvider::NotifyService(google::protobuf::Service *service)
{

}
void RpcProvider::run()
{
    std::string ip = MprpcApplication::getMpracApplication().GetConfig().Load("rpcserverip");
    uint16_t port = atoi(MprpcApplication::getMpracApplication().GetConfig().Load("rpcserverport").c_str());
    muduo::net::InetAddress address(ip,port);

    muduo::net::TcpServer server(&m_eventLoop,address,"RpcProvider");
    // 绑定连接回调和消息读写回调方法  分离了网络代码和业务代码
    server.setConnectionCallback(std::bind(&RpcProvider::onConnection, this, std::placeholders::_1));
    server.setMessageCallback(std::bind(&RpcProvider::onMessage, this, std::placeholders::_1, 
            std::placeholders::_2, std::placeholders::_3));

    server.setThreadNum(4);

    // rpc服务端准备启动，打印信息
    std::cout << "RpcProvider start service at ip:" << ip << " port:" << port << std::endl;

    server.start();
    m_eventLoop.loop();
}

void RpcProvider::onConnection(const muduo::net::TcpConnectionPtr&)
{

}

void RpcProvider::onMessage(const muduo::net::TcpConnectionPtr&, muduo::net::Buffer*, muduo::Timestamp)
{

}
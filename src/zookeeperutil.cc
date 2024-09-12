#include "zookeeperutil.h"
#include "mprpcapplication.h"
#include <semaphore.h>
#include <iostream>
using namespace std;

ZkClient::ZkClient()
{

}
ZkClient::~ZkClient()
{
    if(m_zhandle != nullptr)
    {
        zookeeper_close(m_zhandle);
    }
}

// 全局的watcher观察器   zkserver给zkclient的通知
void global_watcher(zhandle_t *zh, int type,
                   int state, const char *path, void *watcherCtx)
{
    if(type == ZOO_SESSION_EVENT)
    {
        if(state == ZOO_CONNECTED_STATE)
        {
            sem_t *sem = (sem_t*)zoo_get_context(zh);
            sem_post(sem);
        }
    }
}
void ZkClient::Start()
{
    string host = MprpcApplication::getMpracApplication().GetConfig().Load("zookeeperip");
    string port = MprpcApplication::getMpracApplication().GetConfig().Load("zookeeperport");
    string connstr = host + ":" + port;

    m_zhandle = zookeeper_init(connstr.c_str(),global_watcher,30000,nullptr,nullptr,0);
    if(nullptr == m_zhandle)
    {
        cout<<"zookeeper init error"<<endl;
        exit(EXIT_FAILURE);
    }

    sem_t sem;
    sem_init(&sem,0,0);
    zoo_set_context(m_zhandle,&sem);

    sem_wait(&sem);
    cout<<"zookeeper init success"<<endl;
}
void ZkClient::Create(const char *path, const char *data, int datalen, int state)
{
    char path_buffer[128] = {0};
    int bufferlen = sizeof(path_buffer);
    int flag;

    flag = zoo_exists(m_zhandle,path,0,nullptr);
    if(ZNONODE == flag)
    {
        flag = zoo_create(m_zhandle,path,data,datalen,&ZOO_OPEN_ACL_UNSAFE,state,path_buffer,bufferlen);
        if (flag == ZOK)
		{
			std::cout << "znode create success... path:" << path << std::endl;
		}
		else
		{
			std::cout << "flag:" << flag << std::endl;
			std::cout << "znode create error... path:" << path << std::endl;
			exit(EXIT_FAILURE);
		}
    }
}
std::string ZkClient::GetData(const char *path)
{
    char buffer[64] = {0};
    int bufferlen = sizeof(buffer);
    int flag = zoo_get(m_zhandle,path,0,buffer,&bufferlen,nullptr);
    if (flag != ZOK)
	{
		std::cout << "get znode error... path:" << path << std::endl;
		return "";
	}
	else
	{
		return buffer;
	}
}
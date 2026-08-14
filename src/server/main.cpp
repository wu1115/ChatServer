#include"chatserver.hpp"
#include"chatservice.hpp"
#include<iostream>
#include<signal.h>
using namespace std;
//处理服务器ctrl+c结束后，重置user信息
void resetHandler(int)
{
    ChatService::instance()->reset();
    exit(0);
}
int main(int argc, char* argv[])
{
    signal(SIGINT,resetHandler);
    if (argc != 3)
    {
        cerr << "启动格式：./ChatServer 127.0.0.1 6000" << endl;
        exit(-1);
    }
    string ip = argv[1];
    short port = atoi(argv[2]);

    EventLoop loop;
    InetAddress addr(ip, port);
    ChatServer server(&loop,addr,"ChatServer");
    server.start();
    loop.loop();
    return 0;
}

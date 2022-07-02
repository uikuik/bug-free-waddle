#include <optional>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
//#include <optional>
bool init_lib()//初始化库
{
	WSADATA wsaData;

  // 初始化库

  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
      //printf("WSAStartup failed: %d\n", iResult);
      //cout << "\n初始化失败";
      return 0;
    }
  else
    {
      // << "\n初始化成功";
      return 1;
    }
}

SOCKET create_sock()//创建套接字  SOCKET 名字 = 此函数() 
{
	return socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//创建SOCK
	
}

struct addrinfo* create_addr(std::string ip,std::string port,bool l)// // 创建一个结构体来表示IP地址:端口号的组合
{
	 struct addrinfo  hints, * f;//hints告诉getaddrinfo我的类型，返回到resuit
  //不变组合到36行
  memset(&hints, 0, sizeof(hints));//把内存块设为0
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE;
  // 创建一个结构体来表示IP地址:端口号的组合
  if (getaddrinfo(l?NULL:ip.c_str(), port.c_str(), &hints, &f) != 0)
    {
      return NULL;//失败
    }
    
    return f;
}// struct addrinfo* 名字 = create_addr( ip地址, port端口 ,是否为null)

bool _connect(SOCKET s,std::string ip,std::string port)//连接  _connect(套接字名，ip地址，端口号)
{
	 struct addrinfo* f = create_addr(ip,port,0);
	 return connect(s, f->ai_addr, (int)f->ai_addrlen) != SOCKET_ERROR;//成功返回真

}
/*
std::optional<std::string> _recv(SOCKET s,unsigned int n)//接收  _recv(套接字名，接受量)
{
	
	char ch[n]= {0};
	
	int n = recv(S, ch, sizeof(ch), 0);
          if (n == SOCKET_ERROR)
            {
             return std::nullopt;
            }
            
      return std::string(ch);      
}
std::optional<std::string> val=_recv();

if(val.has_value()
{
  // 如果有值
  std::string str = val.get(); // 这样取值！
}
else
{
  // 如果没有值...
}

*/
// { 上方的函数要在c++17下编译，比如  VS c++ 2022 

 std::string _recv2(SOCKET s,unsigned int n)//接收  _recv  _recv(套接字名，接受量)
{
	
	char ch[n]= {0};
	
	int n1 = recv(s, ch, sizeof(ch), 0);
          if (n1 == SOCKET_ERROR)
            {
             return "▓失败▓";
            }
            
      return std::string(ch,n1);      
}

bool _send(SOCKET s,std::string str)//发送
{
	if(send(s,str.c_str(),str.size(),0)==SOCKET_ERROR)
	{
		return 0;//失败
	}
	return 1;
}

///------------------------------下面的函数是服务端使用的，可以完成等待用户并连接 The following function is used by the server to wait for the user and connect
bool tffiubtstwftuac(SOCKET s,std::string ip,std::string port)//tffiubtstwftuac(监听的套接字名,ip,端口)用于准备接受连接
{
	struct addrinfo* f = create_addr(ip,port,0);
	if (bind(s, f->ai_addr, (int)f->ai_addrlen) == SOCKET_ERROR)
    {

        return 0;//失败
    }
     if(listen(s, SOMAXCONN)!=0)
	 {
	 return 0;//失败
	 }//开始监听是否有连接传入
	 
	 return 1;//成功
}

SOCKET tffiubtstwftuac2(SOCKET s)//接受连接
{
	sockaddr remote_addr;//客户端的IP地址和端口
	 return  accept(s, &remote_addr, NULL);//接受连接
	 
}




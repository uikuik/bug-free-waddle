#include "network.h"
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

int main(int argc, char** argv)
{
  cout<<init_lib();
  //---------------------
  SOCKET S =create_sock();//声名对象S

  
  
  //绑定组合

  tffiubtstwftuac(S,"127.0.0.1","3333");
 
  

  while (1)
    {
      cout << "[正在尝试接受连接]\n";
      SOCKET C =  tffiubtstwftuac2( S);
      if (C == INVALID_SOCKET)
        {
          cout << "\n\n连接失败\n\n";
          continue;
        }
      cout << "\n成功\n\n";

      while (1)
        {
          string str;
          cout << "\n发送请输入:";

          cin >> str;
          _send(C, str);
          cout << "\n如果接收请按1\n";
          cin >> str;



          if ( str== "1")
            {
              
              str = _recv2( C,50);
              
              cout << "\n接收到:" << str << "\n";
            }
          else
            {
              cout << "\n已跳过接收\n";
            }




        }

      closesocket(C);
    }

  //---------------------
  WSACleanup();
}
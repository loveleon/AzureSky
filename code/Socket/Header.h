#pragma once 

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <process.h>  //_beginthreadex
#include <thread>	  //thread11
#include <mutex>

#ifdef WIN32
#include <WinSock2.h>
#include <stdio.h>
#else
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif

#include <windows.h>  

#pragma comment(lib, "ws2_32.lib")

//http://blog.chinaunix.net/uid-11848011-id-96439.html

## inet_ntoa() Error
  error C4996: 'inet_ntoa': Use inet_ntop() or InetNtop() instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings

## How to solve
  - 방법 1 : inet_ntoa() 대신 inet_ntop() or InetNtop() 를 사용
  - 방법 2 : #define _WINSOCK_DEPRECATED_NO_WARNINGS   
  ***방법2 주의할 점**: #define 위치가 아래와 같이 #include 위에 위치해야 함.*
  
  ```
  /* lesson 95. TCP/IP 서버 프로그램 */
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "wsock32.lib") 
  ```


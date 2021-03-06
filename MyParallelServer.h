//
// Created by nerya on 16/01/2020.
//

#ifndef UNTITLED2_MYPARALLELSERVER_H
#define UNTITLED2_MYPARALLELSERVER_H

#include "Server.h"
#include "ClientHandler.h"
#include <thread>
#include <bits/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <queue>
#include <list>
#include <strings.h>
#include <unistd.h>
#include "MyClientHandler.h"

#include <vector>

void startParallelAndHandleIt(ClientHandler *clientHandler, int new_sock, bool *isRun) {
  clientHandler->handleClient(new_sock);
  close(new_sock);
  *isRun = false;
}

void openParallelServers(ClientHandler *clientHandler, int port) {
  int s = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in serv;
  serv.sin_addr.s_addr = INADDR_ANY;
  serv.sin_port = htons(port);
  serv.sin_family = AF_INET;
  bool *timeOut = new bool;
  *timeOut = false;
  bool isFirst = true;
  list<bool *> isRunning;
  timeval timeout;
  timeout.tv_sec = 120;
  timeout.tv_usec = 0;

  bind(s, (sockaddr *) &serv, sizeof(serv));

  setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));
  cout << "Server is listening..." << endl;
  while (server_side::isParallelServerConnecting) {
    try {
      int new_sock;
      listen(s, 20000);
      struct sockaddr_in client;
      socklen_t clilen = sizeof(client);
      new_sock = accept(s, (struct sockaddr *) &client, &clilen);
      /*if (server_side::countServersConnect < 10) {
        server_side::countServersConnect++;
      } else {
        continue;
      }*/
      if (*timeOut || new_sock < 0) {
        if (errno == EWOULDBLOCK) {
          cout << "timeout of Parallel!" << endl;
          break;
        } else {
          perror("other error");
          break;
        }
      }

      bool isTimeOut = !isFirst;
      for (auto &r : isRunning) {
        if (*r) {
          isTimeOut = false;
          break;
        }
      }
      if (isTimeOut) {
        if (new_sock < 0) {
          if (errno == EWOULDBLOCK) {
            cout << "parallel timeout!" << endl;
          } else {
            perror("other error");
          }
          server_side::isParallelServerConnecting = false;
          break;
        }
      }


      /*if (server_side::countServersConnect >= 10) {
        continue;
      }*/
      server_side::threads.push_back(new thread);
      bool *isRun = new bool;
      isRunning.push_back(isRun);
      server_side::threads[server_side::threads.size() - 1] =
          new thread(startParallelAndHandleIt, clientHandler, new_sock, isRun);
      isFirst = false;
    } catch (...) {
      cout << "connection with client stopped" << endl;
    }
  }
  delete timeOut;
}

template<class Problem, class Solution>
class MyParallelServer : public server_side::Server<Problem, Solution> {
 public:
  MyParallelServer() = default;

  void stop() {}

  void open(int port, ClientHandler *clientHandler) {
    server_side::isParallelServerConnecting = true;
    thread *t = new thread(openParallelServers, clientHandler, port);
    t->join();
    delete t;
  }
};

#endif //UNTITLED2_MYPARALLELSERVER_H

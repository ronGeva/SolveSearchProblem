//
// Created by nerya on 10/01/2020.
//

#ifndef UNTITELD2_BOOT_H
#define UNTITELD2_BOOT_H
#include "FileCacheManager.h"
#include "MyTestClientHandler.h"
#include "MyClientHandler.h"
#include "MySerialServer.h"
#include "StringReverser.h"
#include "Point.h"
#include "Searchable.h"
#include "SearcherSolverOA.h"
#include "MyParallelServer.h"

using namespace std;

namespace boot {
template<class Problem, class Solution>
class Main {
 public:
  Main() {}
  int main1(int argc, char **argv) {
    auto cm = new FileCacheManager<Problem, Solution>();
    /*auto solver = new StringReverser<string, string>();
    auto *c = new MyTestClientHandler<string, string>(cm, solver);*/
    auto solver = new SearcherSolver<Point>();
    auto *c = new MyClientHandler<Point>(cm, solver);
    auto s = MySerialServer<string, string>();
    auto s2 = MyParallelServer<string, string>();
    int port;
    if (argc < 2) {
      port = 5600;
    } else {
      port = atoi(argv[1]);
    }
    //open the server and start the algorithm
    s2.open(port, c);
    /*s.open(port, c);*/
    return 0;
  }
};

}
#endif //UNTITELD2_BOOT_H
//
// Created by amitai on 10/01/2020.
//

#ifndef UNTITELD2_SEARCHABLE_H
#define UNTITELD2_SEARCHABLE_H

#include "State.h"
#include <vector>
#include <string>

using namespace std;

//interface for a thing to search in it
//the functional of the search problem
template<class T>
class Searchable {
 public:
  //get the initialize of the way
  virtual State<T> *getInitializeState() = 0;

  //return the goal state we got from server
  virtual State<T> *getGoalState() = 0;

  //return all of the possible place that we can go to them
  virtual vector<State<T> *> getPossibleNextStates(State<T> &current) = 0;

  //set the heuristic distance if there is a need
  virtual double setHeuristicForNode(State<T> &firstNode, State<T> &goal) = 0;

  virtual ~Searchable() {}
};

#endif //UNTITELD2_SEARCHABLE_H

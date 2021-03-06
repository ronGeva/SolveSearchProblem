//
// Created by amitai on 10/01/2020
//

#ifndef SOLIDPROJECT_EX2_SOLVER_H
#define SOLIDPROJECT_EX2_SOLVER_H
template<class Problem, class Solution>
class Solver {
 public:
  //a function that solve a generic problem and returns generic solution
  virtual Solution solve(Problem problem) = 0;

  virtual ~Solver() {}
};
#endif //SOLIDPROJECT_EX2_SOLVER_H

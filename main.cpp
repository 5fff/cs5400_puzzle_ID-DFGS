#include <iostream>
#include <string>
#include <chrono>
#include "Node.h"
#include "io_functions.h"
#include "ultility_functions.h"
#include "ID_DFTS.h"
#include "ID_DFGS.h"
using namespace std;

int main(int argc, char** argv)
{
  //handle command input
  if(argc != 3)
  {
    cout<<"2 arguments required: puzzle_file_name output_file_name!"<<endl;
    return 0;
  }
  string puzzle_file_name = argv[1];
  string solution_file_name = argv[2];


  chrono::high_resolution_clock::time_point start_time = chrono::high_resolution_clock::now();
  //get initial node

  //search algorithm is implemented as an object
  ID_DFGS solver(puzzle_reader(puzzle_file_name));
  if(!solver.find_solution())
  {
    cout<<"Solution Not Found!"<<endl;
    return 0;
  }
  chrono::high_resolution_clock::time_point end_time = chrono::high_resolution_clock::now();
  cout<<"Solution Found!"<<endl;
  //if solution found then trace solution
  float time_span = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count()*(1/1000000.0);
  cout << "Time Span =" <<time_span<<endl;
  output_solution(solver.final_node, solver.solution, time_span, solution_file_name);

  return 0;
}

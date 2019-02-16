#ifndef IO_FUNCTIONS_H
#define IO_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include "Node.h"
#include <deque>
#include <tuple>
#include "ultility_functions.h"
#include <ctype.h>

Node puzzle_reader(string file_name);
int output_solution(Node target_node, vector<string> solution, float time_span, string solution_file_name);

#endif

#ifndef ID_DFTS_H
#define ID_DFTS_H

#include "Node.h"
#include <string>
#include <utility>
#include "ultility_functions.h"

struct ID_DFTS
{
  vector<string> solution;
  Action_Node tmp_action_node;
  short height, width, n_snakes;
  pair<short, short> goal_coord;
  Node initial_node, final_node;
  ID_DFTS(Node initial_node_in);
  bool dfts(const Node &current_node, int remaining_depth);
  bool find_solution();

};

#endif

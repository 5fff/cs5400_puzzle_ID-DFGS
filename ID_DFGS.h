#ifndef ID_DFGS_H
#define ID_DFGS_H

#include "Node.h"
#include <string>
#include <utility>
#include "ultility_functions.h"
#include <unordered_set>
struct ID_DFGS
{
  vector<string> solution;
  vector<pair<short,short>> DIRECTION = {{0,1},{-1,0},{0,-1},{1,0}};
  unordered_set<Node> known_nodes;
  Action_Node tmp_action_node;
  short height, width, n_snakes;
  pair<short, short> goal_coord;
  Node initial_node, final_node;
  ID_DFGS(Node initial_node_in);
  bool dfgs(const Node &current_node, int remaining_depth);
  bool find_solution();

};

#endif

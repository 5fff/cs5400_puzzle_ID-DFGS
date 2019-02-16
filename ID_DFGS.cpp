#include "ID_DFGS.h"
#define DEPTH_LIMIT 600


// vector<pair<short,short>> DIRECTION = {{0,1},{-1,0},{0,-1},{1,0}};
// ID_DFGS::DIRECTION = {{0,1},{-1,0},{0,-1},{1,0}};

ID_DFGS::ID_DFGS(Node initial_node_in)
{
  initial_node = initial_node_in;
  height = initial_node.height;
  width = initial_node.width;
  n_snakes = initial_node.n_snakes;
  goal_coord = {(short)(height - 1), (short)(width - 1)};
}

bool ID_DFGS::dfgs(const Node &current_node, int remaining_depth)
{
  //first check base case
  //is it goal state?
  if(is_goal(current_node, goal_coord))
  {
    final_node = current_node;
    return true;
  }
  if(remaining_depth ==0)return false; //depth limit reached, solution not found
  //depth limit not reached, expand
  // snake , head/tail , 4 directions
  for(short snake_index = 0; snake_index < n_snakes; snake_index++)// for each snake
  {
    for (bool terminal_type : { HEAD, TAIL })//get head/tail coordinate
    {
      pair<short,short> terminal_coord = (terminal_type == HEAD)? current_node.snakes[snake_index].front():current_node.snakes[snake_index].back();
      for(auto &direction : DIRECTION)//for each direction
      {
        pair<short,short> tmp_coord = terminal_coord + direction;
        //if inside board and is empty
        if(is_inside(tmp_coord, height, width) && current_node.board[ get<ROW>(tmp_coord) ][ get<COL>(tmp_coord) ] == EMPTY)
        {
          //expand


          Node new_node(current_node); //make a copy of the current_node
          pair<short,short> coord_remove;
          //add new head
          //update snake object
          //if head is moving, push_front
          //if tail is moving, push_back
          if(terminal_type == HEAD) //head is moving
          {
            new_node.snakes[snake_index].push_front(tmp_coord);
            coord_remove = new_node.snakes[snake_index].back();//old tail will be removed from board
            new_node.snakes[snake_index].pop_back();//remove old tail from snake obj
          }
          else // the tail is moving
          {
            new_node.snakes[snake_index].push_back(tmp_coord);
            coord_remove = new_node.snakes[snake_index].front();//old head will be removed from board
            new_node.snakes[snake_index].pop_front();//remove old head form snake obj
          }
          //update board head/tail
          new_node.board[ get<ROW>(tmp_coord) ][ get<COL>(tmp_coord) ] = snake_index; // add new foward direction cell
          // [ get<ROW>(coord_remove) ][ get<COL>(coord_remove) ]
          new_node.board[ get<ROW>(coord_remove) ][ get<COL>(coord_remove) ] = EMPTY; // empty old cell

          //########## Now we have a new node, pass this new node to the function #####
          //########## For each next step
          if(known_nodes.find(new_node) != known_nodes.end())
          {
            // if the node is in set, then skip this node
            continue;
          }
          else
          {
            //add the node to known set
            known_nodes.insert(new_node);
          }

          if(dfgs(new_node, remaining_depth - 1))
          {
            //if a solution found, then the action I'm taking now leads to the solution,
            //so I need to add the solution
            string tmp_str = to_string(snake_index)+" "
            +to_string(terminal_type)+" "
            +to_string(get<COL>(tmp_coord))+" "
            +to_string(get<ROW>(tmp_coord));
            solution.insert(solution.begin(),tmp_str);
            //after adding solution, return true
            return true;
          }
        }
      }
    }
  }
  return false; //if none of the expanded node leads to goal, then return fail(false)
}

bool ID_DFGS::find_solution()
{
  known_nodes = {};
  known_nodes.insert(initial_node);
  for(int depth = 0; depth<DEPTH_LIMIT;depth++)
  {
    known_nodes = {};
    if(dfgs(initial_node, depth))
    {
      return true;
    }
  }
  return false; //max depth limit reached, return false
}

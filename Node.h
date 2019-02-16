#ifndef Node_H
#define Node_H

#include<iostream>
#include<vector>
#include<deque>
#include<map>
#include<utility>
#define EMPTY -1 //used in Node class
#define WALL -2
#define HEAD 0
#define TAIL 1
#define ROW 0
#define COL 1
#define GOAL_SNAKE 0

using namespace std;

struct Node
{
  static short width, height, n_snakes;//board width and height are same across all Nodes
  vector<deque<pair<short,short>>> snakes;
  vector<vector<short>> board; //each cell has a number, -1 means empty,
  // Snakes are represented by a double ended queue of coordinates
  Node(){}

  // width, height, and number of wrigglers
  Node(short width_in, short height_in,short n_snakes_in);
  string get_string() const;
  bool operator==(const Node& rhs) const;
};

struct Action_Node
{
  short snake_index;
  bool terminal_type; //head0 or tail1
  pair<short,short> destination;
  int prev_action; // index of parent action node index
};

//where should I properly place the code below

//Define custom hash function for Node type
namespace std
{
  template <>
  struct hash<Node>
  {
    size_t operator()(const Node& target) const
    {
      return (hash<string>()(target.get_string()));
    }
  };
}

#endif

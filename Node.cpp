#include "Node.h"

Node::Node(short width_in, short height_in,short n_snakes_in)
{
  width = width_in;
  height = height_in;
  n_snakes = n_snakes_in;
  //Initialize an empty board (-1)
  board = vector<vector<short>>(height,vector<short>(width,EMPTY));
  // Initialize n snakes represented by deque of coordinates
  snakes = vector<deque<pair<short,short>>>(n_snakes);
}

string Node::get_string() const
{
  string s;// s = "" upon construction;
  for(short row = 0; row < height; row++)
  {
    for(short col = 0; col < width; col++)
    {
      s += (char)board[row][col]; // shrink the size to char, its not going to go out of range.
    }
  }
  // cout<<"string:"<<s<<endl;
  return s;
}

bool Node::operator==(const Node& rhs) const
{

  // cout<<"== called"<<endl<<"lhs:"<<endl;
  // for(int i = 0;i<n_snakes;i++)
  // {
  //   cout<<"snake #"<<i<<": ";
  //   for(auto&& joint : snakes[i])
  //   {
  //     cout<<"("<<get<ROW>(joint)<<","<<get<COL>(joint)<<")";
  //   }
  //   cout<<endl;
  // }
  // cout<<"rhs:"<<endl;
  //
  // for(int i = 0;i<n_snakes;i++)
  // {
  //   cout<<"snake #"<<i<<": ";
  //   for(auto&& joint : rhs.snakes[i])
  //   {
  //     cout<<"("<<get<ROW>(joint)<<","<<get<COL>(joint)<<")";
  //   }
  //   cout<<endl;
  // }
  // cout<<"RESULT "<<(short)(snakes == rhs.snakes)<<endl;
  //
  return snakes == rhs.snakes;
}

short Node::width = 0;
short Node::height = 0;
short Node::n_snakes = 0;

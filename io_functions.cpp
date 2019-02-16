//Ruicheng Xu CS5400 HW1
#include "io_functions.h"
#include <set>
using namespace std;

map<char,pair<short,short>> HEAD_DIRECTION = {{'R',{0,1}},{'U',{-1,0}},{'L',{0,-1}},{'D',{1,0}}};
map<char,pair<short,short>> BODY_DIRECTION = {{'>',{0,1}},{'^',{-1,0}},{'<',{0,-1}},{'v',{1,0}}};
map<pair<short,short>,char> DIRECTION_HEAD = {{{0,1},'R'},{{-1,0},'U'},{{0,-1},'L'},{{1,0},'D'}};
map<pair<short,short>,char> DIRECTION_BODY = {{{0,1},'>'},{{-1,0},'^'},{{0,-1},'<'},{{1,0},'v'}};

set<char> VALID_CHARS = {'x','e','R','U','L','D','>','^','<','v','0','1','2','3','4','5','6','7','8','9'};

Node puzzle_reader(string file_name)
{
  ifstream Puzzle_File;
  short width, height, n_snakes;
  Puzzle_File.open(file_name);
  char tmp_char;
  if (!Puzzle_File)
  {
    cout<<"Unable to open file!"<<endl;
    exit(1);
  }
  //width, height, and number of wrigglers on the first line
  Puzzle_File>>width>>height>>n_snakes;
  Node target_node(width, height, n_snakes);
  char raw_grid[height][width];
  for(short row = 0;row<height;row++)//row number
  {
    for(short col = 0;col<width;col++)
    {
      Puzzle_File>>raw_grid[row][col];
      if(Puzzle_File.eof())
      {
        cout<<"given board doesn't match the size!"<<endl;
        exit(1);
      }
      if(VALID_CHARS.count(raw_grid[row][col])==0)
      {
        //invalid character
        cout<<"Invalid Character in input file!!"<<endl;
        cout<<raw_grid[row][col]<<endl;
        exit(1);
      }
    }
  }
  Puzzle_File>>tmp_char;
  if(VALID_CHARS.count(tmp_char))
  {
    //we shoul reached the end of file if it is the correct format or size,
    // if not, it means there are extra characters in the input
    cout<<"Extra Character in input file or the wrong size is provided!"<<endl;
    exit(1);
  }

  Puzzle_File.close();
  for(short row = 0;row<height;row++)//row number
  {
        for(short col = 0;col<width;col++)
        {
              if(raw_grid[row][col] == 'x')
              {
                //if its a wall, record it on the board
                target_node.board[row][col] = WALL;
              }
              if(HEAD_DIRECTION.count(raw_grid[row][col]) == 1)
              {
                    // if its a snake head, then trace the whole snake
                    deque<pair<short,short>> tmp_snake;
                    pair<short,short> tmp_coord = {row,col};
                    char tmp_char;
                    //character to direction mapping

                    tmp_char = raw_grid[ get<ROW>(tmp_coord) ][ get<COL>(tmp_coord) ];
                    tmp_snake.push_back(tmp_coord);//head
                    //go to next cell
                    tmp_coord =  tmp_coord + HEAD_DIRECTION[tmp_char];

                    tmp_char = raw_grid[ get<ROW>(tmp_coord) ][ get<COL>(tmp_coord) ];
                    while(! isdigit(tmp_char))
                    {

                          //boundry check
                          if(!is_inside(tmp_coord, height, width))
                          {
                            cout<<"Wrong Wriggler Logic!"<<endl;
                            exit(1);
                          }
                          // get<>()
                          tmp_snake.push_back(tmp_coord);
                          //go to new cell accourding to < > v ^
                          tmp_coord =  tmp_coord + BODY_DIRECTION[tmp_char];
                          //get new char
                          tmp_char = raw_grid[get<ROW>(tmp_coord)][get<COL>(tmp_coord)];
                    }
                    //assign last node
                    // get<ROW>(tmp_coord),get<COL>(tmp_coord)
                    tmp_snake.push_back(tmp_coord);
                    //now tmp_char is a digit, assign the snake to the Node
                    short char_to_int = (int)tmp_char - '0';
                    target_node.snakes[char_to_int] = tmp_snake;
              }
        }

  }
  cout<<"board size height="<<target_node.board.size()<<endl;
  cout<<"board size width="<<target_node.board[0].size()<<endl;
  //fill board(which represent occumency) with snake
  for(short i = 0;i< n_snakes;i++)
  {
    for(auto coord : target_node.snakes[i])
    {
      target_node.board[ get<ROW>(coord) ][ get<COL>(coord) ] = i;
      //i means the index of the snake
    }
  }
  return target_node;
}

int output_solution(Node target_node, vector<string> solution, float time_span, string solution_file_name)
{
  char raw_grid[target_node.height][target_node.width];
  //first put down non snake cells
  for(short row = 0;row<target_node.height;row++)//row number
  {
    for(short col = 0;col<target_node.width;col++)
    {

      switch(target_node.board[row][col])
      {
        case EMPTY:
          raw_grid[row][col] = 'e';
          break;
        case WALL:
          raw_grid[row][col] = 'x';
          break;
      }
    }
  }
  //then trace the snakes
  for(short snake_index = 0; snake_index < target_node.n_snakes; snake_index++)
  {
    pair<short,short> joint_0 = target_node.snakes[snake_index].front();
    pair<short,short> joint_1, delta_coord;
    char corresponding_symbol;
    for(short joint_index = 1; joint_index < target_node.snakes[snake_index].size(); joint_index++)
    {
      joint_1 = target_node.snakes[snake_index][joint_index];
      delta_coord = joint_1 - joint_0;
      corresponding_symbol = DIRECTION_BODY[delta_coord];
      raw_grid[ get<ROW>(joint_0) ][ get<COL>(joint_0) ] = corresponding_symbol;
      joint_0 = joint_1;
    }
    //get the tail
    raw_grid[ get<ROW>(joint_1) ][ get<COL>(joint_1) ] = (snake_index + '0');//convert int to char
    //replace the head joint with the correct symbol
    joint_0 = target_node.snakes[snake_index].front();
    joint_1 = target_node.snakes[snake_index][1];
    delta_coord = joint_1 - joint_0;
    corresponding_symbol = DIRECTION_HEAD[delta_coord];
    raw_grid[ get<ROW>(joint_0) ][ get<COL>(joint_0) ] = corresponding_symbol;
  }

  // open solution file
  ofstream Solution_File;
  Solution_File.open(solution_file_name);
  //output solution
  for(auto && single_sting : solution)
  {
    cout<<single_sting<<endl;
    Solution_File<<single_sting<<endl;
  }
  //output board
  for(short row = 0;row<target_node.height;row++)//row number
  {
    for(short col = 0;col<target_node.width;col++)
    {
      cout<<raw_grid[row][col]<<" ";
      Solution_File<<raw_grid[row][col]<<" ";
    }
    cout<<endl;
    Solution_File<<endl;
  }
  //output time
  Solution_File<<time_span<<endl<<solution.size()<<endl;
  return 0;

}

#ifndef Ultility_Functions
#define Ultility_Functions

#include <iostream>
#include <fstream>
#include <string>
#include "Node.h"
#include <deque>
#include <tuple>
#include <map>
#include <ctype.h>
#include <utility>
using namespace std;

bool is_inside(pair<short,short>& coord, short height, short width);
bool is_goal(const Node& target, pair<short,short> goal_coord);
pair<short,short> operator+ (pair<short,short>& lhs, pair<short,short>& rhs);
pair<short,short> operator- (pair<short,short>& lhs, pair<short,short>& rhs);


#endif

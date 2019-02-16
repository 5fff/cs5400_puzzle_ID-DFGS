#include "ultility_functions.h"

bool is_inside(pair<short,short>& coord, short height, short width)
{
  return (get<ROW>(coord)<height && get<ROW>(coord) >= 0 && get<COL>(coord)<width && get<COL>(coord) >= 0);
}

bool is_goal(const Node& target, pair<short,short> goal_coord)
{
  return (target.snakes[GOAL_SNAKE].front() == goal_coord) ||
  (target.snakes[GOAL_SNAKE].back() == goal_coord);
}


pair<short,short> operator+ (pair<short,short>& lhs, pair<short,short>& rhs)
{
  return {get<0>(lhs)+get<0>(rhs), get<1>(lhs)+get<1>(rhs)};
}

pair<short,short> operator- (pair<short,short>& lhs, pair<short,short>& rhs)
{
  return {get<0>(lhs)-get<0>(rhs), get<1>(lhs)-get<1>(rhs)};
}

#ifndef STATE_H_
#define STATE_H_
#include "suan_png.h"
#include "pxl.h"
#include <vector>
#include <list>

struct node{
    int position_x;
    int position_y;
    int industry;
};

struct State {
    int vertex;
    std::vector<struct node> nodes;
    std::vector<std::list<int>> edges;
};

// function
void init_State(struct State *s);
void delete_State(struct State *s);
void assign(struct State *a, struct State *b);
void parse(struct State *s, struct PNG *p);
int solve1(struct State *s);
int solve2(struct State *s);

#endif

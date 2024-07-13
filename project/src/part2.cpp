#include "suan_png.h"
#include "pxl.h"
#include "state.h"
#include <string>
#include <iostream>

int solve_algo();

int main() {
    solve_algo();
    return 0;
}


int solve_algo() {
    PNG *png = new PNG();
    init_PNG(png);
    load(png, "pic/test2.png");
    State *state = new State();
    init_State(state);
    parse(state, png);
    std::cout << solve1(state) << std::endl;
    std::cout << solve2(state) << std::endl;
    save(png, "pic/test2.png");
    delete_State(state);
    delete_PNG(png);
    delete state;
    delete png;
    return -1;
}

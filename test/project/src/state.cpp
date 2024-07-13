#include "state.h"
#include <queue>
#include <algorithm>

void init_State(struct State *s) {
    return;
}

void delete_State(struct State *s) {
    return;
}

int get_Rgb(struct PXL *p){
    return 255 * 255 * 3 - p->red * p->red - p->green * p->green - p->blue * p->blue;
}

int N = 0;

void parse(struct State *s, struct PNG *p) {
    int width = p->width;
    int height = p->height;
    struct node n;
    int level = 0;

    int col_num = width / 8;

    for (int i = 6; i < height; i += 8) {
        int cnt = 0;
        if(!level){
            for (int j = 4; j < width; j += 8) {
                if(cnt == col_num) {
                    break;
                }
                n.position_x = i;
                n.position_y = j;
                n.industry = 0;
                struct PXL *pxl = get_PXL(p, j, i);
                n.industry = get_Rgb(pxl);
                s->nodes.push_back(n);
                cnt++;
            }
            level = level ^ 1;
        }
        else {
            for (int j = 8; j < width; j += 8) {
                if(cnt == col_num - 1) {
                    break;
                }
                n.position_x = i;
                n.position_y = j;
                n.industry = 0;
                struct PXL *pxl = get_PXL(p, j, i);
                n.industry = get_Rgb(pxl);
                s->nodes.push_back(n);
                cnt++;
            }
            level = level ^ 1;
        }
    }

    s->vertex = s->nodes.size();
    N = s->vertex;
    s->edges.resize(s->vertex);

    int now_col = 0;
    int total = col_num;

    for (int i = 0; i < s->vertex; i++) {
        if(i == total - 1 && i != 0) {
            if(now_col % 2 == 0){
                total += col_num - 1;
            }
            else {
                total += col_num;
            }
            now_col++;
        }
        int x1 = s->nodes[i].position_x;
        int y1 = s->nodes[i].position_y;
        if(x1 == 6) {
            if(y1 == 4) {
                s->edges[i].push_back(i + 1);
                s->edges[i].push_back(i + col_num);
            }
            else if(y1 == width - 4 || i % col_num == col_num - 1) {
                s->edges[i].push_back(i - 1);
                s->edges[i].push_back(i + col_num - 1);
            }
            else {
                s->edges[i].push_back(i - 1);
                s->edges[i].push_back(i + 1);
                s->edges[i].push_back(i + col_num);
                s->edges[i].push_back(i + col_num - 1);
            }
        }
        else if(i >= s->vertex - col_num && i < s->vertex && now_col % 2 == 0) {
            if(y1 == 4) {
                s->edges[i].push_back(i + 1);
                s->edges[i].push_back(i - col_num + 1);
            }
            else if(y1 == width - 4 || (i - (now_col / 2) * (col_num * 2 - 1)) % col_num == 3) {
                s->edges[i].push_back(i - 1);
                s->edges[i].push_back(i - col_num);
            }
            else {
                s->edges[i].push_back(i - 1);
                s->edges[i].push_back(i + 1);
                s->edges[i].push_back(i - col_num);
                s->edges[i].push_back(i - col_num + 1);
            }
        }
        else if(i >= s->vertex - col_num + 1 && i < s->vertex && now_col % 2) {
            if(y1 == 8) {
                s->edges[i].push_back(i + 1);
                s->edges[i].push_back(i - col_num);
                s->edges[i].push_back(i - col_num + 1);
            }
            else if((i - ((now_col + 1) / 2) * col_num - (now_col / 2) * (col_num - 1)) % (col_num - 1) == col_num - 2) {
                s->edges[i].push_back(i - 1);
                s->edges[i].push_back(i - col_num);
                s->edges[i].push_back(i - col_num + 1);
            }
            else {
                s->edges[i].push_back(i - 1);
                s->edges[i].push_back(i + 1);
                s->edges[i].push_back(i - col_num);
                s->edges[i].push_back(i - col_num + 1);
            }
        }
        else {
            if(now_col % 2 == 0) {
                if(y1 == 4){
                    s->edges[i].push_back(i + 1);
                    s->edges[i].push_back(i - col_num + 1);
                    s->edges[i].push_back(i + col_num);
                }
                else if((i - (now_col / 2) * (col_num * 2 - 1)) % col_num == col_num - 1) {
                    s->edges[i].push_back(i - 1);
                    s->edges[i].push_back(i - col_num);
                    s->edges[i].push_back(i + col_num - 1);
                }
                else {
                    s->edges[i].push_back(i - 1);
                    s->edges[i].push_back(i + 1);
                    s->edges[i].push_back(i - col_num);
                    s->edges[i].push_back(i - col_num + 1);
                    s->edges[i].push_back(i + col_num);
                    s->edges[i].push_back(i + col_num - 1);
                }
            } else {
                if(y1 == 8){
                    s->edges[i].push_back(i + 1);
                    s->edges[i].push_back(i - col_num + 1);
                    s->edges[i].push_back(i + col_num);
                    s->edges[i].push_back(i - col_num);
                    s->edges[i].push_back(i + col_num - 1);
                }
                else if((i - ((now_col + 1) / 2) * col_num - ((now_col + 1) / 2 - 1) * (col_num - 1)) % (col_num - 1) == col_num - 2){
                    s->edges[i].push_back(i - 1);
                    s->edges[i].push_back(i - col_num);
                    s->edges[i].push_back(i - col_num + 1);
                    s->edges[i].push_back(i + col_num - 1);
                    s->edges[i].push_back(i + col_num);
                }
                else {
                    s->edges[i].push_back(i - 1);
                    s->edges[i].push_back(i + 1);
                    s->edges[i].push_back(i - col_num);
                    s->edges[i].push_back(i - col_num + 1);
                    s->edges[i].push_back(i + col_num);
                    s->edges[i].push_back(i + col_num - 1);
                }
            }
        }
    }
    return;
}

//path 用于存储路径
std::vector<int> path;
//path2 用于存储次短路径
std::vector<int> path2; 

int ans = 0;
int flag = 1;

// SPFA 求最短路并将路径储存在 path 中
int solve1(struct State *s) {
    int vertex = s->vertex;
    std::vector<long long int> dis(vertex, 0x3f3f3f3f);
    std::vector<long long int> vis(vertex, 0);
    std::vector<int> prev(vertex, -1); // 用于存储路径
    std::queue<int> q;
    dis[0] = 0;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (auto v : s->edges[u]) {
            if(v < 0 || v > vertex - 1){
                continue;
            }
            int cost = dis[u] + s->nodes[v].industry;
            if (dis[v] > cost) {
                dis[v] = cost;
                prev[v] = u; // 记录路径
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            } 
        }
    }

    // 构建路径
    path.resize(0);
    if(prev[vertex - 1] == -1){
        return 0x3f3f3f3f;
    }
    for (int v = vertex - 1; v != -1; v = prev[v]) {
        path.push_back(v);
    }
    std::reverse(path.begin(), path.end());
    if(flag){
        ans = dis[vertex - 1];
        flag = 0;
    }

    return dis[vertex - 1];
}

//SPFA 求次短路
int solve2(struct State *s) {
    path2.clear();
    path2 = path;
    long long int min_dis = 0x3f3f3f3f;
    for(auto i : path2){
        if(i == 0 || i == N - 1){
            continue;
        }
        int temp = s->nodes[i].industry;
        s->nodes[i].industry = 0x3f3f3f3f;
        long long int temp_dis = solve1(s);
        if(temp_dis == ans){
            continue;
        } else {
            min_dis = std::min(min_dis, temp_dis);
        }
        s->nodes[i].industry = temp;
    }
    return min_dis;
}
#include "state.h"
#include <queue>
#include <algorithm>

void init_State(struct State *s) {      //初始化State结构体
    return;
}

void delete_State(struct State *s) {    //删除State结构体
    return;
}

int get_Rgb(struct PXL *p){         //获取当前像素点的RGB值
    return 255 * 255 * 3 - p->red * p->red - p->green * p->green - p->blue * p->blue;
}

int N = 0;      //记录节点数

void parse(struct State *s, struct PNG *p) {        //解析图片函数
    int width = p->width;
    int height = p->height;
    struct node n;
    int level = 0;

    int col_num = width / 8;        //储存偶数行的节点数

    for (int i = 6; i < height; i += 8) {           //遍历图片
        int cnt = 0;                        //记录当前行的节点数
        if(!level){                                 //偶数行
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
        else {                                //奇数行
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

    s->vertex = s->nodes.size();        //记录节点数
    N = s->vertex;                      //全局变量记录节点数
    s->edges.resize(s->vertex);         //初始化边

    int now_row = 0;                    //记录当前行
    int total = col_num;                //记录已遍历的节点数

    for (int i = 0; i < s->vertex; i++) {

        if(i == total - 1 && i != 0) {           //换行操作
            if(now_row % 2 == 0){
                total += col_num - 1;
            }
            else {
                total += col_num;
            }
            now_row++;
        }

        int x1 = s->nodes[i].position_x;        //获取当前节点的横纵坐标
        int y1 = s->nodes[i].position_y;

        if(x1 == 6) {           //处理第一行的节点
            if(y1 == 4) {       //处理第一列的节点
                s->edges[i].push_back(i + 1);
                s->edges[i].push_back(i + col_num);
            }
            else if(y1 == width - 4 || i % col_num == col_num - 1) {        //处理最后一列的节点
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
        else if(i >= s->vertex - col_num && i < s->vertex && now_row % 2 == 0) {        //处理最后一行的节点
            if(y1 == 4) {                                                       //处理第一列的节点
                s->edges[i].push_back(i + 1);
                s->edges[i].push_back(i - col_num + 1);
            }
            else if(y1 == width - 4 || (i - (now_row / 2) * (col_num * 2 - 1)) % col_num == 3) {        //处理最后一列的节点
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
        else if(i >= s->vertex - col_num + 1 && i < s->vertex && now_row % 2) {             //处理最后一行的节点
            if(y1 == 8) {                                                               //处理第一列的节点
                s->edges[i].push_back(i + 1);
                s->edges[i].push_back(i - col_num);
                s->edges[i].push_back(i - col_num + 1);
            }
            else if((i - ((now_row + 1) / 2) * col_num - (now_row / 2) * (col_num - 1)) % (col_num - 1) == col_num - 2) {       //处理最后一列的节点
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
        else {          //处理中间的节点
            if(now_row % 2 == 0) {          //偶数行
                if(y1 == 4){            //第一列
                    s->edges[i].push_back(i + 1);
                    s->edges[i].push_back(i - col_num + 1);
                    s->edges[i].push_back(i + col_num);
                }
                else if((i - (now_row / 2) * (col_num * 2 - 1)) % col_num == col_num - 1) {             //最后一列
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
            } else {                //奇数行
                if(y1 == 8){            //第一列
                    s->edges[i].push_back(i + 1);
                    s->edges[i].push_back(i - col_num + 1);
                    s->edges[i].push_back(i + col_num);
                    s->edges[i].push_back(i - col_num);
                    s->edges[i].push_back(i + col_num - 1);
                }
                else if((i - ((now_row + 1) / 2) * col_num - ((now_row + 1) / 2 - 1) * (col_num - 1)) % (col_num - 1) == col_num - 2){      //最后一列
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

int ans = 0;        //记录最短路径长度
int flag = 1;       //记录是否是第一次求最短路径

// SPFA 求最短路并将路径储存在 path 中
int solve1(struct State *s) {
    int vertex = s->vertex;
    std::vector<long long int> dis(vertex, 0x3f3f3f3f);     //记录最短路径长度
    std::vector<long long int> vis(vertex, 0);      //记录是否在队列中
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
        if(temp_dis == ans){            //如果次短路径等于最短路径，跳过
            continue;
        } else {
            min_dis = std::min(min_dis, temp_dis);
        }
        s->nodes[i].industry = temp;
    }
    return min_dis;
}
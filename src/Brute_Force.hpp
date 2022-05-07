#include "Graph.h"
#include <queue>
#include <assert.h>
#include <set>

#define debugout(x) std::cout << #x << ": " << x << '\n'

//最终答案
static int BF_Min_Acc = -1;

//当前枚举的放大器个数
static int numAcc = 0;
//最大衰减量
static int d = 0;
static const int maxn = 1010;
//在检查是否合法时使用，标识该点的压力
static int pressure[maxn];
//放置了放大器的点
static std::vector<int> acc;

//测试
static bool test(const Graph &G)
{
    //先获得每个点的入度
    int *inDegree = new int[G.v() + 1];
    for (int i = 1; i <= G.v(); i++)
        inDegree[i] = G.inDegree(i);
    //存放0入度的点
    std::queue<int> zeroInDegree;
    for (int vertex : acc)
        pressure[vertex] = d;
    //刚开始有且只有1没有入度
    zeroInDegree.push(1);

    while (!zeroInDegree.empty())
    {
        int u = zeroInDegree.front();
        zeroInDegree.pop();
        for (auto it = G.from(u); it != G.end(); it++)
        {
            int v = it.v(), w = it.w();
            if (pressure[u] - w < 0)
                return false;
            if (pressure[v] != d && pressure[u] - w < pressure[v])
                pressure[v] = pressure[u] - w;
            inDegree[v]--;
            if (inDegree[v] == 0)
                zeroInDegree.push(v);
        }
    }
    delete[] inDegree;
    return true;
}

static void place_acc(const Graph &G, int curVertex, int placedAcc)
{
    if (BF_Min_Acc != -1)
        return;
    if (placedAcc == numAcc)
    {
        std::fill(pressure, pressure + maxn, 1e8);
        if (test(G))
            BF_Min_Acc = numAcc;
        return;
    }
    if (curVertex > G.v())
        return;

    //如果后续可以放置的放大器数量多于剩下的节点数量，返回
    if (numAcc - placedAcc > G.v() - curVertex + 1)
        return;
    //当前节点可以选择放或者不放
    //放
    acc.push_back(curVertex);
    place_acc(G, curVertex + 1, placedAcc + 1);
    //不放
    acc.pop_back();
    place_acc(G, curVertex + 1, placedAcc);
}

//===========================主算法===============================
int Brute_Force(const Graph &G, int D)
{
    //初始化从斯特
    numAcc = 0;
    d = D;
    BF_Min_Acc = -1;
    acc.push_back(1);

    //未枚举到合法时继续枚举
    while (BF_Min_Acc == -1)
    {
        assert(numAcc <= G.v() - 1);
        place_acc(G, 2, 0);
        numAcc++;
    }

    acc.clear();
    return BF_Min_Acc;
}
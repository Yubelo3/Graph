#include "Graph.h"
#include <ctime>
#include <queue>

//计时
double Greedy_Time=0.0;

//===================主算法========================
int Greedy(const Graph &G, int d)
{
    time_t start=clock();

    //最少放大器个数
    int Greedy_Min_Acc=0;

    //设置压力
    int *pressure = new int[G.v() + 1];
    std::fill(pressure, pressure + G.v() + 1, 1e8);
    pressure[1] = d;

    //获取入度
    int *inDegree = new int[G.v() + 1];
    for (int i = 1; i <= G.v(); i++)
        inDegree[i] = G.inDegree(i);

    //拓扑
    std::queue<int> zeroInDegree;
    zeroInDegree.push(1);

    while (!zeroInDegree.empty())
    {
        int curVertex = zeroInDegree.front();
        zeroInDegree.pop();
        //策略：有不合法的边，则为该点加上放大器
        //先检查所有边
        for (auto it = G.from(curVertex); it != G.end(); it++)
        {
            int nextVertex = it.v(), w = it.w();
            //遇到不合法的，给该点加放大器
            if (pressure[curVertex] - w < 0)
            {
                Greedy_Min_Acc++;
                pressure[curVertex] = d;
                break;
            }
        }
        //设置子节点的压力，顺便删边
        for (auto it = G.from(curVertex); it != G.end(); it++)
        {
            int nextVertex = it.v(), w = it.w();
            pressure[nextVertex] = std::min(pressure[nextVertex], pressure[curVertex] - w);
            inDegree[nextVertex]--;
            if (!inDegree[nextVertex])
                zeroInDegree.push(nextVertex);
        }
    }

    //输出一下每个点的压力(可有可无)
    for(int i=1;i<=G.v();i++)
        std::cout<<pressure[i]<<" ";
    std::cout<<'\n';

    delete[] inDegree;
    delete[] pressure;
    Greedy_Time+=clock()-start;
    return Greedy_Min_Acc;
}
#include <iostream>
#include <sstream>
#include "Graph.h"
#include "Brute_Force.hpp"
#include "Greedy.hpp"
#include <fstream>

static std::string filename_bf(int index)
{
    std::stringstream ret;
    ret<<"../Test/myoutput_bf/"<<index<<".out";
    return ret.str();
}
static std::string filename_greedy(int index)
{
    std::stringstream ret;
    ret<<"../Test/myoutput_greedy/"<<index<<".out";
    return ret.str();
}

int main()
{
    std::ios::sync_with_stdio(false);

    //创建好输出环境
    system("mkdir ../Test/myoutput_bf");
    system("mkdir ../Test/myoutput_greedy");

    for(int i=1;i<=100;i++)
    {
        //打开输入文件
        std::stringstream ss;
        ss<<"../Test/input/input"<<i<<".in";
        freopen(ss.str().c_str(),"r",stdin);

        //输入图
        int n,m,d;
        std::cin>>n>>m>>d;
        Graph G(n);
        for(int i=0;i<m;i++)
        {
            int u,v,w;
            std::cin>>u>>v>>w;
            //只保留最长边
            if(G.w(u,v)==Graph::noEdge||G.w(u,v)<w)
                G.insertEdge(u,v,w);
        }

        std::cout<<"process: "<<i<<"/100\n";

        //1.枚举
        std::ofstream file_bf(filename_bf(i));
        file_bf<<Brute_Force(G,d);
        file_bf.close();

        // //2.贪心
        std::ofstream file_greedy(filename_greedy(i));
        file_greedy<<Greedy(G,d);
        file_greedy.close();
    }

    return 0;
}
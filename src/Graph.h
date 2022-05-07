#pragma once
#include <iostream>
#include <vector>
#include <limits>

class Graph
{
    friend std::ostream &operator<<(std::ostream &os, const Graph &G);

public:
    enum {noEdge = (int)1e8};

private:
    //顶点个数
    int _v = 0;
    //边数
    int _e = 0;
    //邻接矩阵
    int **_adj = nullptr;
    //入度存储
    int *_inDegree = nullptr;
    //出度存储
    int *_outDegree = nullptr;

public:
    Graph(int v);
    ~Graph();
    Graph(const Graph &G);

public:
    //顶点数
    inline int v() const { return _v; }
    //边数
    inline int e() const { return _e; }
    //边权
    inline int w(int u, int v) const { return _adj[u][v]; }
    //入度
    int inDegree(int v) const { return _inDegree[v]; }
    //出度
    inline int outDegree(int u) const { return _outDegree[u]; }

    //对于不存在的边，插入并返回true。对于存在的边，修改并返回false
    bool insertEdge(int u, int v, int w);
    //删除边。对于不存在的边，返回false
    bool eraseEdge(int u, int v);

    //迭代器相关
public:
    class iterator
    {
        friend class Graph;

    private:
        const Graph *_G = nullptr;
        int _u = 0;
        int _v = 0;
        // mode==1: 遍历以u为起点的边
        // mode==0: 遍历以v为终点的边
        int _mode = 0;

    public:
        iterator(const Graph *g);
        iterator(const Graph *g, int m);

    public:
        inline int w() const {return _G->_adj[_u][_v];}
        inline int u() const {return _u;}
        inline int v() const {return _v;}
        iterator operator++(int);
        inline bool operator==(const iterator &it) const
        {
            return (_G == it._G && _u == it._u && _v == it._v);
        }
        inline bool operator!=(const iterator &it) const
        {
            return !(*this == it);
        }
    };

    //用于遍历从u出发的点
    iterator from(int u) const;
    //用于遍历连接到v的点
    iterator to(int v) const;
    //结束迭代器
    inline iterator end() const
    {
        return iterator(this);
    }
};
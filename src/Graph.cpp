#include "Graph.h"

std::ostream &operator<<(std::ostream &os, const Graph &G)
{
    for (int i = 1; i <= G.v(); i++)
    {
        for (int j = 1; j <= G.v(); j++)
        {
            if (G._adj[i][j] != Graph::noEdge)
                os << G._adj[i][j] << '\t';
            else
                os << "inf\t";
        }
        os << '\n';
    }
    return os;
}

Graph::Graph(int v) : _v(v)
{
    _adj = new int *[v + 1];
    for (int i = 0; i <= v; i++)
    {
        _adj[i] = new int[v + 1]();
        std::fill(_adj[i], _adj[i] + _v + 1, noEdge);
    }
    _inDegree = new int[v + 1]();
    _outDegree = new int[v + 1]();
}
Graph::~Graph()
{
    for (int i = 0; i < _v + 1; i++)
        delete[] _adj[i];
    delete[] _adj;
    delete[] _inDegree;
    delete[] _outDegree;
}
Graph::Graph(const Graph &G) : _v(G._v), _e(G._e)
{
    _adj = new int *[_v + 1];
    for (int i = 0; i <= _v; i++)
        _adj[i] = new int[_v + 1]();
    for (int i = 0; i <= _v; i++)
        std::copy(G._adj[i], G._adj[i] + _v + 1, _adj[i]);
    _inDegree = new int[_v + 1];
    _outDegree = new int[_v + 1];
    std::copy(G._inDegree, G._inDegree + _v + 1, _inDegree);
    std::copy(G._outDegree, G._outDegree + _v + 1, _outDegree);
}

//对于不存在的边，插入并返回true。对于存在的边，修改并返回false
bool Graph::insertEdge(int u, int v, int w)
{
    bool notExist = (_adj[u][v] == noEdge);
    _adj[u][v] = w;
    if (notExist)
    {
        _e++;
        _outDegree[u]++;
        _inDegree[v]++;
    }
    return notExist;
}
//删除边。对于不存在的边，返回false
bool Graph::eraseEdge(int u, int v)
{
    bool notExist = (_adj[u][v] == noEdge);
    if (!notExist)
    {
        _e--;
        _adj[u][v] = noEdge;
        _outDegree[u]--;
        _inDegree[v]--;
    }
    return notExist;
}

Graph::iterator::iterator(const Graph *g) : _G(g){};
Graph::iterator::iterator(const Graph *g, int m) : _G(g), _mode(m){};

Graph::iterator Graph::iterator::operator++(int)
{
    iterator ret = *this;
    (&_u)[_mode] += 1;
    while (_u <= _G->_v && _v <= _G->_v && _G->_adj[_u][_v] == Graph::noEdge)
        (&_u)[_mode] += 1;
    if (_u > _G->_v || _v > _G->_v)
        _u = _v = 0;
    return ret;
}

//用于遍历从u出发的点
Graph::iterator Graph::from(int u) const
{
    Graph::iterator ret(this, 1);
    ret._u = u;
    ret++;
    return ret;
}
//用于遍历连接到v的点
Graph::iterator Graph::to(int v) const
{
    Graph::iterator ret(this, 0);
    ret._v = v;
    ret++;
    return ret;
}

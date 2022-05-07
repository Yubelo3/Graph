## RUN
mkdir build  
cd build  
cmake ..
make  
./Booster  

`先将测试数据Test文件夹放在src同级目录下再运行`  

---  

## FILES
* main.cpp: 处理图输入，调用暴力算法和贪心算法求解  
* Graph.h, Graph.cpp: 定义了邻接矩阵图的一些接口  
* Brute_Force.hpp: 封装了枚举放大器位置并判断是否合法，来求解最少放大器个数的函数。  
* Greedy.hpp: 封装了求解放大器位置的贪心算法的函数。  
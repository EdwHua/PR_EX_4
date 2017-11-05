//本实验使用不同的分类准则实现聚类

/*
*   @ VS2015 Windows10 x64 C++类编程方法
*   @ 编写了Classification类并实现内部方法，主要包括：

    //使用维度和数据组进行初始化操作
    Classification(int d, int group);
    //格式化打印数据点
    void printData();
    //这里的i,j是指点的顺序，从0~19
    double getDistance(int i,int j);
    //计算点与点之间的距离并保存在distance[]中
    void computeDistance();
    //最大距离聚类法
    void MaxDistanceMethod();
    //最小距离聚类法
    void MinDistanceMethod();
    //均值距离聚类法
    void MeanDistanceMethod();
    //格式化输出数据
    void printClassResult();

*   @ 使用时，引入Classification类的头文件和CPP文件
*/

#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include "Classification.h"

int main() {
    
    std::cout << "预留测试使用，如果维数为2，数据组为0，将使用讲义中的 5个点 进行快速验证" << std::endl<< std::endl;
    std::cout << "选择向量维数（2或3）:";
    int d = 0;
    scanf_s("%d", &d);
    std::cout << std::endl <<"选择数据所在组（1~5）：";
    int group = 0;
    scanf_s("%d", &group);
    
    //创建对象
    Classification classfication(d, group);
    //格式化打印数据
    classfication.printData();
    //计算任意两点之间的距离
    classfication.computeDistance();
    //使用最大距离聚类法，并格式化输出结果
    classfication.MaxDistanceMethod();
    //使用最小距离聚类法，并格式化输出结果
    classfication.MinDistanceMethod();
    //使用均值距离聚类法，并格式化输出结果
    classfication.MeanDistanceMethod();
    
    if (_DEBUG) {
        system("PAUSE");
    }

    return 0;

}
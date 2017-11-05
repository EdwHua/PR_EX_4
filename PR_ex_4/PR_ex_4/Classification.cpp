#include "Classification.h"
Classification::Classification()
{
}

Classification::Classification(int d, int group)
{
    Dimensionality = d;
    dataGroup = group;
    dataAmount = 20;
    distanceAmount = 190;
    if (Dimensionality == 3) {
        switch (dataGroup)
        {
            case 1:
                m_x = &m_x31[0];
                m_y = &m_y31[0];
                m_z = &m_z31[0];
                break;
            case 2:
                m_x = &m_x32[0];
                m_y = &m_y32[0];
                m_z = &m_z32[0];
                break;
            case 3:
                m_x = &m_x33[0];
                m_y = &m_y33[0];
                m_z = &m_z33[0];
                break;
            case 4:
                m_x = &m_x34[0];
                m_y = &m_y34[0];
                m_z = &m_z34[0];
                break;
            case 5:
                m_x = &m_x35[0];
                m_y = &m_y35[0];
                m_z = &m_z35[0];
                break;
            default:
                std::cout << "错误，数据组为1~5";
                break;
        }
    }
    else if (Dimensionality == 2) {
        switch (dataGroup)
        {
        case 0:
            m_x = &m_x5[0];
            m_y = &m_y5[0];
            dataAmount = 5;
            distanceAmount = 10;
            break;
        case 1:
            m_x = &m_x21[0];
            m_y = &m_y21[0];
            
            break;
        case 2:
            m_x = &m_x22[0];
            m_y = &m_y22[0];
            
            break;
        case 3:
            m_x = &m_x23[0];
            m_y = &m_y23[0];
            
            break;
        case 4:
            m_x = &m_x24[0];
            m_y = &m_y24[0];
            
            break;
        case 5:
            m_x = &m_x25[0];
            m_y = &m_y25[0];
            break;
        default:
            std::cout << "错误，数据组为1~5";
            break;
        }
    } 
    else {
        std::cout << "维数错误！";

    }
    
    
}
//格式化输出 点 数据
void Classification::printData()
{
    char A = 65;
    for (int i = 0; i < dataAmount; i++) {
        std::cout << A++ << "<" << std::setw(2) << m_x[i] << "," << std::setw(2) << m_y[i];
        if (Dimensionality == 2) {
            std::cout << ">\t";
        }
        else
        {
            std::cout << "," << std::setw(2) << m_z[i] << ">\t";
        }
        if ((i + 1) % 5 == 0) {
            std::cout << std::endl;
        }
    }
    
    
}

double Classification::getDistance(int i,int j)
{
    //将 线性存储 和 表格存储 相联系的转换函数
    int row, col, offset=0;
    if (i > j) {
        row = j;
        col = i-j-1;
    }
    else {
        row = i;
        col = j-i-1;
    }
    if (row == 0) {
        return distance[col];
    }
    else {
        for (int start=1;start<=row ;start++) {
            offset += (dataAmount - start);
        }
        offset += col;
        return distance[offset];
    }
}

void Classification::computeDistance()
{

    int count = 0;
    for (int i = 0; i < dataAmount - 1; i++) {
        for (int j = i + 1; j < dataAmount; j++) {
            if (Dimensionality == 2)
                distance[count] = std::sqrt(std::pow(m_x[i] - m_x[j], 2) + std::pow(m_y[i] - m_y[j], 2));
            else
                distance[count] = std::sqrt(std::pow(m_x[i] - m_x[j], 2) + std::pow(m_y[i] - m_y[j], 2) + std::pow(m_z[i] - m_z[j], 2));
            if (i == 0 && j == 1) {
                Maxdistance = distance[count];
                Mindistance = distance[count];
            }
            else {
                Maxdistance = (distance[count] > Maxdistance ? distance[count] : Maxdistance);
                Mindistance = (distance[count] < Mindistance ? distance[count] : Mindistance);
            }
            count++;
        }
    }


    /*** 这部分是用于格式化输出的     ***
     *** 输出效果是显示各点之间的距离 ***/
    std::cout << std::endl;
    char charA = 65;
    std::cout << std::setw(2) << " " << " ";
    for (int i = 1; i < dataAmount; i++) {
        std::cout << std::setw(5) << (char)(charA + i) << "|";
    }
    std::cout << std::endl;

    for (int i = 0; i < dataAmount-1; i++) {
        std::cout << std::setw(2) << charA++ << " ";
        for (int j = 1; j < dataAmount; j++)
        {
            if (j > i)
                std::cout << std::setw(5) << std::fixed << std::setprecision(2) << getDistance(i, j) << "|";
            else
                std::cout << std::setw(5) << " " << "|";
        }
        std::cout << std::endl;
    }


    std::cout << "the max distance is " << Maxdistance << std::endl;
    std::cout << "the min distance is " << Mindistance << std::endl;



}

void Classification::MaxDistanceMethod()
{
    //最大距离测度

    //初始选点为0号点，和与0号距离最远的点，为两类中心，其他方法同
    double distanceWithA = Mindistance, distanceWithB = Mindistance;
    classAcountNum = 0; classBcountNum = 0;
    classA[0] = 0;
    classAcountNum++;
    int temp = 0;
    double tempDistance = 0.0;

    for (int j = 1; j < dataAmount; j++) {
        if (getDistance(classA[0], j) > tempDistance) {
            tempDistance = getDistance(classA[0], j);
            temp = j;
        }
    }
    classB[0] = temp;
    classBcountNum++;
    
    for (int i = dataAmount-1; i > 0; i--) {
        if (i == temp)
            continue;
        //先取出相对于 A类与B类 的距离的最大值，然后比较最大值小的进行归类

        for (int Aclass = 0; Aclass < classAcountNum; Aclass++) {
            distanceWithA = (getDistance(classA[Aclass], i)>distanceWithA ? getDistance(classA[Aclass], i) : distanceWithA);
        }

        for (int Bclass = 0; Bclass < classBcountNum; Bclass++)
        {
            distanceWithB = (getDistance(classB[Bclass], i)>distanceWithA ? getDistance(classB[Bclass], i) : distanceWithB);
        }

        if (distanceWithA < distanceWithB) {
            classA[classAcountNum] = i;
            classAcountNum++;
        }
        else
        {
            classB[classBcountNum] = i;
            classBcountNum++;
        }

        distanceWithA = Mindistance;
        distanceWithB = Mindistance;
    }
    std::cout << "最大距离测度" << std::endl;
    printClassResult();

}

void Classification::MinDistanceMethod()
{
    //最小距离测度
    double distanceWithA = Maxdistance, distanceWithB = Maxdistance;
    classAcountNum = 0; classBcountNum = 0;
    classA[0] = 0;
    classAcountNum++;
    int temp = 0;
    double tempDistance = 0.0;

    for (int j = 1; j < dataAmount; j++) {   
        if (getDistance(classA[0], j) > tempDistance) {
            tempDistance = getDistance(classA[0], j);
            temp = j;
        }
    }
    classB[0] = temp;
    classBcountNum++;

    for (int i = dataAmount-1; i > 0; i--) {
        if (i == temp)
            continue;

        //先取出相对于 A类与B类 的距离的最小值，然后比较最大值小的进行归类
        for (int Aclass = 0; Aclass < classAcountNum; Aclass++) {
            distanceWithA = (getDistance(classA[Aclass], i)<distanceWithA ? getDistance(classA[Aclass], i) : distanceWithA);
        }

        for (int Bclass = 0; Bclass < classBcountNum; Bclass++)
        {
            distanceWithB = (getDistance(classB[Bclass], i)<distanceWithA ? getDistance(classB[Bclass], i) : distanceWithB);
        }

        if (distanceWithA < distanceWithB) {
            classA[classAcountNum] = i;
            classAcountNum++;
        }
        else
        {
            classB[classBcountNum] = i;
            classBcountNum++;
        }

        distanceWithA = Maxdistance;
        distanceWithB = Maxdistance;
    }
    std::cout << "最小距离测度" << std::endl;
    printClassResult();
    
}

void Classification::MeanDistanceMethod()
{
    //均值距离测度
    double distanceWithA = 0, distanceWithB = 0;
    classAcountNum = 0; classBcountNum = 0;
    classA[0] = 0;
    classAcountNum++;
    int temp = 0;
    double tempDistance = 0.0;

    for (int j = 1; j < dataAmount; j++) {
        if (getDistance(classA[0], j) > tempDistance) {
            tempDistance = getDistance(classA[0], j);
            temp = j;
        }
    }
    classB[0] = temp;
    classBcountNum++;



    for (int i = dataAmount - 1; i > 0; i--) {
        if (i == temp)
            continue;

        //对相对某类内部所有点距离作和之后求平均
        for (int Aclass = 0; Aclass < classAcountNum; Aclass++) 
        {
            distanceWithA += getDistance(classA[Aclass], i);
        }

        for (int Bclass = 0; Bclass < classBcountNum; Bclass++)
        {
            distanceWithB += getDistance(classB[Bclass], i);
        }

        if ( distanceWithA/(classAcountNum+1) < distanceWithB/(classBcountNum+1) ) 
        {
            classA[classAcountNum] = i;
            classAcountNum++;
        }
        else
        {
            classB[classBcountNum] = i;
            classBcountNum++;
        }

        distanceWithA = 0;
        distanceWithB = 0;
    }

    std::cout << "均值距离测度" << std::endl;
    printClassResult();   
}

void Classification::printClassResult()
{
    //由于所有的点都是整数点，所以加了int方便观察，如果有非整数点，需要把(int)去掉
    std::cout << std::endl;
    std::cout << "第一类：";
    for (int i = 0; i < classAcountNum; i++) {
        std::cout <<"<" << std::setw(2) <<(int) m_x[classA[i]] << "," << std::setw(2) << (int)m_y[classA[i]];
        if (Dimensionality == 2) {
            std::cout << ">\t";
        }
        else
        {
            std::cout << "," << std::setw(2) << (int)m_z[classA[i]] << ">\t";
        }
        if ((i + 1) % 5 == 0) {
            std::cout << std::endl << std::setw(8) << " ";
        }
    }

    std::cout << std::endl << std::endl << "第二类：";
    for (int i = 0; i < classBcountNum; i++) {
        std::cout << "<" << std::setw(2) <<(int) m_x[classB[i]] << "," << std::setw(2) <<(int) m_y[classB[i]];
        if (Dimensionality == 2) {
            std::cout << ">\t";
        }
        else
        {
            std::cout << "," << std::setw(2) << (int)m_z[classB[i]] << ">\t";
        }
        if ((i + 1) % 5 == 0) {
            std::cout << std::endl << std::setw(8) << " ";
        }
    }
    
    std::cout << std::endl << "-------------------------------------------------------" << std::endl;
}



Classification::~Classification()
{
    //delete[] distance;
}

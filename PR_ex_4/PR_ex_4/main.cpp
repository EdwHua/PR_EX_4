//��ʵ��ʹ�ò�ͬ�ķ���׼��ʵ�־���

/*
*   @ VS2015 Windows10 x64 C++���̷���
*   @ ��д��Classification�ಢʵ���ڲ���������Ҫ������

    //ʹ��ά�Ⱥ���������г�ʼ������
    Classification(int d, int group);
    //��ʽ����ӡ���ݵ�
    void printData();
    //�����i,j��ָ���˳�򣬴�0~19
    double getDistance(int i,int j);
    //��������֮��ľ��벢������distance[]��
    void computeDistance();
    //��������෨
    void MaxDistanceMethod();
    //��С������෨
    void MinDistanceMethod();
    //��ֵ������෨
    void MeanDistanceMethod();
    //��ʽ���������
    void printClassResult();

*   @ ʹ��ʱ������Classification���ͷ�ļ���CPP�ļ�
*/

#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include "Classification.h"

int main() {
    
    std::cout << "Ԥ������ʹ�ã����ά��Ϊ2��������Ϊ0����ʹ�ý����е� 5���� ���п�����֤" << std::endl<< std::endl;
    std::cout << "ѡ������ά����2��3��:";
    int d = 0;
    scanf_s("%d", &d);
    std::cout << std::endl <<"ѡ�����������飨1~5����";
    int group = 0;
    scanf_s("%d", &group);
    
    //��������
    Classification classfication(d, group);
    //��ʽ����ӡ����
    classfication.printData();
    //������������֮��ľ���
    classfication.computeDistance();
    //ʹ����������෨������ʽ��������
    classfication.MaxDistanceMethod();
    //ʹ����С������෨������ʽ��������
    classfication.MinDistanceMethod();
    //ʹ�þ�ֵ������෨������ʽ��������
    classfication.MeanDistanceMethod();
    
    if (_DEBUG) {
        system("PAUSE");
    }

    return 0;

}
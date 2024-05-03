#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Expression
{
private:
	int Judge_Priority(char ch1, char ch2); // �ж�����������ȼ� 
	float Cal(float x, float y, char op1); // ����x op y �򵥱��ʽ��ֵ
	string Solve_Bracket(string s);       // Ϊ�ַ������������� 
	int Random_Num(int n);               // ����0~n������� 
	string Solve_Float(float X, int Is_Float); // �����Ƿ����С�����ַ��� 
	string Solve_Complex(string s, int MaxV, int Is_Float); // ���ɸ��ӱ��ʽ
	string Procced_Expression(string s, int MaxV, int Is_Bracket, int Is_Float); // �ӹ����ʽ
public:
	vector<string> Generate_Expression(int num, string ops, int MaxV, int Is_Bracket, int Is_Float); // ��������num�����������ops, �����MaxV, Is_Float�Ƿ�С����Is_Bracket�Ƿ������
	float Calculate_Expression(string s); // ������ʽ��ֵ
	string Solve_Input_Ops(string s);    // Ϊ�����������Ƴ���(+,-,*,/)����� 
	void Print_file(vector<string> p);   // �����ļ�
};
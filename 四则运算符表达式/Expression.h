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
	int Judge_Priority(char ch1, char ch2); // 判断运算符的优先级 
	float Cal(float x, float y, char op1); // 计算x op y 简单表达式的值
	string Solve_Bracket(string s);       // 为字符串随机添加括号 
	int Random_Num(int n);               // 产生0~n的随机数 
	string Solve_Float(float X, int Is_Float); // 处理是否产生小数的字符串 
	string Solve_Complex(string s, int MaxV, int Is_Float); // 生成复杂表达式
	string Procced_Expression(string s, int MaxV, int Is_Bracket, int Is_Float); // 加工表达式
public:
	vector<string> Generate_Expression(int num, string ops, int MaxV, int Is_Bracket, int Is_Float); // 生成满足num数量，运算符ops, 最大数MaxV, Is_Float是否小数，Is_Bracket是否加括号
	float Calculate_Expression(string s); // 计算表达式的值
	string Solve_Input_Ops(string s);    // 为输入的运算符移除非(+,-,*,/)运算符 
	void Print_file(vector<string> p);   // 生成文件
};
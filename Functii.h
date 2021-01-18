
#ifndef D3_FUNCTII_H
#define D3_FUNCTII_H
#ifndef FUNCTII_H
#define FUNCTII_H

#include <iostream>
#include <string>
#include <clocale> //для setlocal>
#include <stack>
#include <cmath>
#include <map>
#include <algorithm>


bool error(std::string s);
bool isSeparator(char s);
int priority(char s);
bool isOperator(char s);
float doIt(char s, float a, float b);
std::string trigonometry(std::string input, int buf);
std::string trigonometryforsqrt(std::string input, int buf);
float counter(std::string input);



#endif
#endif //D3_FUNCTII_H

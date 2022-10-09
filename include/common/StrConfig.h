#pragma once

#include <string>

using namespace std;

namespace str_utility
{
	string RepeatChar(char ch, int n);
	string RepeatSpace(int n);
	string IntToStr(int val);
	string FloatToStr(double val);
	string FloatToStr(double val, int precision);
}
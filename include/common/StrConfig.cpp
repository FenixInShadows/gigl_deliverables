#include "StrConfig.h"

#include <sstream>

string str_utility::IntToStr(int val)
{
	ostringstream tmp_str_stream;
	tmp_str_stream << val;
	return tmp_str_stream.str();
}

string str_utility::FloatToStr(double val, int precision)
{
	ostringstream tmp_str_stream;
	tmp_str_stream.precision(precision);
	tmp_str_stream.setf(ios::fixed, ios::floatfield);
	tmp_str_stream << val;
	return tmp_str_stream.str();
}

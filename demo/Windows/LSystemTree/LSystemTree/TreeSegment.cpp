#include "TreeSegment.h"

#include <SDL2/SDL_opengl.h>

#include <limits>
#include <cmath>

#define MATH_PI 3.141592653589793

//#define PLAIN_RENDER

Range1D::Range1D()
{
}

Range1D::Range1D(double _min, double _max)
	: min(_min), max(_max), span(max - min)
{
}

Range1D::Range1D(double _min, double _max, double _span)
	: min(_min), max(_max), span(_span)
{
}

Range1D MkRange1D(double _min, double _max)
{
	return Range1D(_min, _max);
}

Range1D MkRange1DFromMin(double _min, double _span)
{
	return Range1D(_min, _min + _span, _span);
}

Range1D MkRange1DFromMax(double _max, double _span)
{
	return Range1D(_max - _span, _max, _span);
}

Range1D MkNoConstraintRange1D()
{
	return Range1D(std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity());
}

Range1D MkMinConstraintRange1D(double _min)
{
	return Range1D(_min, -std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity());
}

Range1D MkMaxConstraintRange1D(double _max)
{
	return Range1D(std::numeric_limits<double>::infinity(), _max, -std::numeric_limits<double>::infinity());
}

Range1D UnionRange1D(const Range1D& r1, const Range1D& r2)
{
	return Range1D((r1.min < r2.min ? r1.min : r2.min), (r1.max > r2.max ? r1.max : r2.max));
}

Range1D IntersectRange1D(const Range1D& r1, const Range1D& r2)
{
	return Range1D((r1.min > r2.min ? r1.min : r2.min), (r1.max < r2.max ? r1.max : r2.max));
}

DrawCheckResult CheckDraw1D(const Range1D& range, const Range1D& screen_range)
{
	if (range.min <= screen_range.min)
	{
		if (range.max <= screen_range.min)
			return DRAW_NONE;
		return DRAW_PART;
	}
	if (range.min < screen_range.max)
	{
		if (range.max < screen_range.max)
			return DRAW_ALL;
		return DRAW_PART;
	}
	return DRAW_NONE;
}


Range2D::Range2D()
{
}

Range2D::Range2D(double _left, double _bottom, double _right, double _top)
	: left(_left), bottom(_bottom), right(_right), top(_top), span_x(right - left), span_y(top - bottom)
{
}

Range2D::Range2D(double _left, double _bottom, double _right, double _top, double _span_x, double _span_y)
	: left(_left), bottom(_bottom), right(_right), top(_top), span_x(_span_x), span_y(_span_y)
{
}

double Range2D::GetMinSpan() const
{
	return (span_x < span_y ? span_x : span_y);
}

double Range2D::GetMaxSpan() const
{
	return (span_x > span_y ? span_x : span_y);
}

Range2D Range2D::GetShiftedRange(double dx, double dy) const
{
	return Range2D(left + dx, bottom + dy, right + dx, top + dy, span_x, span_y);
}

Range1D Range2D::ExtractXRange() const
{
	return Range1D(left, right, span_x);
}

Range1D Range2D::ExtractYRange() const
{
	return Range1D(bottom, top, span_y);
}

void Range2D::DrawRect(float r, float g, float b) const
{
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	glVertex2d(left, bottom);
	glVertex2d(right, bottom);
	glVertex2d(right, top);
	glVertex2d(left, top);
	glEnd();
}

Range2D MkRange2D(double _left, double _bottom, double _right, double _top)
{
	return Range2D(_left, _bottom, _right, _top);
}

Range2D MkRange2DFromRange1D(const Range1D& r1, const Range1D& r2)
{
	return Range2D(r1.min, r2.min, r1.max, r2.max);
}

Range2D MkNoConstraintRange2D()
{
	return MkRange2DFromRange1D(MkNoConstraintRange1D(), MkNoConstraintRange1D());
}

Range2D UnionRange2D(const Range2D& r1, const Range2D& r2)
{
	return Range2D(
		(r1.left < r2.left ? r1.left : r2.left),		
		(r1.bottom < r2.bottom ? r1.bottom : r2.bottom),
		(r1.right > r2.right ? r1.right : r2.right),
		(r1.top > r2.top ? r1.top : r2.top));
}

Range2D IntersectRange2D(const Range2D& r1, const Range2D& r2)
{
	return Range2D(
		(r1.left > r2.left ? r1.left : r2.left),		
		(r1.bottom > r2.bottom ? r1.bottom : r2.bottom),
		(r1.right < r2.right ? r1.right : r2.right),
		(r1.top < r2.top ? r1.top : r2.top));
}

DrawCheckResult CheckDraw2D(const Range2D& range, const Range2D& screen_range)
{
	DrawCheckResult check_x = CheckDraw1D(range.ExtractXRange(), screen_range.ExtractXRange());
	DrawCheckResult check_y = CheckDraw1D(range.ExtractYRange(), screen_range.ExtractYRange());

	return (check_x < check_y ? check_x : check_y); // exploit the precedence
}

Range2D GetRange2DFromLineSeg(const Vector2D& start, const Vector2D& end)
{
	double left, bottom, right, top;
	if (start.x <= end.x)
	{
		left = start.x;
		right = end.x;
	}
	else
	{
		left = end.x;
		right = start.x;
	}
	if (start.y <= end.y)
	{
		bottom = start.y;
		top = end.y;
	}
	else
	{
		bottom = end.y;
		top = start.y;
	}

	return Range2D(left, bottom, right, top);
}


Vector2D::Vector2D() : x(0.0), y(0.0)
{
}

Vector2D::Vector2D(double _x, double _y) : x(_x), y(_y)
{
}

Vector2D MkVector2D(double x, double y)
{
	return Vector2D(x, y);
}

Vector2D operator + (const Vector2D& vec_0, const Vector2D& vec_1)
{
	return Vector2D(vec_0.x + vec_1.x, vec_0.y + vec_1.y);
}

Vector2D operator - (const Vector2D& vec_0, const Vector2D& vec_1)
{
	return Vector2D(vec_0.x - vec_1.x, vec_0.y - vec_1.y);
}

Vector2D operator * (double fac, const Vector2D& vec)
{
	return Vector2D(fac * vec.x, fac * vec.y);
}

Vector2D GetVertDir(const Vector2D& vec)
{
	return Vector2D(-vec.y, vec.x);
}

Vector2D RotateDegrees(const Vector2D& vec, double angle)
{
	double cosAngle = cos(angle * MATH_PI / 180.0);
	double sinAngle = sin(angle * MATH_PI / 180.0);
	return Vector2D(cosAngle * vec.x - sinAngle * vec.y, sinAngle * vec.x + cosAngle * vec.y);
}

extern Range2D image_range;

TreeSegment::TreeSegment(const Vector2D& _start, const Vector2D& _end, const Vector2D& _dir, double _len, double _wid)
	: start(_start), end(_end), dir(_dir), length(_len), width(_wid), range(GetRange2DFromLineSeg(start, end))
{
	image_range = UnionRange2D(image_range, range);
}

void TreeSegment::Draw() const
{
#ifdef PLAIN_RENDER
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2d(start.x, start.y);
	glVertex2d(end.x, end.y);
	glEnd();
#else
	if (width < 0.0) // negative indicates it is a leaf
	{
		glColor3f(0.0f, 0.8f, 0.0f);
		Vector2D half_bottom_vec = 0.125 * length * GetVertDir(dir);
		Vector2D mid_pos = 0.5 * (start + end);
		Vector2D mid_left = mid_pos + half_bottom_vec;
		Vector2D mid_right = mid_pos - half_bottom_vec;
		glBegin(GL_QUADS);
		glVertex2d(start.x, start.y);
		glVertex2d(mid_right.x, mid_right.y);
		glVertex2d(end.x, end.y); 
		glVertex2d(mid_left.x, mid_left.y);
		glEnd();
	}
	else
	{
		glColor3f(0.5f, 0.3f, 0.2f);
		Vector2D half_bottom_vec = 0.5 * width * GetVertDir(dir);
		Vector2D bottom_left = start + half_bottom_vec;
		Vector2D bottom_right = start - half_bottom_vec;
		Vector2D top_left = end + half_bottom_vec;
		Vector2D top_right = end - half_bottom_vec;
		glBegin(GL_QUADS);
		glVertex2d(bottom_left.x, bottom_left.y);
		glVertex2d(bottom_right.x, bottom_right.y);
		glVertex2d(top_right.x, top_right.y);
		glVertex2d(top_left.x, top_left.y);
		glEnd();
	}		
#endif	
}

TreeSegment* TermSegGen(int depth, const Vector2D& start, const Vector2D& dir, double bottom_w, double top_w, int n, double unit_len)
{
	double seg_w;
	if (depth >= n)
	{
		seg_w = (top_w < 1e-7 ? -1.0 : 0.5 * (bottom_w + top_w)); // negative means draw as a leaf
	}
	else
	{
		double factor = 1.0 / (double)(1 << (n - depth + 1));
		seg_w = (1.0 - factor) * bottom_w + factor * top_w; // linear interpolation
	}
	return new TreeSegment(start, start + unit_len * dir, dir, unit_len, seg_w);
}

#pragma once

#include "macro.h"

class Range2D;
class Vector2D;

extern Range2D window_range;

enum DrawCheckResult { DRAW_NONE, DRAW_PART, DRAW_ALL };

class Range1D
{
public:
	Range1D();
	Range1D(double _min, double _max);
	Range1D(double _min, double _max, double _span);
	double min, max;
	double span;
};

Range1D MkRange1D(double _min, double _max); // to get around construct expr conflicting with ableC
Range1D MkRange1DFromMin(double _min, double _span);
Range1D MkRange1DFromMax(double _max, double _span);
Range1D MkNoConstraintRange1D(); // used to mean covering nothing, or allowing all coverage if used as a constraint
Range1D MkMinConstraintRange1D(double _min); // use to ensure the coverage start from no larger than a min value 
Range1D MkMaxConstraintRange1D(double _max); // use to ensure the coverage end at no larger than a max value
Range1D UnionRange1D(const Range1D& r1, const Range1D& r2);
Range1D IntersectRange1D(const Range1D& r1, const Range1D& r2);
DrawCheckResult CheckDraw1D(const Range1D& range, const Range1D& screen_range);

class Range2D
{
public:
	Range2D();
	Range2D(double _left, double _bottom, double _right, double _top);
	Range2D(double _left, double _bottom, double _right, double _top, double _span_x, double _span_y);	
	double left, bottom, right, top;
	double span_x, span_y;
	double GetMinSpan() const;
	double GetMaxSpan() const;	// not used atm
	Range2D GetShiftedRange(double dx, double dy) const;
	Range1D ExtractXRange() const;
	Range1D ExtractYRange() const;
	void DrawRect(float r, float g, float b) const;
};

Range2D MkRange2D(double _left, double _bottom, double _right, double _top); // to get around construct expr conflicting with ableC
Range2D MkRange2DFromRange1D(const Range1D& r1, const Range1D& r2);
Range2D MkNoConstraintRange2D(); // used to mean covering nothing, or allowing all coverage if used as a constraint
Range2D UnionRange2D(const Range2D& r1, const Range2D& r2);
Range2D IntersectRange2D(const Range2D& r1, const Range2D& r2);
DrawCheckResult CheckDraw2D(const Range2D& range, const Range2D& screen_range);
Range2D GetRange2DFromLineSeg(const Vector2D& start, const Vector2D& end);

class Vector2D
{
public:
	Vector2D();
	Vector2D(double _x, double _y);
	double x, y;
};

Vector2D MkVector2D(double x, double y); // this is needed only because gigl can't handle construction type expression
Vector2D operator + (const Vector2D& vec_0, const Vector2D& vec_1);
Vector2D operator - (const Vector2D& vec_0, const Vector2D& vec_1);
Vector2D operator * (double fac, const Vector2D& vec);
Vector2D GetVertDir(const Vector2D& vec); // should be the same as RotateDegrees(vec, 90) but the performance should be better
Vector2D RotateDegrees(const Vector2D& vec, double angle);

class TreeSegment
{
public:
	TreeSegment(const Vector2D& _start, const Vector2D& _end, const Vector2D& _dir, double _len, double _wid);
	Vector2D start, end, dir;
	double length;
	double width;
	Range2D range;
	void Draw() const;
};

TreeSegment* TermSegGen(int depth, const Vector2D& start, const Vector2D& dir, double bottom_w, double top_w, int n, double unit_len);
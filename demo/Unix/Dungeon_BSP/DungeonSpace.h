#pragma once

class Range2D;

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
Range2D PadRange2D(const Range2D& range, double padding);
DrawCheckResult CheckDraw2D(const Range2D& range, const Range2D& screen_range);

class Room
{
public:
	Room(double _left, double _bottom, double _right, double _top);
	Range2D range;
	void Draw(bool is_padded) const;
};

Room* TermRoomGen(const Range2D& range, const Range1D& cover_x, const Range1D& cover_y, double room_min, double wall_min);

class BossRoom
{
public:
	BossRoom(double _left, double _bottom, double _right, double _top);
	Range2D range;
	void Draw(bool is_padded) const;
};

BossRoom* BossRoomGen(const Range2D& range, const Range1D& cover_x, const Range1D& cover_y, double room_min, double wall_min);

class Corridor
{
public:
	Corridor(double _left, double _bottom, double _right, double _top);
	Range2D range;
	void Draw(bool is_padded) const;
};

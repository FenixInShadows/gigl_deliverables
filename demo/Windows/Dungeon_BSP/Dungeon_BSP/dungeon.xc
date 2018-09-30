giglstart;

import "DungeonSpace.h";

class Range1D;
class Range2D;
class Room;
class BossRoom;
class Corridor;

gigltype BspDungeon{const Range2D& whole_range, double unit_min, double unit_max, double wall_min, bool have_boss_area}:
< disable auto_prob_noneg >
{
wrapper:
	generator
	{
		root = generate DungeonArea(whole_range, MkNoConstraintRange1D(), MkNoConstraintRange1D(), have_boss_area);
	}
	void Draw()
	{
		root->Draw(true);
		root->Draw(false);
	}

node:
	Range2D bound_box;
	Range2D room_range;
	double GetContactFromLeft(double y);
	double GetContactFromBottom(double x);
	double GetContactFromRight(double y);
	double GetContactFromTop(double x);
	void Draw(bool is_padded)
	{
		switch (CheckDraw2D(bound_box, window_range))
		{
			case DRAW_NONE: break;
			case DRAW_PART: DrawPart(is_padded); break;
			case DRAW_ALL: DrawAll(is_padded); break;
		}
	}
	void DrawPart(bool is_padded);
	void DrawAll(bool is_padded);

nonterminal:
	DungeonArea(const Range2D& range, const Range1D& cover_x, const Range1D& cover_y, bool have_boss);

rule:
	DungeonArea
	default:
		{
			preselector
			{
				if (range.span_x < 2 * unit_min)
					forbid vDivide;
				if (range.span_y < 2 * unit_min)
					forbid hDivide;
				if (range.span_x > unit_max || range.span_y > unit_max)
					forbid tArea, bossArea;
				else if (have_boss)
					forbid<transferto bossArea> tArea;
				else
					forbid<transferto tArea> bossArea;
			}
			pregenerator
			{
				bound_box = range;
			}
		}
	:=
	| hDivide{double corrid_min, double corrid_max}: DungeonArea* b_area, DungeonArea* t_area, Corridor* corridor
		{
			generator
			{
				double corrid_size = GetRandFloat(corrid_min, corrid_max);
				double corrid_pos = GetRandFloat(range.left + wall_min, range.right - wall_min - corrid_size);
				Range1D corrid_cover = MkRange1DFromMin(corrid_pos, corrid_size);
				Range1D union_cover = UnionRange1D(corrid_cover, cover_x);
				double subarea_max = range.span_y - unit_min;
				double bottom_size = GetRandFloat(unit_min, (unit_max < subarea_max ? unit_max : subarea_max));
				double separator_y = range.bottom + bottom_size;
				bool boss_in_bottom = false, boss_in_top = false;
				if (RandomRoll(0.5))
					boss_in_bottom = have_boss;
				else
					boss_in_top = have_boss;
				if (RandomRoll(0.5))
				{
					b_area = generate DungeonArea(MkRange2D(range.left, range.bottom, range.right, separator_y), union_cover, MkMinConstraintRange1D(cover_y.min), boss_in_bottom);
					t_area = generate DungeonArea(MkRange2D(range.left, separator_y, range.right, range.top), corrid_cover, MkMaxConstraintRange1D(cover_y.max), boss_in_top);
				}
				else
				{
					b_area = generate DungeonArea(MkRange2D(range.left, range.bottom, range.right, separator_y), corrid_cover, MkMinConstraintRange1D(cover_y.min), boss_in_bottom);
					t_area = generate DungeonArea(MkRange2D(range.left, separator_y, range.right, range.top), union_cover, MkMaxConstraintRange1D(cover_y.max), boss_in_top);
				}

				double corrid_bottom_left = b_area->GetContactFromTop(corrid_cover.min);
				double corrid_bottom_right = b_area->GetContactFromTop(corrid_cover.max);
				double corrid_bottom = (corrid_bottom_left < corrid_bottom_right ? corrid_bottom_left : corrid_bottom_right);
				double corrid_top_left = t_area->GetContactFromBottom(corrid_cover.min);
				double corrid_top_right = t_area->GetContactFromBottom(corrid_cover.max);
				double corrid_top = (corrid_top_left > corrid_top_right ? corrid_top_left : corrid_top_right);
				corridor = new Corridor(corrid_cover.min, corrid_bottom, corrid_cover.max, corrid_top);

				room_range = UnionRange2D(UnionRange2D(b_area->room_range, t_area->room_range), corridor->range);
			}
			GetContactFromLeft
			{
				double contact = 1e10;
				if (y <= b_area->room_range.top)
					contact = b_area->GetContactFromLeft(y);
				else if (y >= t_area->room_range.bottom)
					contact = t_area->GetContactFromLeft(y);
				return (contact <= corridor->range.left || y <= corridor->range.bottom || y >= corridor->range.top ? contact : corridor->range.left);
			}
			GetContactFromBottom
			{
				if (x >= b_area->room_range.left && x < b_area->room_range.right)
					return b_area->GetContactFromBottom(x);
				return t_area->GetContactFromBottom(x);
			}
			GetContactFromRight
			{
				double contact = -1e10;
				if (y <= b_area->room_range.top)
					contact = b_area->GetContactFromRight(y);
				else if (y >= t_area->room_range.bottom)
					contact = t_area->GetContactFromRight(y);
				return (contact >= corridor->range.right || y <= corridor->range.bottom || y >= corridor->range.top ? contact : corridor->range.right);
			}
			GetContactFromTop
			{
				if (x >= t_area->room_range.left && x < t_area->room_range.right)
					return t_area->GetContactFromTop(x);
				return b_area->GetContactFromTop(x);
			}
			DrawPart
			{
				b_area->Draw(is_padded);
				t_area->Draw(is_padded);
				corridor->Draw(is_padded);
			}
			DrawAll
			{
				b_area->DrawAll(is_padded);
				t_area->DrawAll(is_padded);
				corridor->Draw(is_padded);
			}
		}
	| vDivide{double corrid_min, double corrid_max}: DungeonArea* l_area, DungeonArea* r_area, Corridor* corridor
		{
			generator
			{
				double corrid_size = GetRandFloat(corrid_min, corrid_max);
				double corrid_pos = GetRandFloat(range.bottom + wall_min, range.top - wall_min - corrid_size);
				Range1D corrid_cover = MkRange1DFromMin(corrid_pos, corrid_size);
				Range1D union_cover = UnionRange1D(corrid_cover, cover_y);
				double subarea_max = range.span_x - unit_min;
				double left_size = GetRandFloat(unit_min, (unit_max < subarea_max ? unit_max : subarea_max));
				double separator_x = range.left + left_size;
				bool boss_in_left = false, boss_in_right = false;
				if (RandomRoll(0.5))
					boss_in_left = have_boss;
				else
					boss_in_right = have_boss;
				if (RandomRoll(0.5))
				{
					l_area = generate DungeonArea(MkRange2D(range.left, range.bottom, separator_x, range.top), MkMinConstraintRange1D(cover_x.min), union_cover, boss_in_left);
					r_area = generate DungeonArea(MkRange2D(separator_x, range.bottom, range.right, range.top), MkMaxConstraintRange1D(cover_x.max), corrid_cover, boss_in_right);
				}
				else
				{
					l_area = generate DungeonArea(MkRange2D(range.left, range.bottom, separator_x, range.top), MkMinConstraintRange1D(cover_x.min), corrid_cover, boss_in_left);
					r_area = generate DungeonArea(MkRange2D(separator_x, range.bottom, range.right, range.top), MkMaxConstraintRange1D(cover_x.max), union_cover, boss_in_right);
				}

				double corrid_left_bottom = l_area->GetContactFromRight(corrid_cover.min);
				double corrid_left_top = l_area->GetContactFromRight(corrid_cover.max);
				double corrid_left = (corrid_left_bottom < corrid_left_top ? corrid_left_bottom : corrid_left_top);
				double corrid_right_bottom = r_area->GetContactFromLeft(corrid_cover.min);
				double corrid_right_top = r_area->GetContactFromLeft(corrid_cover.max);
				double corrid_right = (corrid_right_bottom > corrid_right_top ? corrid_right_bottom : corrid_right_top);
				corridor = new Corridor(corrid_left, corrid_cover.min, corrid_right, corrid_cover.max);
				
				room_range = UnionRange2D(UnionRange2D(l_area->room_range, r_area->room_range), corridor->range);
			}
			GetContactFromLeft
			{
				if (y >= l_area->room_range.bottom && y < l_area->room_range.top)
					return l_area->GetContactFromLeft(y);
				return r_area->GetContactFromLeft(y);
			}
			GetContactFromBottom
			{
				double contact = 1e10;
				if (x <= l_area->room_range.right)
					contact = l_area->GetContactFromBottom(x);
				else if (x >= r_area->room_range.left)
					contact = r_area->GetContactFromBottom(x);
				return (contact <= corridor->range.bottom || x <= corridor->range.left || x >= corridor->range.right ? contact : corridor->range.bottom);
			}
			GetContactFromRight
			{
				if (y >= r_area->room_range.bottom && y < r_area->room_range.top)
					return r_area->GetContactFromRight(y);
				return l_area->GetContactFromRight(y);
			}
			GetContactFromTop
			{
				double contact = -1e10;
				if (x <= l_area->room_range.right)
					contact = l_area->GetContactFromTop(x);
				else if (x >= r_area->room_range.left)
					contact = r_area->GetContactFromTop(x);
				return (contact >= corridor->range.top || x <= corridor->range.left || x >= corridor->range.right ? contact : corridor->range.top);
			}
			DrawPart
			{
				l_area->Draw(is_padded);
				r_area->Draw(is_padded);
				corridor->Draw(is_padded);
			}
			DrawAll
			{
				l_area->DrawAll(is_padded);
				r_area->DrawAll(is_padded);
				corridor->Draw(is_padded);
			}
		}
	| tArea{double room_min}: Room* room
		{
			generator
			{
				room = TermRoomGen(range, cover_x, cover_y, room_min, wall_min);
				room_range = room->range;
			}
			GetContactFromLeft = room_range.left;
			GetContactFromBottom = room_range.bottom;
			GetContactFromRight = room_range.right;
			GetContactFromTop = room_range.top;
			DrawPart = room->Draw(is_padded);
			DrawAll = room->Draw(is_padded);
		}
	| bossArea{double room_min}: BossRoom* room
		{
			generator
			{
				room = BossRoomGen(range, cover_x, cover_y, room_min, wall_min);
				room_range = room->range;
			}
			GetContactFromLeft = room_range.left;
			GetContactFromBottom = room_range.bottom;
			GetContactFromRight = room_range.right;
			GetContactFromTop = room_range.top;
			DrawPart = room->Draw(is_padded);
			DrawAll = room->Draw(is_padded);
		}
};

BspDungeon* GenerateDungeon(const Range2D& whole_range, double unit_min, double unit_max, double wall_min, bool have_boss_area)
{
	return generate BspDungeon with <* BspDungeon{whole_range, unit_min, unit_max, wall_min, have_boss_area}:
		DungeonArea :=
			| hDivide{0.1 * unit_min, 0.2 * unit_min} @ {0.3}
			| vDivide{0.1 * unit_min, 0.2 * unit_min} @ {0.3}
			| tArea{0.7 * range.GetMinSpan()} @ {0.4}
			| bossArea{0.7 * range.GetMinSpan()} *>;
}

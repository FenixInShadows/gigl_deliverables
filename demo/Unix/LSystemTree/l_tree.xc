giglstart;

import "TreeSegment.h";

class Range2D;
class Vector2D;
class TreeSegment;

gigltype LTree{int n, double unit_len, double max_wid}:
{
wrapper:
	generator
	{
		root = generate TreePart(0, MkVector2D(0.0, 0.0), MkVector2D(0.0, 1.0), max_wid, 0.0);
	}

node:
	Vector2D start_pos;
	Vector2D end_pos;
	void Draw();

nonterminal:
	TreePart(int depth, const Vector2D& start, const Vector2D& dir, double bottom_w, double top_w);

rule:
	TreePart :=
	| ntTree{double branch_prob, dynamic double branch_deg}: TreePart* bottom, TreePart* right, TreePart* left, TreePart* top
		{
			generator
			{
				double mid_w = 0.5 * (bottom_w + top_w);
				bottom = generate TreePart(depth + 1, start, dir, bottom_w, mid_w);
				right = generate<branch_prob> TreePart(depth + 1, bottom->end_pos, RotateDegrees(dir, -branch_deg), mid_w, 0.0);
				left = generate<branch_prob> TreePart(depth + 1, bottom->end_pos, RotateDegrees(dir, branch_deg), mid_w, 0.0);
				top = generate TreePart(depth + 1, bottom->end_pos, dir, mid_w, top_w);
				start_pos = start;
				end_pos = top->end_pos;
			}
			Draw
			{
				bottom->Draw();
				top->Draw();
				if (right) right->Draw();
				if (left) left->Draw();
			}
		}
	| termTree: TreeSegment* seg
		{
			generator
			{
				seg = TermSegGen(depth, start, dir, bottom_w, top_w, n, unit_len);
				start_pos = seg->start;
				end_pos = seg->end;
			}
			Draw = seg->Draw();
		}
};

LTree* GenerateDetermLTree(int n, double unit_len)
{
	double max_wid = (double)(1 << n);
	return generate LTree with <* LTree{n, unit_len, max_wid}:
		TreePart := ntTree{1.0, 45.0} @ {depth < n} | termTree *>;
}

LTree* GenerateNDLTree(int n, double unit_len)
{
	double max_wid = (double)(1 << n);
	return generate LTree with <* LTree{n, unit_len, max_wid}:
		TreePart := ntTree{0.7, GetRandFloat(30.0, 60.0)} @ {depth < n ? 0.8 : 0.0} | termTree *>;
}

double ntFac(int d, int n, double w, double max_w) // better tuned probability to not terminate early (continue expanding)
{
	return d < n ? 0.5 + w/max_w : 0.0;
}

double brchFac(double w, double max_w) // better tuned probability for a branch (left or right) to exist
{
	return  2 - 3*w/max_w;
}

LTree* GenerateAdvNDLTree(int n, double unit_len)
{
	double max_wid = (double)(1 << n);
	return generate LTree with <* LTree{n, unit_len, max_wid}:
		TreePart := ntTree{brchFac(top_w, max_wid), GetRandFloat(30.0, 60.0)} @ {ntFac(depth, n, bottom_w, max_wid)} | termTree *>;
}

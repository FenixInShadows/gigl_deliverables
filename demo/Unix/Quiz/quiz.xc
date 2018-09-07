giglstart;

gigltype MathQuiz:
{
wrapper:
	generator { root = generate Expr(0); }
	string Translate() { return root->Translate(0); }

node:
	string Translate(int preced);
	int Evaluate();

nonterminal:
	Expr(int depth);

rule:
	Expr :=
	| mulExpr: Expr* lexpr, Expr* rexpr
		{
			generator { lexpr = generate Expr(depth + 1);
				rexpr = generate Expr(depth + 1); }
			Translate = lexpr->Translate(1) + " * " + rexpr->Translate(1);
			Evaluate = lexpr->Evaluate() * rexpr->Evaluate();
		}
	| addExpr: Expr* lexpr, Expr* rexpr
		{
			generator { lexpr = generate Expr(depth + 1);
				rexpr = generate Expr(depth + 1); }
			Translate = ( preced > 0 ?
				"( " + lexpr->Translate(0) + " + " + rexpr->Translate(0) + " )" :
				lexpr->Translate(0) + " + " + rexpr->Translate(0) );
			Evaluate = lexpr->Evaluate() + rexpr->Evaluate();
		}
	| intExpr{int min_int, int max_int}: int val
		{
			generator { val = GetRandInt(min_int, max_int); }
			Translate = IntToStr(val);
			Evaluate = val;
		}
};

void GenerateQuizListIncDiffic(MathQuiz** list)
{
	int diffic = 0;
	giglconfig quiz_config = <* MathQuiz:
		Expr :=
		| mulExpr @ {(depth < diffic ? 0.3 : 0.0)}
		| addExpr @ {(depth < diffic ? 0.7 : 0.0)}
		| intExpr{diffic * 5, diffic * 10 + 10} @ {depth >= diffic} *>;
	for (; diffic < 5; diffic++)
		list[diffic] = generate MathQuiz with quiz_config;
}

giglstart;

gigltype Greeting:
{
node:
	string Print();

nonterminal:
	Message;
	Timing;
	Object;

rule:
	Message :=
	| message: Timing* t, Object* o
		{
			Print = t->Print() + ", " + o->Print() + "!";
		}
	
	Timing :=
	| morning:
		{
			Print = "Good morning";
		}
	| afternoon:
		{
			Print = "Good afternoon";
		}

	Object :=
	| world:
		{
			Print = "World";
		}
	| mom:
		{
			Print = "Mom";
		}
};

Greeting* GenerateGreeting()
{
	return generate Greeting with <* Greeting:
		Message := message,
		Timing := morning @ {0.7} | afternoon @ {0.3},
		Object := world | mom *>;
}

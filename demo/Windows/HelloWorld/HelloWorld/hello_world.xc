/*
	Welcome to GIGL!
	Hope you'll be having fun.
*/
giglstart;

gigltype Greeting: // don't forget the ":"
{
node:
	string Print();

nonterminal:
	Message;

rule:
	Message :=
	| helloWorld:
		{ Print = "Hello World!"; }
	| helloMom:
		{ Print = "Hello Mom!"; }
};

Greeting* GenerateGreeting()
{
	return generate Greeting with <* Greeting:
		Message := helloWorld | helloMom *>;
}

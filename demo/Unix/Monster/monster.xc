giglstart;

gigltype DungeonMonster:
{
node:
	int damage;

nonterminal:
	Monster;
	Weapon;

rule:
	Monster :=
	| weakMonster:
		{ damage = GetRandInt(2, 5); }
	| strongMonster: Weapon* weapon
		{ damage = GetRandInt(6, 9) + weapon->damage; }

	Weapon :=
	| clubWeapon:
		{ damage = GetRandInt(1, 3); }
	| flailWeapon:
		{ damage = GetRandInt(11, 19); }
};

void GenerateEasyRoomMonsters(DungeonMonster** list)
{
	for(int i = 0; i < 10; i++)
		list[i] = generate DungeonMonster with <* DungeonMonster:
			Monster := weakMonster @ {0.8} | strongMonster @ {0.2},
			Weapon := clubWeapon @ {1.0} *>;
}

void GenerateHardRoomMonsters(DungeonMonster** list)
{
	for(int i = 0; i < 10; i++)
		list[i] = generate DungeonMonster with <* DungeonMonster:
			Monster := weakMonster @ {0.6} | strongMonster @ {0.4},
			Weapon := clubWeapon @ {0.7} | flailWeapon @ {0.3} *>;
}

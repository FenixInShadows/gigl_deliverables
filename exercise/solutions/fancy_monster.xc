giglstart;

gigltype FancyMonster:
{
node:
	int health;
	int resist;
	int damage;
	int range;
	int experience;
	string Print();

nonterminal:
	Monster;
	Armor;
	Weapon;

rule:
	Monster :=
	| justMonster{int min_health, int max_health}: Armor* armor, Weapon* weapon
		{
			health = GetRandInt(min_health, max_health);
			resist = armor->resist;
			damage = weapon->damage;
			range = weapon->range;
			experience = health * resist * damage * range;
			Print = armor->Print() + "; " + weapon->Print() +
				"; Health: " + IntToStr(health) +
				"; Resist: " + IntToStr(resist) +
				"; Damage: " + IntToStr(damage) +
				"; Range: " + IntToStr(range) +
				"; Exp: " + IntToStr(experience) + ".";
		}

	Armor :=
	| clothArmor:
		{
			resist = GetRandInt(5, 9);
			Print = "Armor: Cloth Armor";
		}
	| chainMail:
		{
			resist = GetRandInt(16, 20);
			Print = "Armor: Chain Mail";
		}
	| noArmor:
		{
			resist = 1;
			Print = "Armor: N/A";
		}

	Weapon :=
	| clubWeapon:
		{ 
			damage = GetRandInt(2, 5);
			range = 1;
			Print = "Weapon: Club";
		}
	| flailWeapon:
		{ 
			damage = GetRandInt(8, 12);
			range = 2;
			Print = "Weapon: Flail";
		}	
	| swordWeapon:
		{
			damage = GetRandInt(21, 30);
			range = 1;
			Print = "Weapon: Sword";
		}
	| bowWeapon:
		{
			damage = GetRandInt(6, 15);
			range = GetRandInt(4, 5);
			Print = "Weapon: Bow";
		}
	| noWeapon:
		{
			damage = GetRandInt(1, 3);
			range = 1;
			Print = "Weapon: N/A";
		}
};

FancyMonster* GenerateFancyMonster(int level)
{
	return generate FancyMonster with <* FancyMonster:
		Monster := justMonster{30 + 20*level, 50 + 30*level},
		Armor := clothArmor @ {0.2 + level * 0.1} | chainMail @ {0.1 + level * 0.1} | noArmor,
		Weapon := clubWeapon @ {0.2} | flailWeapon @ {0.1 + level * 0.1} | swordWeapon @ {level * 0.1} | bowWeapon @ {level * 0.2} | noWeapon *>;
}

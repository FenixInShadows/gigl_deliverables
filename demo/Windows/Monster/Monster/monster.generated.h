
#include "GiglDefaultInclude.h"



class DungeonMonster;

class DungeonMonster__Node;

class DungeonMonster__Monster;

class DungeonMonster__Weapon;

class DungeonMonster__weakMonster;

class DungeonMonster__strongMonster;

class DungeonMonster__clubWeapon;

class DungeonMonster__flailWeapon;

class DungeonMonster {
public:
  DungeonMonster(const GiglConfig  & input__config);
  DungeonMonster(GiglConfig  && input__config);
  DungeonMonster(DungeonMonster__Node  * input__root);
  DungeonMonster(const GiglConfig  & input__config, DungeonMonster__Node  * input__root);
  DungeonMonster(GiglConfig  && input__config, DungeonMonster__Node  * input__root);
  ~DungeonMonster();
  GiglConfig config;
  DungeonMonster__Node  *root;
  signed int damage;
  DungeonMonster__Monster  *Generate__Monster(void);
  DungeonMonster__weakMonster  *Generate__weakMonster(void);
  DungeonMonster__strongMonster  *Generate__strongMonster(void);
  DungeonMonster__Weapon  *Generate__Weapon(void);
  DungeonMonster__clubWeapon  *Generate__clubWeapon(void);
  DungeonMonster__flailWeapon  *Generate__flailWeapon(void);
  

};
class DungeonMonster__Node {
public:
  DungeonMonster__Node(DungeonMonster  * input__item);
  DungeonMonster__Node();
  virtual ~DungeonMonster__Node();
  DungeonMonster  *item;
  signed int damage;
  

};
class DungeonMonster__Monster : public DungeonMonster__Node {
public:
  DungeonMonster__Monster(DungeonMonster  * input__item);
  DungeonMonster__Monster();
  

};
class DungeonMonster__Weapon : public DungeonMonster__Node {
public:
  DungeonMonster__Weapon(DungeonMonster  * input__item);
  DungeonMonster__Weapon();
  

};
class DungeonMonster__weakMonster : public DungeonMonster__Monster {
public:
  DungeonMonster__weakMonster();
  DungeonMonster__weakMonster(DungeonMonster  * input__item);
  ~DungeonMonster__weakMonster();
  

};
class DungeonMonster__strongMonster : public DungeonMonster__Monster {
public:
  DungeonMonster__strongMonster();
  DungeonMonster__strongMonster(DungeonMonster  * input__item, DungeonMonster__Weapon  * input__weapon);
  ~DungeonMonster__strongMonster();
  DungeonMonster__Weapon  *weapon;
  

};
class DungeonMonster__clubWeapon : public DungeonMonster__Weapon {
public:
  DungeonMonster__clubWeapon();
  DungeonMonster__clubWeapon(DungeonMonster  * input__item);
  ~DungeonMonster__clubWeapon();
  

};
class DungeonMonster__flailWeapon : public DungeonMonster__Weapon {
public:
  DungeonMonster__flailWeapon();
  DungeonMonster__flailWeapon(DungeonMonster  * input__item);
  ~DungeonMonster__flailWeapon();
  

};
DungeonMonster::DungeonMonster(const GiglConfig  & input__config) : config((input__config)), root(((Generate__Monster)()))
{

  ((damage) = ((root)->damage));
}

DungeonMonster::DungeonMonster(GiglConfig  && input__config) : config(((move)((input__config)))), root(((Generate__Monster)()))
{

  ((damage) = ((root)->damage));
}

DungeonMonster::DungeonMonster(DungeonMonster__Node  * input__root) : config(), root((input__root))
{

  ((damage) = ((root)->damage));
}

DungeonMonster::DungeonMonster(const GiglConfig  & input__config, DungeonMonster__Node  * input__root) : config((input__config)), root((input__root))
{

  ((damage) = ((root)->damage));
}

DungeonMonster::DungeonMonster(GiglConfig  && input__config, DungeonMonster__Node  * input__root) : config(((move)((input__config)))), root((input__root))
{

  ((damage) = ((root)->damage));
}

DungeonMonster::~DungeonMonster()
{

  if ((root))
  {
    delete (root);
  } else {
    
  }
}




DungeonMonster__Monster  *DungeonMonster::Generate__Monster(void)
{

  double probs[2] = {(((double (*)(const GiglConfig  & ))(((config).funcs)[0]))((config))), (((double (*)(const GiglConfig  & ))(((config).funcs)[1]))((config)))};
  ((NonegativeProbs)((probs), 2));
  
  ((NormalizeProbs)((probs), 2));
  signed int choice = ((GetRandChoiceFromProbs)((probs), 2));
  switch ((choice))
  {
    case 0:
      return ((Generate__weakMonster)());
    
    case 1:
      return ((Generate__strongMonster)());
    
  }
  return 0;
}

DungeonMonster__weakMonster  *DungeonMonster::Generate__weakMonster(void)
{

  DungeonMonster__weakMonster  *node = (new DungeonMonster__weakMonster);
  (((node)->item) = (this));
  (((node)->damage) = ((GetRandInt)(2, 5)));
  return (node);
}

DungeonMonster__strongMonster  *DungeonMonster::Generate__strongMonster(void)
{

  DungeonMonster__strongMonster  *node = (new DungeonMonster__strongMonster);
  (((node)->item) = (this));
  (((node)->weapon) = ((Generate__Weapon)()));
  
  (((node)->damage) = (((GetRandInt)(6, 9)) + (((node)->weapon)->damage)));
  return (node);
}

DungeonMonster__Weapon  *DungeonMonster::Generate__Weapon(void)
{

  double probs[2] = {(((double (*)(const GiglConfig  & ))(((config).funcs)[2]))((config))), (((double (*)(const GiglConfig  & ))(((config).funcs)[3]))((config)))};
  ((NonegativeProbs)((probs), 2));
  
  ((NormalizeProbs)((probs), 2));
  signed int choice = ((GetRandChoiceFromProbs)((probs), 2));
  switch ((choice))
  {
    case 0:
      return ((Generate__clubWeapon)());
    
    case 1:
      return ((Generate__flailWeapon)());
    
  }
  return 0;
}

DungeonMonster__clubWeapon  *DungeonMonster::Generate__clubWeapon(void)
{

  DungeonMonster__clubWeapon  *node = (new DungeonMonster__clubWeapon);
  (((node)->item) = (this));
  (((node)->damage) = ((GetRandInt)(1, 3)));
  return (node);
}

DungeonMonster__flailWeapon  *DungeonMonster::Generate__flailWeapon(void)
{

  DungeonMonster__flailWeapon  *node = (new DungeonMonster__flailWeapon);
  (((node)->item) = (this));
  (((node)->damage) = ((GetRandInt)(11, 19)));
  return (node);
}



DungeonMonster__Node::DungeonMonster__Node(DungeonMonster  * input__item) : item((input__item))
{

  
}

DungeonMonster__Node::DungeonMonster__Node()
{

  
}

DungeonMonster__Node::~DungeonMonster__Node()
{

  
}





DungeonMonster__Monster::DungeonMonster__Monster(DungeonMonster  * input__item) : DungeonMonster__Node((input__item))
{

  
}

DungeonMonster__Monster::DungeonMonster__Monster()
{

  
}



DungeonMonster__Weapon::DungeonMonster__Weapon(DungeonMonster  * input__item) : DungeonMonster__Node((input__item))
{

  
}

DungeonMonster__Weapon::DungeonMonster__Weapon()
{

  
}



DungeonMonster__weakMonster::DungeonMonster__weakMonster()
{

  
}

DungeonMonster__weakMonster::DungeonMonster__weakMonster(DungeonMonster  * input__item) : DungeonMonster__Monster((input__item))
{

  ((damage) = ((GetRandInt)(2, 5)));
}

DungeonMonster__weakMonster::~DungeonMonster__weakMonster()
{

  
}



DungeonMonster__strongMonster::DungeonMonster__strongMonster()
{

  
}

DungeonMonster__strongMonster::DungeonMonster__strongMonster(DungeonMonster  * input__item, DungeonMonster__Weapon  * input__weapon) : DungeonMonster__Monster((input__item)), weapon((input__weapon))
{

  
  ((damage) = (((GetRandInt)(6, 9)) + ((weapon)->damage)));
}

DungeonMonster__strongMonster::~DungeonMonster__strongMonster()
{

  
  {
    if ((weapon))
    {
      delete (weapon);
    } else {
      
    }
  }
}




DungeonMonster__clubWeapon::DungeonMonster__clubWeapon()
{

  
}

DungeonMonster__clubWeapon::DungeonMonster__clubWeapon(DungeonMonster  * input__item) : DungeonMonster__Weapon((input__item))
{

  ((damage) = ((GetRandInt)(1, 3)));
}

DungeonMonster__clubWeapon::~DungeonMonster__clubWeapon()
{

  
}



DungeonMonster__flailWeapon::DungeonMonster__flailWeapon()
{

  
}

DungeonMonster__flailWeapon::DungeonMonster__flailWeapon(DungeonMonster  * input__item) : DungeonMonster__Weapon((input__item))
{

  ((damage) = ((GetRandInt)(11, 19)));
}

DungeonMonster__flailWeapon::~DungeonMonster__flailWeapon()
{

  
}




double DungeonMonster__ConfigLambda__31__50(const GiglConfig  & config);
double DungeonMonster__ConfigLambda__31__74(const GiglConfig  & config);
double DungeonMonster__ConfigLambda__32__48(const GiglConfig  & config);
double DungeonMonster__1__ConfigLambda__32__24(const GiglConfig  & config);
double DungeonMonster__ConfigLambda__31__50(const GiglConfig  & config)
{

  return 0.8;
}
double DungeonMonster__ConfigLambda__31__74(const GiglConfig  & config)
{

  return 0.2;
}
double DungeonMonster__ConfigLambda__32__48(const GiglConfig  & config)
{

  return 1.0;
}
double DungeonMonster__1__ConfigLambda__32__24(const GiglConfig  & config)
{

  return 0.0;
}

void GenerateEasyRoomMonsters(DungeonMonster  * * list)
{

  {
    for (signed int i = 0; ((i) < 10); ((i)++))
    {
      (((list)[(i)]) = (new DungeonMonster((GiglConfig(0, 4, 0, (SizeVec{}), (VarPtrVec{}), (IndexVec{0, 1, 2, 3}), (FuncPtrVec{((FuncPtr)(&(DungeonMonster__ConfigLambda__31__50))), ((FuncPtr)(&(DungeonMonster__ConfigLambda__31__74))), ((FuncPtr)(&(DungeonMonster__ConfigLambda__32__48))), ((FuncPtr)(&(DungeonMonster__1__ConfigLambda__32__24)))}))))));
    }
  }
}
double DungeonMonster__ConfigLambda__39__50(const GiglConfig  & config);
double DungeonMonster__ConfigLambda__39__74(const GiglConfig  & config);
double DungeonMonster__ConfigLambda__40__48(const GiglConfig  & config);
double DungeonMonster__ConfigLambda__40__70(const GiglConfig  & config);
double DungeonMonster__ConfigLambda__39__50(const GiglConfig  & config)
{

  return 0.6;
}
double DungeonMonster__ConfigLambda__39__74(const GiglConfig  & config)
{

  return 0.4;
}
double DungeonMonster__ConfigLambda__40__48(const GiglConfig  & config)
{

  return 0.7;
}
double DungeonMonster__ConfigLambda__40__70(const GiglConfig  & config)
{

  return 0.3;
}

void GenerateHardRoomMonsters(DungeonMonster  * * list)
{

  {
    for (signed int i = 0; ((i) < 10); ((i)++))
    {
      (((list)[(i)]) = (new DungeonMonster((GiglConfig(0, 4, 0, (SizeVec{}), (VarPtrVec{}), (IndexVec{0, 1, 2, 3}), (FuncPtrVec{((FuncPtr)(&(DungeonMonster__ConfigLambda__39__50))), ((FuncPtr)(&(DungeonMonster__ConfigLambda__39__74))), ((FuncPtr)(&(DungeonMonster__ConfigLambda__40__48))), ((FuncPtr)(&(DungeonMonster__ConfigLambda__40__70)))}))))));
    }
  }
}


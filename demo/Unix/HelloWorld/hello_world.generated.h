
#include "GiglDefaultInclude.h"



class Greeting;

class Greeting__Node;

class Greeting__Message;

class Greeting__helloWorld;

class Greeting__helloMom;

class Greeting {
public:
  Greeting(const GiglConfig  & input__config);
  Greeting(GiglConfig  && input__config);
  Greeting(Greeting__Node  * input__root);
  Greeting(const GiglConfig  & input__config, Greeting__Node  * input__root);
  Greeting(GiglConfig  && input__config, Greeting__Node  * input__root);
  ~Greeting();
  GiglConfig config;
  Greeting__Node  *root;
  string Print();
  Greeting__Message  *Generate__Message(void);
  Greeting__helloWorld  *Generate__helloWorld(void);
  Greeting__helloMom  *Generate__helloMom(void);
  

};
class Greeting__Node {
public:
  Greeting__Node(Greeting  * input__item);
  Greeting__Node();
  virtual ~Greeting__Node();
  Greeting  *item;
  string virtual Print() = 0;
  

};
class Greeting__Message : public Greeting__Node {
public:
  Greeting__Message(Greeting  * input__item);
  Greeting__Message();
  

};
class Greeting__helloWorld : public Greeting__Message {
public:
  Greeting__helloWorld();
  Greeting__helloWorld(Greeting  * input__item);
  ~Greeting__helloWorld();
  string Print();
  

};
class Greeting__helloMom : public Greeting__Message {
public:
  Greeting__helloMom();
  Greeting__helloMom(Greeting  * input__item);
  ~Greeting__helloMom();
  string Print();
  

};
Greeting::Greeting(const GiglConfig  & input__config) : config((input__config)), root(((Generate__Message)()))
{

  
}

Greeting::Greeting(GiglConfig  && input__config) : config(((move)((input__config)))), root(((Generate__Message)()))
{

  
}

Greeting::Greeting(Greeting__Node  * input__root) : config(), root((input__root))
{

  
}

Greeting::Greeting(const GiglConfig  & input__config, Greeting__Node  * input__root) : config((input__config)), root((input__root))
{

  
}

Greeting::Greeting(GiglConfig  && input__config, Greeting__Node  * input__root) : config(((move)((input__config)))), root((input__root))
{

  
}

Greeting::~Greeting()
{

  if ((root))
  {
    delete (root);
  } else {
    
  }
}



string Greeting::Print()
{

  return (((root)->Print)());
}

Greeting__Message  *Greeting::Generate__Message(void)
{

  double probs[2] = {(((double (*)(const GiglConfig  & ))(((config).funcs)[0]))((config))), (((double (*)(const GiglConfig  & ))(((config).funcs)[1]))((config)))};
  ((NonegativeProbs)((probs), 2));
  
  ((NormalizeProbs)((probs), 2));
  signed int choice = ((GetRandChoiceFromProbs)((probs), 2));
  switch ((choice))
  {
    case 0:
      return ((Generate__helloWorld)());
    
    case 1:
      return ((Generate__helloMom)());
    
  }
  return 0;
}

Greeting__helloWorld  *Greeting::Generate__helloWorld(void)
{

  Greeting__helloWorld  *node = (new Greeting__helloWorld);
  (((node)->item) = (this));
  
  return (node);
}

Greeting__helloMom  *Greeting::Generate__helloMom(void)
{

  Greeting__helloMom  *node = (new Greeting__helloMom);
  (((node)->item) = (this));
  
  return (node);
}



Greeting__Node::Greeting__Node(Greeting  * input__item) : item((input__item))
{

  
}

Greeting__Node::Greeting__Node()
{

  
}

Greeting__Node::~Greeting__Node()
{

  
}





Greeting__Message::Greeting__Message(Greeting  * input__item) : Greeting__Node((input__item))
{

  
}

Greeting__Message::Greeting__Message()
{

  
}



Greeting__helloWorld::Greeting__helloWorld()
{

  
}

Greeting__helloWorld::Greeting__helloWorld(Greeting  * input__item) : Greeting__Message((input__item))
{

  
}

Greeting__helloWorld::~Greeting__helloWorld()
{

  
}

string Greeting__helloWorld::Print()
{

  return "Hello World!";
}



Greeting__helloMom::Greeting__helloMom()
{

  
}

Greeting__helloMom::Greeting__helloMom(Greeting  * input__item) : Greeting__Message((input__item))
{

  
}

Greeting__helloMom::~Greeting__helloMom()
{

  
}

string Greeting__helloMom::Print()
{

  return "Hello Mom!";
}




double Greeting__ConfigLambda__22__23(const GiglConfig  & config);
double Greeting__ConfigLambda__22__34(const GiglConfig  & config);
double Greeting__ConfigLambda__22__23(const GiglConfig  & config)
{

  return ((1.0 - 0.0) / 2.0);
}
double Greeting__ConfigLambda__22__34(const GiglConfig  & config)
{

  return ((1.0 - 0.0) / 2.0);
}

Greeting  *GenerateGreeting()
{

  {
    return (new Greeting((GiglConfig(0, 2, 0, (SizeVec{}), (VarPtrVec{}), (IndexVec{0, 1}), (FuncPtrVec{((FuncPtr)(&(Greeting__ConfigLambda__22__23))), ((FuncPtr)(&(Greeting__ConfigLambda__22__34)))})))));
  }
}



#include "GiglDefaultInclude.h"



class MathQuiz;

class MathQuiz__Node;

class MathQuiz__Expr;

class MathQuiz__mulExpr;

class MathQuiz__addExpr;

class MathQuiz__intExpr;

class MathQuiz {
public:
  MathQuiz(const GiglConfig  & input__config);
  MathQuiz(GiglConfig  && input__config);
  MathQuiz(MathQuiz__Node  * input__root);
  MathQuiz(const GiglConfig  & input__config, MathQuiz__Node  * input__root);
  MathQuiz(GiglConfig  && input__config, MathQuiz__Node  * input__root);
  ~MathQuiz();
  GiglConfig config;
  MathQuiz__Node  *root;
  string Translate();
  string Translate(signed int  preced);
  signed int Evaluate();
  MathQuiz__Expr  *Generate__Expr(signed int  depth);
  MathQuiz__mulExpr  *Generate__mulExpr(signed int  depth);
  MathQuiz__addExpr  *Generate__addExpr(signed int  depth);
  MathQuiz__intExpr  *Generate__intExpr(signed int  depth);
  

};
class MathQuiz__Node {
public:
  MathQuiz__Node(MathQuiz  * input__item);
  MathQuiz__Node();
  virtual ~MathQuiz__Node();
  MathQuiz  *item;
  string virtual Translate(signed int  preced) = 0;
  signed int virtual Evaluate() = 0;
  

};
class MathQuiz__Expr : public MathQuiz__Node {
public:
  MathQuiz__Expr(MathQuiz  * input__item);
  MathQuiz__Expr();
  

};
class MathQuiz__mulExpr : public MathQuiz__Expr {
public:
  MathQuiz__mulExpr();
  MathQuiz__mulExpr(MathQuiz  * input__item, MathQuiz__Expr  * input__lexpr, MathQuiz__Expr  * input__rexpr);
  ~MathQuiz__mulExpr();
  MathQuiz__Expr  *lexpr;
  MathQuiz__Expr  *rexpr;
  string Translate(signed int  preced);
  signed int Evaluate();
  

};
class MathQuiz__addExpr : public MathQuiz__Expr {
public:
  MathQuiz__addExpr();
  MathQuiz__addExpr(MathQuiz  * input__item, MathQuiz__Expr  * input__lexpr, MathQuiz__Expr  * input__rexpr);
  ~MathQuiz__addExpr();
  MathQuiz__Expr  *lexpr;
  MathQuiz__Expr  *rexpr;
  string Translate(signed int  preced);
  signed int Evaluate();
  

};
class MathQuiz__intExpr : public MathQuiz__Expr {
public:
  MathQuiz__intExpr();
  MathQuiz__intExpr(MathQuiz  * input__item, signed int  input__val);
  ~MathQuiz__intExpr();
  signed int min_int;
  signed int max_int;
  signed int val;
  string Translate(signed int  preced);
  signed int Evaluate();
  

};
MathQuiz::MathQuiz(const GiglConfig  & input__config) : config((input__config))
{

  {
    ((root) = ((Generate__Expr)(0)));
  }
}

MathQuiz::MathQuiz(GiglConfig  && input__config) : config(((move)((input__config))))
{

  {
    ((root) = ((Generate__Expr)(0)));
  }
}

MathQuiz::MathQuiz(MathQuiz__Node  * input__root) : config(), root((input__root))
{

  
}

MathQuiz::MathQuiz(const GiglConfig  & input__config, MathQuiz__Node  * input__root) : config((input__config)), root((input__root))
{

  
}

MathQuiz::MathQuiz(GiglConfig  && input__config, MathQuiz__Node  * input__root) : config(((move)((input__config)))), root((input__root))
{

  
}

MathQuiz::~MathQuiz()
{

  if ((root))
  {
    delete (root);
  } else {
    
  }
}



string MathQuiz::Translate()
{

  {
    return (((root)->Translate)(0));
  }
}

string MathQuiz::Translate(signed int  preced)
{

  return (((root)->Translate)((preced)));
}

signed int MathQuiz::Evaluate()
{

  return (((root)->Evaluate)());
}

MathQuiz__Expr  *MathQuiz::Generate__Expr(signed int  depth)
{

  double probs[3] = {(((double (*)(const GiglConfig  & , signed int  ))(((config).funcs)[0]))((config), (depth))), (((double (*)(const GiglConfig  & , signed int  ))(((config).funcs)[1]))((config), (depth))), (((double (*)(const GiglConfig  & , signed int  ))(((config).funcs)[2]))((config), (depth)))};
  ((NonegativeProbs)((probs), 3));
  
  ((NormalizeProbs)((probs), 3));
  signed int choice = ((GetRandChoiceFromProbs)((probs), 3));
  switch ((choice))
  {
    case 0:
      return ((Generate__mulExpr)((depth)));
    
    case 1:
      return ((Generate__addExpr)((depth)));
    
    case 2:
      return ((Generate__intExpr)((depth)));
    
  }
  return 0;
}

MathQuiz__mulExpr  *MathQuiz::Generate__mulExpr(signed int  depth)
{

  MathQuiz__mulExpr  *node = (new MathQuiz__mulExpr);
  (((node)->item) = (this));
  
  
  {
    (((node)->lexpr) = ((Generate__Expr)(((depth) + 1))));
    (((node)->rexpr) = ((Generate__Expr)(((depth) + 1))));
  }
  return (node);
}

MathQuiz__addExpr  *MathQuiz::Generate__addExpr(signed int  depth)
{

  MathQuiz__addExpr  *node = (new MathQuiz__addExpr);
  (((node)->item) = (this));
  
  
  {
    (((node)->lexpr) = ((Generate__Expr)(((depth) + 1))));
    (((node)->rexpr) = ((Generate__Expr)(((depth) + 1))));
  }
  return (node);
}

MathQuiz__intExpr  *MathQuiz::Generate__intExpr(signed int  depth)
{

  MathQuiz__intExpr  *node = (new MathQuiz__intExpr);
  (((node)->item) = (this));
  (((node)->min_int) = (((signed int (*)(const GiglConfig  & , signed int  ))(((config).funcs)[3]))((config), (depth))));
  (((node)->max_int) = (((signed int (*)(const GiglConfig  & , signed int  ))(((config).funcs)[4]))((config), (depth))));
  
  {
    (((node)->val) = ((GetRandInt)(((node)->min_int), ((node)->max_int))));
  }
  return (node);
}



MathQuiz__Node::MathQuiz__Node(MathQuiz  * input__item) : item((input__item))
{

  
}

MathQuiz__Node::MathQuiz__Node()
{

  
}

MathQuiz__Node::~MathQuiz__Node()
{

  
}






MathQuiz__Expr::MathQuiz__Expr(MathQuiz  * input__item) : MathQuiz__Node((input__item))
{

  
}

MathQuiz__Expr::MathQuiz__Expr()
{

  
}



MathQuiz__mulExpr::MathQuiz__mulExpr()
{

  
}

MathQuiz__mulExpr::MathQuiz__mulExpr(MathQuiz  * input__item, MathQuiz__Expr  * input__lexpr, MathQuiz__Expr  * input__rexpr) : MathQuiz__Expr((input__item)), lexpr((input__lexpr)), rexpr((input__rexpr))
{

  
  
  
}

MathQuiz__mulExpr::~MathQuiz__mulExpr()
{

  
  {
    if ((lexpr))
    {
      delete (lexpr);
    } else {
      
    }
  }
  {
    if ((rexpr))
    {
      delete (rexpr);
    } else {
      
    }
  }
}



string MathQuiz__mulExpr::Translate(signed int  preced)
{

  return (((((lexpr)->Translate)(1)) + " * ") + (((rexpr)->Translate)(1)));
}

signed int MathQuiz__mulExpr::Evaluate()
{

  return ((((lexpr)->Evaluate)()) * (((rexpr)->Evaluate)()));
}



MathQuiz__addExpr::MathQuiz__addExpr()
{

  
}

MathQuiz__addExpr::MathQuiz__addExpr(MathQuiz  * input__item, MathQuiz__Expr  * input__lexpr, MathQuiz__Expr  * input__rexpr) : MathQuiz__Expr((input__item)), lexpr((input__lexpr)), rexpr((input__rexpr))
{

  
  
  
}

MathQuiz__addExpr::~MathQuiz__addExpr()
{

  
  {
    if ((lexpr))
    {
      delete (lexpr);
    } else {
      
    }
  }
  {
    if ((rexpr))
    {
      delete (rexpr);
    } else {
      
    }
  }
}



string MathQuiz__addExpr::Translate(signed int  preced)
{

  return ((((preced) > 0) ? (((("( " + (((lexpr)->Translate)(0))) + " + ") + (((rexpr)->Translate)(0))) + " )") : (((((lexpr)->Translate)(0)) + " + ") + (((rexpr)->Translate)(0)))));
}

signed int MathQuiz__addExpr::Evaluate()
{

  return ((((lexpr)->Evaluate)()) + (((rexpr)->Evaluate)()));
}



MathQuiz__intExpr::MathQuiz__intExpr()
{

  
}

MathQuiz__intExpr::MathQuiz__intExpr(MathQuiz  * input__item, signed int  input__val) : MathQuiz__Expr((input__item)), min_int(), max_int(), val((input__val))
{

  
  
}

MathQuiz__intExpr::~MathQuiz__intExpr()
{

  
  {
    
  }
}




string MathQuiz__intExpr::Translate(signed int  preced)
{

  return ((IntToStr)((val)));
}

signed int MathQuiz__intExpr::Evaluate()
{

  return (val);
}




double MathQuiz__ConfigLambda__47__15(const GiglConfig  & config, signed int  depth);
double MathQuiz__ConfigLambda__48__15(const GiglConfig  & config, signed int  depth);
signed int MathQuiz__ConfigLambda__49__12(const GiglConfig  & config, signed int  depth);
signed int MathQuiz__ConfigLambda__49__24(const GiglConfig  & config, signed int  depth);
double MathQuiz__ConfigLambda__49__45(const GiglConfig  & config, signed int  depth);
double MathQuiz__ConfigLambda__47__15(const GiglConfig  & config, signed int  depth)
{

  return ((((depth) < (*(*((signed int * *)(((config).vars)[0]))))) ? 0.3 : 0.0));
}
double MathQuiz__ConfigLambda__48__15(const GiglConfig  & config, signed int  depth)
{

  return ((((depth) < (*(*((signed int * *)(((config).vars)[1]))))) ? 0.7 : 0.0));
}
signed int MathQuiz__ConfigLambda__49__12(const GiglConfig  & config, signed int  depth)
{

  return ((*(*((signed int * *)(((config).vars)[2])))) * 5);
}
signed int MathQuiz__ConfigLambda__49__24(const GiglConfig  & config, signed int  depth)
{

  return (((*(*((signed int * *)(((config).vars)[3])))) * 10) + 10);
}
double MathQuiz__ConfigLambda__49__45(const GiglConfig  & config, signed int  depth)
{

  return ((depth) >= (*(*((signed int * *)(((config).vars)[4])))));
}

void GenerateQuizListIncDiffic(MathQuiz  * * list)
{

  {
    signed int diffic = 0;
    GiglConfig quiz_config = (GiglConfig(5, 5, ((sizeof(signed int *)) + ((sizeof(signed int *)) + ((sizeof(signed int *)) + ((sizeof(signed int *)) + (sizeof(signed int *)))))), (SizeVec{(sizeof(signed int *)), (sizeof(signed int *)), (sizeof(signed int *)), (sizeof(signed int *)), (sizeof(signed int *))}), (VarPtrVec{((VarPtr)(&((*((signed int * *)((malloc)((sizeof(signed int *)))))) = (&(diffic))))), ((VarPtr)(&((*((signed int * *)((malloc)((sizeof(signed int *)))))) = (&(diffic))))), ((VarPtr)(&((*((signed int * *)((malloc)((sizeof(signed int *)))))) = (&(diffic))))), ((VarPtr)(&((*((signed int * *)((malloc)((sizeof(signed int *)))))) = (&(diffic))))), ((VarPtr)(&((*((signed int * *)((malloc)((sizeof(signed int *)))))) = (&(diffic)))))}), (IndexVec{0, 1, 3, 4, 2}), (FuncPtrVec{((FuncPtr)(&(MathQuiz__ConfigLambda__47__15))), ((FuncPtr)(&(MathQuiz__ConfigLambda__48__15))), ((FuncPtr)(&(MathQuiz__ConfigLambda__49__12))), ((FuncPtr)(&(MathQuiz__ConfigLambda__49__24))), ((FuncPtr)(&(MathQuiz__ConfigLambda__49__45)))})));
    for(; ((diffic) < 5); ((diffic)++))
    {
      (((list)[(diffic)]) = (new MathQuiz((quiz_config))));
    }
  }
}



#include "GiglDefaultInclude.h"


#include "TreeSegment.h"


class Range2D;

class Vector2D;

class TreeSegment;


class LTree;

class LTree__Node;

class LTree__TreePart;

class LTree__ntTree;

class LTree__termTree;

class LTree {
public:
  LTree(const GiglConfig  & input__config);
  LTree(GiglConfig  && input__config);
  LTree(LTree__Node  * input__root);
  LTree(const GiglConfig  & input__config, LTree__Node  * input__root);
  LTree(GiglConfig  && input__config, LTree__Node  * input__root);
  ~LTree();
  GiglConfig config;
  signed int n;
  double unit_len;
  double max_wid;
  LTree__Node  *root;
  Vector2D start_pos;
  Vector2D end_pos;
  void Draw();
  LTree__TreePart  *Generate__TreePart(signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
  LTree__ntTree  *Generate__ntTree(signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
  LTree__termTree  *Generate__termTree(signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
  

};
class LTree__Node {
public:
  LTree__Node(LTree  * input__item);
  LTree__Node();
  virtual ~LTree__Node();
  LTree  *item;
  Vector2D start_pos;
  Vector2D end_pos;
  void virtual Draw() = 0;
  

};
class LTree__TreePart : public LTree__Node {
public:
  LTree__TreePart(LTree  * input__item);
  LTree__TreePart();
  

};
class LTree__ntTree : public LTree__TreePart {
public:
  LTree__ntTree();
  LTree__ntTree(LTree  * input__item, LTree__TreePart  * input__bottom, LTree__TreePart  * input__right, LTree__TreePart  * input__left, LTree__TreePart  * input__top);
  ~LTree__ntTree();
  double branch_prob;
  LTree__TreePart  *bottom;
  LTree__TreePart  *right;
  LTree__TreePart  *left;
  LTree__TreePart  *top;
  void Draw();
  

};
class LTree__termTree : public LTree__TreePart {
public:
  LTree__termTree();
  LTree__termTree(LTree  * input__item, TreeSegment  * input__seg);
  ~LTree__termTree();
  TreeSegment  *seg;
  void Draw();
  

};
LTree::LTree(const GiglConfig  & input__config) : config((input__config)), n((((signed int (*)(const GiglConfig  & ))(((config).funcs)[0]))((config)))), unit_len((((double (*)(const GiglConfig  & ))(((config).funcs)[1]))((config)))), max_wid((((double (*)(const GiglConfig  & ))(((config).funcs)[2]))((config))))
{

  {
    ((root) = ((Generate__TreePart)(0, ((MkVector2D)(0.0, 0.0)), ((MkVector2D)(0.0, 1.0)), (max_wid), 0.0)));
  }
  ((start_pos) = ((root)->start_pos));
  ((end_pos) = ((root)->end_pos));
}

LTree::LTree(GiglConfig  && input__config) : config(((move)((input__config)))), n((((signed int (*)(const GiglConfig  & ))(((config).funcs)[0]))((config)))), unit_len((((double (*)(const GiglConfig  & ))(((config).funcs)[1]))((config)))), max_wid((((double (*)(const GiglConfig  & ))(((config).funcs)[2]))((config))))
{

  {
    ((root) = ((Generate__TreePart)(0, ((MkVector2D)(0.0, 0.0)), ((MkVector2D)(0.0, 1.0)), (max_wid), 0.0)));
  }
  ((start_pos) = ((root)->start_pos));
  ((end_pos) = ((root)->end_pos));
}

LTree::LTree(LTree__Node  * input__root) : config(), n(), unit_len(), max_wid(), root((input__root))
{

  ((start_pos) = ((root)->start_pos));
  ((end_pos) = ((root)->end_pos));
}

LTree::LTree(const GiglConfig  & input__config, LTree__Node  * input__root) : config((input__config)), n((((signed int (*)(const GiglConfig  & ))(((config).funcs)[0]))((config)))), unit_len((((double (*)(const GiglConfig  & ))(((config).funcs)[1]))((config)))), max_wid((((double (*)(const GiglConfig  & ))(((config).funcs)[2]))((config)))), root((input__root))
{

  ((start_pos) = ((root)->start_pos));
  ((end_pos) = ((root)->end_pos));
}

LTree::LTree(GiglConfig  && input__config, LTree__Node  * input__root) : config(((move)((input__config)))), n((((signed int (*)(const GiglConfig  & ))(((config).funcs)[0]))((config)))), unit_len((((double (*)(const GiglConfig  & ))(((config).funcs)[1]))((config)))), max_wid((((double (*)(const GiglConfig  & ))(((config).funcs)[2]))((config)))), root((input__root))
{

  ((start_pos) = ((root)->start_pos));
  ((end_pos) = ((root)->end_pos));
}

LTree::~LTree()
{

  if ((root))
  {
    delete (root);
  } else {
    
  }
}








void LTree::Draw()
{

  return (((root)->Draw)());
}

LTree__TreePart  *LTree::Generate__TreePart(signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  double probs[2] = {(((double (*)(const GiglConfig  & , signed int  , const Vector2D  & , const Vector2D  & , double  , double  ))(((config).funcs)[3]))((config), (depth), (start), (dir), (bottom_w), (top_w))), (((double (*)(const GiglConfig  & , signed int  , const Vector2D  & , const Vector2D  & , double  , double  ))(((config).funcs)[4]))((config), (depth), (start), (dir), (bottom_w), (top_w)))};
  ((NonegativeProbs)((probs), 2));
  
  ((NormalizeProbs)((probs), 2));
  signed int choice = ((GetRandChoiceFromProbs)((probs), 2));
  switch ((choice))
  {
    case 0:
      return ((Generate__ntTree)((depth), (start), (dir), (bottom_w), (top_w)));
    
    case 1:
      return ((Generate__termTree)((depth), (start), (dir), (bottom_w), (top_w)));
    
  }
  return 0;
}

LTree__ntTree  *LTree::Generate__ntTree(signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  LTree__ntTree  *node = (new LTree__ntTree);
  (((node)->item) = (this));
  (((node)->branch_prob) = (((double (*)(const GiglConfig  & , signed int  , const Vector2D  & , const Vector2D  & , double  , double  ))(((config).funcs)[5]))((config), (depth), (start), (dir), (bottom_w), (top_w))));
  
  
  
  
  {
    double mid_w = (0.5 * (((bottom_w) + (top_w))));
    (((node)->bottom) = ((Generate__TreePart)(((depth) + 1), (start), (dir), (bottom_w), (mid_w))));
    (((node)->right) = (((RandomRoll)(((node)->branch_prob))) ? ((Generate__TreePart)(((depth) + 1), (((node)->bottom)->end_pos), ((RotateDegrees)((dir), (-(((double (*)(const GiglConfig  & , signed int  , const Vector2D  & , const Vector2D  & , double  , double  ))(((config).funcs)[6]))((config), (depth), (start), (dir), (bottom_w), (top_w)))))), (mid_w), 0.0)) : 0));
    (((node)->left) = (((RandomRoll)(((node)->branch_prob))) ? ((Generate__TreePart)(((depth) + 1), (((node)->bottom)->end_pos), ((RotateDegrees)((dir), (((double (*)(const GiglConfig  & , signed int  , const Vector2D  & , const Vector2D  & , double  , double  ))(((config).funcs)[6]))((config), (depth), (start), (dir), (bottom_w), (top_w))))), (mid_w), 0.0)) : 0));
    (((node)->top) = ((Generate__TreePart)(((depth) + 1), (((node)->bottom)->end_pos), (dir), (mid_w), (top_w))));
    (((node)->start_pos) = (start));
    (((node)->end_pos) = (((node)->top)->end_pos));
  }
  return (node);
}

LTree__termTree  *LTree::Generate__termTree(signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  LTree__termTree  *node = (new LTree__termTree);
  (((node)->item) = (this));
  
  {
    (((node)->seg) = ((TermSegGen)((depth), (start), (dir), (bottom_w), (top_w), (n), (unit_len))));
    (((node)->start_pos) = (((node)->seg)->start));
    (((node)->end_pos) = (((node)->seg)->end));
  }
  return (node);
}



LTree__Node::LTree__Node(LTree  * input__item) : item((input__item))
{

  
}

LTree__Node::LTree__Node()
{

  
}

LTree__Node::~LTree__Node()
{

  
}







LTree__TreePart::LTree__TreePart(LTree  * input__item) : LTree__Node((input__item))
{

  
}

LTree__TreePart::LTree__TreePart()
{

  
}



LTree__ntTree::LTree__ntTree()
{

  
}

LTree__ntTree::LTree__ntTree(LTree  * input__item, LTree__TreePart  * input__bottom, LTree__TreePart  * input__right, LTree__TreePart  * input__left, LTree__TreePart  * input__top) : LTree__TreePart((input__item)), branch_prob(), bottom((input__bottom)), right((input__right)), left((input__left)), top((input__top))
{

  
  
  
  
  
}

LTree__ntTree::~LTree__ntTree()
{

  
  {
    if ((bottom))
    {
      delete (bottom);
    } else {
      
    }
  }
  {
    if ((left))
    {
      delete (left);
    } else {
      
    }
  }
  {
    if ((right))
    {
      delete (right);
    } else {
      
    }
  }
  {
    if ((top))
    {
      delete (top);
    } else {
      
    }
  }
}






void LTree__ntTree::Draw()
{

  {
    (((bottom)->Draw)());
    (((top)->Draw)());
    if ((right))
    {
      (((right)->Draw)());
    } else {
      
    }
    if ((left))
    {
      (((left)->Draw)());
    } else {
      
    }
  }
}



LTree__termTree::LTree__termTree()
{

  
}

LTree__termTree::LTree__termTree(LTree  * input__item, TreeSegment  * input__seg) : LTree__TreePart((input__item)), seg((input__seg))
{

  
  
}

LTree__termTree::~LTree__termTree()
{

  
  {
    if ((seg))
    {
      delete (seg);
    } else {
      
    }
  }
}


void LTree__termTree::Draw()
{

  return (((seg)->Draw)());
}




signed int LTree__ConfigLambda__63__44(const GiglConfig  & config);
double LTree__ConfigLambda__63__47(const GiglConfig  & config);
double LTree__ConfigLambda__63__57(const GiglConfig  & config);
double LTree__ConfigLambda__64__35(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
double LTree__ConfigLambda__64__40(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
double LTree__ConfigLambda__64__49(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
double LTree__ConfigLambda__64__70(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
signed int LTree__ConfigLambda__63__44(const GiglConfig  & config)
{

  return (*(*((signed int * *)(((config).vars)[0]))));
}
double LTree__ConfigLambda__63__47(const GiglConfig  & config)
{

  return (*(*((double * *)(((config).vars)[1]))));
}
double LTree__ConfigLambda__63__57(const GiglConfig  & config)
{

  return (*(*((double * *)(((config).vars)[2]))));
}
double LTree__ConfigLambda__64__35(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  return 1.0;
}
double LTree__ConfigLambda__64__40(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  return 45.0;
}
double LTree__ConfigLambda__64__49(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  return ((depth) < (*(*((signed int * *)(((config).vars)[3])))));
}
double LTree__ConfigLambda__64__70(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  return (1.0 - ((depth) < (*(*((signed int * *)(((config).vars)[3]))))));
}

LTree  *GenerateDetermLTree(signed int  n, double  unit_len)
{

  {
    double max_wid = ((double)((1 << (n))));
    return (new LTree((GiglConfig(4, 7, ((sizeof(signed int *)) + ((sizeof(double *)) + ((sizeof(double *)) + (sizeof(signed int *))))), (SizeVec{(sizeof(signed int *)), (sizeof(double *)), (sizeof(double *)), (sizeof(signed int *))}), (VarPtrVec{((VarPtr)(&((*((signed int * *)((malloc)((sizeof(signed int *)))))) = (&(n))))), ((VarPtr)(&((*((double * *)((malloc)((sizeof(double *)))))) = (&(unit_len))))), ((VarPtr)(&((*((double * *)((malloc)((sizeof(double *)))))) = (&(max_wid))))), ((VarPtr)(&((*((signed int * *)((malloc)((sizeof(signed int *)))))) = (&(n)))))}), (IndexVec{0, 1, 2, 5, 6, 3, 4}), (FuncPtrVec{((FuncPtr)(&(LTree__ConfigLambda__63__44))), ((FuncPtr)(&(LTree__ConfigLambda__63__47))), ((FuncPtr)(&(LTree__ConfigLambda__63__57))), ((FuncPtr)(&(LTree__ConfigLambda__64__35))), ((FuncPtr)(&(LTree__ConfigLambda__64__40))), ((FuncPtr)(&(LTree__ConfigLambda__64__49))), ((FuncPtr)(&(LTree__ConfigLambda__64__70)))})))));
  }
}
signed int LTree__ConfigLambda__70__44(const GiglConfig  & config);
double LTree__ConfigLambda__70__47(const GiglConfig  & config);
double LTree__ConfigLambda__70__57(const GiglConfig  & config);
double LTree__ConfigLambda__71__35(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
double LTree__ConfigLambda__71__40(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
double LTree__ConfigLambda__71__69(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
double LTree__ConfigLambda__71__102(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
signed int LTree__ConfigLambda__70__44(const GiglConfig  & config)
{

  return (*(*((signed int * *)(((config).vars)[0]))));
}
double LTree__ConfigLambda__70__47(const GiglConfig  & config)
{

  return (*(*((double * *)(((config).vars)[1]))));
}
double LTree__ConfigLambda__70__57(const GiglConfig  & config)
{

  return (*(*((double * *)(((config).vars)[2]))));
}
double LTree__ConfigLambda__71__35(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  return 0.7;
}
double LTree__ConfigLambda__71__40(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  return ((GetRandFloat)(30.0, 60.0));
}
double LTree__ConfigLambda__71__69(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  return (((depth) < (*(*((signed int * *)(((config).vars)[3]))))) ? 0.8 : 0.0);
}
double LTree__ConfigLambda__71__102(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  return (1.0 - (((depth) < (*(*((signed int * *)(((config).vars)[3]))))) ? 0.8 : 0.0));
}

LTree  *GenerateNDLTree(signed int  n, double  unit_len)
{

  {
    double max_wid = ((double)((1 << (n))));
    return (new LTree((GiglConfig(4, 7, ((sizeof(signed int *)) + ((sizeof(double *)) + ((sizeof(double *)) + (sizeof(signed int *))))), (SizeVec{(sizeof(signed int *)), (sizeof(double *)), (sizeof(double *)), (sizeof(signed int *))}), (VarPtrVec{((VarPtr)(&((*((signed int * *)((malloc)((sizeof(signed int *)))))) = (&(n))))), ((VarPtr)(&((*((double * *)((malloc)((sizeof(double *)))))) = (&(unit_len))))), ((VarPtr)(&((*((double * *)((malloc)((sizeof(double *)))))) = (&(max_wid))))), ((VarPtr)(&((*((signed int * *)((malloc)((sizeof(signed int *)))))) = (&(n)))))}), (IndexVec{0, 1, 2, 5, 6, 3, 4}), (FuncPtrVec{((FuncPtr)(&(LTree__ConfigLambda__70__44))), ((FuncPtr)(&(LTree__ConfigLambda__70__47))), ((FuncPtr)(&(LTree__ConfigLambda__70__57))), ((FuncPtr)(&(LTree__ConfigLambda__71__35))), ((FuncPtr)(&(LTree__ConfigLambda__71__40))), ((FuncPtr)(&(LTree__ConfigLambda__71__69))), ((FuncPtr)(&(LTree__ConfigLambda__71__102)))})))));
  }
}

double ntFac(signed int  d, signed int  n, double  w, double  max_w)
{

  {
    return (((d) < (n)) ? (0.5 + ((w) / (max_w))) : 0.0);
  }
}

double brchFac(double  w, double  max_w)
{

  {
    return (2 - ((3 * (w)) / (max_w)));
  }
}
signed int LTree__ConfigLambda__87__44(const GiglConfig  & config);
double LTree__ConfigLambda__87__47(const GiglConfig  & config);
double LTree__ConfigLambda__87__57(const GiglConfig  & config);
double LTree__ConfigLambda__88__35(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
double LTree__ConfigLambda__88__60(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
double LTree__ConfigLambda__88__89(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
double LTree__ConfigLambda__88__135(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
signed int LTree__ConfigLambda__87__44(const GiglConfig  & config)
{

  return (*(*((signed int * *)(((config).vars)[0]))));
}
double LTree__ConfigLambda__87__47(const GiglConfig  & config)
{

  return (*(*((double * *)(((config).vars)[1]))));
}
double LTree__ConfigLambda__87__57(const GiglConfig  & config)
{

  return (*(*((double * *)(((config).vars)[2]))));
}
double LTree__ConfigLambda__88__35(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  return ((brchFac)((top_w), (*(*((double * *)(((config).vars)[3]))))));
}
double LTree__ConfigLambda__88__60(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  return ((GetRandFloat)(30.0, 60.0));
}
double LTree__ConfigLambda__88__89(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  return ((ntFac)((depth), (*(*((signed int * *)(((config).vars)[4])))), (bottom_w), (*(*((double * *)(((config).vars)[5]))))));
}
double LTree__ConfigLambda__88__135(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  return (1.0 - ((ntFac)((depth), (*(*((signed int * *)(((config).vars)[4])))), (bottom_w), (*(*((double * *)(((config).vars)[5])))))));
}

LTree  *GenerateAdvNDLTree(signed int  n, double  unit_len)
{

  {
    double max_wid = ((double)((1 << (n))));
    return (new LTree((GiglConfig(6, 7, ((sizeof(signed int *)) + ((sizeof(double *)) + ((sizeof(double *)) + ((sizeof(double *)) + ((sizeof(signed int *)) + (sizeof(double *))))))), (SizeVec{(sizeof(signed int *)), (sizeof(double *)), (sizeof(double *)), (sizeof(double *)), (sizeof(signed int *)), (sizeof(double *))}), (VarPtrVec{((VarPtr)(&((*((signed int * *)((malloc)((sizeof(signed int *)))))) = (&(n))))), ((VarPtr)(&((*((double * *)((malloc)((sizeof(double *)))))) = (&(unit_len))))), ((VarPtr)(&((*((double * *)((malloc)((sizeof(double *)))))) = (&(max_wid))))), ((VarPtr)(&((*((double * *)((malloc)((sizeof(double *)))))) = (&(max_wid))))), ((VarPtr)(&((*((signed int * *)((malloc)((sizeof(signed int *)))))) = (&(n))))), ((VarPtr)(&((*((double * *)((malloc)((sizeof(double *)))))) = (&(max_wid)))))}), (IndexVec{0, 1, 2, 5, 6, 3, 4}), (FuncPtrVec{((FuncPtr)(&(LTree__ConfigLambda__87__44))), ((FuncPtr)(&(LTree__ConfigLambda__87__47))), ((FuncPtr)(&(LTree__ConfigLambda__87__57))), ((FuncPtr)(&(LTree__ConfigLambda__88__35))), ((FuncPtr)(&(LTree__ConfigLambda__88__60))), ((FuncPtr)(&(LTree__ConfigLambda__88__89))), ((FuncPtr)(&(LTree__ConfigLambda__88__135)))})))));
  }
}


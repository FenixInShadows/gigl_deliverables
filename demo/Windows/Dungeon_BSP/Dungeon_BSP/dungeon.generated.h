
#include "GiglDefaultInclude.h"


#include "DungeonSpace.h"


class Range1D;

class Range2D;

class Room;

class BossRoom;

class Corridor;


class BspDungeon;

class BspDungeon__Node;

class BspDungeon__DungeonArea;

class BspDungeon__hDivide;

class BspDungeon__vDivide;

class BspDungeon__tArea;

class BspDungeon__bossArea;

class BspDungeon {
public:
  BspDungeon(const GiglConfig  & input__config);
  BspDungeon(GiglConfig  && input__config);
  BspDungeon(BspDungeon__Node  * input__root);
  BspDungeon(const GiglConfig  & input__config, BspDungeon__Node  * input__root);
  BspDungeon(GiglConfig  && input__config, BspDungeon__Node  * input__root);
  ~BspDungeon();
  GiglConfig config;
  const Range2D  &whole_range;
  double unit_min;
  double unit_max;
  double wall_min;
  signed int have_boss_area;
  BspDungeon__Node  *root;
  void Draw();
  Range2D bound_box;
  Range2D room_range;
  double GetContactFromLeft(double  y);
  double GetContactFromBottom(double  x);
  double GetContactFromRight(double  y);
  double GetContactFromTop(double  x);
  void Draw(signed int  is_padded);
  void DrawPart(signed int  is_padded);
  void DrawAll(signed int  is_padded);
  BspDungeon__DungeonArea  *Generate__DungeonArea(const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss);
  BspDungeon__hDivide  *Generate__hDivide(const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss);
  BspDungeon__vDivide  *Generate__vDivide(const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss);
  BspDungeon__tArea  *Generate__tArea(const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss);
  BspDungeon__bossArea  *Generate__bossArea(const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss);
  

};
class BspDungeon__Node {
public:
  BspDungeon__Node(BspDungeon  * input__item);
  BspDungeon__Node();
  virtual ~BspDungeon__Node();
  BspDungeon  *item;
  Range2D bound_box;
  Range2D room_range;
  double virtual GetContactFromLeft(double  y) = 0;
  double virtual GetContactFromBottom(double  x) = 0;
  double virtual GetContactFromRight(double  y) = 0;
  double virtual GetContactFromTop(double  x) = 0;
  void virtual Draw(signed int  is_padded);
  void virtual DrawPart(signed int  is_padded) = 0;
  void virtual DrawAll(signed int  is_padded) = 0;
  

};
class BspDungeon__DungeonArea : public BspDungeon__Node {
public:
  BspDungeon__DungeonArea(BspDungeon  * input__item);
  BspDungeon__DungeonArea();
  

};
class BspDungeon__hDivide : public BspDungeon__DungeonArea {
public:
  BspDungeon__hDivide();
  BspDungeon__hDivide(BspDungeon  * input__item, BspDungeon__DungeonArea  * input__b_area, BspDungeon__DungeonArea  * input__t_area, Corridor  * input__corridor);
  ~BspDungeon__hDivide();
  double corrid_min;
  double corrid_max;
  BspDungeon__DungeonArea  *b_area;
  BspDungeon__DungeonArea  *t_area;
  Corridor  *corridor;
  double GetContactFromLeft(double  y);
  double GetContactFromBottom(double  x);
  double GetContactFromRight(double  y);
  double GetContactFromTop(double  x);
  void DrawPart(signed int  is_padded);
  void DrawAll(signed int  is_padded);
  

};
class BspDungeon__vDivide : public BspDungeon__DungeonArea {
public:
  BspDungeon__vDivide();
  BspDungeon__vDivide(BspDungeon  * input__item, BspDungeon__DungeonArea  * input__l_area, BspDungeon__DungeonArea  * input__r_area, Corridor  * input__corridor);
  ~BspDungeon__vDivide();
  double corrid_min;
  double corrid_max;
  BspDungeon__DungeonArea  *l_area;
  BspDungeon__DungeonArea  *r_area;
  Corridor  *corridor;
  double GetContactFromLeft(double  y);
  double GetContactFromBottom(double  x);
  double GetContactFromRight(double  y);
  double GetContactFromTop(double  x);
  void DrawPart(signed int  is_padded);
  void DrawAll(signed int  is_padded);
  

};
class BspDungeon__tArea : public BspDungeon__DungeonArea {
public:
  BspDungeon__tArea();
  BspDungeon__tArea(BspDungeon  * input__item, Room  * input__room);
  ~BspDungeon__tArea();
  double room_min;
  Room  *room;
  double GetContactFromLeft(double  y);
  double GetContactFromBottom(double  x);
  double GetContactFromRight(double  y);
  double GetContactFromTop(double  x);
  void DrawPart(signed int  is_padded);
  void DrawAll(signed int  is_padded);
  

};
class BspDungeon__bossArea : public BspDungeon__DungeonArea {
public:
  BspDungeon__bossArea();
  BspDungeon__bossArea(BspDungeon  * input__item, BossRoom  * input__room);
  ~BspDungeon__bossArea();
  double room_min;
  BossRoom  *room;
  double GetContactFromLeft(double  y);
  double GetContactFromBottom(double  x);
  double GetContactFromRight(double  y);
  double GetContactFromTop(double  x);
  void DrawPart(signed int  is_padded);
  void DrawAll(signed int  is_padded);
  

};
BspDungeon::BspDungeon(const GiglConfig  & input__config) : config((input__config)), whole_range((((const Range2D & (*)(const GiglConfig  & ))(((config).funcs)[0]))((config)))), unit_min((((double (*)(const GiglConfig  & ))(((config).funcs)[1]))((config)))), unit_max((((double (*)(const GiglConfig  & ))(((config).funcs)[2]))((config)))), wall_min((((double (*)(const GiglConfig  & ))(((config).funcs)[3]))((config)))), have_boss_area((((signed int (*)(const GiglConfig  & ))(((config).funcs)[4]))((config))))
{

  {
    ((root) = ((Generate__DungeonArea)((whole_range), ((MkNoConstraintRange1D)()), ((MkNoConstraintRange1D)()), (have_boss_area))));
  }
  ((bound_box) = ((root)->bound_box));
  ((room_range) = ((root)->room_range));
}

BspDungeon::BspDungeon(GiglConfig  && input__config) : config(((move)((input__config)))), whole_range((((const Range2D & (*)(const GiglConfig  & ))(((config).funcs)[0]))((config)))), unit_min((((double (*)(const GiglConfig  & ))(((config).funcs)[1]))((config)))), unit_max((((double (*)(const GiglConfig  & ))(((config).funcs)[2]))((config)))), wall_min((((double (*)(const GiglConfig  & ))(((config).funcs)[3]))((config)))), have_boss_area((((signed int (*)(const GiglConfig  & ))(((config).funcs)[4]))((config))))
{

  {
    ((root) = ((Generate__DungeonArea)((whole_range), ((MkNoConstraintRange1D)()), ((MkNoConstraintRange1D)()), (have_boss_area))));
  }
  ((bound_box) = ((root)->bound_box));
  ((room_range) = ((root)->room_range));
}

BspDungeon::BspDungeon(BspDungeon__Node  * input__root) : config(), whole_range((Range2D())), unit_min(), unit_max(), wall_min(), have_boss_area(), root((input__root))
{

  ((bound_box) = ((root)->bound_box));
  ((room_range) = ((root)->room_range));
}

BspDungeon::BspDungeon(const GiglConfig  & input__config, BspDungeon__Node  * input__root) : config((input__config)), whole_range((((const Range2D & (*)(const GiglConfig  & ))(((config).funcs)[0]))((config)))), unit_min((((double (*)(const GiglConfig  & ))(((config).funcs)[1]))((config)))), unit_max((((double (*)(const GiglConfig  & ))(((config).funcs)[2]))((config)))), wall_min((((double (*)(const GiglConfig  & ))(((config).funcs)[3]))((config)))), have_boss_area((((signed int (*)(const GiglConfig  & ))(((config).funcs)[4]))((config)))), root((input__root))
{

  ((bound_box) = ((root)->bound_box));
  ((room_range) = ((root)->room_range));
}

BspDungeon::BspDungeon(GiglConfig  && input__config, BspDungeon__Node  * input__root) : config(((move)((input__config)))), whole_range((((const Range2D & (*)(const GiglConfig  & ))(((config).funcs)[0]))((config)))), unit_min((((double (*)(const GiglConfig  & ))(((config).funcs)[1]))((config)))), unit_max((((double (*)(const GiglConfig  & ))(((config).funcs)[2]))((config)))), wall_min((((double (*)(const GiglConfig  & ))(((config).funcs)[3]))((config)))), have_boss_area((((signed int (*)(const GiglConfig  & ))(((config).funcs)[4]))((config)))), root((input__root))
{

  ((bound_box) = ((root)->bound_box));
  ((room_range) = ((root)->room_range));
}

BspDungeon::~BspDungeon()
{

  if ((root))
  {
    delete (root);
  } else {
    
  }
}








void BspDungeon::Draw()
{

  {
    (((root)->Draw)(1));
    (((root)->Draw)(0));
  }
}



double BspDungeon::GetContactFromLeft(double  y)
{

  return (((root)->GetContactFromLeft)((y)));
}

double BspDungeon::GetContactFromBottom(double  x)
{

  return (((root)->GetContactFromBottom)((x)));
}

double BspDungeon::GetContactFromRight(double  y)
{

  return (((root)->GetContactFromRight)((y)));
}

double BspDungeon::GetContactFromTop(double  x)
{

  return (((root)->GetContactFromTop)((x)));
}

void BspDungeon::Draw(signed int  is_padded)
{

  return (((root)->Draw)((is_padded)));
}

void BspDungeon::DrawPart(signed int  is_padded)
{

  return (((root)->DrawPart)((is_padded)));
}

void BspDungeon::DrawAll(signed int  is_padded)
{

  return (((root)->DrawAll)((is_padded)));
}

BspDungeon__DungeonArea  *BspDungeon::Generate__DungeonArea(const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss)
{

  double probs[4] = {(((double (*)(const GiglConfig  & , const Range2D  & , const Range1D  & , const Range1D  & , signed int  ))(((config).funcs)[5]))((config), (range), (cover_x), (cover_y), (have_boss))), (((double (*)(const GiglConfig  & , const Range2D  & , const Range1D  & , const Range1D  & , signed int  ))(((config).funcs)[6]))((config), (range), (cover_x), (cover_y), (have_boss))), (((double (*)(const GiglConfig  & , const Range2D  & , const Range1D  & , const Range1D  & , signed int  ))(((config).funcs)[7]))((config), (range), (cover_x), (cover_y), (have_boss))), (((double (*)(const GiglConfig  & , const Range2D  & , const Range1D  & , const Range1D  & , signed int  ))(((config).funcs)[8]))((config), (range), (cover_x), (cover_y), (have_boss)))};
  
  {
    if ((((range).span_x) < (2 * (unit_min))))
    {
      (((probs)[1]) = 0.0);
      
    } else {
      
    }
    if ((((range).span_y) < (2 * (unit_min))))
    {
      (((probs)[0]) = 0.0);
      
    } else {
      
    }
    if (((((range).span_x) > (unit_max)) || (((range).span_y) > (unit_max))))
    {
      (((probs)[2]) = 0.0);
      (((probs)[3]) = 0.0);
      
    } else {
      if ((have_boss))
      {
        (((probs)[3]) += ((probs)[2]));
        (((probs)[2]) = 0.0);
        
      } else {
        (((probs)[2]) += ((probs)[3]));
        (((probs)[3]) = 0.0);
        
      }
    }
  }
  ((NormalizeProbs)((probs), 4));
  signed int choice = ((GetRandChoiceFromProbs)((probs), 4));
  switch ((choice))
  {
    case 0:
      return ((Generate__hDivide)((range), (cover_x), (cover_y), (have_boss)));
    
    case 1:
      return ((Generate__vDivide)((range), (cover_x), (cover_y), (have_boss)));
    
    case 2:
      return ((Generate__tArea)((range), (cover_x), (cover_y), (have_boss)));
    
    case 3:
      return ((Generate__bossArea)((range), (cover_x), (cover_y), (have_boss)));
    
  }
  return 0;
}

BspDungeon__hDivide  *BspDungeon::Generate__hDivide(const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss)
{

  BspDungeon__hDivide  *node = (new BspDungeon__hDivide);
  (((node)->item) = (this));
  (((node)->corrid_min) = (((double (*)(const GiglConfig  & , const Range2D  & , const Range1D  & , const Range1D  & , signed int  ))(((config).funcs)[9]))((config), (range), (cover_x), (cover_y), (have_boss))));
  (((node)->corrid_max) = (((double (*)(const GiglConfig  & , const Range2D  & , const Range1D  & , const Range1D  & , signed int  ))(((config).funcs)[10]))((config), (range), (cover_x), (cover_y), (have_boss))));
  
  
  
  {
    (((node)->bound_box) = (range));
  }
  {
    double corrid_size = ((GetRandFloat)(((node)->corrid_min), ((node)->corrid_max)));
    double corrid_pos = ((GetRandFloat)((((range).left) + (wall_min)), ((((range).right) - (wall_min)) - (corrid_size))));
    Range1D corrid_cover = ((MkRange1DFromMin)((corrid_pos), (corrid_size)));
    Range1D union_cover = ((UnionRange1D)((corrid_cover), (cover_x)));
    double subarea_max = (((range).span_y) - (unit_min));
    double bottom_size = ((GetRandFloat)((unit_min), ((((unit_max) < (subarea_max)) ? (unit_max) : (subarea_max)))));
    double separator_y = (((range).bottom) + (bottom_size));
    signed int boss_in_bottom = 0, boss_in_top = 0;
    if (((RandomRoll)(0.5)))
    {
      ((boss_in_bottom) = (have_boss));
    } else {
      ((boss_in_top) = (have_boss));
    }
    if (((RandomRoll)(0.5)))
    {
      {
        (((node)->b_area) = ((Generate__DungeonArea)(((MkRange2D)(((range).left), ((range).bottom), ((range).right), (separator_y))), (union_cover), ((MkMinConstraintRange1D)(((cover_y).min))), (boss_in_bottom))));
        (((node)->t_area) = ((Generate__DungeonArea)(((MkRange2D)(((range).left), (separator_y), ((range).right), ((range).top))), (corrid_cover), ((MkMaxConstraintRange1D)(((cover_y).max))), (boss_in_top))));
      }
    } else {
      {
        (((node)->b_area) = ((Generate__DungeonArea)(((MkRange2D)(((range).left), ((range).bottom), ((range).right), (separator_y))), (corrid_cover), ((MkMinConstraintRange1D)(((cover_y).min))), (boss_in_bottom))));
        (((node)->t_area) = ((Generate__DungeonArea)(((MkRange2D)(((range).left), (separator_y), ((range).right), ((range).top))), (union_cover), ((MkMaxConstraintRange1D)(((cover_y).max))), (boss_in_top))));
      }
    }
    double corrid_bottom_left = ((((node)->b_area)->GetContactFromTop)(((corrid_cover).min)));
    double corrid_bottom_right = ((((node)->b_area)->GetContactFromTop)(((corrid_cover).max)));
    double corrid_bottom = ((((corrid_bottom_left) < (corrid_bottom_right)) ? (corrid_bottom_left) : (corrid_bottom_right)));
    double corrid_top_left = ((((node)->t_area)->GetContactFromBottom)(((corrid_cover).min)));
    double corrid_top_right = ((((node)->t_area)->GetContactFromBottom)(((corrid_cover).max)));
    double corrid_top = ((((corrid_top_left) > (corrid_top_right)) ? (corrid_top_left) : (corrid_top_right)));
    (((node)->corridor) = (new Corridor(((corrid_cover).min), (corrid_bottom), ((corrid_cover).max), (corrid_top))));
    (((node)->room_range) = ((UnionRange2D)(((UnionRange2D)((((node)->b_area)->room_range), (((node)->t_area)->room_range))), (((node)->corridor)->range))));
  }
  return (node);
}

BspDungeon__vDivide  *BspDungeon::Generate__vDivide(const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss)
{

  BspDungeon__vDivide  *node = (new BspDungeon__vDivide);
  (((node)->item) = (this));
  (((node)->corrid_min) = (((double (*)(const GiglConfig  & , const Range2D  & , const Range1D  & , const Range1D  & , signed int  ))(((config).funcs)[11]))((config), (range), (cover_x), (cover_y), (have_boss))));
  (((node)->corrid_max) = (((double (*)(const GiglConfig  & , const Range2D  & , const Range1D  & , const Range1D  & , signed int  ))(((config).funcs)[12]))((config), (range), (cover_x), (cover_y), (have_boss))));
  
  
  
  {
    (((node)->bound_box) = (range));
  }
  {
    double corrid_size = ((GetRandFloat)(((node)->corrid_min), ((node)->corrid_max)));
    double corrid_pos = ((GetRandFloat)((((range).bottom) + (wall_min)), ((((range).top) - (wall_min)) - (corrid_size))));
    Range1D corrid_cover = ((MkRange1DFromMin)((corrid_pos), (corrid_size)));
    Range1D union_cover = ((UnionRange1D)((corrid_cover), (cover_y)));
    double subarea_max = (((range).span_x) - (unit_min));
    double left_size = ((GetRandFloat)((unit_min), ((((unit_max) < (subarea_max)) ? (unit_max) : (subarea_max)))));
    double separator_x = (((range).left) + (left_size));
    signed int boss_in_left = 0, boss_in_right = 0;
    if (((RandomRoll)(0.5)))
    {
      ((boss_in_left) = (have_boss));
    } else {
      ((boss_in_right) = (have_boss));
    }
    if (((RandomRoll)(0.5)))
    {
      {
        (((node)->l_area) = ((Generate__DungeonArea)(((MkRange2D)(((range).left), ((range).bottom), (separator_x), ((range).top))), ((MkMinConstraintRange1D)(((cover_x).min))), (union_cover), (boss_in_left))));
        (((node)->r_area) = ((Generate__DungeonArea)(((MkRange2D)((separator_x), ((range).bottom), ((range).right), ((range).top))), ((MkMaxConstraintRange1D)(((cover_x).max))), (corrid_cover), (boss_in_right))));
      }
    } else {
      {
        (((node)->l_area) = ((Generate__DungeonArea)(((MkRange2D)(((range).left), ((range).bottom), (separator_x), ((range).top))), ((MkMinConstraintRange1D)(((cover_x).min))), (corrid_cover), (boss_in_left))));
        (((node)->r_area) = ((Generate__DungeonArea)(((MkRange2D)((separator_x), ((range).bottom), ((range).right), ((range).top))), ((MkMaxConstraintRange1D)(((cover_x).max))), (union_cover), (boss_in_right))));
      }
    }
    double corrid_left_bottom = ((((node)->l_area)->GetContactFromRight)(((corrid_cover).min)));
    double corrid_left_top = ((((node)->l_area)->GetContactFromRight)(((corrid_cover).max)));
    double corrid_left = ((((corrid_left_bottom) < (corrid_left_top)) ? (corrid_left_bottom) : (corrid_left_top)));
    double corrid_right_bottom = ((((node)->r_area)->GetContactFromLeft)(((corrid_cover).min)));
    double corrid_right_top = ((((node)->r_area)->GetContactFromLeft)(((corrid_cover).max)));
    double corrid_right = ((((corrid_right_bottom) > (corrid_right_top)) ? (corrid_right_bottom) : (corrid_right_top)));
    (((node)->corridor) = (new Corridor((corrid_left), ((corrid_cover).min), (corrid_right), ((corrid_cover).max))));
    (((node)->room_range) = ((UnionRange2D)(((UnionRange2D)((((node)->l_area)->room_range), (((node)->r_area)->room_range))), (((node)->corridor)->range))));
  }
  return (node);
}

BspDungeon__tArea  *BspDungeon::Generate__tArea(const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss)
{

  BspDungeon__tArea  *node = (new BspDungeon__tArea);
  (((node)->item) = (this));
  (((node)->room_min) = (((double (*)(const GiglConfig  & , const Range2D  & , const Range1D  & , const Range1D  & , signed int  ))(((config).funcs)[13]))((config), (range), (cover_x), (cover_y), (have_boss))));
  
  {
    (((node)->bound_box) = (range));
  }
  {
    (((node)->room) = ((TermRoomGen)((range), (cover_x), (cover_y), ((node)->room_min), (wall_min))));
    (((node)->room_range) = (((node)->room)->range));
  }
  return (node);
}

BspDungeon__bossArea  *BspDungeon::Generate__bossArea(const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss)
{

  BspDungeon__bossArea  *node = (new BspDungeon__bossArea);
  (((node)->item) = (this));
  (((node)->room_min) = (((double (*)(const GiglConfig  & , const Range2D  & , const Range1D  & , const Range1D  & , signed int  ))(((config).funcs)[14]))((config), (range), (cover_x), (cover_y), (have_boss))));
  
  {
    (((node)->bound_box) = (range));
  }
  {
    (((node)->room) = ((BossRoomGen)((range), (cover_x), (cover_y), ((node)->room_min), (wall_min))));
    (((node)->room_range) = (((node)->room)->range));
  }
  return (node);
}



BspDungeon__Node::BspDungeon__Node(BspDungeon  * input__item) : item((input__item))
{

  
}

BspDungeon__Node::BspDungeon__Node()
{

  
}

BspDungeon__Node::~BspDungeon__Node()
{

  
}








void BspDungeon__Node::Draw(signed int  is_padded)
{

  {
    switch (((CheckDraw2D)((bound_box), (window_range))))
    {
      {
        case (DRAW_NONE):
          break;
        
        case (DRAW_PART):
          ((DrawPart)((is_padded)));
        
        break;
        case (DRAW_ALL):
          ((DrawAll)((is_padded)));
        
        break;
      }
    }
  }
}





BspDungeon__DungeonArea::BspDungeon__DungeonArea(BspDungeon  * input__item) : BspDungeon__Node((input__item))
{

  
}

BspDungeon__DungeonArea::BspDungeon__DungeonArea()
{

  
}



BspDungeon__hDivide::BspDungeon__hDivide()
{

  
}

BspDungeon__hDivide::BspDungeon__hDivide(BspDungeon  * input__item, BspDungeon__DungeonArea  * input__b_area, BspDungeon__DungeonArea  * input__t_area, Corridor  * input__corridor) : BspDungeon__DungeonArea((input__item)), corrid_min(), corrid_max(), b_area((input__b_area)), t_area((input__t_area)), corridor((input__corridor))
{

  
  
  
  
}

BspDungeon__hDivide::~BspDungeon__hDivide()
{

  
  {
    if ((b_area))
    {
      delete (b_area);
    } else {
      
    }
  }
  {
    if ((corridor))
    {
      delete (corridor);
    } else {
      
    }
  }
  {
    if ((t_area))
    {
      delete (t_area);
    } else {
      
    }
  }
}






double BspDungeon__hDivide::GetContactFromLeft(double  y)
{

  {
    double contact = 1e10;
    if (((y) <= (((b_area)->room_range).top)))
    {
      ((contact) = (((b_area)->GetContactFromLeft)((y))));
    } else {
      if (((y) >= (((t_area)->room_range).bottom)))
      {
        ((contact) = (((t_area)->GetContactFromLeft)((y))));
      } else {
        
      }
    }
    return ((((((contact) <= (((corridor)->range).left)) || ((y) <= (((corridor)->range).bottom))) || ((y) >= (((corridor)->range).top))) ? (contact) : (((corridor)->range).left)));
  }
}

double BspDungeon__hDivide::GetContactFromBottom(double  x)
{

  {
    if ((((x) >= (((b_area)->room_range).left)) && ((x) < (((b_area)->room_range).right))))
    {
      return (((b_area)->GetContactFromBottom)((x)));
    } else {
      
    }
    return (((t_area)->GetContactFromBottom)((x)));
  }
}

double BspDungeon__hDivide::GetContactFromRight(double  y)
{

  {
    double contact = (-1e10);
    if (((y) <= (((b_area)->room_range).top)))
    {
      ((contact) = (((b_area)->GetContactFromRight)((y))));
    } else {
      if (((y) >= (((t_area)->room_range).bottom)))
      {
        ((contact) = (((t_area)->GetContactFromRight)((y))));
      } else {
        
      }
    }
    return ((((((contact) >= (((corridor)->range).right)) || ((y) <= (((corridor)->range).bottom))) || ((y) >= (((corridor)->range).top))) ? (contact) : (((corridor)->range).right)));
  }
}

double BspDungeon__hDivide::GetContactFromTop(double  x)
{

  {
    if ((((x) >= (((t_area)->room_range).left)) && ((x) < (((t_area)->room_range).right))))
    {
      return (((t_area)->GetContactFromTop)((x)));
    } else {
      
    }
    return (((b_area)->GetContactFromTop)((x)));
  }
}

void BspDungeon__hDivide::DrawPart(signed int  is_padded)
{

  {
    (((b_area)->Draw)((is_padded)));
    (((t_area)->Draw)((is_padded)));
    (((corridor)->Draw)((is_padded)));
  }
}

void BspDungeon__hDivide::DrawAll(signed int  is_padded)
{

  {
    (((b_area)->DrawAll)((is_padded)));
    (((t_area)->DrawAll)((is_padded)));
    (((corridor)->Draw)((is_padded)));
  }
}



BspDungeon__vDivide::BspDungeon__vDivide()
{

  
}

BspDungeon__vDivide::BspDungeon__vDivide(BspDungeon  * input__item, BspDungeon__DungeonArea  * input__l_area, BspDungeon__DungeonArea  * input__r_area, Corridor  * input__corridor) : BspDungeon__DungeonArea((input__item)), corrid_min(), corrid_max(), l_area((input__l_area)), r_area((input__r_area)), corridor((input__corridor))
{

  
  
  
  
}

BspDungeon__vDivide::~BspDungeon__vDivide()
{

  
  {
    if ((corridor))
    {
      delete (corridor);
    } else {
      
    }
  }
  {
    if ((l_area))
    {
      delete (l_area);
    } else {
      
    }
  }
  {
    if ((r_area))
    {
      delete (r_area);
    } else {
      
    }
  }
}






double BspDungeon__vDivide::GetContactFromLeft(double  y)
{

  {
    if ((((y) >= (((l_area)->room_range).bottom)) && ((y) < (((l_area)->room_range).top))))
    {
      return (((l_area)->GetContactFromLeft)((y)));
    } else {
      
    }
    return (((r_area)->GetContactFromLeft)((y)));
  }
}

double BspDungeon__vDivide::GetContactFromBottom(double  x)
{

  {
    double contact = 1e10;
    if (((x) <= (((l_area)->room_range).right)))
    {
      ((contact) = (((l_area)->GetContactFromBottom)((x))));
    } else {
      if (((x) >= (((r_area)->room_range).left)))
      {
        ((contact) = (((r_area)->GetContactFromBottom)((x))));
      } else {
        
      }
    }
    return ((((((contact) <= (((corridor)->range).bottom)) || ((x) <= (((corridor)->range).left))) || ((x) >= (((corridor)->range).right))) ? (contact) : (((corridor)->range).bottom)));
  }
}

double BspDungeon__vDivide::GetContactFromRight(double  y)
{

  {
    if ((((y) >= (((r_area)->room_range).bottom)) && ((y) < (((r_area)->room_range).top))))
    {
      return (((r_area)->GetContactFromRight)((y)));
    } else {
      
    }
    return (((l_area)->GetContactFromRight)((y)));
  }
}

double BspDungeon__vDivide::GetContactFromTop(double  x)
{

  {
    double contact = (-1e10);
    if (((x) <= (((l_area)->room_range).right)))
    {
      ((contact) = (((l_area)->GetContactFromTop)((x))));
    } else {
      if (((x) >= (((r_area)->room_range).left)))
      {
        ((contact) = (((r_area)->GetContactFromTop)((x))));
      } else {
        
      }
    }
    return ((((((contact) >= (((corridor)->range).top)) || ((x) <= (((corridor)->range).left))) || ((x) >= (((corridor)->range).right))) ? (contact) : (((corridor)->range).top)));
  }
}

void BspDungeon__vDivide::DrawPart(signed int  is_padded)
{

  {
    (((l_area)->Draw)((is_padded)));
    (((r_area)->Draw)((is_padded)));
    (((corridor)->Draw)((is_padded)));
  }
}

void BspDungeon__vDivide::DrawAll(signed int  is_padded)
{

  {
    (((l_area)->DrawAll)((is_padded)));
    (((r_area)->DrawAll)((is_padded)));
    (((corridor)->Draw)((is_padded)));
  }
}



BspDungeon__tArea::BspDungeon__tArea()
{

  
}

BspDungeon__tArea::BspDungeon__tArea(BspDungeon  * input__item, Room  * input__room) : BspDungeon__DungeonArea((input__item)), room_min(), room((input__room))
{

  
  
}

BspDungeon__tArea::~BspDungeon__tArea()
{

  
  {
    if ((room))
    {
      delete (room);
    } else {
      
    }
  }
}



double BspDungeon__tArea::GetContactFromLeft(double  y)
{

  return ((room_range).left);
}

double BspDungeon__tArea::GetContactFromBottom(double  x)
{

  return ((room_range).bottom);
}

double BspDungeon__tArea::GetContactFromRight(double  y)
{

  return ((room_range).right);
}

double BspDungeon__tArea::GetContactFromTop(double  x)
{

  return ((room_range).top);
}

void BspDungeon__tArea::DrawPart(signed int  is_padded)
{

  return (((room)->Draw)((is_padded)));
}

void BspDungeon__tArea::DrawAll(signed int  is_padded)
{

  return (((room)->Draw)((is_padded)));
}



BspDungeon__bossArea::BspDungeon__bossArea()
{

  
}

BspDungeon__bossArea::BspDungeon__bossArea(BspDungeon  * input__item, BossRoom  * input__room) : BspDungeon__DungeonArea((input__item)), room_min(), room((input__room))
{

  
  
}

BspDungeon__bossArea::~BspDungeon__bossArea()
{

  
  {
    if ((room))
    {
      delete (room);
    } else {
      
    }
  }
}



double BspDungeon__bossArea::GetContactFromLeft(double  y)
{

  return ((room_range).left);
}

double BspDungeon__bossArea::GetContactFromBottom(double  x)
{

  return ((room_range).bottom);
}

double BspDungeon__bossArea::GetContactFromRight(double  y)
{

  return ((room_range).right);
}

double BspDungeon__bossArea::GetContactFromTop(double  x)
{

  return ((room_range).top);
}

void BspDungeon__bossArea::DrawPart(signed int  is_padded)
{

  return (((room)->Draw)((is_padded)));
}

void BspDungeon__bossArea::DrawAll(signed int  is_padded)
{

  return (((room)->Draw)((is_padded)));
}




const Range2D  &BspDungeon__ConfigLambda__265__54(const GiglConfig  & config);
double BspDungeon__ConfigLambda__265__67(const GiglConfig  & config);
double BspDungeon__ConfigLambda__265__77(const GiglConfig  & config);
double BspDungeon__ConfigLambda__265__87(const GiglConfig  & config);
signed int BspDungeon__ConfigLambda__265__97(const GiglConfig  & config);
double BspDungeon__ConfigLambda__267__26(const GiglConfig  & config, const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss);
double BspDungeon__ConfigLambda__267__42(const GiglConfig  & config, const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss);
double BspDungeon__ConfigLambda__267__61(const GiglConfig  & config, const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss);
double BspDungeon__ConfigLambda__268__26(const GiglConfig  & config, const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss);
double BspDungeon__ConfigLambda__268__42(const GiglConfig  & config, const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss);
double BspDungeon__ConfigLambda__268__61(const GiglConfig  & config, const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss);
double BspDungeon__ConfigLambda__269__24(const GiglConfig  & config, const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss);
double BspDungeon__ConfigLambda__269__53(const GiglConfig  & config, const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss);
double BspDungeon__ConfigLambda__270__27(const GiglConfig  & config, const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss);
double BspDungeon__ConfigLambda__270__52(const GiglConfig  & config, const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss);
const Range2D  &BspDungeon__ConfigLambda__265__54(const GiglConfig  & config)
{

  return (*(*((const Range2D * *)(((config).vars)[0]))));
}
double BspDungeon__ConfigLambda__265__67(const GiglConfig  & config)
{

  return (*(*((double * *)(((config).vars)[1]))));
}
double BspDungeon__ConfigLambda__265__77(const GiglConfig  & config)
{

  return (*(*((double * *)(((config).vars)[2]))));
}
double BspDungeon__ConfigLambda__265__87(const GiglConfig  & config)
{

  return (*(*((double * *)(((config).vars)[3]))));
}
signed int BspDungeon__ConfigLambda__265__97(const GiglConfig  & config)
{

  return (*(*((double * *)(((config).vars)[4]))));
}
double BspDungeon__ConfigLambda__267__26(const GiglConfig  & config, const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss)
{

  return (0.1 * (*(*((double * *)(((config).vars)[5])))));
}
double BspDungeon__ConfigLambda__267__42(const GiglConfig  & config, const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss)
{

  return (0.2 * (*(*((double * *)(((config).vars)[6])))));
}
double BspDungeon__ConfigLambda__267__61(const GiglConfig  & config, const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss)
{

  return 0.3;
}
double BspDungeon__ConfigLambda__268__26(const GiglConfig  & config, const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss)
{

  return (0.1 * (*(*((double * *)(((config).vars)[7])))));
}
double BspDungeon__ConfigLambda__268__42(const GiglConfig  & config, const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss)
{

  return (0.2 * (*(*((double * *)(((config).vars)[8])))));
}
double BspDungeon__ConfigLambda__268__61(const GiglConfig  & config, const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss)
{

  return 0.3;
}
double BspDungeon__ConfigLambda__269__24(const GiglConfig  & config, const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss)
{

  return (0.7 * (((range).GetMinSpan)()));
}
double BspDungeon__ConfigLambda__269__53(const GiglConfig  & config, const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss)
{

  return 0.4;
}
double BspDungeon__ConfigLambda__270__27(const GiglConfig  & config, const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss)
{

  return (0.7 * (((range).GetMinSpan)()));
}
double BspDungeon__ConfigLambda__270__52(const GiglConfig  & config, const Range2D  & range, const Range1D  & cover_x, const Range1D  & cover_y, signed int  have_boss)
{

  return (1.0 - (0.3 + (0.3 + 0.4)));
}

BspDungeon  *GenerateDungeon(const Range2D  & whole_range, double  unit_min, double  unit_max, double  wall_min, double  have_boss_area)
{

  {
    return (new BspDungeon((GiglConfig(9, 15, ((sizeof(const Range2D *)) + ((sizeof(double *)) + ((sizeof(double *)) + ((sizeof(double *)) + ((sizeof(double *)) + ((sizeof(double *)) + ((sizeof(double *)) + ((sizeof(double *)) + (sizeof(double *)))))))))), (SizeVec{(sizeof(const Range2D *)), (sizeof(double *)), (sizeof(double *)), (sizeof(double *)), (sizeof(double *)), (sizeof(double *)), (sizeof(double *)), (sizeof(double *)), (sizeof(double *))}), (VarPtrVec{((VarPtr)(&((*((const Range2D * *)((malloc)((sizeof(const Range2D *)))))) = (&(whole_range))))), ((VarPtr)(&((*((double * *)((malloc)((sizeof(double *)))))) = (&(unit_min))))), ((VarPtr)(&((*((double * *)((malloc)((sizeof(double *)))))) = (&(unit_max))))), ((VarPtr)(&((*((double * *)((malloc)((sizeof(double *)))))) = (&(wall_min))))), ((VarPtr)(&((*((double * *)((malloc)((sizeof(double *)))))) = (&(have_boss_area))))), ((VarPtr)(&((*((double * *)((malloc)((sizeof(double *)))))) = (&(unit_min))))), ((VarPtr)(&((*((double * *)((malloc)((sizeof(double *)))))) = (&(unit_min))))), ((VarPtr)(&((*((double * *)((malloc)((sizeof(double *)))))) = (&(unit_min))))), ((VarPtr)(&((*((double * *)((malloc)((sizeof(double *)))))) = (&(unit_min)))))}), (IndexVec{0, 1, 2, 3, 4, 9, 10, 5, 11, 12, 6, 13, 7, 14, 8}), (FuncPtrVec{((FuncPtr)(&(BspDungeon__ConfigLambda__265__54))), ((FuncPtr)(&(BspDungeon__ConfigLambda__265__67))), ((FuncPtr)(&(BspDungeon__ConfigLambda__265__77))), ((FuncPtr)(&(BspDungeon__ConfigLambda__265__87))), ((FuncPtr)(&(BspDungeon__ConfigLambda__265__97))), ((FuncPtr)(&(BspDungeon__ConfigLambda__267__26))), ((FuncPtr)(&(BspDungeon__ConfigLambda__267__42))), ((FuncPtr)(&(BspDungeon__ConfigLambda__267__61))), ((FuncPtr)(&(BspDungeon__ConfigLambda__268__26))), ((FuncPtr)(&(BspDungeon__ConfigLambda__268__42))), ((FuncPtr)(&(BspDungeon__ConfigLambda__268__61))), ((FuncPtr)(&(BspDungeon__ConfigLambda__269__24))), ((FuncPtr)(&(BspDungeon__ConfigLambda__269__53))), ((FuncPtr)(&(BspDungeon__ConfigLambda__270__27))), ((FuncPtr)(&(BspDungeon__ConfigLambda__270__52)))})))));
  }
}


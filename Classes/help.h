//
//  help.h
//  FruitEat
//
//  Created by eisoo on 14-3-31.
//
//

#ifndef FruitEat_help_h
#define FruitEat_help_h
enum MoveDirection
{
    NONE=0,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum CellStatus
{
    cellNormale=0,
    cellHeightLight,
    cellDestory
};

struct CellIndex
{
    int columnPos;
    int rowPos;
};

enum AnimationType {
    
    OnlyMoveAnimation=0,
    OnlyMoveAnimation2=1,
    DeleteAnimation,
    DropAnimation
};


#endif

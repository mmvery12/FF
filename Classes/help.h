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

struct CellSquare
{
    int columnPos1;//zuo
    int columnPos2;//you
    int columnPos3;//xialuocell
};

enum AnimationType {
    
    OnlyMoveAnimation=0,
    OnlyMoveAnimation2=1,
    DeleteAnimation,
    DropAnimation,
    MoveAndDeleteAnimate,
    LightAnimate
};


#endif

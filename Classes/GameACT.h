//
//  MainACT.h
//  FishingEat
//
//  Created by eisoo on 14-2-14.
//
//

#ifndef __FishingEat__GameACT__
#define __FishingEat__GameACT__


#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <deque>
#include <map>
#include <pthread.h>
#include <algorithm> 

#include "SimpleAudioEngine.h"
#include "SceneManager.h"
#include "define.h"
#include "Category.h"
#include "FruntCell.h"
#include "help.h"
#include "ClickDelegate.h"
#include "define.h"

#include "cocos2d.h"
using namespace cocos2d;
using std::string;
using namespace std;


namespace Game {
	typedef int _MAX_ROW;
    typedef int _ROW;
    typedef int _COLUMN;
    typedef int _DROPLENGTH;
    
    typedef map<_ROW,_COLUMN> DropRange;
    typedef DropRange::iterator RangeIterator;
    typedef multimap<DropRange ,_DROPLENGTH> DropSubMap;
    typedef DropSubMap::iterator SubMapIterator;
    
    
    
    typedef pair<int, int> CellPos;
    typedef multimap<CellPos,DropSubMap> DropMap;//
    typedef DropMap::iterator MapIterator;
    typedef list<DropMap> DropList;
    typedef DropList::iterator ListIterator;
    typedef deque<DropList> Dropdeque;
    typedef Dropdeque::iterator DequeIterator;
    
    
#define MAXCOUNT 9
    
    static bool isCellIndexEqual(CellIndex cell1,CellIndex cell2)
    {
        if (cell1.columnPos==cell2.columnPos&&cell1.rowPos==cell2.rowPos) return true;
        return false;
    }
    
    static void *thr_fun(void *arge);
    
    void recuse(DeleteIterator it,DropMap *map,pair<DeleteIterator, DeleteIterator> Findpair,int topIndex);
    
    class GameLayer : public Layer,ClickDelegate{
        
        GameLayer();
		virtual ~GameLayer();
        void showTag();
    public:
        
    private:
		Category *cy;
		FruntCell *_tempCell1;
		FruntCell *_tempCell2;
        
        
        CellIndex compute(MoveDirection dir,CellIndex lastedClick);
        CellIndex _lastedClick;
        
        CellIndex compute2(MoveDirection dir,CellIndex lastedClick);
        CellIndex _lastedClick2;
        
        
        void loadGameMap();
        /*
         -1     NULL
         0      normal
         1      willanimate
         2      moving
         3      droping
         4      deleteing
         5      deleted
         99     storn
         */
        int cellsStatus[7][7];
        DeleteFNMap prefnmap;
        struct CmpByValue {
            bool operator()(const PAIR& lhs, const PAIR& rhs) {
                return lhs.second >= rhs.second;
            }
        };
        
        DeleteFNMap TODO_FindDeleteCells();
        bool TODO_DeleteCell();
        bool TODO_ResetCell();
        bool TODO_DropCell();
        Deletemultimap sortMapByRow(pair<DeleteIterator,DeleteIterator> Findpair,int column);
        void addNewCell(int addcount,int column);
        
        void timeCallBack();
        
        void checkColumnHaveAnimation();
        void destory();
        
        void registTwoCell(CellIndex c1,CellIndex c2);
        void addNewCells(int column);
        //FruntCell * randNewCell(int columnPos,int rowPos,bool isPlaying);
        FruntCell * createNewCell(int column,int row,bool isPlaying,int type ,int rowcount,int status);
        ProgressTimer *progress;
        float dtf;
        void pop(Ref *node);
        
        
        list<int> _isDrop;
        list<int> _isDeleteing;
        list<int> _isMoving;
        
        void findCurrent();
        DeleteFNMap TODO_FindDeleteCells2(int row,int column,int row2,int column2);
        DeleteList findRowDelete(string ss,int row);
        DeleteList findColDelete(string ss,int column);
        DeleteList findRowDelete2(string ss,int row,int row1,int col1,int row2,int col2);
        DeleteList findColDelete2(string ss,int column,int row1,int col1,int row2,int col2);
        string getCellTypeString(int row,int column);
    public:
        
        static Scene *createGameACTScene(void);
        virtual bool init();
        virtual void onEnter();
        virtual void update(float delta);
        CREATE_FUNC(GameLayer);
        //override for register one point touch
        //virtual void registerWithTouchDispatcher(void);
        //cctouch delegate
        virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
        virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
        virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
        
        //click delegate
        virtual void clickAtInde(CellIndex index);
        virtual void direction(MoveDirection dir,CellIndex lastedClick);
        
        virtual void willAnimate(Layer *cell);
        virtual void moving(Layer *cell);
        virtual void deleteing(Layer *cell);
        virtual void droping(Layer *cell);
        
        virtual void deleteComplete(Layer *cell);
        virtual void movingComplete(Layer *cell);
        virtual void dropComplete(Layer *cell);
    };
}
    
    

#endif /* defined(__FishingEat__GameACT__) */

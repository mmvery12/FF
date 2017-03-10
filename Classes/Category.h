

#ifndef __FishingEat__Category__
#define __FishingEat__Category__

#pragma once
#include "cocos2d.h"
#include "define.h"
using namespace cocos2d;
namespace Game
{
	class Category;
	typedef void (*back)(Category *category);
 #define callbackfc(_function) (back)(&_function)
 
	enum DeleteAnimationType
	{
		threeDelete,
		fiveDelte,
		ldelete
	};
	class Category
	{
	public:
		void noteDeleteCells(int row,int column,int celltype,int number);


		void compute(DeleteUnitList dprow,DeleteUnitList dpcolumn);
		Category(void);
		~Category(void);
	private:
        DeleteUnitList _dCMap;
		DeleteUnitList _dRMap;
		DeleteReturnMap _rMap;
		void RowC(DeleteUnitList &dprow,DeleteUnitList &dpcolumn,DeleteReturnMap rtMap);
		void ColumnC(DeleteUnitList &dpcolumn,DeleteUnitList &dprow,DeleteReturnMap rtMap);
	};


	
		



}
	
#endif

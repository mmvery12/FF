#include "Category.h"

namespace Game
{
	Category::Category(void)
	{
	}


	Category::~Category(void)
	{
	}

	void Category::noteDeleteCells(int row,int column,int celltype,int number)
	{
		if (celltype==0)
		{
			for (int i=0;i<number;i++)
			{
				if (0!=_dCMap.count(row+i))
				{
                    DeleteIterator it;
                    for (it=_dCMap.equal_range(column).first; it!=_dCMap.equal_range(column).second; ++it)
                    {
                        int itcolumn=it->first;
                        int itrow=it->second;
                        if (itrow==row) {
                            
                        }
                    }
				}else
				{
					_dRMap.insert(pair<int,int>(row+i,column));
				}
				
			}
		}else
			if (celltype==1)//
		{
			for (int i=0;i<number;i++)
			{
				if (0!=_dRMap.count(column+i))
				{
					DeleteIterator it;
                    for (it=_dRMap.equal_range(column+i).first; it!=_dRMap.equal_range(column+i).second; ++it)
                    {
                        int itcolumn=it->first;
                        int itrow=it->second;
                        if (itrow==row+i) {
                            
                        }
                    }
				}else
				{
					_dCMap.insert(pair<int,int>(column+i,row));
				}
				
			}
		}
	}

    
    
    
    
	void Category::compute(Deletemultimap dprow,Deletemultimap dpcolumn)
	{
		DeleteReturnMap returnMap;
		DeleteIterator itrow=dprow.begin();
		DeleteIterator itecol=dpcolumn.begin();
		if (dprow.empty()!=true
			&&dpcolumn.empty()!=true)//row&&column
		{
			for (itrow;itrow!=dprow.end();itrow++)
			{
				int row=itrow->first;
				int column=itrow->second;
				PosMap pos;
				pos.insert(pair<int,int>(row,column));
				MoveMap move;
				move.insert(pair<int,int>(0,0));
				returnMap.insert(pair<PosMap,MoveMap>(pos,move));
				DeleteIterator it;
				for (it=dpcolumn.equal_range(column).first; it!=dpcolumn.equal_range(column).second; ++it)
				{	
					int row2=it->second;
					if (row==row2)
					{
                        
					}else
					{

					}
				}
			}
		}else
		{
			if (dprow.empty()!=true)//only row
			{
				RowC(dprow,dpcolumn,returnMap);
			}else
				if (dpcolumn.empty()!=true)//only column
				{
					ColumnC(dpcolumn,dprow,returnMap);
				}
		}
	}
	void Category::RowC(Deletemultimap &dprow,Deletemultimap &dpcolumn,DeleteReturnMap returnMap)
	{
		for (int i=0;i<CELLNUM;i++)
		{
			int colcount=dprow.count(i);
			if (colcount==0)
			{
				continue;
			}else
			{
				DeleteIterator it=dprow.find(i);
				int index=0;
				for (it;it!=dprow.end();it++)
				{
					int row=it->first;
					int column=it->second;

					int rowCount=dpcolumn.count(i);//查看此列对应的行是否有删除的cell
					if (rowCount!=0)
					{
						/*for (DeleteIterator it=dpcolumn.find(i);it!=)
						{
						}*/
					}


					PosMap pos;
					pos.insert(pair<int,int>(row,column));
					MoveMap move;
					if (colcount<=3)
					{
						move.insert(pair<int,int>(0,0));
					}else
					{
						index++;
						if (index==0)
						{
							move.insert(pair<int,int>(1,0));
						}else if (index==1)
						{
							move.insert(pair<int,int>(0,0));
						}else if (index!=0&&index!=1)
						{
							move.insert(pair<int,int>(-(index-1),0));
						}
					}
					returnMap.insert(pair<PosMap,MoveMap>(pos,move));
				}




			}


		}
	}
	void Category::ColumnC(Deletemultimap &dpcolumn,Deletemultimap &dprow,DeleteReturnMap returnMap)
	{
		for (int i=0;i<CELLNUM;i++)
		{
			int count=dpcolumn.count(i);
			if (count==0)
			{
				continue;
			}else
			{
				DeleteIterator it=dpcolumn.find(i);
				int index=0;
				for (it;it!=dpcolumn.end();it++)
				{
					int column=it->first;
					int row=it->second;
					PosMap pos;
					pos.insert(pair<int,int>(row,column));
					MoveMap move;
					if (count<=3)
					{
						move.insert(pair<int,int>(0,0));
					}else
					{
						index++;
						if (index==0)
						{
							move.insert(pair<int,int>(0,1));
						}else if (index==1)
						{
							move.insert(pair<int,int>(0,0));
						}else if (index!=0&&index!=1)
						{
							move.insert(pair<int,int>(0,-(index-1)));
						}
					}
					returnMap.insert(pair<PosMap,MoveMap>(pos,move));
				}
			}
		}
	}
}
	




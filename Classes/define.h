#include <map>
#include <list>
using namespace std;
#define CELLNUM 9
typedef int column;
typedef int row;


#define CDestoryKO 9781
#define CNDestoryKO 9782
#define WhiteSpace  9783

typedef map<int,int> PosMap;
typedef map<int,int> MoveMap;
typedef map<int,int> CellMap;
typedef map<PosMap,MoveMap> DeleteReturnMap;
typedef pair<int, int> PAIR;



typedef list<long long> DeleteUnitList;
typedef DeleteUnitList::const_iterator DeleteUnitListIterator;


typedef list<DeleteUnitList> DeleteTotalUnitList;
typedef DeleteTotalUnitList::const_iterator DeleteTotalUnitListIterator;


typedef multimap<long long,DeleteUnitList> DeleteFNMap;
typedef DeleteFNMap::const_iterator DeleteFNMapIterator;

typedef  DeleteFNMap DropFNMap;
typedef DeleteFNMapIterator DropFNMapIterator;

typedef list<long long> QUJIANlist;

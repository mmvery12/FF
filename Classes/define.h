#include <map>
#include <list>
using namespace std;
typedef int column;
typedef int row;
typedef multimap<column,row> Deletemultimap;
typedef map<int,int> PosMap;
typedef map<int,int> MoveMap;
typedef map<int,int> CellMap;
typedef map<PosMap,MoveMap> DeleteReturnMap;
typedef Deletemultimap::const_iterator DeleteIterator;
typedef pair<int, int> PAIR;

typedef list<Deletemultimap> DeleteList;
typedef DeleteList::const_iterator DeleteListIterator;


typedef multimap<int,Deletemultimap> DeleteFNMap;
typedef DeleteFNMap::const_iterator DeleteFNMapIterator;

typedef  DeleteFNMap DropFNMap;
typedef DeleteFNMapIterator DropFNMapIterator;

#include <fstream>
#include <vector>
using namespace std;
class tb_qinshi
{
public:
	char qin_num[4];
	char qin_name[13];
	char qin_phone[9];
	char qin_area[6];
	vector<tb_qinshi> vecQin;
	bool read();
	char* getQin_name(char* qin_num);
};
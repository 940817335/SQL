#include <functional>
#include "tb_StuScor.h"

using namespace std;
class tb_StuScor:public unary_function<tb_StuScor,bool>
{
public:
    int num;
    explicit tb_StuScor(int argNum);
    bool operator ()(const tb_student& student);
};
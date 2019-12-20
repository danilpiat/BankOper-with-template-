
//#define NDEBUG
#include <iostream>
#include "bankint.h"
int debug = 0;
using namespace std;
int main() {
    Application<double> * app = new Application<double>;
    app->start();
    return 0;
}


// std::ostream& operator <<(std::ostream &os, const std::map<int, UsualDep*>::iterator &el){
//	return os<< el->first <<": "<<el->second<<endl;
//}
//std::ostream& operator <<(std::ostream &os, const std::map<int, UsualDep*>::const_iterator &el){
//	return os<< el->first <<": "<<el->second<<endl;
//}
// */
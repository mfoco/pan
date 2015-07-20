
#include <pan/range.hpp>

pan::best_fitting_integral<0, 10> uc1;
pan::best_fitting_integral<0, 255> uc2;
pan::best_fitting_integral<0, 256> us1;
pan::best_fitting_integral<0, 65535> us2;
pan::best_fitting_integral<0, 65536> ui1;
pan::best_fitting_integral<0, std::numeric_limits<uint32_t>::max()> ui2;
pan::best_fitting_integral<0, 1ull + std::numeric_limits<uint32_t>::max()> ull1;
pan::best_fitting_integral<0, std::numeric_limits<uint64_t>::max()> ull2;

pan::best_fitting_integral<-1, 10> sc1;
pan::best_fitting_integral<-1, 127> sc2;
pan::best_fitting_integral<-1, 128> ss1;
pan::best_fitting_integral<-1, 32767> ss2;
pan::best_fitting_integral<-1, 32768> si1;
pan::best_fitting_integral<-1, std::numeric_limits<int32_t>::max()> si2;
pan::best_fitting_integral<-1, 1ull + std::numeric_limits<int32_t>::max()> sll1;
pan::best_fitting_integral<-1, std::numeric_limits<int64_t>::max()> sll2;
//pan::best_fitting_integral<-1, std::numeric_limits<uint64_t>::max()> sll3; // this should fail


#include <typeinfo>
#include <iostream>

using namespace std;

int main()
{
    cout << typeid(uc1).name() << endl;
    cout << typeid(uc2).name() << endl;
    cout << typeid(us1).name() << endl;
    cout << typeid(us2).name() << endl;
    cout << typeid(ui1).name() << endl;
    cout << typeid(ui2).name() << endl;
    cout << typeid(ull1).name() << endl;
    cout << typeid(ull2).name() << endl;

    cout << typeid(sc1).name() << endl;
    cout << typeid(sc2).name() << endl;
    cout << typeid(ss1).name() << endl;
    cout << typeid(ss2).name() << endl;
    cout << typeid(si1).name() << endl;
    cout << typeid(si2).name() << endl;
    cout << typeid(sll1).name() << endl;
    cout << typeid(sll2).name() << endl;
}

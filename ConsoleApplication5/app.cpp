
#include "bankint.h"


template <class T> void Application<T>::find(int num) {
    auto it = a->get(num);
    cout << it.elem->first <<": "<< *(it.elem->second)<<endl;
    cout <<"interests: ";
    it.elem->second->print_interests(a->getCurDate(),a->getCurYear());
    cout<<endl;
}


template <class T> void Application<T>::printAll() {
    //a->arr.print();
    cout<<*a<<endl;
}

template <class T> void Application<T>::start() {
    int numx;
    cout << "put date:";
    cin >> numx;
    a->setCurDate(numx);
    cout << "put year:";
    cin >> numx;
    a->setCurYear(numx);
    int fl=1;
    while (fl) {
        try {
        int x;
        cout
                << "1 - add deposit\n2 - delete deposit\n3 - modify\n4 - print all\n5 - findDeposit\n6 - recalculate\n7 - reset current date,year\n9 - exit\n:";
        cin >> x;
        switch (x) {
            case 1: {
                int num;
                cout << "put number:";
                cin >> num;
                bool check = a->check(num);
                if (check) {addDeposit(num); }
                break;
            }
            case 2: {
                int num;
                cout << "put number:";
                cin >> num;
                bool check = a->check(num);
                if (!check) { closeDeposit(num);}

                break;
            }
            case 3: {
                int num;
                cout << "put number:";
                cin >> num;
                bool check = a->check(num);
                if (!check) {modify(num);}
                break;
            }
            case 4: {
                printAll();
                break;
            }
            case 5: {
                int num;
                cout << "put number:";
                cin >> num;
                bool check = a->check(num);
                if (!check) {find(num);}
                break;
            }
            case 6: {
                recalculate();
                break;
            }
            case 7: {
                int num;
                cout << "put date:";
                cin >> num;
                a->setCurDate(num);
                cout << "put year:";
                cin >> num;
                a->setCurYear(num);
                break;
            }
            case 9: {
                fl = 0;
                break;
            }
            default: {
                cout << "invalid option"<< endl;
                break;
            }
        }
    }  catch(exception &e){cout << e.what()<< endl;}
    }

}

template <class T> void Application<T>::recalculate() {

    for (auto it = a->arr->begin(); it.elem != nullptr; ++it)
    {
        it.elem->second->recalculate(a->getCurDate(),a->getCurYear());
    }
}

template <class T> void Application<T>::addDeposit(int num) {
    int x;
    cout<<"1-add Usual deposit\n2-add term deposit\n3-add currency deposit\n4 - exit\n:";
    cin >> x;
    switch (x) {
        case 1: {
                UsualDep *u = new UsualDep;
                int aa;
                double bb;

                cout << "put amount:";
                cin >> bb;
                u->setAmount(bb);
                cout << "put percent:";
                cin >> bb;
                u->setPercent(bb);
                cout << "put date:";
                cin >> aa;
                u->setDate(aa);
                u->setDateLast(aa);
                cout << "put year:";
                cin >> aa;
                u->setYear(aa);
                u->setNumber(num);
                //a->insert(u.getNumber(),uu);
                pairx* mypair=new pairx(num, u);
                a->insert( mypair);
            break;
        }
        case 2: {
                termDep *u = new termDep;
                int aa;
                double bb;
                cout << "put amount:";
                cin >> bb;
                u->setAmount(bb);
                cout << "put percent:";
                cin >> bb;
                u->setPercent(bb);
                cout << "put date:";
                cin >> aa;
                u->setDate(aa);
                u->setDateLast(aa);
                cout << "put year:";
                cin >> aa;
                u->setYear(aa);
                cout << "put SafeDate:";
                cin >> aa;
                u->setSafeDate(aa);
                u->setNumber(num);
                //a->insert(u.getNumber(),uu);
                pairx* mypair=new pairx(num, u);
                a->insert(mypair);

            break;
        }
        case 3: {
                currencyDep *u = new currencyDep;
                int aa;
                double bb;
                cout << "put amount:";
                cin >> bb;
                u->setAmount(bb);
                cout << "put percent:";
                cin >> bb;
                u->setPercent(bb);
                cout << "put date:";
                cin >> aa;
                u->setDate(aa);
                u->setDateLast(aa);
                cout << "put year:";
                cin >> aa;
                u->setYear(aa);
                cout << "put ExchangeRate:";
                cin >> aa;
                u->setExchangeRate(aa);
                u->setNumber(num);
                //a->insert(u.getNumber(),uu);
                pairx* mypair=new pairx(num, u);
                a->insert(mypair);
            break;
        }
        case 4:{break;}
        default:{cout<<"invalid option"; break;}
    }
}

template <class T> void Application<T>::modify(int num) {
    int x;
    cout<<"1-put money\n2-get money\n3-get interests\n4 - exit\n:";
    cin >> x;
    switch (x) {
        case 1: {
            int sum;
            cout<<"print sum:";
            cin >> sum;
            auto el = a->get(num);
            el.elem->second->recalculate(a->getCurDate(),a->getCurYear());
            double cursum = el.elem->second->getAmount();
            cout <<"was: " <<cursum<< endl;
            el.elem->second->setAmount(cursum +sum);
            cout <<"became: "<<el.elem->second->getAmount()<<endl;
            el.elem->second->setDate(a->getCurDate());
            el.elem->second->setDateLast(a->getCurDate());
            break;}
        case 2: {
            int sum;
            cout<<"print sum:";
            cin >> sum;
            auto el = a->get(num);
            el.elem->second->recalculate(a->getCurDate(),a->getCurYear());
            double cursum = el.elem->second->getAmount();
            if (sum>cursum) throw MyException("invalid sum");
            cout <<"was: "<<cursum << endl;
            el.elem->second->setAmount(cursum -sum);
            cout <<"became: "<< el.elem->second->getAmount()<< endl;
            el.elem->second->setDate(a->getCurDate());
            el.elem->second->setDateLast(a->getCurDate());
            break;}
        case 3: {
            auto el = a->get(num);
            cout <<"interests: "<< endl;
            el.elem->second->print_interests(a->getCurDate(),a->getCurYear());
            el.elem->second->setDate(a->getCurDate());
            el.elem->second->setDateLast(a->getCurDate());
            break;}
        case 4: {
            break;}
        default:{cout<<"invalid option"; break;}
    }
}

template <class T> void Application<T>::closeDeposit(int num) {
    a->erase(num);
}

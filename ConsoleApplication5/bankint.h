
#ifndef DAN2_BANKINT_H
#define DAN2_BANKINT_H
#include <iostream>
#include <map>
#include <cmath>
#include <vector>

using namespace std;
struct MyException : public std::exception
{
    std::string s;
    MyException(std::string ss) : s(ss) {}
    ~MyException() throw () {} // Updated
    const char* what() const throw() { return s.c_str(); }
};

class UsualDep
{
public:
    UsualDep()= default;
    UsualDep(double amount, double percent, int date, int year, int number);
    int getNumber() const;
    void setNumber(int _number);
    double getAmount() const;
    void setAmount(double _amount);
    int getDate() const;
    void setDate(int _date);
     int getDateLast() const;
    void setDateLast(int _dateLast);
    double getPercent() const;
    void setPercent(double _percent);
     double getYear() const ;
    void setYear(int _year);
    virtual std::ostream& show(ostream &os)const;
    virtual double the_amount_of_accrued_interest(int datex, int yearx);
    virtual void print_interests(int datex, int yearx);
    void recalculate (int datex, int yearx);

    friend ostream &operator<<(ostream &os, const UsualDep &dep);
    virtual void getMoney(double a, int date , int year);
protected:
    double amount;
    double percent;
    int date;
    int year;
    int dateLast;
    int number;
};
class termDep : public UsualDep
{
public:
    termDep(){};
    virtual std::ostream& show(ostream &os)const;
    termDep(double amount, double percent, int date, int year, int number, int safeDate);
   int getSafeDate() const;
    void setSafeDate(int _safeDate);
    virtual double the_amount_of_accrued_interest(int datex, int yearx);
    virtual void print_interests(int datex, int yearx);

    friend ostream &operator<<(ostream &os, const termDep &dep);
    virtual void getMoney(double a, int date , int year);
private:
    int safeDate;
};
class currencyDep : public UsualDep
{

public:
    virtual std::ostream& show(ostream &os)const;
    friend ostream &operator<<(ostream &os, const currencyDep &dep);
    currencyDep(){};
    currencyDep(double amount, double percent, int date, int year, int number, double exchange_rate);
    double getExchangeRate() const;
    void setExchangeRate(double _exchangeRate);
    virtual double the_amount_of_accrued_interest(int datex, int yearx);
    virtual void print_interests(int datex, int yearx);
    virtual double the_amount_of_accrued_interest_incurr(int datex, int yearx);
    virtual void getMoney(double a, int date , int year);
private:
    double exchange_rate;
};



class pairx{
public:
    pairx(int f,UsualDep* s):first(f),second(s){};
    friend ostream &operator<<(ostream &os, const pairx &pairx) {
        os << "first: " << pairx.first << " second: " <<*(pairx.second)<<endl;
        os<<(pairx.second==nullptr);
        return os;
    }

    pairx()= default;
    virtual ~pairx() {
        delete second;
    }
    int first;
    UsualDep* second;
};
template <class T>
class OwnIterator {
public:

   OwnIterator(pairx** v,int ii,size_t t,int ls) : i(ii),size(t),vector(v),lastx(ls){if(ii<lastx)elem=v[ii];
    else elem= nullptr;}
     OwnIterator &operator++();
   bool  operator!=(OwnIterator const &other) const;
    bool operator==(OwnIterator const &other) const;
    friend std::ostream &operator<<(std::ostream &os, const OwnIterator &iterator);
    bool outofrange(){return i>=lastx;}
    pairx* elem;
    pairx** vector ;
    int i;
    int lastx;
    size_t size;

};
template <class T>
class OwnContainer
{
public:
   OwnContainer(int t):beginx(0),lastx(0), size(t)
    {data=new pairx *[t];
    for(int j=0; j<t;j++){data[j]= nullptr;}};
   OwnIterator<T> begin();
   OwnIterator<T> end();
   OwnIterator<T> find(int k);



    pairx** data;
    int beginx;
    int lastx;
    int size;
};

template <class T>
class Assoc
{
private:
    int cur_date=0;
    int cur_year=0;
   OwnContainer<T>* getOwn() const { return arr; }
public:
    int getCurYear() const;
    void setCurYear(int curYear);
    int getCurDate() const;
    void setCurDate(int curCate);

public:
    OwnContainer<T>* arr;
    Assoc() {arr=new OwnContainer<T>(20);}
    Assoc(const Assoc&);
    ~Assoc() {};
    friend std::ostream& operator <<(std::ostream&, const Assoc&);
    void insert(pairx*);
    void erase(int n);
    OwnIterator<T> get(int x);
    bool check(int num);
    void swap(int k, int j);
};

template <class T>
class Application
{
private:
   Assoc<T>* a;
public:
    Application()
    { a = new Assoc<T>;}
    void start();
    void printAll();

    void recalculate();
    void addDeposit(int num);
    void closeDeposit(int num);
    void find(int num);
    void modify(int num);

};




#endif //DAN2_BANKINT_H
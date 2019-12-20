

#include "bankint.h"
void UsualDep::getMoney(double a, int d , int y){
    if (a>the_amount_of_accrued_interest(d,y)) throw MyException("not enough money");
    else setAmount(the_amount_of_accrued_interest(d,y)-a);
}
void termDep::getMoney(double a, int d , int y){
    if ((date-d)>safeDate)throw MyException("too much date");
    if (a>the_amount_of_accrued_interest(d,y)) throw MyException("not enough money");
    else setAmount(the_amount_of_accrued_interest(d,y)-a);
}
void currencyDep::getMoney(double a, int d , int y){
    if (a>the_amount_of_accrued_interest(d,y)) throw MyException("not enough money");
    else setAmount(the_amount_of_accrued_interest(d,y)-a);
}
UsualDep::UsualDep(double amount, double percent, int date, int year, int number)
{  if((amount<=0)||(percent<=0)|| (date<0)|| (year<0) || (dateLast<0)||(number<0) ) throw MyException("invalid params");
    UsualDep::amount=amount;
    UsualDep::percent=percent;
    UsualDep::date=date;
    UsualDep::year=year;
    UsualDep::dateLast=date;
    UsualDep::number=number;
}
[[nodiscard]] int UsualDep::getNumber() const {
    return number;
}
void UsualDep::setNumber(int _number) {
    if (_number<0) throw MyException("invalid number");
    UsualDep::number = _number;
}
[[nodiscard]] double UsualDep::getAmount() const {
    return amount;
}
void UsualDep::setAmount(double _amount) {
    if (_amount<0) throw MyException("invalid amount");
    UsualDep::amount = _amount;
}
[[nodiscard]] int UsualDep::getDate() const {
    return date;
}
void UsualDep::setDate(int _date) {
    if (_date<0) throw MyException("invalid date");
    UsualDep::date = _date;
}
[[nodiscard]] int UsualDep::getDateLast() const {
    return dateLast;
}
void UsualDep::setDateLast(int _dateLast) {
    if (_dateLast<0 || (_dateLast-date)<0 ) throw MyException("invalid last date");
    UsualDep::dateLast = _dateLast;
}
[[nodiscard]] double UsualDep::getPercent() const {
    return percent;
}
void UsualDep::setPercent(double _percent) {
    if (_percent<0) throw MyException("invalid percent");
    UsualDep::percent = _percent;
}
[[nodiscard]] double UsualDep::getYear() const {
    return year;
}
void UsualDep::setYear(int _year) {
    if (_year<0) throw MyException("invalid year");
    UsualDep::year = _year;
}

double UsualDep::the_amount_of_accrued_interest(int datex, int yearx)
{
    if (((datex - date) <0) ||  ((yearx - year) <0) ) { throw MyException("invalid date for interest");}
    dateLast=datex;
    return amount * pow(1+percent,double((datex +  360 * (yearx - year) - date)/30.0))-amount;
}
void UsualDep::print_interests(int datex, int yearx)
{
    if (((datex - date) <0) ||  ((yearx - year) <0) ) { throw MyException("invalid date for interest");}
    dateLast=datex;
    cout<< amount * pow(1+percent,double((datex +  360 * (yearx - year) - date)/30.0))-amount << endl;
}
void UsualDep::recalculate(int datex, int yearx)
{    if (((datex - date) <0) ||  ((yearx - year) <0) ) { throw MyException("invalid date for recalculate");}
   dateLast=datex;
   amount=amount * pow(1+percent,double((datex +  360 * (yearx - year) - date)/30.0));
    date=datex;
    year=yearx;
}




///-----------------------------------------------------------
termDep::termDep(double amount, double percent, int date, int year, int number, int safeDate) : UsualDep(
        amount, percent, date, year, number),safeDate(safeDate){};

[[nodiscard]] int termDep::getSafeDate() const {
    return safeDate;
}

void termDep::setSafeDate(int _safeDate) {
    if (_safeDate<=0) throw MyException("invalid safe date");
    termDep::safeDate = _safeDate;
}
double termDep::the_amount_of_accrued_interest(int datex, int yearx)
{
if ((datex-UsualDep::date)>safeDate) return  UsualDep::the_amount_of_accrued_interest(UsualDep::date+safeDate, yearx);
return UsualDep::the_amount_of_accrued_interest(datex, yearx);
}

void termDep::print_interests(int datex, int yearx)
{
    if ((datex-UsualDep::date)>safeDate) cout<< UsualDep::the_amount_of_accrued_interest(UsualDep::date+safeDate, yearx)<<endl;
    else cout<<UsualDep::the_amount_of_accrued_interest(datex, yearx)<<endl;
}




///---------------------------------------------------------------------
currencyDep::currencyDep(double amount, double percent, int date, int year, int number, double exchange_rate) :
        UsualDep(amount, percent,
                 date, year,number)
{
    if (exchange_rate<=0) throw MyException("invalid exchange rate");
    currencyDep::exchange_rate=exchange_rate;
}


[[nodiscard]] double currencyDep::getExchangeRate() const {
    return exchange_rate;
}

void currencyDep::setExchangeRate(double _exchangeRate) {
    if (_exchangeRate<=0) throw MyException("invalid exchange rate");
    exchange_rate = _exchangeRate;
}

double currencyDep::the_amount_of_accrued_interest(int datex, int yearx)  { return UsualDep::the_amount_of_accrued_interest(datex, yearx);}

double currencyDep::the_amount_of_accrued_interest_incurr(int datex, int yearx)  { return UsualDep::the_amount_of_accrued_interest(datex, yearx)* exchange_rate;}

void currencyDep::print_interests(int datex, int yearx)
{
    cout<<"in currency: " << the_amount_of_accrued_interest(datex, yearx) << endl;
    cout<<"in rub: " << the_amount_of_accrued_interest_incurr(datex, yearx)<<endl;
}



ostream &operator<<(ostream &os, const currencyDep &dep) {
    return dep.show(os);
}
ostream &operator<<(ostream &os, const UsualDep &dep) {
    return dep.show(os);
}
ostream &operator<<(ostream &os, const termDep &dep) {
    return dep.show(os);
}


std::ostream& UsualDep::show(ostream &os)const {
    return  os <<"Usual Deposit: "<< "amount: " << getAmount() << " percent: " << getPercent()
    << " date: " << getDate() << " year: "<< getYear()
               << " dateLast: " << getDateLast();
}
std::ostream& termDep::show(ostream &os)const {
    return  os <<"Term Deposit: "<< "amount: " << getAmount() << " percent: " << getPercent()
               << " date: " << getDate() << " year: "<< getYear()
               << " dateLast: " << getDateLast()
               << " safeDate: " <<getSafeDate();
}
std::ostream& currencyDep::show(ostream &os)const {
    return  os <<"Currency Deposit: "<< "amount: " << getAmount() << " percent: " << getPercent()
               << " date: " << getDate() << " year: "<< getYear()
               << " dateLast: " << getDateLast()
               << " ExchangeRate: " <<getExchangeRate()<<" in rub: "<<getAmount() *getExchangeRate();
}


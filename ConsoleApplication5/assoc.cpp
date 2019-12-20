
#include "bankint.h"

template <class T> Assoc<T>::Assoc(const Assoc &a) {
    for (auto it = arr->begin(); it != a.getOwn()->end(); ++it)
    {arr->data[arr->lastx]=new pairx(it.elem->first, it.elem->second);arr->lastx++;}
}


template <class T> std::ostream &operator<<(std::ostream &s, const Assoc<T> &a) {
    s << "===== Assoc =====" << std::endl;
    for(auto it = a.getOwn()->begin();it!=a.getOwn()->end();++it)
        s<<it;
    s<<a.getOwn()->lastx;
    return s;
}
template <class T> void Assoc<T>::insert(pairx* s) {
    if(arr->lastx==arr->size){
        int oldsize=arr->size;
        arr->size+=arr->size;
        pairx ** temp = new pairx*[arr->size];
        void* t = memcpy(temp, arr->data, (oldsize) * sizeof(pairx*));
        if (t==nullptr) throw std::runtime_error("error");
        arr->data=temp;
    }
    auto ix=arr->find(s->first);
    if(ix.elem==nullptr)
    {arr->data[arr->lastx]=s;arr->lastx++;}
}
template <class T> void Assoc<T>::swap(int k,int j)
{
    if (k==j)return;
    if(j>k){auto c=arr->data[j]; arr->data[j]=arr->data[k]; arr->data[k]=c;}
}
template <class T> void Assoc<T>::erase(int k)  {
    auto a=arr->find(k);
    int key=a.i;
    swap(key,arr->lastx-1);
    delete a.elem;
    a.elem=nullptr;
    arr->lastx--;
}
template <class T> OwnIterator<T> Assoc<T>::get(int x) {
    auto ix=arr->find(x);
    if (!ix.elem)
        throw MyException("illegal index");
    return ix;
    //cout <<"number = "<<p->first <<"\nDeposit = "<< p->second << endl;
}

template <class T> bool Assoc<T>::check(int s)
{
    auto  p = arr->find(s);
    return p.i == arr->lastx;
}

template <class T> int Assoc<T>::getCurDate() const {
    return cur_date;
}

template <class T> void Assoc<T>::setCurDate(int curCate) {
    cur_date = curCate;
}

template <class T> int Assoc<T>::getCurYear() const {
    return cur_year;
}

template <class T> void Assoc<T>::setCurYear(int curYear) {
    cur_year = curYear;
}

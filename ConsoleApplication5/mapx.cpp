
#include "bankint.h"
template <class T>OwnIterator<T> OwnContainer<T>::begin() {return OwnIterator<T>(data,beginx,size,lastx);}
template <class T>OwnIterator<T> OwnContainer<T>::end()  {return OwnIterator<T>(data,lastx,size,lastx);}
template <class T>OwnIterator<T> OwnContainer<T>::find(int k) {
    OwnIterator<T> ix=begin();
    for(;((ix!=end())&&(ix.elem->first!=k));++ix);
    return ix;
}

template <class T>OwnIterator<T> &OwnIterator<T>::operator++(){elem=vector[++i];return *this;}
template <class T> bool OwnIterator<T>::operator!=(OwnIterator<T> const& other) const{return i != other.i;}
template <class T> bool OwnIterator<T>::operator==(OwnIterator<T> const& other) const{return i == other.i;}
std::ostream &operator<<(std::ostream &os,const OwnIterator<class T> &iterator) {return os << *(iterator.elem);}


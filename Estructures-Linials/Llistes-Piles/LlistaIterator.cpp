//
// Created by tonix on 19/10/2020.
//

#include "LlistaIterator.h"


// Cost: (1)
template <typename T>
LlistaIterator<T>::LlistaIterator() {
    _head = new node;
    _head->next = _head->prev = _head;
    _sz = 0;
}

// Cost: (n)
template <typename T>
LlistaIterator<T>::LlistaIterator(const LlistaIterator<T> &l) throw(){
    _head = new node;
    _head->next = copiar_llista(l._head->next,
                                l._head, _head);
    _head->next->prev = _head;
    _sz = l._sz;
}

// Cost: (n)
template <typename T>
typename LlistaIterator<T>::node*LlistaIterator<T>::copiar_llista(node* orig, node* orig_head, node* h) throw() {
    node* dst = h;
    if (orig != orig_head) {
        dst = new node;
        try {
            dst->info = orig->info;
            dst->next = copiar_llista(orig->next,
                                      orig_head, h);
            dst -> next -> prev = dst;
        }
        catch (...) {
            delete dst;
            throw;
        }
    }
    return dst;
}

// Cost: (n)
template <typename T>
LlistaIterator<T>& LlistaIterator<T>::operator=(const LlistaIterator<T> & l) throw() {
    if (this != &l) {
        LlistaIterator<T> aux = l;
        swap(aux);
    }
    return *this;
}

// Cost: (1)
template <typename T>
void LlistaIterator<T>::swap(LlistaIterator<T> &l) throw(){
    node* auxn = _head;
    _head = l._head;
    l._head = auxn;
    int auxs = _sz;
    _sz = l._sz;
    l._sz = auxs;
}

// Cost: (n)
template <typename T>
void LlistaIterator<T>::destruir_llista(node* p, node* h) throw(){
    if (p != h) {
        destruir_llista(p->next, h);
        delete p;
    }
}

// Cost: (n)
template <typename T>
LlistaIterator<T>::~LlistaIterator() throw(){
    destruir_llista(_head->next, _head);
    delete _head;
}

// Cost: (1)
template <typename T>
LlistaIterator<T>::iterador::iterador(){
}

// Cost: (1)
template <typename T>
const T& LlistaIterator<T>::iterador::operator*() const
throw() {
    if (_p == _h) {
        throw (IteradorIndef);
    }
    return _p->info;
}

// Cost: (1)
template <typename T>
typename LlistaIterator<T>::iterador&LlistaIterator<T>::iterador::operator++() throw(){
    if (_p != _h) {
        _p = _p->next;
    }
    return *this;
}
// Cost: (1)
//Operador postincrement a++
template <typename T>
typename LlistaIterator<T>::iterador LlistaIterator<T>::iterador::operator++(int) throw() {
    iterador tmp(*this);
    ++(*this); // es crida al mètode de preincrement
    return tmp;
}


// Cost: (1)
template <typename T>
bool LlistaIterator<T>::iterador::operator==(iterador it)const throw() {
    return (_p == it._p) and (_h == it._h);
}

// Cost: (1)
template <typename T>
bool LlistaIterator<T>::iterador::operator!=(iterador it)const throw() {
    return not (*this == it);
}

// Cost: (1)
template <typename T>
typename LlistaIterator<T>::iterador&LlistaIterator<T>::iterador::operator--() throw() {
    if (_p != _h) {
        _p = _p->prev;
    }
    return *this;
}

// Cost: (1)

template <typename T>
typename LlistaIterator<T>::iterador LlistaIterator<T>::iterador::operator--(int) throw() {
    iterador tmp(*this);
    --(*this); // es crida al mètode de predecrement
    return tmp;
}

// Cost: (1)
template <typename T>
void LlistaIterator<T>::inserir_davant(const T& x, iterador it) throw(){
    node* nn = new node;
    // no sabem com és el tipus T. Cap la possibilitat
    // que usi memòria dinàmica i per tant cal comprovar
    // que tot vagi bé.
    try {
        nn->info = x;
    }catch(...) {
        delete nn;
        throw;
    }
    nn->next = it._p->next;
    nn->prev = it._p;
    it._p->next = nn;
    nn->next->prev = nn;
    ++_sz;
}
// Cost: (1)
template <typename T>
void LlistaIterator<T>::inserir_darrera(const T& x, iterador it) throw(){
    node* nn = new node;
    try {
        nn -> info = x;
    }catch(...) {
        delete nn;
        throw;
    }
    nn->prev = it._p->prev;
    nn->next = it._p;
    it._p -> prev = nn;
    nn -> prev -> next = nn;
    ++_sz;
}

// Cost: (1)
template <typename T>
void LlistaIterator<T>::esborrar_avnc(iterador& it) throw() {
    if (it._p != _head) {
        node* todel = it._p;
        todel->prev->next = todel->next;
        todel->next->prev = todel->prev;
        delete todel;
        --_sz;
        it._p = it._p -> next;
    }
}
// Cost: (1)
template <typename T>
void LlistaIterator<T>::esborrar_darr(iterador& it) throw() {
    if (it._p != _head) {
        node* todel = it._p;
        todel->prev->next = todel->next;
        todel->next->prev = todel->prev;
        delete todel;
        --_sz;
        it._p = it._p->prev;
    }
}
// Cost: (1)
template <typename T>
nat LlistaIterator<T>::longitud() const throw() {
    return _sz;
}
// Cost: (1)
template <typename T>
bool LlistaIterator<T>::es_buida() const throw() {
    return _sz == 0;
}
// Cost: (1)
template <typename T>
typename LlistaIterator<T>::iterador LlistaIterator<T>::primer() const throw() {
    iterador it;
    it._p = _head->next;
    it._h = _head;
    return it;
}
// Cost: (1)
template <typename T>
typename LlistaIterator<T>::iterador LlistaIterator<T>::ultim() const throw() {
    iterador it;
    it._p = _head -> prev;
    it._h = _head;
    return it;
}
// Cost: (1)
template <typename T>
typename LlistaIterator<T>::iterador LlistaIterator<T>::indef() const throw() {
    iterador it;
    it._p = _head;
    it._h = _head;
    return it;
}

template<typename T>
void LlistaIterator<T>::mostra() const {
    iterador i = primer();
    while (i != indef()){
        cout <<*i<<" ";
        i++;
    }
    cout<<endl;
}

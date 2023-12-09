//
// Created by z yu on 03/11/2023.
//

#ifndef PSCR_TME_INVERSE_H
#define PSCR_TME_INVERSE_H
#include <unordered_map>
#include <forward_list>
#include <vector>
#include <functional>
#include <string>
#include <iostream>
using  namespace std;

 class Person {
     string nom;
     string prenom;
     public :
     Person(const string & nom, const string & prenom):nom(nom),prenom(prenom){}
     const string & getPrenom() const { return prenom ;}
     const string & getNom() const { return nom ;}
     };

template<typename K,typename V>
std::unordered_map<V,std::forward_list<K> > inverse(const std::unordered_map<K,V> & src){
    std::unordered_map<V,std::forward_list<K>> dest;
    for (auto & e : src){
        dest[e.second].push_front(e.first);
    }
    return dest;
}

template<typename T>
unordered_map<string,forward_list<T> > groupBy (const vector<T> & src){
    unordered_map<string,std::forward_list<T>> dest;
    for (auto & e : src){
        dest[e.getPrenom()].push_front(e);
    }
    return dest;
}





#endif //PSCR_TME_INVERSE_H

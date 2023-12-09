//
// Created by z yu on 02/11/2023.
//

#ifndef PSCR_TME_TME3_H
#define PSCR_TME_TME3_H

#include <cstddef>
#include <ostream>
#include <forward_list>
#include <vector>


namespace pr{

    template<typename iterator>
    size_t count(iterator begin,iterator end){
        size_t sz = 0;
        while(begin != end){
            sz ++;
            begin ++;
        }
        return  sz;
    }

    template<typename iterator,typename T>
    size_t count_if_equal(iterator begin,iterator end,const T& val){
        size_t sz = 0;
        while(begin != end){
            if(*begin == val)
            {  sz ++; }
            begin ++;
        }
        return sz;
    }












}

#endif //PSCR_TME_TME3_H

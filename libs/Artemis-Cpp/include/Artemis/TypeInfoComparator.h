/****************************************************************************
 * TypeInfoComparator.h
 * Gasboy
 *
 * Created by Stefan Nguyen on 9/12/12.
 *
 * Copyright Vinova Pte. Ltd. All rights reserved.
 ****************************************************************************/

#ifndef Gasboy_TypeInfoComparator_h
#define Gasboy_TypeInfoComparator_h

#include <typeinfo>

struct type_info_comparator {
  bool operator ()(const std::type_info* a, const std::type_info* b) const {
    return a->before(*b);
  }
};


#endif

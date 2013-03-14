//
//  utilities.h
//  gen-usb
//
//  Created by Jenny Valdez on 12/03/13.
//  Copyright (c) 2013 Jenny Valdez & Luis Vieira. All rights reserved.
//

#ifndef __gen_usb__utilities__
#define __gen_usb__utilities__

#include "individual.h"

// Busqueda binaria de acuerdo al fitness <= key
int specialBinarySearch(std::vector<float> vec, float key);

// Mergesort de acuerdo al fitness
void mergeSort(std::vector<Individual>& v, int start, int end);


// Mergesort de acuerdo al fitness relativo
void mergeSort(std::vector<Individual>& v, int start, int end, float sum);

#endif /* defined(__gen_usb__utilities__) */

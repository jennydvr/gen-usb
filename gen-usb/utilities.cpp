//
//  utilities.cpp
//  gen-usb
//
//  Created by Jenny Valdez on 12/03/13.
//  Copyright (c) 2013 Jenny Valdez & Luis Vieira. All rights reserved.
//

#include "utilities.h"

bool compareFitness(Individual x, Individual y)
{
    return x.getFitness() < y.getFitness();
}

int specialBinarySearch(std::vector<float> vec, float key)
{
    int start = 0, end = (int)vec.size() - 1;
    
    // Retorna el individuo tal que vec[x] <= key
    while (end >= start)
    {
        int mid = start + (end - start) / 2;
        
        if (vec[mid] < key)
            start = mid + 1;
        else
            return mid;
    }
    
    // No hallado - retorna cualquier cosa
    return rand() % vec.size();
}
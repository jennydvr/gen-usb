//
//  individual.h
//  gen-usb
//
//  Created by Jenny Valdez on 07/03/13.
//  Copyright (c) 2013 Jenny Valdez & Luis Vieira. All rights reserved.
//

#ifndef __gen_usb__individual__
#define __gen_usb__individual__

#include <iostream>
#include <bitset>
#include <vector>
#include <sstream>
#include <random>

#define PENALTY 0

extern std::vector<std::bitset<66>> trainingExamples;

class Individual {

protected:
    
    // Numero de reglas
    int numRules;
    
    // Fitness del individuo
    float fitness;
    
    // Reglas que contiene el individuo
    std::string rules;
    
    // Chequea si esta regla admite el ejemplo dado
    int matches(std::bitset<66> example);
    
    // Crea una regla
    std::string createRule(int type);
    
public:
    
    // Constructor aleatorio
    Individual();
    
    // Retorna el fitness de este individuo
    float getFitness();
    
};

#endif /* defined(__gen_usb__individual__) */

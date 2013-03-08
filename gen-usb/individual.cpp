//
//  individual.cpp
//  gen-usb
//
//  Created by Jenny Valdez on 07/03/13.
//  Copyright (c) 2013 Jenny Valdez & Luis Vieira. All rights reserved.
//

#include "individual.h"

using namespace std;

vector<bitset<66>> trainingExamples;

Individual::Individual()
{
    // Creo x reglas aleatorias
    numRules = rand() % 4 + 1;
    
    stringstream ss;
    int init = rand() % 2;
    
    for (int i = 0; i != numRules; ++i)
        ss << createRule((i + init) % 2);
    
    rules = ss.str();
    
    
    // Calculo el fitness
    fitness = 0;
    
    for (int i = 0; i != trainingExamples.size(); ++i)
        fitness += matches(trainingExamples[i]);
    
    fitness = fitness * 100.0 / (float)trainingExamples.size();
    
    fitness = fitness * fitness + PENALTY * numRules * 100 / 4;
}

string Individual::createRule(int type)
{
    unsigned int seed = (unsigned int)chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(0, 1);
    
    stringstream ss;
    
    for (int i = 0; i != 65; ++i)
        ss << distribution(generator);
    
    ss << type;
    
    return ss.str();
}

int Individual::matches(bitset<66> example)
{
    string x = example.to_string();
    for (int i = 0; i != numRules; ++i) {
        
        string y = rules.substr(i * 66, 66);
        
        bitset<66> rule = bitset<66>(rules.substr(i * 66, 66));
        
        // No considerar las reglas que no clasifiquen a lo mismo
        if (rule[0] != example[0])
            continue;
        
        // E[n] == 1 => R[n] == 1
        if ((int)(~example | rule).count() != 66)
            return 0;
    }
    
    return 1;
}

float Individual::getFitness()
{
    return fitness;
}

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

#define PSIZE 0.0
#define PONES 0.005
#define RULESIZE 66
#define MINRULES 2
#define MAXRULES 15

extern std::vector<std::bitset<66>> trainingExamples;

class Individual {

protected:
    
    // Numero de reglas
    int numRules;
    
    // Fitness del individuo
    float fitness;
    
    // Reglas que contiene el individuo
    std::string rules;
    
    // Chequea si el individuo admite el ejemplo dado
    int matches(std::bitset<66> example);
    
    // Crea una regla aleatoria
    std::string createRule(int type);
    
    // Calcula el fitness
    void calculateFitness();
    
    // Cruza dos individuos con crossover de dos puntos
    static std::vector<Individual> twoPointCrossover(Individual &mom, Individual &dad);
    
public:
    
    // Constructor aleatorio
    Individual();
    
    // Constructor con regla
    Individual(std::string r);
    
    // Retorna el fitness de este individuo
    float getFitness();
    
    // Muta el individuo con una mutacion puntual
    void mutate();
    
    // Cruza dos individuos
    static std::vector<Individual> crossover(Individual &p1, Individual &p2);
    
    // Imprime este individuo
    std::string toString();
    
};

#endif /* defined(__gen_usb__individual__) */

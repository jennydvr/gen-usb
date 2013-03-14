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

#define PSIZE 0
#define RULESIZE 66
#define NUMFEATURES 16
#define MINRULES 1
#define MAXRULES 5

// Ejemplos para el calculo del fitness
extern std::vector<std::bitset<66>> trainingExamples;

// Tamano de cada caracteristica en la regla
extern int FEATURESIZE[16];

// Comienzo de cada feature en la regla
extern int FEATUREINDEXES[16];

class Individual {

protected:
    
    // Numero de reglas
    int numRules;
    
    // Porcentaje de ejemplos hace match el individuo
    float classified;
    
    // Reglas que contiene el individuo
    std::string rules;
    
    // Crea una regla aleatoria
    std::string createRule(int type);
    
    // Calcula el fitness
    void calculateFitness();
    
    // Cruza dos individuos con crossover de dos puntos
    static std::vector<Individual> twoPointCrossover(Individual &mom, Individual &dad);
    
    // Chequea si el individuo admite el ejemplo dado
    int matches(std::bitset<66> example);
    
public:
    
    // Fitness del individuo
    float fitness;
    
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
    
    // Operador add alternative
    void addAlternative();
    
    // Operador drop condition
    void dropCondition();
    
    // Imprime este individuo
    std::string toString();
};

#endif /* defined(__gen_usb__individual__) */

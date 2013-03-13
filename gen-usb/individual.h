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

#define PSIZE 0.2
#define RULESIZE 66
#define NUMFEATURES 16
#define MINRULES 1
#define MAXRULES 10

// Ejemplos para el calculo del fitness
static std::vector<std::bitset<66>> trainingExamples;

// Tamano de cada caracteristica en la regla
static int FEATURESIZE[16] = {2, 5, 5, 4, 3, 14, 9, 4, 2, 2, 2, 2, 3, 4, 3, 2};

// Comienzo de cada feature en la regla
static int FEATUREINDEXES[16] = {0, 2, 7, 12, 16, 19, 33, 42, 46, 48, 50, 52, 54, 57, 61, 64};

class Individual {

protected:
    
    // Numero de reglas
    int numRules;
    
    // Fitness del individuo
    float fitness;
    
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

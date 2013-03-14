//
//  geneticAlgorithm.cpp
//  gen-usb
//
//  Created by Jenny Valdez on 08/03/13.
//  Copyright (c) 2013 Jenny Valdez & Luis Vieira. All rights reserved.
//

#include "geneticAlgorithm.h"

#define POPSIZE 100

using namespace std;

float crossoverRate = 0.25;
float mutationRate = 0.25;

vector<Individual> tournamentSelection(vector<Individual> &population, int size)
{
    vector<Individual> newPopulation;
    
    vector<int> indexes;
    for (int i = 0; i != population.size(); ++i)
        indexes.push_back(i);
    
    while (newPopulation.size() != size)
    {
        // Selecciono dos individuos aleatorios
        int a = rand() % indexes.size();
        int b = rand() % (indexes.size() - 1);
        
        if (b == a)
            ++b;
        
        // Seleccionar al mejor entre a y b
        if (population[indexes[a]].getFitness() < population[indexes[b]].getFitness())
            a = b;
        
        newPopulation.push_back(population[indexes[a]]);
        
        // Elimino al individuo que acabo de utilizar
        swap(indexes[a], indexes.back());
        indexes.pop_back();
    }
    
    return newPopulation;
}

vector<Individual> rouletteSelection(vector<Individual> population, int size)
{
    vector<Individual> newPopulation;
    
    // Calcular el fitness total
    vector<int> indexes;
    float sum = 0;
    for (int i = 0; i != (int)population.size(); ++i) {
        sum += population[i].getFitness();
        indexes.push_back(i);
    }
    
    // Ordenar la poblacion
    //mergeSort(population, 0, (int)population.size() - 1);
    bool takeone = false;
    while (newPopulation.size() != size)
    {   
        takeone = false;
        float prob = (float)rand()/((float)RAND_MAX/sum);
        float aux = 0;
                
        for (int i = (int)indexes.size() - 1; i != -1; --i) {
            aux += population[indexes[i]].getFitness();
            
            
            if (aux >= prob) {
                newPopulation.push_back(population[indexes[i]]);
                
                sum -= population[indexes[i]].getFitness();
                indexes.erase(indexes.begin() + i);
                takeone = true;
                break;
            }
            
        }
        if (!takeone) {
            newPopulation.push_back(population.back());
            sum -= population.back().getFitness();
            indexes.pop_back();
        }
    }
    
    return newPopulation;
}

vector<Individual> rankingSelection(vector<Individual> population, int size)
{
    vector<Individual> newPopulation;
    
    // Calcular el fitness total
    float sum = 0;
    for (int i = 0; i != (int)population.size(); ++i)
        sum += population[i].getFitness();
    
    // Ordenar la poblacion por fitness relativo
    mergeSort(population, 0, (int)population.size() - 1, sum);
    
    for (int i = (int)population.size() - 1; i != (int)population.size() - 1 - size; --i)
        newPopulation.push_back(population[i]);
    
    return newPopulation;
}

vector<Individual> elitismSelection(vector<Individual> &population, int size)
{
    vector<Individual> newPopulation;
    
    // Ordenar la poblacion
    mergeSort(population, 0, (int)population.size() - 1);
    
    for (int i = (int)population.size() - 1; i != (int)population.size() - 1 - size; --i)
        newPopulation.push_back(population[i]);
    
    return newPopulation;
}

Individual findBest(vector<Individual> population)
{
    int bestIndex = 0;
    float bestFit = numeric_limits<float>::min();
    
    for (int i = 0; i != population.size(); ++i)
        if (population[i].getFitness() >= bestFit) {
            bestIndex = i;
            bestFit = population[i].getFitness();
        }
    
    return population[bestIndex];
}

Individual geneticAlgorithm(int epochs)
{
    // Inicializacion aleatoria
    vector<Individual> population;
    for (int i = 0; i != POPSIZE; ++i)
        population.push_back(Individual());
    
    for (int e = 0; e != epochs && findBest(population).getFitness() < 10000; ++e)
    {
        cout << e << "\n" << findBest(population).toString() << "\n\n";
        
        // Seleccion de padres
        int np = crossoverRate * POPSIZE;
        if (np % 2 != 0)
            np += 1;
        
        vector<Individual> parents = rouletteSelection(population, np);
        
        // Crossover
        vector<Individual> offspring;
        for (int i = 0; i != parents.size(); i += 2)
        {
            vector<Individual> osp = Individual::crossover(parents[i], parents[i+1]);
            offspring.push_back(osp[0]);
            offspring.push_back(osp[1]);
        }
        
        // Mutacion
        int maxMutation = mutationRate * offspring.size();
        for (int i = 0; i != maxMutation; ++i)
            offspring[i].mutate();
        
        // Seleccion de sobrevivientes
        for (int i = 0; i != offspring.size(); ++i)
            population.push_back(offspring[i]);
        
        population = rouletteSelection(population, POPSIZE);
    }
    
    cout << findBest(population).toString() << "\n\n";
    
    // Retornar el mejor individuo
    return findBest(population);
}


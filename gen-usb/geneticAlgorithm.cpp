//
//  geneticAlgorithm.cpp
//  gen-usb
//
//  Created by Jenny Valdez on 08/03/13.
//  Copyright (c) 2013 Jenny Valdez & Luis Vieira. All rights reserved.
//

#include "geneticAlgorithm.h"

#define POPSIZE 500

using namespace std;

float crossoverRate = 0.25;
float mutationRate = 0.25;

bool compareFitness(Individual x, Individual y)
{
    return x.getFitness() < y.getFitness();
}

int binarySearch(vector<Individual>& vec, float key)
{
    int end = (int)vec.size() - 1, start = 0;
    
    while (end >= start)
    {
        int mid = start + ((end - start) / 2);
        
        if (vec[mid].getFitness() < key)
            start = mid + 1;
        else
            return mid;
    }
    
    // si no hay ni un caso que coincida, retorna cuaquier cosa
    return rand() % vec.size();
}

vector<Individual> tournamentSelection(vector<Individual> population, int size)
{
    vector<Individual> newPopulation;
    
    while (newPopulation.size() != size)
    {
        // Selecciono dos individuos aleatorios
        int a = rand() % population.size();
        int b = rand() % (population.size() - 1);
        
        if (b == a)
            ++b;
        
        // Seleccionar al mejor entre a y b
        if (population[a].getFitness() < population[b].getFitness())
            a = b;
        
        newPopulation.push_back(population[a]);
        population.erase(population.begin() + a);
    }
    
    return newPopulation;
}

vector<Individual> rouletteSelection(vector<Individual> population, int size)
{
    vector<Individual> newPopulation;
    
    stable_sort(population.begin(), population.end(), compareFitness);
    float max = population.back().getFitness();
    
    while (newPopulation.size() != size)
    {
        int pos = binarySearch(population, (float)rand()/((float)RAND_MAX/max));
        
        newPopulation.push_back(population[pos]);
        population.erase(population.begin() + pos);
    }
    
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
        
        population = tournamentSelection(population, POPSIZE);
    }
    
    cout << findBest(population).toString() << "\n\n";
    
    // Retornar el mejor individuo
    return findBest(population);
}


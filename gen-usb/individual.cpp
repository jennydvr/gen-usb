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
int FEATURESIZE[16] = {2, 5, 5, 4, 3, 14, 9, 4, 2, 2, 2, 2, 3, 4, 3, 2};
int FEATUREINDEXES[16] = {0, 2, 7, 12, 16, 19, 33, 42, 46, 48, 50, 52, 54, 57, 61, 64};

Individual::Individual()
{
    // Creo x reglas aleatorias
    numRules = rand() % (MAXRULES - MINRULES + 1) + MINRULES;
    int init = rand() % 2;
    stringstream ss;
    
    for (int i = 0; i != numRules; ++i)
        ss << createRule((i + init) % 2);
    
    rules = ss.str();
    fitness = classified = numeric_limits<float>::min();
}

Individual::Individual(string r)
{
    rules = r;
    numRules = (int)rules.size() / RULESIZE;
    fitness = classified = numeric_limits<float>::min();
}

string Individual::createRule(int type)
{
    stringstream ss;
    
    for (int i = 0; i != RULESIZE - 1; ++i)
        ss << rand() % 2;
    
    ss << type;
    
    return ss.str();
}

void Individual::calculateFitness()
{
    // Calculo el % de ejemplos clasificados
    classified = 0;
    
    for (int i = 0; i != (int)trainingExamples.size(); ++i)
        classified += (float)matches(trainingExamples[i]);
    
    classified = classified * 100.0 / (float)trainingExamples.size();
    
    // Fitness = (% clasificados correctamente) ^ 2
    fitness = classified * classified;
    
    // Penalizar tamano
    fitness -= numRules > 50 ? PSIZE * (numRules - 50) * 100 / 50 : 0;
}

int Individual::matches(bitset<66> example)
{
    int someoneMatched = 0;
    
    for (int i = 0; i != numRules; ++i) {
        bitset<RULESIZE> rule = bitset<RULESIZE>(rules.substr(i * RULESIZE, RULESIZE));
        
        // E[n] == 1 => R[n] == 1
        if (((int)(~example | rule).count() - (int)(~example[0] | rule[0])) < RULESIZE - 1)
            continue;
        
        // No considerar las reglas que no clasifiquen a lo mismo
        if (rule[0] != example[0])
            return 0;
        
        someoneMatched = 1;
    }
    
    return someoneMatched;
}

float Individual::getFitness()
{
    if (fitness == numeric_limits<float>::min())
        calculateFitness();
    
    return fitness;
}

void Individual::mutate()
{
    // Mutacion puntual
    int ind = rand() % rules.size();
    rules[ind] = rules[ind] == '0' ? '1' : '0';
    fitness = classified = numeric_limits<float>::min();
}

vector<Individual> Individual::crossover(Individual &p1, Individual &p2)
{
    // La mama es quien tiene menos reglas
    if (p1.numRules > p2.numRules)
        return twoPointCrossover(p2, p1);
    
    return twoPointCrossover(p1, p2);
}

vector<Individual> Individual::twoPointCrossover(Individual &mom, Individual &dad)
{
    vector<Individual> offspring;
    int ma, mb, pa, pb;
    
    // Escoger dos puntos de corte
    ma = rand() % ((int)mom.rules.size() - 2);
    mb = ma + 1 + rand() % ((int)mom.rules.size() - 1 - (ma + 1));    // [a+1, size - 1 - a]
    
    // Escoger los puntos de corte en el otro padre
    if (ma % RULESIZE >= mb % RULESIZE) {    // Calculo las reglas
        
        pa = rand() % (dad.numRules - 1);
        pb = rand() % (dad.numRules - pa - 1) + pa + 1;
        
    } else {
        
        pa = rand() % dad.numRules;
        pb = rand() % (dad.numRules - pa) + pa;
        
    }
    
    pa = ma % RULESIZE + RULESIZE * pa;     // Calculo los indices finales del papa
    pb = mb % RULESIZE + RULESIZE * pb;
    
    
    // Hacer el crossover final
    stringstream s1, s2;
    s1 << mom.rules.substr(0, ma + 1) << dad.rules.substr(pa + 1, pb - pa) << mom.rules.substr(mb + 1);
    s2 << dad.rules.substr(0, pa + 1) << mom.rules.substr(ma + 1, mb - ma) << dad.rules.substr(pb + 1);
    
    offspring.push_back(Individual(s1.str()));
    offspring.push_back(Individual(s2.str()));
    
    return offspring;
}

void Individual::addAlternative()
{
    // Crear un vector que almacene las reglas de forma aleatoria
    vector<int> sr;
    for (int i = 0; i != numRules; ++i)
        sr.push_back(i);
    random_shuffle(sr.begin(), sr.end());
    
    // Crear un vector que haga aleatorias los features de la regla
    vector<int> sf;
    for (int i = 0; i != NUMFEATURES - 1; ++i)
        sf.push_back(i);
    random_shuffle(sf.begin(), sf.end());
    
    
    
    // Tratar de agregar una alternativa a alguna regla
    for (int i = 0; i != numRules; ++i) {
        string rule = rules.substr(sr[i] * RULESIZE, RULESIZE);
        
        // Agarro cada conjunto de bits que forman un feature
        for (int j = 0; j != 15; ++j) {
            string feature = rule.substr(FEATUREINDEXES[sf[j]], FEATURESIZE[sf[j]]);
            
            // Al primer feature que encuentre valido, le cambio un bit
            if (count(feature.begin(), feature.end(), '1') < feature.size() - 1)
            {
                for (int k = 0; k != FEATURESIZE[sf[j]]; ++k)
                    if (feature[k] == '0')
                        rules[sr[i] * RULESIZE + FEATUREINDEXES[sf[j]] + k] = '1';
                
                fitness = classified = numeric_limits<float>::min();
                return;
            }
        }
    }
}

void Individual::dropCondition()
{
    // Crear un vector que almacene las reglas de forma aleatoria
    vector<int> sr;
    for (int i = 0; i != numRules; ++i)
        sr.push_back(i);
    random_shuffle(sr.begin(), sr.end());
    
    // Crear un vector que haga aleatorias los features de la regla
    vector<int> sf;
    for (int i = 0; i != NUMFEATURES - 1; ++i)
        sf.push_back(i);
    random_shuffle(sf.begin(), sf.end());
    
    
    
    // Tratar de agregar una alternativa a alguna regla
    for (int i = 0; i != numRules; ++i) {
        string rule = rules.substr(sr[i] * RULESIZE, RULESIZE);
        
        // Agarro cada conjunto de bits que forman un feature
        for (int j = 0; j != 15; ++j) {
            string feature = rule.substr(FEATUREINDEXES[sf[j]], FEATURESIZE[sf[j]]);
            
            // Al primer feature que encuentre valido, le cambio un bit
            if (count(feature.begin(), feature.end(), '1') == feature.size() - 1)
            {
                for (int k = 0; k != FEATURESIZE[sf[j]]; ++k)
                    if (feature[k] == '0')
                        rules[sr[i] * RULESIZE + FEATUREINDEXES[sf[j]] + k] = '1';
                
                fitness = classified = numeric_limits<float>::min();
                return;
            }
        }
    }
}

string Individual::toString()
{
    stringstream ss;
    
    ss << "Fitness = " << fitness << endl;
    ss << "Clasificados = " << classified << endl;
    ss << "Reglas = " << numRules << endl;
    
    /*
    for (int i = 0; i != numRules; ++i)
        ss << "    " << rules.substr(i * RULESIZE, RULESIZE) << endl;
    */
    
    return ss.str();
}

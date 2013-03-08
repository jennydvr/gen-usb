//
//  main.cpp
//  gen-usb
//
//  Created by Jenny Valdez & Luis Vieira on 05/03/13.
//  Copyright (c) 2013 Jenny Valdez & Luis Vieira. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include "stringHelper.h"
#include "individual.h"

using namespace std;

vector<bitset<66>> trainingCases;
vector<bitset<66>> testCases;

string normalizeContinuousValues(int index, string str)
{
    float value = str.compare("?") == 0 ? -1 : (float)atof(str.c_str());
    
    switch (index) {
        case 1:
            if (value >= 40)
                return "10000";
            else if (value >= 32)
                return "01000";
            else if (value >= 25.5)
                return "00100";
            else if (value >= 21.5)
                return "00010";
            else if (value >= 0)
                return "00001";
            else
                return "11111";
            
        case 2:
            if (value >= 10)
                return "10000";
            else if (value >= 4.5)
                return "01000";
            else if (value >= 2.2)
                return "00100";
            else if (value >= 0.8)
                return "00010";
            else
                return "00001";
            
        case 7:
            if (value >= 3)
                return "1000";
            else if (value >= 1)
                return "0100";
            else if (value >= 0.15)
                return "0010";
            else
                return "0001";
            
        case 10:
            if (value >= 1)
                return "10";
            else
                return "01";
            
        case 13:
            if (value >= 275)
                return "1000";
            else if (value >= 160)
                return "0100";
            else if (value >= 60)
                return "0010";
            else if (value >= 0)
                return "0001";
            else
                return "1111";
            
        case 14:
        default:
            if (value >= 400)
                return "100";
            else if (value >= 1)
                return "010";
            else
                return "001";
    }
}

string normalizeDiscreteValues(int index, string str)
{
    switch (index) {
        case 0:     // b, a, ?
            
            if (str.compare("?") == 0)
                return "11";
            
        case 8:     // t, f
        case 9:     // t, f
        case 11:    // t, f
        case 15:    // +, -
            
            if (str.compare("b") == 0 || str.compare("t") == 0 || str.compare("+") == 0)
                return "10";
            else
                return "01";
            
        case 4:     // g, p, gg, ?
            
            if (str.compare("?") == 0)
                return "111";
            
        case 12:    // g, p, s
            
            if (str.compare("g") == 0)
                return "100";
            else if (str.compare("p") == 0)
                return "010";
            else
                return "001";
            
        case 3:         // u, y, l, t, ?
            if (str.compare("u") == 0)
                return "1000";
            else if (str.compare("y") == 0)
                return "0100";
            else if (str.compare("l") == 0)
                return "0010";
            else if (str.compare("t") == 0)
                return "0001";
            else
                return "1111";
            
        case 5:         // c, d, cc, i, j, k, m, r, q, w, x, e, aa, ff
            
            if (str.compare("c") == 0)
                return "10000000000000";
            else if (str.compare("d") == 0)
                return "01000000000000";
            else if (str.compare("cc") == 0)
                return "00100000000000";
            else if (str.compare("i") == 0)
                return "00010000000000";
            else if (str.compare("j") == 0)
                return "00001000000000";
            else if (str.compare("k") == 0)
                return "00000100000000";
            else if (str.compare("m") == 0)
                return "00000010000000";
            else if (str.compare("r") == 0)
                return "00000001000000";
            else if (str.compare("q") == 0)
                return "00000000100000";
            else if (str.compare("w") == 0)
                return "00000000010000";
            else if (str.compare("x") == 0)
                return "00000000001000";
            else if (str.compare("e") == 0)
                return "00000000000100";
            else if (str.compare("aa") == 0)
                return "00000000000010";
            else
                return "00000000000001";
            
        case 6:         // v, h, bb, j, n, z, dd, ff, o, ?
            
            if (str.compare("v") == 0)
                return "100000000";
            else if (str.compare("h") == 0)
                return "010000000";
            else if (str.compare("bb") == 0)
                return "001000000";
            else if (str.compare("j") == 0)
                return "000100000";
            else if (str.compare("n") == 0)
                return "000010000";
            else if (str.compare("z") == 0)
                return "000001000";
            else if (str.compare("dd") == 0)
                return "000000100";
            else if (str.compare("ff") == 0)
                return "000000010";
            else if (str.compare("o") == 0)
                return "000000001";
            else
                return "111111111";
            
        default:    // continuous
            return str;
    }
}

void readFile(const char * casesFile)
{
    ifstream file(casesFile);
    
    if (!file.is_open())
    {
        cout << "Error: No pudo abrirse el archivo.\n";
        exit(0);
    }
    
    vector<string> strs;
    string line;
    
    while (file.good())
    {
        getline(file, line);
        strs = split(line, ',', 1);
        
        // Creo un string que represente la codificacion
        stringstream ss;
        
        for (int n = 0; n != strs.size(); ++n) {
            string str = normalizeDiscreteValues(n, strs[n]);
            
            if (n == 1 || n == 2 || n == 7 || n == 10 || n == 13 || n == 14)
                str = normalizeContinuousValues(n, str);
            
            ss << str;
        }
        
        // Transformo ese string en un arreglo de bits
        testCases.push_back(bitset<66>(ss.str()));
    }
    
    file.close();
}

bool firstMatch(int val)
{
    for (int i = 0; i != testCases.size(); ++i)
        if (testCases[i][0] == val)
            return i;
    
    return 0;
}

void takeDataPercent(int percent)
{
    if (percent > 100)
        percent = 100;
    else if (percent < 0)
        percent = 0;
    
    int awayData = ((100 - percent) * (int)testCases.size()) / 100;
    
    int pos = 0;
    
    for (int i = 0; i < awayData; i++)
    {
        int index = i % 2;
        
        if (index == 0) {
            pos += 1;
        }
        
        index = firstMatch(index);
        
        trainingCases.push_back(testCases[index]);
        testCases.erase(testCases.begin() + index);
    }
    
    if ((int)trainingCases.size() < 1)
    {
        perror("Error: No hay suficientes casos para entrenar.\n" );
        exit(0);
    }
}

int main(int argc, char * argv[])
{
    unsigned int seed = (unsigned int)chrono::system_clock::now().time_since_epoch().count();
    srand(seed);
    
    readFile("crx.data.txt");
    
    
    takeDataPercent(40);
    
    trainingExamples = trainingCases;
    
    for (int i = 0; i != 100; ++i) {
        
        Individual ind;
    }
    
    return 0;
}

//
//  main.cpp
//  gen-usb
//
//  Created by Jenny Valdez & Luis Vieira on 05/03/13.
//  Copyright (c) 2013 Jenny Valdez & Luis Vieira. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "stringHelper.h"
#include "draftsman.h"

using namespace std;

vector<vector<float>> cases;

vector<vector<int>> trainingCases;
vector<vector<int>> testCases;

float normalizeContinuousValues(int index, float value)
{
    switch (index) {
        case 1:
            if (value >= 40)
                return 0;
            else if (value >= 32)
                return 1;
            else if (value >= 25.5)
                return 2;
            else if (value >= 21.5)
                return 3;
            else if (value >= 0)
                return 4;
            else
                return 5;
            
        case 2:
            if (value >= 10)
                return 0;
            else if (value >= 4.5)
                return 1;
            else if (value >= 2.2)
                return 2;
            else if (value >= 0.8)
                return 3;
            else
                return 4;
            
        case 7:
            if (value >= 3)
                return 0;
            else if (value >= 1)
                return 1;
            else if (value >= 0.15)
                return 2;
            else
                return 3;
            
        case 10:
            if (value >= 1)
                return 0;
            else
                return 1;
            
        case 13:
            if (value >= 275)
                return 0;
            else if (value >= 160)
                return 1;
            else if (value >= 60)
                return 2;
            else if (value >= 0)
                return 3;
            else
                return 4;
            
        case 14:
        default:
            if (value >= 400)
                return 0;
            else if (value >= 1)
                return 1;
            else
                return 2;
    }
}

/*
 
 A1: 2
 A2: 5
 A3: 5
 A4: 4
 A5: 3
 A6: 14
 A7: 9
 A8: 4
 A9: 2
 A10: 2
 A11: 2
 A12: 2
 A13: 3
 A14: 4
 A15: 3
 A16: 2
 
 
 */

float normalizeDiscreteValues(int index, string str)
{
    switch (index) {
        case 0:     // b, a, ?
            
            if (str.compare("?") == 0)
                return 2;
            
        case 8:     // t, f
        case 9:     // t, f
        case 11:    // t, f
        case 15:    // +, -
            
            if (str.compare("b") == 0 || str.compare("t") == 0 || str.compare("+") == 0)
                return 0;
            else
                return 1;
            
        case 4:     // g, p, gg, ?
            
            if (str.compare("?") == 0)
                return 3;
            
        case 12:    // g, p, s
            
            if (str.compare("g") == 0)
                return 0;
            else if (str.compare("p") == 0)
                return 1;
            else
                return 2;
            
        case 3:         // u, y, l, t, ?
            if (str.compare("u") == 0)
                return 0;
            else if (str.compare("y") == 0)
                return 1;
            else if (str.compare("l") == 0)
                return 2;
            else if (str.compare("t") == 0)
                return 3;
            else
                return 4;
            
        case 5:         // c, d, cc, i, j, k, m, r, q, w, x, e, aa, ff
            
            if (str.compare("c") == 0)
                return 0;
            else if (str.compare("d") == 0)
                return 1;
            else if (str.compare("cc") == 0)
                return 2;
            else if (str.compare("i") == 0)
                return 3;
            else if (str.compare("j") == 0)
                return 4;
            else if (str.compare("k") == 0)
                return 5;
            else if (str.compare("m") == 0)
                return 6;
            else if (str.compare("r") == 0)
                return 7;
            else if (str.compare("q") == 0)
                return 8;
            else if (str.compare("w") == 0)
                return 9;
            else if (str.compare("x") == 0)
                return 10;
            else if (str.compare("e") == 0)
                return 11;
            else if (str.compare("aa") == 0)
                return 12;
            else if (str.compare("ff") == 0)
                return 13;
            else
                return 14;
            
        case 6:         // v, h, bb, j, n, z, dd, ff, o, ?
            
            if (str.compare("v") == 0)
                return 0;
            else if (str.compare("h") == 0)
                return 1;
            else if (str.compare("bb") == 0)
                return 2;
            else if (str.compare("j") == 0)
                return 3;
            else if (str.compare("n") == 0)
                return 4;
            else if (str.compare("z") == 0)
                return 5;
            else if (str.compare("dd") == 0)
                return 6;
            else if (str.compare("ff") == 0)
                return 7;
            else if (str.compare("o") == 0)
                return 8;
            else
                return 9;
            
        
        case 1:     // continuous
        case 13:    // continuous
            
            if (str.compare("?") == 0)
                return -1;
            
        default:    // continuous
            return (float)atof(str.c_str());
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
        
        vector<float> cc;
        
        for (int n = 0; n != strs.size(); ++n) {
            cc.push_back(normalizeDiscreteValues(n, strs[n]));
            
            if (n == 1 || n == 2 || n == 7 || n == 10 || n == 13 || n == 14)
                cc[n] = normalizeContinuousValues(n, cc[n]);
        }
        
        cases.push_back(cc);
    }
    
    file.close();
}

int main(int argc, char * argv[])
{
    readFile("crx.data.txt");
    
    for (int i = 0; i != cases.size(); ++i) {
        dataset.push_back(cases[i][14]);
    }
    
    stable_sort(dataset.begin(), dataset.end());
    
    for (int i = 0; i != dataset.size(); ++i) {
        cout << dataset[i] << endl;
    }
    
    return 0;
}

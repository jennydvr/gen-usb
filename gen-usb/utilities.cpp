//
//  utilities.cpp
//  gen-usb
//
//  Created by Jenny Valdez on 12/03/13.
//  Copyright (c) 2013 Jenny Valdez & Luis Vieira. All rights reserved.
//

#include "utilities.h"

int specialBinarySearch(std::vector<float> vec, float key)
{
    int start = 0, end = (int)vec.size() - 1;
    
    // Retorna el individuo tal que vec[x] <= key
    while (end >= start)
    {
        int mid = start + (end - start) / 2;
        
        if (vec[mid] < key)
            start = mid + 1;
        else
            return mid;
    }
    
    // No hallado - retorna cualquier cosa
    return rand() % vec.size();
}

void merge(std::vector<Individual>& v, int start, int mid, int end)
{
    std::vector<Individual> aux(end - start + 1);
    int i = start;      // Indice de la parte izquierda
    int j = mid + 1;    // Indice de la parte derecha
    int k = 0;          // Indice del vector aux
    
    // Mientras ninguno de los indices llegue a su fin vamos realizando comparaciones
    while (i <= mid && j <= end)
        if (v[i].getFitness() < v[j].getFitness())
            aux[k++] = v[i++];
        else
            aux[k++] = v[j++];
    
    // Uno de los dos sub-vectores ya ha sido copiado del todo
    while (i <= mid)
        aux[k++] = v[i++];
    
    while (j <= end)
        aux[k++] = v[j++];
    
    // Copiamos los elementos ordenados de aux al vector original
    for (int n = 0; n != aux.size(); ++n)
        v[start + n] = aux[n];
}

void mergeSort(std::vector<Individual>& v, int start, int end)
{
    if (start < end) {
        // El valor de mid siempre es redondeado hacia abajo.
        int mid = (start + end)/2;
        mergeSort(v, start, mid);
        mergeSort(v, mid + 1, end);
        merge(v, start, mid, end);
    }
}

void merge(std::vector<Individual>& v, int start, int mid, int end, float sum)
{
    std::vector<Individual> aux(end - start + 1);
    int i = start;      // Indice de la parte izquierda
    int j = mid + 1;    // Indice de la parte derecha
    int k = 0;          // Indice del vector aux
    
    // Mientras ninguno de los indices llegue a su fin vamos realizando comparaciones
    while (i <= mid && j <= end)
        if (v[i].getFitness() / sum < v[j].getFitness() / sum)
            aux[k++] = v[i++];
        else
            aux[k++] = v[j++];
    
    // Uno de los dos sub-vectores ya ha sido copiado del todo
    while (i <= mid)
        aux[k++] = v[i++];
    
    while (j <= end)
        aux[k++] = v[j++];
    
    // Copiamos los elementos ordenados de aux al vector original
    for (int n = 0; n != aux.size(); ++n)
        v[start + n] = aux[n];
}

void mergeSort(std::vector<Individual>& v, int start, int end, float sum)
{
    if (start < end) {
        // El valor de mid siempre es redondeado hacia abajo.
        int mid = (start + end)/2;
        mergeSort(v, start, mid, sum);
        mergeSort(v, mid + 1, end, sum);
        merge(v, start, mid, end, sum);
    }
}

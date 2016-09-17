/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Quicksort.h
 * Author: vinicius
 *
 * Created on September 8, 2016, 5:25 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#ifndef ORDENACAO_H
#define ORDENACAO_H

#ifdef __cplusplus
extern "C" {
#endif

    struct timeval seed;
    
    double shellSort(int *vetor,int tamanho);
    double quickSort(int *vet, int esquerda, int direita);
    double determinaSoma(int *vetor,int tamanhoVetor,int x);
    void medeTempoQuicksort();
    void medeTempoShellsort();
    
    int *preencheVetor(int *vet,int tamanho);
  
#ifdef __cplusplus
}
#endif

#endif /* QUICKSORT_H */


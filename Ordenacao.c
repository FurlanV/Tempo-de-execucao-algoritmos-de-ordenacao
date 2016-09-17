#include "Ordenacao.h"

int *preencheVetor(int *vet,int tamanho) // Preenche o vetor com numeros gerados aleatoriamente
{
    int i;
    gettimeofday(&seed,NULL);
    srand((int)(seed.tv_sec+1000000*seed.tv_usec));
     
    for(i=0;i<tamanho;i++){   
        vet[i] = ((int)rand()%1450);
    }
    
    return vet;    
}

double quickSort(int *vet, int esquerda, int direita)
{
    struct timeval inicio,fim;
    double tempoDecorrido = 0.0;
    int i,j,x,y;
    clock_t ticks[2] = {0.0,0.0};
    
    
    i = esquerda;
    j = direita;
    x = vet[(esquerda + direita)/2];
    
    ticks[0] = clock();
    
    while(i <= j)
    {
        while(vet[i] < x && i < direita)
        {
            i++;
        }
        while(vet[j] > x && j > esquerda)
        {
            j--;
        }
        if(i <= j)
        {
            y = vet[i];
            vet[i] = vet[j];
            vet[j] = y;
            i++;
            j--;
        }
    }
    if(j > esquerda)
    {
        quickSort(vet,esquerda,j);
    }
    if(i < direita)
    {
        quickSort(vet,i, direita);
    }   
    
    ticks[1] = clock();
    tempoDecorrido = (double)(ticks[1] - ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    
    return tempoDecorrido;
}

double determinaSoma(int *vetor,int tamanhoVetor,int x)
{
    int i,j;
    int guardaValor;
    double tempoDecorrido = 0.0;
    clock_t ticks[2];       
    
    ticks[0] = clock();
    for(i=0;i<tamanhoVetor;i++){
        guardaValor = vetor[i];
        if(guardaValor >= vetor[i]){
            ticks[1] = clock();
            tempoDecorrido = (double)(ticks[1] - ticks[0]) * 1000.0 /CLOCKS_PER_SEC;
            return tempoDecorrido;
        }
        else{
           for(j=i;j<tamanhoVetor;j++){
                if(guardaValor+vetor[j] == x){
                    ticks[1] = clock();
                    tempoDecorrido = (double)(ticks[1] - ticks[0]) * 1000.0 /CLOCKS_PER_SEC;
                    return tempoDecorrido;
                }
            }
        }
    }
    
    ticks[1] = clock();
    tempoDecorrido = (double)(ticks[1] - ticks[0]) * 1000.0 /CLOCKS_PER_SEC;
    return tempoDecorrido;
}

void imprimeVetorOrdenado(int *vet,int tamanho)
{
    int j;
    for(j=0;j<tamanho;j++){
        printf("%d ",vet[j]);
    }
    printf("\n");
}

double shellSort(int *vetor,int tamanho)
{   
    struct timeval inicio,fim;
    double tempoDecorrido = 0.0;
    int i , j , value;
    int gap = 1;
    clock_t ticks[2];

    ticks[0] = clock();
    while(gap < tamanho) {
        gap = 3*gap+1;
    }
    while ( gap > 1) {
        gap /= 3;
        for(i = gap; i < tamanho; i++) {
            value = vetor[i];
            j = i - gap;
            while (j >= 0 && value < vetor[j]) {
                vetor[j + gap] = vetor[j];
                j -= gap;
            }
            vetor[j + gap] = value;
        }
    }
    ticks[1] = clock();

    tempoDecorrido = (double)(ticks[1] - ticks[0]) * 1000.0 /CLOCKS_PER_SEC;
    
    return tempoDecorrido;
}

void medeTempoQuicksort(){
    FILE *file;
    int *vetor;
    int i = 0,j,k = 0,x;
    int tamanhoEntrada[5] = {1000,10000,100000,1000000,10000000};
    double tempo = 0.0,tempoSoma = 0.0;
    double temposQuicksort[5] = {0.0,0.0,0.0,0.0,0.0},temposDeterminaSoma[5] = {0.0,0.0,0.0,0.0,0.0};
    double tempoTotal[5] = {0.0,0.0,0.0,0.0,0.0};       
     
    file = fopen("Tempos - Quicksort","w");
     
  while(i<5){                 
       
        gettimeofday(&seed,NULL);
        srand((int)(seed.tv_sec+1000000*seed.tv_usec));
        
        x = (rand()%1450);
       
        for(j=0;j<20;j++){ //numero de vezes que vamos executar o algoritmo para medir o tempo            
            vetor = (int*)malloc(sizeof(int)*tamanhoEntrada[i]); //a cada passada o vetor é liberado e um novo vetor é criado
            vetor = preencheVetor(vetor,tamanhoEntrada[i]);
            tempo += quickSort(vetor,0,tamanhoEntrada[i]-1); //o contador é acionado dentro da função de ordenação que retorna um double com o tempo decorrido
            tempoSoma += determinaSoma(vetor,tamanhoEntrada[i],x);
            free(vetor);    
        }
        
        temposQuicksort[i] = (double)(tempo/20.0); 
        temposDeterminaSoma[i] = (double)(tempoSoma/20.0);
        tempo = 0.0;
        tempoSoma = 0.0;
        i++;
    }       
    
    fprintf(file,"%s | %s | %s | %s\n\n","Tamanho","Shellsort","DeterminaSoma","Total");
    printf("QuickSort:\n");
    for(i=0;i<5;i++){
        tempoTotal[i] = temposQuicksort[i]+temposDeterminaSoma[i];
        printf("Tempo decorrido para entrada de tamanho %d: %lf ms\nTempo do algoritmo determina Soma: %lf ms\nTotal: %lf ms\n\n",tamanhoEntrada[i],temposQuicksort[i],temposDeterminaSoma[i],tempoTotal[i]);
        fprintf(file,"| %d | %lf | %lf | %lf |\n",tamanhoEntrada[i],temposQuicksort[i],temposDeterminaSoma[i],tempoTotal[i]);
    }
    
    fclose(file);
}

void medeTempoShellsort(){
    FILE *file;
    int *vetor;
    int i = 0,j,k = 0,x;
    int tamanhoEntrada[5] = {1000,10000,100000,1000000,10000000};
    double tempo = 0.0,tempoSoma = 0.0;
    double temposDeterminaSoma[5] = {0.0,0.0,0.0,0.0,0.0};
    double temposShellsort[5] = {0.0,0.0,0.0,0.0,0.0};
    double tempoTotal[5] = {0.0,0.0,0.0,0.0,0.0};     
    
    file = fopen("Tempos - Shellsort","w");
    
    while(k<5){
        
        gettimeofday(&seed,NULL);
        srand((int)(seed.tv_sec+1000000*seed.tv_usec));
        
        x = (rand()%1450);        
        tempo = 0.0;
        tempoSoma = 0.0;
        
        for(j=0;j<20;j++){ //numero de vezes que vamos executar o algoritmo para medir o tempo            
            vetor = (int*)malloc(sizeof(int)*tamanhoEntrada[k]); //a cada passada o vetor é liberado e um novo vetor é criado
            vetor = preencheVetor(vetor,tamanhoEntrada[k]);// O vetor é preenchido com valores aleatorios
            tempo += shellSort(vetor,tamanhoEntrada[k]); //o contador é acionado dentro da função de ordenação que retorna um double com o tempo decorrido
            tempoSoma += determinaSoma(vetor,tamanhoEntrada[k],x);
            free(vetor);    
        }
        
        temposShellsort[k] = ((double)(tempo/20.0));
        temposDeterminaSoma[k] = ((double)(tempoSoma/20.0));
        k++;
    }
    
    fprintf(file,"%s | %s | %s | %s\n\n","Tamanho","Shellsort","DeterminaSoma","Total");
    printf("Shellsort:\n");
    for(i=0;i<5;i++){
        tempoTotal[i] = temposShellsort[i]+temposDeterminaSoma[i];
        printf("Tempo decorrido para entrada de tamanho %d: %lf ms\nTempo do algoritmo determina Soma: %lf ms\nTotal: %lf ms\n\n",tamanhoEntrada[i],temposShellsort[i],temposDeterminaSoma[i],tempoTotal[i]);
        fprintf(file,"| %d | %lf | %lf | %lf |\n",tamanhoEntrada[i],temposShellsort[i],temposDeterminaSoma[i],tempoTotal[i]);
    }
    fclose(file);
}
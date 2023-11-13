#include <iostream>
#include <omp.h>
#include <cmath>
#include <list>
#include <time.h>
#include <sys/time.h>
//#include <bits/stdc++.h>

using namespace std;

class Objeto {
	public:
		int ID;
		int Total;
		int Grupo;
		Objeto(int id){
			ID = id;
			Total = rand() % 11;
			Grupo = rand() % 5 + 1;
		}
		Objeto(){
			//Do nothing;
		}
};

int main(int argc, char *argv[])
{
	int N = atoi(argv[1]), T = atoi(argv[2]), base10N = 0;
	long int totais = 0, totaisGrupo[5] = {0}, somas[264] = {0}, somasGrupo[264][5] = {0};
	
	srand(27600);
	
	base10N = pow(10, N);
	
	Objeto *lista = new Objeto[base10N];
	list<int> *listaMenor = new list<int>[T];
	list<int> *listaMaior = new list<int>[T];
	list <int> finalMenorList;
	list <int> finalMaiorList;
	
	for(int i=0; i<base10N; i++)
	{
		lista[i] = Objeto(i);
	}
	
	float teto = float(base10N)/float(T);
	
	struct timeval start, stop;
	gettimeofday(&start, 0);
	////Processamento
	#pragma omp parallel num_threads(T) shared (lista)
	{
		int inicio = ceil( teto * omp_get_thread_num() );
		int fim = ceil( teto * (omp_get_thread_num()+1) );
		for(int i=inicio; i < fim; i++)
		{
			
			somas[omp_get_thread_num()] += lista[i].Total;
			somasGrupo[omp_get_thread_num()][lista[i].Grupo-1] += lista[i].Total;
			if(lista[i].Total < 5)
			{
				listaMenor[omp_get_thread_num()].push_back(lista[i].ID);
			}
			else
			{
				listaMaior[omp_get_thread_num()].push_back(lista[i].ID);
			}
		}
	}
	#pragma omp parallel for reduction(+:totaisGrupo, totais) num_threads(T)	
		for(int i=0; i<T; i++)
		{
			
			totais += somas[i];
			for(int j=0; j<5; j++)
			{
				totaisGrupo[j] += somasGrupo[i][j];
			}
		}
		
	for(int i=0; i<T; i++)
	{
		finalMenorList.splice(finalMenorList.end(), listaMenor[i]);
		finalMaiorList.splice(finalMaiorList.end(), listaMaior[i]);
	}
	////Processamento
	gettimeofday(&stop, 0);
	
	cout << "N = " << N << endl;
	cout << "T = " << T << endl;
	
      	printf("Tempo de execucao: %1.10f \n", (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec));
      	
	cout << "Total:" << totais << endl;
	cout << "totais grupo: " << endl;
	
	for(int i=0; i<5; i++)
	{
		cout << totaisGrupo[i] << endl;
	}
	
	cout << "Quantidade menores que 5: " << finalMenorList.size() << endl;
	cout << "Quantidade maiores que 5: " << finalMaiorList.size() << endl;
	
	free (lista);
}

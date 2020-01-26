#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <chrono>
#include "City.h"
#include "Map.h"
#include "Tour.h"
#include "Population.h"
#include "ImportData.h"

using std::cout;
using std::cin;
using std::stoi;

typedef std::chrono::high_resolution_clock Clock;

const long int LIM_UNCHANGED{5000};
const long int LIMIT_ALL{50000};

void start(string);
bool end(Population&,long int&);


int main(int argc, char *argv[])
{
	string nome{""};

    if(argc == 2)
	{
            nome = argv[1];
    }else
	{
        cout<<"----------------------------TSP----------------------------"<< '\n';
        cout<<"Digite o caminho para o arquivo tsp (/home/usuario/TSP/lib/file.tsp): ";
        cin>>nome;
    }
    start(nome);
    return(0);
}



void start(string nome){
    long int i{0},mapSize{0},endCond{0};
    
    srand(time(NULL));

    auto tInicial=Clock::now();  //startando cronometro
    
        cout<<"Comecando o algoritmo ..."<<'\n';
        ImportData dataFile(nome); 
		// popSIZE NAO É NECESSÀRIO POIS O VALOR DEVERIA SER PROCESSADO DENTRO DO ARQUIVO

			//dataFile.printInfos();
    
        Map map(dataFile.getCitiesCoord());
    
        for(City c : map.getCityList()){
            cout<<c<<'\n';
        }
    
        cout<<"comecando a processar..."<<'\n';
        cout<<"TAMANHO POPULACAO: " <<  dataFile.get_population_size() << '\n';
    
        Population *pop = new Population(map,dataFile.get_population_size());
    
        cout<<"Primeira populacao: "<<'\n';
        cout<<(*pop)<<'\n';
        cout<<"Melhor fitness: "<<maxFitness((*pop).getPopulation())<<'\n';
        cout<<"distancia: "<<(1/maxFitness((*pop).getPopulation())*10000)<<'\n';
        
    
        while(!end(*pop,endCond)){   // Roda enquanto nenhuma das condições de parada forem atendidas
    
            Population *oldPop = pop;
            pop = (*pop).newGeneration();
            delete oldPop;
            ++i;
            if(i%5000==0){
                cout<<"Geracao: "<<i<<" e rodando..."<<'\n';
            }
        } 
    
        auto tFinal=Clock::now();
    
        
        
        if(endCond==1){
            cout<<"População convergiu!"<<'\n';
        }else if(endCond==2){
            cout<<"Fitness inalterada com "<<LIMIT_ALL<<" de gerações!"<<'\n';
        }
    
        cout<<i<<" geracoes depois!"<<'\n';
        cout<<"Fitness maxima: "<<maxFitness((*pop).getPopulation())<<'\n';
        cout<<"distancia: "<<(1/maxFitness((*pop).getPopulation())*10000)<<'\n';
    
        cout<<"-----------------------------" << '\n';
    
        cout<<"Tempo de execucao: "<<std::chrono::duration_cast<std::chrono::seconds>(tFinal - tInicial).count()<<" segundos!"<<'\n';
        cout << '\n';
       
} 

bool end(Population &pop,long int &eC){
    static long int genWithoutChanges{0};
    static double maxFitEver{0.0};
    double maxFit{maxFitness(pop.getPopulation())}, minFit{minFitness(pop.getPopulation())};

    if(maxFit > maxFitEver){  // contagem de gerações inalteradas
        maxFitEver = maxFit;
        genWithoutChanges = 0;
        cout<<"aumentou a fitness maxima! fitness: "<<maxFitEver<<" distancia: "<<((1/maxFitEver)*10000)<<'\n';
    }else{
        genWithoutChanges++;
    }

    if((maxFit-minFit) < (maxFit*0.01)){
        eC=1;
        return(true);
    }else if(genWithoutChanges >= LIM_UNCHANGED){
        if(genWithoutChanges >= LIMIT_ALL){
            eC=2;
            return(true);
        }
        return(false);
    }else{
        return(false);
    }
}

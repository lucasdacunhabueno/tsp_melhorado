#include "../headers/ImportData.h"

// TEMPORÁRIO
#define DEBUG(X) std::cerr << #X << " : " << X << '\n'

ImportData::ImportData(string file_name)
{
	inputManager(file_name);
}

// ============
void ImportData::inputManager(string file_name)
{
	myfile.open(file_name);

    if(!myfile.is_open())
	{
        cout <<"Falha na leitura do arquivo" <<endl;
        exit(EXIT_FAILURE);
    }

	int line_counter = 6; // Para pegar apenas as 6 primeiras linhas

	string line;
	/* 	Pegando as informações do arquivo tsp
		como: Nome, Dimensão, etc.
	*/
	while(std::getline(myfile,line) && line_counter-- )
	{
		std::stringstream ss(line); // [1] Exemplo: line =  "NAME : a280"


		while(ss >> line){} // Percorre a linha até "a280", exemplo [1]

		file_descriptions.push_back(line); // Adiciona "a280" ao final do vetor
	}



	/*
		Após ter pego todas as informações
		serão guardadas as distâncias
	*/
	do
	{
		std::stringstream ss(line);

		string key;
		ss >> key;

		double x,y;
		ss >> x >> y;


		citiescoord.push_back(City(x,y));

	}while(std::getline(myfile,line));


}

// ============

/*
void ImportData::printInfos(){
    cout <<"Nome: " << gettspName() <<endl;
    cout<< "Tipo: " <<getType()<<endl;
    cout<< "Comentário: "<<getcomment()<<endl;
    cout<< "Tipo do Vértice: "<< getedge_type()<<endl;
    cout<< "Comentário do tipo de node: "<<getnode_comment()<<endl;
}
*/


vector<City> ImportData::getCitiesCoord(){
    return citiescoord;
}
string ImportData::gettspName(){
    return file_descriptions[NAME];
}
string ImportData::getType(){
    return file_descriptions[TYPE];
}
string ImportData::getedge_type(){
    return file_descriptions[EDGE_WEIGHT_TYPE];
}
string ImportData::getnode_comment(){
    return file_descriptions[NODE_COORD_SECTION];
}
string ImportData:: getcomment(){
        return file_descriptions[COMMENT];
}

int ImportData::get_population_size()
{
	return std::stoi(file_descriptions[DIMENSION]);
}

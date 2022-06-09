#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
using namespace std;

#include "config.h"
#include "estudante.h"
#include "hash.h"

#define table_size 1111

// Obtem estudantes do arquivo file, colocados no vetor.
int ImportCSVData(string file, std::vector<Estudante> &estudantes)
{

    cout << "Importando dados do arquivo " << endl;
    ifstream arq;
    arq.open(file, ios::in);
    if(!arq.is_open()){
        cout << "FALHA AO ABRIR O ARQUIVO" << endl;
        return -1;
    }
    string line;
    getline(arq, line); // header line
    while(getline(arq, line))
    {
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while(getline(ss, token, ';')){
            tokens.push_back(token);
        }
        if(tokens.size() == 5){
            int     matricula = stoi(tokens[0]);
            string nome = tokens[1];
            int ano_ingresso = stoi(tokens[2]);
            int curso = stoi(tokens[3]);
            float IRA = stof(tokens[4]);
            //Estudante(const char* nome, int matricula, int ano_ingresso, int curso, float ira);
            Estudante est(nome.c_str(), matricula, ano_ingresso, curso, IRA);
            estudantes.push_back(est);
        }
    }

    return estudantes.size();
 
}

/**
 * @brief Implementa função hash bastante simples
 * 
 * @param key chave a ser calculada
 * @return int indice calculado
 */
int hash1(const char *key)
{
    int hash = 0;
    for (int i = 0; i < strlen(key); i++)
    {
        hash += key[i];
    }
    return hash;
}


int main(int argc, char *argv[])
{

    // Usado para uma busca simples na tabela hash.
    char* nomes[2] = {"João","John"};

    // arquivo que será lido contendo os estudantes.
    string input = INPUT_DIR + std::string("alunos.csv");
    
    // Cria Hash de tamanho table_size e usando hash1 como função.
    HashLinearProbing hash(table_size, hash1);
    
    std::vector<Estudante> estudantes;
    ImportCSVData(input, estudantes);
    
    // Insere os estudantes da hash.
    // A hash armazena a chave a posição do estudante no vetor estudantes
    int n_inseridos = 0;
    for(int i = 0; i < estudantes.size(); i++){
        if(hash.Insere(estudantes[i].ObterNome(),i))
            n_inseridos++;
    }

    // Testa a hasg buscando por alguns nomes.
    // Tente pesquisar por outros nomes...
    for(int i =0; i < 2; i++)
    {
        int idx = hash.Pesquisa(nomes[i]);
        if(idx >= 0){
            
            cout << "Encontrado" << endl;
            cout << "  Posicao: " << hash[idx]._position << endl;

        }
        else
            cout << "Nao encontrado" << endl;
    }

    cout << "Numero de estudantes inseridos: " << n_inseridos << endl;
    cout << "Numero de Colisões: " << hash.ObterNumeroColisoes() << endl;

}

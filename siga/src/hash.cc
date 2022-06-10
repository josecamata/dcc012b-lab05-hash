#include <iostream>
#include <vector>

#include "hash.h"

HashLinearProbing::HashLinearProbing(int size, int (*hash)(const char* key))
{
 
    _hash_table.resize(size);
    _n_colisoes = 0;
    _table_size = size;
    _hash = hash;
    for(int i = 0; i < _table_size; i++)
    {
        _hash_table[i]._flag = MASK_EMPTY;
    }
}

int HashLinearProbing::Pesquisa(const char *key)
{
    // 1. Obter o indice da chave na tabela usando
    //    a função hash

    int i     = 0;
    int h1 = _hash(key) % _table_size;

    // TODO: Implementar sondagem linear. Veja os passos abaixo:
    
    

    // 1. Calcular index = (h1(k) + i) mod _table_size
    

    // 2. Verificar se é uma posição indica por index é invalida, se for, retorna -1.
    //    Observacao: index é uma posição invalida se o bit flag na posição index 
    //                for MASK_EMPTY.


    // 3. Verificar se a chave é igual a chave na posição, se for, retorne index;

    // 4. Se não for, incrementar i
    // 5. Se i for menor que _table_size volta ao passo 1
       
    // 6. Se não houver espaço disponível, ou seja i == _table_size, retorna -1

}

int HashLinearProbing::Insere(const char *key, unsigned int position)
{
   
    // 1. Obter o indice da chave na tabela usando
    //    a função hash
    int i     = 0;
    int h1 = _hash(key) % _table_size;

    // 1. Calcular index: H1(k) + i mod _table_size
   
    // 2. Verificar se é uma posição vazia.
    //    Observacao: index é uma posição vazia se o bit flag na posição index
    //                for MASK_EMPTY ou MASK_DELETED.

    // 3. Se for, colocar a chave na posição, 
    // marcar posição como ocupada (MASK_FILLED) e retornar index;
    //     
  
    // 4. Se não for, houve colisão,
    //    incrementar i e incrementar _n_colisoes
    // 5. Se i for menor que _table_size volta ao passo 1

    // 6. Se não houver espaço disponível, retorna -1
 
}  

int HashLinearProbing::Remove(const char *key)
{
    int index = Pesquisa(key);
    if(index != -1)
    {
        _hash_table[index]._flag = MASK_DELETED;
        return index;
    }
    return -1;
}

int HashLinearProbing::ObterNumeroColisoes()
{
    return _n_colisoes;
}

HashLinearProbing::~HashLinearProbing()
{
    _hash_table.clear();
}

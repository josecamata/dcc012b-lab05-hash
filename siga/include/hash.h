#ifndef HASH_H__
#define HASH_H__

#include <cstring>
#include <vector>

#define MASK_EMPTY   0
#define MASK_FILLED  1
#define MASK_DELETED 2
#define HASH_KEY_SIZE 128


class HashData 
{
  public:
    HashData(): _flag(MASK_EMPTY), _position(0) {
        memset(_hash_key, 0, HASH_KEY_SIZE);
    }
    HashData(char* key, unsigned int pos) : 
        _position(pos),
        _flag(0)
    {
        strcpy(_hash_key, key);
    }
    
    char           _hash_key[HASH_KEY_SIZE+1];
    unsigned int   _position;
    unsigned short _flag;
};

/**
 * @brief Classe que implementa o algoritmo de hash.
 *        Com sondagem linear.
 * */

class HashLinearProbing
{
    public:
        HashLinearProbing(int size, int (*hash)(const char* key));
        int Pesquisa(const char *key);
        int Insere(const char *key, unsigned int position);
        int Remove(const char *key);
        int ObterNumeroColisoes();
        HashData& operator[](int index) { return _hash_table[index]; }
        ~HashLinearProbing();
    private:
        int (*_hash)(const char *key);
        std::vector<HashData> _hash_table;
        int _table_size;
        int _n_colisoes;
};

#endif /* HASH_H__ */

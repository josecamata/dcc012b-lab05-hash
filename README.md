
# Tabela Hash

## Objetivos:

Implementar a sondagem linear para o tratamento de colisões em uma tabela hash.

## 📝 Sondagem Linear

Como visto em sala de aula, a técnica de sondagem linear usada para a resolução de colisões tem desempenho rapidamente deteriorado se uma porcentagem relativamente pequena de células está disponível. Este problema pode ser sanado com outra técnica para resolver ascolisões, e também encontrando uma melhor função de espalhamento, idealmente uma função hash perfeita.  

Nesta atividade, iremos avaliar a eficiencia de diversas funções  hash combinadas com o método de sondagem linear.

## O que deve ser feito? 

Uma estrutura básica para a implementação da tabela hash já foi fornecida. 
 - Os arquivos [hash.h](siga/include/hash.h) e [hash.cc](siga/src/hash.cc) contêm a implementação de uma tabela hash que usa sondagem linear para o tratamento de colisções.

 Nessa atividade, vocês devem implementar: 
 1 . As operações **Pesquisa** e **Insere**. Veja os comentários que são fornecidos nestas rotinas para a implementação.
 2. Funções hash para operar em cadeias de caracteres.
 
 Eis alguns exemplos de funções hash: Dada uma string s
 - *hash1(s)* = PrimeiraLetra(s) + SegundaLetra(s) + ... + UltimaLetra(s)
 - *hash2(s)* = PrimeiraLetra(s) + UltimaLetra(s) + Tamanho(s)
 - *hash3(s)*
 ```C++
 for(i=0, index=0; i < strlen(s); i++)
    index = (26*index+s[i] - ' ');
```

A funçao referente ao item (a) já se encontra no arquivo [teste_hash.cc](tests/teste_hash.cc). Observe que a função é
passada como parametro no construtor da tabela Hash. Dessa forma,
vc pode usar diferentes funções hash em seus testes.


## Compilação e execução
Configuraçao inicial:

```
cmake -B build 
```
Compilação e execução:

```
cd build 
make
./tests/test_hash
```


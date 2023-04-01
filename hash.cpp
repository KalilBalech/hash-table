#include <algorithm>
#include "hash.h"
#include <forward_list>


// LOOK FOR THE COMMENTS IN THE .H 
// TO UNDERSTAND WHAT EACH FUNCTION MUST DO

Hash::Hash(int tablesize, int (*hf) (std::string) ) {
 // CONSTRUTOR 
    _table.resize(tablesize);
    _hash_func = hf;
}

int Hash::hash(std::string str) {
    return _hash_func(str);
}//hash

int Hash::contains(std::string str, int &collisions) {
    
    int position = hash(str);

    auto it = std::find(_table[position].begin(), _table[position].end(), str);

    if(it != _table[position].end()){
        collisions = std::distance(_table[position].begin(), it) + 1;
        return 1;
    }
    collisions = std::distance(_table[position].begin(), _table[position].end());
    return 0;
    
}//contains

int Hash::add(std::string str, int &collisions) { 
    
    int position = hash(str);

    if(contains(str, collisions)){
        return 0;
    }
        
    _table[position].push_front(str);
    return 1;

    // porque existe 'return 0' neste codigo? 
    // para executar os testes, mesmo falhando, eh preciso compilar
    // assim, eh preciso retornar algum valor.
    // ** o aluno deve implementar a funcao completa e retornar o valor correto **
    
}//add

int Hash::remove(std::string str, int &collisions) { 
    
    int position = hash(str);

    if(!contains(str, collisions)){
        return 0;
    }

    _table[position].remove(str);
    return 1;
    
}//remove


    


int Hash::worst_case() {

    int worstCase = 0;

    for(int i = 0; i < _table.size(); i++){
        if(std::distance(_table[i].begin(), _table[i].end())>worstCase) worstCase = std::distance(_table[i].begin(), _table[i].end());
    }

    return worstCase;
    
}//worst_case

int Hash::size() {

    int stringAmount = 0;

    for(int i = 0; i < _table.size(); i++){
        stringAmount += std::distance(_table[i].begin(), _table[i].end());
    }

    return stringAmount;

}//size


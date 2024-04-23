/* A função ja está corrigida onde havia erro */

// Estou assumindo que a função acessa alguma(s) variavel global e que por isso apenas o 'int key' esta sendo fornecido. O acesso à lista vem de uma referencia externa, acredito eu.
void removeEntry (int key)
{
    /* 
        noPrev | noNext | node position
          0    |   0    |      inner     
          0    |   1    |       tail
          1    |   0    |       head
          1    |   1    |      last entry
    */

    int noPrev=1, noNext=1;
    list_entry *entry;
    
    for (entry = List_head; entry != NULL ; entry = entry->next) {
            // Acredito que a comparação deva ser pela igualdade aqui, afinal esta varrendo a list_entry procurando uma entry que seja igual à key passada. Do contrário, se for mantido a comparação pela diferença, a primeira key diferente da key passada à função irá satisfazer a expressão.
            if(entry->key == key) 
                    break;
    }

    // Imagino que entry pode ser nulo quando a lista for vazia (não sei exatamente como é a estrutura de dados) ou quando varrer toda a lista no for acima e não encontrar nenhuma entry cuja key corresponda à key fornecida.
    if (entry == NULL)
            return;

    //  Se existe uma entry anterior à atual, atribui ao ponteiro next da entry anterior o endereço da próxima entry que a entry atual aponta.
    // Em suma, remove as referencias entre a entry anterior e a atual
    if (entry->previous != NULL) {
            entry->previous->next = entry->next;
            noPrev=0;
    }

    //  Se existe uma próxima entry à atual, atribui ao ponteiro previous da proxima entry o endereço da entry anterior que a entry atual aponta.
    // Em suma, remove as referencias entre a entry atual e a próxima
    if (entry->next != NULL) {
            entry->next->previous = entry->previous;
            noNext=0;
    }

    // libera o endereço de memoria no qual a entry atual ocupa
    free (entry);


    // se noPrev=1 e noNext=1, é a única entry da lista, então a lista ficara vazia e o head deve ser null
    if (noPrev && noNext) {
            List_head = NULL;
            return;
    } 
    
    // se noPrev=1 e noNext=0, removeu o primeiro e agora list_head apontara para o proximo
    if (noPrev && !noNext) {
            entry->next->previous = NULL;
            List_head = entry->next;
            return;
    }

    // se noPrev=0 e noNext=1, removeu a última entry e agora o penultimo será o último
    if (!noPrev && noNext) {
        entry.previous.next = NULL;
        return;
    }
    
    // se noPrev=0 e noNext=0, removeu uma entry intermediaria, ai o anterior apontará para o próximo e vice-versa
    entry.previous.next = entry.next;
    entry.next.previous = entry.previous;
}


/* A função funciona? */
/* 
    Do jeito original a função não funcionaria como deveria e ajustes foram necessários. Primeiro erro estava no for para encontrar a entry cuja key deveria ser removida. E os demais erros estavam no if/else final que não reorganizava os ponteiros corretamente após a remoção.
*/


/* É reentrante? (Porque?) 
    Acredito que nao seja reentrante porque a função da fomra que esta acessa uma variavel global externa à ela (list_head) que pode ser um ponto de vulnerabilidade e colisão em caso de execuções concorrentes.
*/

/* O que a função faz? 
    A função remove um elemento de uma lista duplamente ligada baseado no valor da key passada.
*/
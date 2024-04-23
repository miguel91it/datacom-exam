char *insert_header(int *packet, int *length)
{
    int i;
    char header[12] = {0x80, 0x52, 0x66, 0x61, 0x77, 0x52};
    /* os outros 6 são 0 */
    if (packet == NULL || length == NULL)
    {
        return NULL;
    }
    
    for (i = 0; i < *length; i++)
        packet[i + 3] = packet[i];
    for (i = 0; i < 12; i++)
        packet[i] = header[i];
    *length += 12;
    return packet;
}

/*
    1) O tipo de dado retornado (ponteiro de inteiro) não confere com o tipo de dado na definição da função (char)
*/

/* 
    3) 'header' é do tipo array de char, enquanto 'packet' é um ponteiro de inteiro. Há, no loop, uma atribuição ao 'packet[i]' do valor 'header[i]', isto é, um char sendo atribuido a um ponteiro de inteiro.
*/

/*
    o primeiro 'for':
    * pensando o que poderia ser a ideia original do for caso packet fosse um array de inteiros: ele criaria uma repetição de sequencia de 3 bytes, por exemplo, 0x00 0x01 0x02 0x00 0x01 0x02 ...

    Esse for não tem sentido algum ao propósito da função.
*/

/*
    o segundo 'for':
    * Ele esta com a lógica errada também porque ele substitui os 12 primeiros bytes do packet pelos do header. Não é isso que a função se propõe.

    Além disso, a instrução 'i<12' pode levar a um erro em tempo de execução no acesso à posição i caso o tamanho do packet seja menor que 12. O for como está é errado.
*/

/*
    comparar 'packet' com NULL funciona, caso NULL seja uma macro para o valor 0, porem, pesquisando, descobri o nullptr como uma opção melhor para saber se um ponteiro é nulo caso estejamos usndo c++11 ou acima.   
*/


/*
    o array header se considerado como char da erro por estouro de range de valores. Char aceita inteiros entre -128 e 127. O primeiro byte 0x80 corresponde a 128 em inteiro e isso gera erro. Transformar o array de char em unsigned char resolve esse problema porque unsigned char aceita valores entre 0 e 255.
*/

// O arquivo improved_insert_header.cpp é uma reescrita dessa função e que funciona.
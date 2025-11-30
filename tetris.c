#include <stdio.h>
#include <stdlib.h>

//cria um novo tipo de dado chamado Peca.
typedef struct
{
    char tipo;
    int id;
}Peca;

// Define o tamanho maximo da fila e o tipo
#define TAM_MAX 5
#define TIPOS "IOTL"

// O array que guarda as 5 peças.
Peca fila_pecas[TAM_MAX];
int primeira_peca = -1; // Peça que vai sair
int ultima_peca = -1; // Peça que acabou de entrar
int tamanho_atual = 0; // Contador das peças da fila
int proximo_id = 0; // Contador de ID único

// Checa se a fila está vazia.
int esta_vazia() {
    return tamanho_atual == 0;
}

// Checa se a fila está cheia.
int esta_cheia() {
    return tamanho_atual == TAM_MAX;
}

// Cria uma nova peça com ID único e tipo aleatório.
Peca nova_peca(){
    Peca np;
    int indice_tipo = rand() % (sizeof(TIPOS)-1);
    np.tipo = TIPOS[indice_tipo];
    np.id = proximo_id++;
    return np;
}

// Insere a peça.
void insere_peca() {
    if (esta_cheia()) {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\n>>>>>>>> Fila cheia (TAM_PAX: %d)\n", TAM_MAX);
        return;
    }
    
    Peca np = nova_peca (); // Cria a nova peça.

    // Se for a primeira peça, o ponteiro de saída vai para a posição 0.
    if (primeira_peca == -1){
        primeira_peca = 0;
    }

    // Calcula a próxima posição da última peça.
    ultima_peca = (ultima_peca + 1) % TAM_MAX;

    // Confirmação da inclusão da peça.
    fila_pecas[ultima_peca] = np;
    tamanho_atual++;
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\nPEÇA INSERIDA!");
    printf("\n++ TIPO: %c", np.tipo);
    printf("\n++ ID: %d", np.id);
}

// Jogar peça.
void jogar_peca() {
    if (esta_vazia()) {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\n>>>>>>>> Fila vazia, não há peças.\n");
        return;
    }

    Peca jp = fila_pecas[primeira_peca]; // Guarda a peça que será removida.
    tamanho_atual--; // Diminui o contador

    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\nPEÇA JOGADA!");
    printf("\n>> TIPO: %c", jp.tipo);
    printf("\n>> ID: %d", jp.id);

    if (tamanho_atual > 0){
        // Move o ponteiro de saída para o próximo item
        primeira_peca = (primeira_peca + 1) % TAM_MAX;
    }else {
        // Reseta os ponteiros para -1.   
        primeira_peca= -1;
        ultima_peca = -1;
    }
}

// Exibe a fila no seu estado atual.
void exibe_fila(){
    printf("\n");
    printf("\nFILA (Tamanho Atual: %d/%d)\n",tamanho_atual, TAM_MAX);


    if (esta_vazia()){
        printf("Fila está VAZIA.");~
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        return;
    }

    int i = primeira_peca; // 'i' começa na posição do primeiro item.
    int c = 0; // 'c' conta quantos itens já foram mostrados.

    // Loop que repete até mostrar todos os itens (igual a 'tamanho_atual').
    while (c < tamanho_atual)
    {
        printf("[%c %d]", fila_pecas[i].tipo, fila_pecas[i].id);

        // Avança para a próxima posição
        i = (i + 1) % TAM_MAX;
        c++;
    }
    printf("\n");
    printf("\n=========================================================\n");
}

// início do programa, menu de opções.
int main (){
    int opcao;

    // Inicia o gerador aleatório.
    srand(1); 

    printf("\nVAMOS JOGAR?\n");

    // Insere peças até a fila ficar cheia.
    while (!esta_cheia()) {
        insere_peca();
    }

    exibe_fila(); // Mostra o estado inicial da fila.

    // Loop do menu.
    do{
        printf("\n1. Jogar Peça.\n");
        printf("2. Inserir Nova Peça.\n");
        printf("3. Sair.\n");
        printf("ESCOLHA UMA OPÇÃO: ");

        // Testa o item escolhido do menu.
        if (scanf("%d", &opcao) != 1) {
            printf("\nENTRADA INVÁLIDA!, ESCOLHA UMA OPÇÃO: ");
            opcao = -1;
            continue;
        }

        // Executa a função baseada na opção (1, 2 ou 3).
        switch (opcao){
            case 1:
                jogar_peca();
                exibe_fila();
                break;
            case 2:
                insere_peca();
                exibe_fila();
                break;
            case 3:
                printf("\nSaindo do jogo, obrigado por JOGAR!\n");
                break;
            
            default:
                printf("\nOpção INVÁLIDA.");
        }
    // O loop continua enquanto o usuário não digitar 3 (Sair).
    } while (opcao != 3);

return 0; // Finaliza o programa.

}
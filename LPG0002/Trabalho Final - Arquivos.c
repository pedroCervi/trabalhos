/*
  Você é o dono de uma loja de materiais e precisa manter um inventário que
  poderá informar quais e quantas ferramentas você possui, e o custo de cada
  uma. Escreva um programa que inicialize o "hardware.dat" para 100 registros
  vazios e permita que você insira os dados referentes a cada ferramenta, liste
  todas as suas ferramentas, exclua um registro para a ferramenta que não possui
  mais e atualize qualquer informação. O número de identificação da ferramenta
  deverá ser o número do registro. Use a informação a seguir para inicializar
  seu arquivo:

  #registro     Nome da Ferramenta             Quantidade            Custo 
  3             Furadeira                      7                     57.98 
  17            Martelo                        76                    11.99
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct registro {
  char nome[100];
  int quantidade;
  float preco;
};

struct registro REGISTROS[100];

void salvar_banco() {
  FILE *banco = fopen("hardware.dat", "w");
  
  // Salva no arquivo
  
  fwrite(&REGISTROS, sizeof(struct registro), 100, banco); // 100 de REGISTRO, e arquivo banco
  
  // Fecha o arquivo
  
  fclose(banco);
}

void criar_banco() {
  
  // Coloca os dois itens iniciais como pede o enunciado
  
  strcpy(REGISTROS[3].nome, "Furadeira");
  REGISTROS[3].quantidade = 7;
  REGISTROS[3].preco = 57.98;
  
  strcpy(REGISTROS[17].nome, "Martelo");
  REGISTROS[17].quantidade = 76;
  REGISTROS[17].preco = 11.99;
  
  
  salvar_banco(); // e salva
}

void abrir_banco() {
  // Tenta abrir o banco
  
  FILE *banco = fopen("hardware.dat", "r");
  
  // Vê se o banco já existe
  
  if(banco) {
    
    // Lê os registros no banco
    fread(&REGISTROS, sizeof(struct registro), 100, banco);
    
    // Fecha o arquivo
    fclose(banco);
  } else {
    
    // Se não conseguiu abrir o banco,cria um banco
    
    criar_banco();
    
    abrir_banco();
    
  }
}

void listar() {
  printf("\n\tLista de itens\n");
  
  int i;
  printf("#Registro  Nome    Custo  Quantidade\n");
  for(i = 0; i < 100; i++) {
    // se tiver um item nesse numero
    if(strlen(REGISTROS[i].nome) != 0) {
      printf("Item #%d = %s (R$%0.2f, Qntd %d)\n", i, REGISTROS[i].nome, REGISTROS[i].preco, REGISTROS[i].quantidade);
    } 
  }
}

void excluir() {
  printf("\n\tExcluir um item\n");
  printf("\n- Por favor, digite o numero do item que voce deseja excluir\n");
  listar();
  
  int numero;
  printf("\nNumero: ");
  scanf("%d", &numero);
  
  //__fpurge(stdin); //  função para limpar o teclado no linux
  fflush(stdin); // função para limpar o teclado no windows
  
  // verifica se o numero esta dentro do limite e não esta vazio
  if(numero >= 0) {
    if((numero < 100) && (numero != 0)) {
      // está... pode deletar
      if(strlen(REGISTROS[numero].nome) != 0) {// e também se existe
        printf("\nItem selecionado: Item #%d\n", numero, REGISTROS[numero].nome, REGISTROS[numero].preco, REGISTROS[numero].quantidade);
        strcpy(REGISTROS[numero].nome, "");
        printf("\nO item %d foi excluido do registro com sucesso.", numero );
        return;
      } else {
        printf("\nItem #%d nao existe. \n", numero);
        return;
      }
      
    } 
  } 
}

void atualizar() {
  printf("\n\tAtualizar um item\n");
  printf("\n- Por favor, digite o numero do item que voce deseja atualizar: \n");
  listar();
  int numero;
  printf("\nNumero informado: ");
  scanf("%d", &numero);
  
  //__fpurge(stdin); //  função para limpar o teclado no linux
  fflush(stdin); // função para limpar o teclado no windows
  
  // verifica se o numero esta dentro do limite
  if(numero >= 0) {
    if(numero < 100 && numero == numero) {
      
      if(strlen(REGISTROS[numero].nome) != 0) { // e também se existe
        printf("\nItem selecionado: Item #%d = %s (preco R$%0.2f, quantidade %d)\n", numero, REGISTROS[numero].nome, REGISTROS[numero].preco, REGISTROS[numero].quantidade);
	  } else {
        printf("\nItem #%d nao existe. \n", numero);
        return;
      }
      printf("\nDigite o novo nome:\n");
      scanf("%s", REGISTROS[numero].nome);
      
      printf("\nDigite o novo preco:\n");
      scanf("%f", &REGISTROS[numero].preco);
      
      printf("\nDigite a nova quantidade:\n");
      scanf("%d", &REGISTROS[numero].quantidade);
      
      printf("\nO item %d foi atualizado com sucesso.", numero );
      printf("\nItem atualizado: Item #%d = %s (preco R$%0.2f, quantidade %d)\n", numero, REGISTROS[numero].nome, REGISTROS[numero].preco, REGISTROS[numero].quantidade);
      fflush(stdin);

  	}
  }
}

void adicionar() {
  printf("\n\tAdicionar um item\n");
  printf("\n- Por favor, digite o numero do item que voce adicionar: \n");
  listar();
  int numero;
  printf("\nNumero: ");
  scanf("%d", &numero);
  
  //__fpurge(stdin); //  função para limpar o teclado no linux
  fflush(stdin); // função para limpar o teclado no windows
  
  // verifica se o numero esta dentro do limite
  if(numero >= 0) {
    if(numero < 100 && &numero != 0) {
    	if(strlen(REGISTROS[numero].nome) != 0) {
    	    printf("\nItem #%d ja existe nos registros. \n", numero);
    	    return;
        } else {
        	printf("\nItem #%d ainda nao existe. Continue para adicionar.\n", numero);
        }
      
      printf("\nDigite o nome: \n");
      scanf("%s", REGISTROS[numero].nome);
      
      printf("Digite o preco: \n");
      scanf("%f", &REGISTROS[numero].preco);
      
      printf("Digite a quantidade: \n");
      scanf("%d", &REGISTROS[numero].quantidade);
      
      printf("Item #%d = %s (preco R$%0.2f, quantidade %d)\n", numero, REGISTROS[numero].nome, REGISTROS[numero].preco, REGISTROS[numero].quantidade);
      fflush(stdin);
	}
  }
}

void mostra_menu() {

  while(1) { //enquanto for 1, continuar
    
    printf("\n\n\nPor favor, digite uma opcao: \n\n1 - (L)istar as ferramentas; \n2 - (E)xcluir uma ferramenta; \n3 - (A)tualizar uma ferramenta; \n4 - A(d)icionar uma ferramenta; \n5 - (S)air do programa.\n");
    printf("\nOpcao: ");
    char opcao = getchar();
    

     //__fpurge(stdin); //  função para limpar o teclado no linux
 	 fflush(stdin); // função para limpar o teclado no windows
    
    switch(opcao) {
      case 'l':
      case 'L':
      case '1':
        listar();
        break;
      
      case 'e':
      case 'E':
      case '2':
        excluir();
        break;
      
      case 'a':
      case 'A':
      case '3':
        atualizar();
        break;
        
      case 'd':
      case 'D':
      case '4':
		adicionar();
		break;
		
      case 's':
      case 'S':
      case '5':
        return; // termina a funcao
      
      default:
        printf("Opcao invalida!\n");
    }
    
    // depois de executar uma operação, salvar o arquivo de novo
    salvar_banco();
  }
}

int main() {
  
  abrir_banco();
  
  mostra_menu();
  
  return 0;
}

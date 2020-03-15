#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct datanode
{
  int id;
} DataNode;

typedef struct node
{
  DataNode data;
  struct node *next;
} Node;

typedef struct list
{
  int size;
  Node *head;
} List;

// HEADERS DAS FUNÇÕES
List *createList();                                   // Cria a lista
void push(List *list, DataNode data);                 // Adiciona um elemento no inicio
void pop(List *list);                                 // Remove um elemento do início
void whiteList(List *list);                           // Imprime a lista
bool isEmpty(List *list);                             // Retorna bool se a lista esta vazia
Node *showNode(List *list, int index);                // Retorna um node de uma posição
int showIndex(List *list, Node *node);                // Retorna a posição de um node
void destroy(List *list, int index);                  // Remove o node de uma posição
void insert(List *list, DataNode data, int index);    // Insere um node em uma posição
void xchgNodes(List *list, Node *nodeA, Node *nodeB); // Altera a posição de dois nodes
Node *min(List *list, int index);                     // Retorna o node com menor ID da lista
Node *max(List *list, int index);                     // Retorna o node com maior ID da lista
void incSort(List *list);                             // Ordena a lista em ordem decrescente
void decSort(List *list);                             // Ordena a lista em ordem crescente

// IMPLEMENTAÇÕES
List *createList()
{
  List *list = (List *)malloc(sizeof(List)); // Aloca na memória RAM um espaço de bytes com o tamanho da lista
  list->size = 0;                            // Inicia com o tamanho 0
  list->head = NULL;                         // Aponta a cabeça para null

  return list;
}

void push(List *list, DataNode data)
{
  Node *node = (Node *)malloc(sizeof(Node)); // Cria um novo node
  node->data = data;                         // Adiciona os dados nele
  node->next = list->head;                   // Adiciona o da cabeça no novo node
  list->head = node;                         // Adiciona o novo node na cabeça
  list->size++;                              // Incrementa o tamanho
}

void whiteList(List *list)
{
  if (isEmpty(list))
  {
    printf("Lista vazia!\n");
    return;
  }

  Node *pointer = list->head; // Recebe o node da cabeça
  int index = 0;

  while (pointer != NULL)
  {
    DataNode data = pointer->data;                 // Extrai os dados do node
    printf("Index: %d, ID: %d\n", index, data.id); // Imprime o dado na tela
    index++;                                       // Incrementa o indice
    pointer = pointer->next;                       // Vai para o proximo node para repetição
  }
  return;
}

bool isEmpty(List *list)
{
  return (list->size == 0); // Retorna true ou false
}

void pop(List *list)
{
  if (!isEmpty(list))
  {
    Node *pointer = list->head; // Pega o node da cabeça
    list->head = pointer->next; //Adiciona o proximo node na cabeça
    free(pointer);              // Apaga o node anterior da cabeça
    list->size--;               // Decrementa o tamanho da lista
    return;
  }

  printf("A lista esta vazia!\n");
  return;
}

Node *showNode(List *list, int index)
{
  if (index >= 0 && index < list->size)
  {                          // Valida a posição informada
    Node *node = list->head; // Recupera o node da cabeça
    int i;

    for (i = 0; i < index; i++) // Percorre ate a posição desejada
      node = node->next;        // Pula para o proximo node ate a posição indicada

    return node; // Retorna o node na posição indicada
  }

  printf("Este index nao existe!\n");
  return NULL;
}

int showIndex(List *list, Node *node)
{
  if (node != NULL)
  {                             // Valida a existencia do node
    Node *pointer = list->head; // Recupera o node da cabeça
    int index = 0;              // Cria uma posição inicial

    while (pointer != NULL && pointer != node)
    {                          // Percorre todos os nodes
      pointer = pointer->next; // Pula para o proximo node
      index++;                 // Incrementa a posição inicial
    }

    if (pointer != NULL) // Verifica se existe um node no ponto indicado
      return index;      // Retorna a posição
  }

  printf("Não pertencente a lista!\n");
  return -1;
}

void destroy(List *list, int index)
{
  if (index == 0)
  {
    pop(list); // Apaga o node da cabea
    return;
  }
  else
  {
    Node *nodeASerExcluido = showNode(list, index); // Busca o node da posição indicada
    if (nodeASerExcluido != NULL)
    {                                                 // Verifica a existencia do node
      Node *nodeAnterior = showNode(list, index - 1); // Busca um node anterior ao indicado
      nodeAnterior->next = nodeASerExcluido->next;    // Adiciona o node posterior ao indicado para o node anterior
      free(nodeASerExcluido);                         // Remove o node indicado, pois o posterios á foi salvo no anterior
      list->size--;                                   // Decrementa a lista
      return;
    }
    else
    {
      printf("Não encontrado!\n");
      return;
    }
  }
  return;
}

void insert(List *list, DataNode data, int index)
{
  if (index == 0)
    push(list, data); // Insere um node na cabeça
  else
  {
    Node *nodeAtual = showNode(list, index); // Recupera o node da posição indicada
    if (nodeAtual != NULL)
    {                                                        // Verifica a existencia do node indicado
      Node *nodeASerInserido = (Node *)malloc(sizeof(Node)); // Cria um novo node para ser inserido
      nodeASerInserido->data = data;                         // Adiciona os dados no novo node

      Node *nodeAnterior = showNode(list, index - 1); // Busca p noe anterior ao indicado

      nodeAnterior->next = nodeASerInserido; // Adiciona o novo node como posterior ao node anterior
      nodeASerInserido->next = nodeAtual;    // Adiciona o node indicado como posterior ao novo node
      list->size++;                          // Incrementa a lista
    }
  }

  return;
}

void xchgNodes(List *list, Node *nodeA, Node *nodeB)
{
  if (nodeA == nodeB) // Verifica de o nodeA é igual ao NodeB
    return;

  int indexA = showIndex(list, nodeA); // Recupera a posição do nodeA
  int indexB = showIndex(list, nodeB); // Recupera a posição do nodeB

  if (indexA == -1 || indexB == -1) // Verifica se a posição é existente e válida
    return;

  if (indexA > indexB)
  {                                 // Verifica se o nodeA é maior que o nodeB. O nodeA deve ser anterior ao nodeB na lista
    nodeA = nodeB;                  // O nodeA recebe o nodeB pois ele é posterior
    nodeB = showNode(list, indexA); // Recupera o nodeA e adiciona ao nodeB, para que ele possa ser menor

    indexA = indexB;                 // Altera o index salvo do nodeA para o menor (nodeB)
    indexB = showIndex(list, nodeB); // Recupera a posição do nodeB que já foi atualizada para ser maior ao nodeA
  }

  Node *pointB = showNode(list, indexB - 1); // Recupera o node anterior do nodeB

  if (nodeA == list->head)
  {                     // Verifica se o nodeA esta na cabeça da lista
    list->head = nodeB; // Se ele estiver na cabeça da lista, adiciona o nodeB para a cabeça, alterando a posição
  }
  else
  {
    Node *pointA = showNode(list, indexA - 1); // Se não estiver, recupera o node anterior ao nodeA
    pointA->next = nodeB;                      // Adiciona o nodeB para como o posterior ao anterior do nodeA
  }

  pointB->next = nodeA; // Adiciona o nodeA como posterior ao nodeB

  Node *pointer = nodeA->next; // Salva o node posterior ao nodeA
  nodeA->next = nodeB->next;   // Adiciona o posterior do nodeB como um posterior ao nodeA
  nodeB->next = pointer;       // Adiciona o posterior do nodeA salvo como o posterior do nodeB

  return;
}

Node *min(List *list, int index)
{
  Node *pointer = showNode(list, index); // Busca o node na posição escolhida
  if (pointer != NULL)
  {
    Node *minNode = pointer; // Grava a o node retornado
    while (pointer != NULL)
    {
      if (pointer->data.id < minNode->data.id) // Verifica o ID do node atual com o node que foi gravado
        minNode = pointer;                     // Se for menor, atualiza o node gravado

      pointer = pointer->next; // Vai para o próximo node
    }
    return minNode; // Retorna o node com ID mínimo
  }
  return NULL;
}

Node *max(List *list, int index)
{
  Node *pointer = showNode(list, index); // Busca o node na posição escolhida
  if (pointer != NULL)
  {
    Node *maxNode = pointer; // Grava a o node retornado
    while (pointer != NULL)
    {
      if (pointer->data.id > maxNode->data.id) // Verifica o ID do node atual com o node que foi gravado
        maxNode = pointer;                     // Se for maior, atualiza o node gravado

      pointer = pointer->next; // Vai para o próximo node
    }
    return maxNode; // Retorna o node com ID máximo
  }
  return NULL;
}

void incSort(List *list)
{
  int i;
  for (i = 0; i < list->size - 1; i++)
    xchgNodes(list, showNode(list, i), min(list, i)); // Troca a posição do node pelo índice com o menor node a partir do índice
}

void decSort(List *list)
{
  int i;
  for (i = 0; i < list->size - 1; i++)
    xchgNodes(list, showNode(list, i), max(list, i)); // Troca a posição do node pelo índice com o maior node a partir do índice
}

// INICIO
int main(void)
{
  printf("_________________________________\n");

  List *listaAtual = createList(); // Cria a lista

  DataNode data; // Cria os dados para manipulação
  data.id = 6;
  push(listaAtual, data); // Adiciona os dados no inicio da lista
  data.id = 12;
  push(listaAtual, data); // Adiciona os dados no inicio da lista
  data.id = 2;
  push(listaAtual, data); // Adiciona os dados no inicio da lista
  data.id = 14;
  push(listaAtual, data); // Adiciona os dados no inicio da lista
  data.id = 5;
  push(listaAtual, data); // Adiciona os dados no inicio da lista

  whiteList(listaAtual); // Imprime a lista
  incSort(listaAtual);

  printf("\nLista ordenada crescente:\n");
  whiteList(listaAtual);
  decSort(listaAtual);

  printf("\nLista ordenada decrecente:\n");
  whiteList(listaAtual);

  printf("\nTamanho da lista: %d\n", listaAtual->size); // Imprime o tamanho da lista
  return 0;
}
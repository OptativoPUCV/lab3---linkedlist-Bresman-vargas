#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List *nuevaLista = (List *)malloc(sizeof(List));
  //En caso de error en la reserva 
  assert(nuevaLista != NULL);
  nuevaLista->head = NULL;
  nuevaLista->tail = NULL;
  nuevaLista->current = NULL;
  return nuevaLista;
}

void * firstList(List * list) {
  if(list -> head != NULL){
    list -> current = list -> head;
    return list-> head-> data;
  }
  return NULL;
}

void * nextList(List * list) {
  if(list -> current != NULL && list -> current -> next != NULL){ //Tiene que ser alguna de las dos
    list -> current = list -> current -> next;
    return list -> current -> data;
  }
    return NULL;
}

void * lastList(List * list) {
  if(list -> head != NULL){
    Node* current = list -> head;
    while(current-> next != NULL){
      current = current -> next;
    }
    list -> current = current;
    return current -> data;
  }
  return NULL;
}

void * prevList(List * list) {
  if(list -> current != NULL && list -> current != list -> head){
    Node * current = list -> head;
    Node * prev = NULL;
    while(current != list -> current ){
      prev = current;
      current =  current -> next;
    }
    list->current = prev;
    return prev -> data;
  }
    return NULL;
}

void pushFront(List * list, void * data) {
  Node *newNode = createNode(data);
  //De estar en Null el head
  if(list -> head == NULL){
    list -> head = newNode;
    list -> tail = newNode;
  } else {
    newNode -> next = list -> head;
    list -> head -> prev = newNode;
    list -> head = newNode;
  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  if(list == NULL){
    return;
  }
  Node * nuevoNodo = (Node *)malloc(sizeof(Node));
  assert(nuevoNodo != NULL);
  nuevoNodo->data = data;

  if(list -> head == NULL){
    nuevoNodo->next = NULL;
    nuevoNodo->prev = NULL;
    list->head = nuevoNodo;
    list->current = nuevoNodo;
    list->tail = nuevoNodo;
  } else {
    if(list->current == NULL){
      return;
    }
  }
  nuevoNodo->next = list->current->next;
  nuevoNodo->prev = list->current;
  list->current->next = nuevoNodo;
  list->current = nuevoNodo;

  if(nuevoNodo->next == NULL){
    list->tail->prev = nuevoNodo;
    list->tail = nuevoNodo;
    
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  if(list->current == NULL || list == NULL){
    return NULL;
  }
  Node *prev = NULL;
  Node *current = list->head;
  while(current != list->current){
    prev = current;
    current = current->next;
  }

  if(prev != NULL){
    prev->next = current->next;
  } else {
    list->head = current->next;
  }

  if(current->next != NULL){
    current->next->prev = current->prev;
  } else {
    list->tail = current->prev;
  }

  void *data = current->data;
  free(current);
  return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
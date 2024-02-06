#include "arvore.h"

//IMPLEMENTADO
Arvore* alocarArvore(){
    Arvore* arvore = malloc(sizeof(Arvore));
    arvore -> raiz = NULL;
    return arvore;
}

//IMPLEMENTADO
No* newnode(Pessoa pessoa, int id){
    No* no = (No*) malloc(sizeof(No));
    no -> noPai = NULL;
    no -> esquerda = NULL;
    no -> direita = NULL;
    if(id != 1){
        no -> cor = 'v';
    }
    else{
        no -> cor = 'p';
    }
    no -> info = pessoa;
    return no;
}

//IMPLEMENTADO
void desalocarArvore(No* no){
    if(no == NULL) return;

    else{
        desalocarArvore(no -> esquerda);
        desalocarArvore(no -> direita);
    }
    free(no);
}

//IMPLEMENTADO
void leArvore(Pessoa* pessoa){
    scanf("%s %d", pessoa->nome, &pessoa->idade);
}

//IMPLEMENTADO
No* insercao(No* no, Pessoa pessoa){
    if ( no == NULL ) return false ;
    if (pessoa.idade < no -> info . idade) {
        if ( no -> esquerda == NULL ) {
            no -> esquerda = newnode(pessoa, 0);
            no -> esquerda -> noPai = no;
            return no -> esquerda ;
        }
        return insercao( no->esquerda, pessoa);
    }
    if (pessoa.idade > no -> info . idade) {
        if ( no -> direita == NULL ) {
            no -> direita = newnode(pessoa, 0);
            no -> direita -> noPai = no;
            return no -> direita ;
        }
        return insercao( no->direita, pessoa);
    }   
    return NULL;
}

//IMPLEMENTADO
No* Avo(No* no){
    if(no->noPai->noPai == NULL){
        return NULL;
    }
    return no->noPai->noPai;
}

//IMPLEMENTADO
No* Tio(No* no){
    No*aux = Avo(no);
    if(aux != NULL){
        if(aux->esquerda == no->noPai){
            return aux->direita;
        }
        else if(aux->direita == no->noPai){
            return aux->esquerda;
        }
    }
    return NULL;
}

void RSE ( No * x , Arvore* T ) {
    No *y = x->direita;
    x->direita = y->esquerda;
    if(y->esquerda!=NULL){
      y->esquerda->noPai = x;
    }
    y->noPai = x->noPai;
    if(x->noPai==NULL){
      T->raiz = y;
    }else{
      if(x==x->noPai->esquerda){
        x->noPai->esquerda = y;
      }else{
        x->noPai->direita = y;
      }
    }
    y->esquerda = x;
    x->noPai = y;
    if((y->esquerda != NULL) && (y->direita != NULL)){
        y->esquerda->cor = 'v';
        y->direita->cor = 'v';
        y->cor = 'p';
    }
    else{
        y->esquerda->cor = 'v';
        y->cor = 'p';
    }
}   

void RSD ( No * x , Arvore* T  ) {
    No *y = x->esquerda;
    x->esquerda = y->direita;
    if(y->direita!=NULL){
      y->direita->noPai = x;
    }
    y->noPai = x->noPai;
    if(x->noPai==NULL){
      T->raiz = y;
    }else{
      if(x==x->noPai->direita){
        x->noPai->direita = y;
      }else{
        x->noPai->esquerda = y;
      }
    }
    y->direita = x;
    x->noPai = y;
    if((y->esquerda != NULL) && (y->direita != NULL)){
        y->esquerda->cor = 'v';
        y->direita->cor = 'v';
        y->cor = 'p';
    }
    else{
        y->direita->cor = 'v';
        y->cor = 'p';
    }
    
}

void fix(No* no, Arvore *T){
    if(no->noPai == NULL){
        no->cor = 'p';
        return;
    }
    if((no->noPai->cor == 'p') || (no == NULL)){
        return;
    }

    No* tio = Tio(no);
    No* avo = Avo(no);

    if((tio != NULL)&&(avo != NULL)){
        if((tio->cor == 'v')&&(no->noPai->cor == tio->cor)){
            tio->cor = 'p';
            no->noPai->cor = 'p';
            avo->cor = 'v';
            if(avo == T->raiz){
                avo->cor = 'p';
            } 
            else{
                fix(avo, T);
            } 
        }
    }
    else if ((avo != NULL)){
        if((no->noPai == avo->esquerda)&&((no->noPai->cor == 'v')&&(tio == NULL))){
            if(no == no->noPai->esquerda){
                RSD(avo,T);
            }
            else if(no == no->noPai->direita){
                RSE(no->noPai,T); 
                RSD(avo, T);
                //printf("|%s %s %s|", avo->info.nome, no->noPai->info.nome, no->info.nome);
            }
        }
        else if((no->noPai == avo->direita)&&((no->noPai->cor == 'v')&&(tio == NULL))){
            if(no == no->noPai->direita){
                RSE(avo,T);
            }
            else if(no == no->noPai->esquerda){
                RSD(no->noPai,T);   
                RSE(avo, T);
                //printf("|%s |", avo->noPai->info.nome);       
            }
        }
    }
}


//IMPLEMENTADO
void printInOrder(No* no){
    if (no != NULL) {
    if (no->esquerda != NULL)
      printInOrder(no->esquerda);
    if(no->cor == 'p')
      printf(Preto"Nome: %s\nIdade: %d\n", no->info.nome, no->info.idade);
    else
      printf(Vermelho"Nome: %s\nIdade: %d\n", no->info.nome, no->info.idade);
    if (no->direita != NULL)
      printInOrder(no->direita);
  }
}

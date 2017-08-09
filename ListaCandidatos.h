#include <cstring>
#include <fstream>
#include <iostream>
#include "NoCandidato.h"

class ListaCandidatos
{
public:
    NoCandidato *head;

    ListaCandidatos()
    {
        this->head = NULL;
    }

    void adicioneComoHead(Candidato* c)
    {
        this->head = new NoCandidato(c,head);
    }

    bool estaVazia()
    {
        return head == NULL;
    }

    int tamanho()
    {
        int tam = 0;
        NoCandidato *aux = head;
        while(aux != NULL)
        {
            tam++;
            aux = aux->next;
        }
        return tam;
    }

    string toString()
    {
        if(estaVazia())
        {
            return ("0");
        }
        else
        {
            return head->toString();
        }
    }

    ListaCandidatos(string nomeDoArquivo)
    {
        this->head = NULL;
        ifstream fcin(nomeDoArquivo.c_str());
        string dados;
        getline(fcin,dados);
        cout << "criacao da lista de candidatos de: " << dados << endl;
        while(getline(fcin,dados))
        {
            adicioneComoHead(new Candidato(dados));
        }
    }

    bool remover(string nome, string sobrenome) // Simplificarei depois utilizando a lógica do ponteiro para o nó anterior
    {
        NoCandidato* it = this->head;
        if(estaVazia()) // Tratamento caso a lista esteja vazia
        {
            return false;
        }
        else if(it->conteudo->igual(nome,sobrenome)) // Tratamento especial caso o candidato esteja na head
        {
            NoCandidato* aux = it;
            head = it->next;
            delete(aux);
            return true;
        }
        else  // Caso a lista não esteja vazia e o candidato não esteja na head, percorrer a lista inteira em busca do candidato
        {
            while(it->next!=NULL) // Percorre todos os nós (a partir do segundo) da lista
            {
                if(it->next->conteudo->igual(nome,sobrenome))
                {
                    NoCandidato* aux = it->next;
                    it->next = it->next->next;
                    delete(aux);
                    return true;
                }
                it = it->next;
            }
            return false; // Se chegar aqui (sair do while) é porque o candidato não foi encontrado!
        }
    }

    void filtrarCandidatos(int nota)
    {
        NoCandidato* previous;
        NoCandidato* aux;
        if(estaVazia())
        {
            aux = NULL;
        }
        else
        {
            previous = head;
            aux = head;
        }
        while(aux!=NULL)
        {
            if( (aux->conteudo->nota) < nota)
            {
                if(aux == head)
                {
                    head = head->next;
                    delete(aux);
                    previous = head;
                    aux = head;
                }
                else
                {
                    previous->next = aux->next;
                    delete(aux);
                    aux = previous->next;
                }
            }
            else
            {
                previous = aux;
                aux = aux->next;
            }
        }
    }

    void concatena(ListaCandidatos* l)
    {
        NoCandidato* aux = this->head;
        if(estaVazia())
        {
            this->head = l->head;
        }
        else
        {
            while(aux->next!=NULL)
            {
                aux = aux->next;
            }
            aux->next = l->head;
        }
    }
};


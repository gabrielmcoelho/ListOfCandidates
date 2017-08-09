#include "candidato.h"

class NoCandidato {
	public:
	Candidato *conteudo;
	NoCandidato *next;

	NoCandidato(Candidato *c, NoCandidato *prox) {
		this -> conteudo = c;
		this -> next = prox;
	}

	string toString(){
     stringstream stream;
     stream << conteudo->toString() << " -> ";
     if(next != NULL){
        stream << next->toString();
     }
     else{
        stream << 0;
     }
     return stream.str();
  }
};

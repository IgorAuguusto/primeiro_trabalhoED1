#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

//Funcao que contem um menu para chamar o resto das funcoes
int menuGeral();
void retiraEnter(char *);
void maiuscSemAcento(char *);
int validarCPF(char *);
int validarCNPJ(char *);
int verificaData(char *);
void dataParaCaractere(int, int, int, char *);
int intervaloData(char *,char *, char *, int);
void pressioneEnter();


#endif // FUNCOES_H_INCLUDED

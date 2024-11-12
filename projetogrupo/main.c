#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>

void clearScreen()
{
    const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
    printf("\n\n\n\n\n");
}

#define Max_Size 30


typedef struct{
    int seqestudante, numestudante ;
    char nomeestudante[30], emailestudante[30];
        
}estudante;
typedef struct{
    int seqficha, numexercicios;
    char nomeficha[20],dataficha[10];
}fichaexercicios;
struct exercicio{
    int seqexercicio, identficadorficha;
    char nomeexercicio[12],graudifexercicio[7],solução[9];
};
struct submissao{
    int  seqsubmissao, identficadorestudante , identficadorficha, identificadorexercicio , numlinhasolucao,classificacaoestudante;
    char datasubmissao;
};




void listartodosestudantes(){
    estudante e1;
    FILE *dadosEstudante = fopen("dadosalunos.dat", "rb");
    while(fread(&e1, sizeof(estudante), 1, dadosEstudante) == 1){
        if(e1.numestudante != 0){
            printf("\n\n\t\033[0;36m|| Listade de estudantes -- \n\t|| Sequência do aluno: %d \n\t|| Número do aluno : %d \n\t|| Nome do aluno: %s \t|| Email: %s \n",
                e1.seqestudante,e1.numestudante, e1.nomeestudante, e1.emailestudante);
        }else{
            printf("\nA lista encontra-se vazia");
        }
        
    }
    printf("\n\t Prima Enter para voltar ao menu!");
    getch(); clearScreen();
    fclose(dadosEstudante);
}

void lerdadosestudante(){
    estudante e1;
    int i,n=0;
    
    do{
        printf("\n\t--(Para sair insira '0')--\n\n\t|| --Insira a sequencia ou o número do estundante a ser consultado: ");
        scanf("%d",&i);
        FILE *dadosEstudante = fopen("dadosalunos.dat", "rb");
        //fread(&e1, sizeof(estudante), 1, dadosEstudante);
        while(fread(&e1, sizeof(estudante), 1, dadosEstudante) == 1){
        // Process the read data (e.g., print or manipulate)
        if(e1.numestudante == i || e1.seqestudante == i){
            printf("\n\n\t\033[0;36m|| --Estudante encontrado-- \n\t|| Sequência do aluno: %d \n\t|| Número do aluno : %d \n\t|| Nome do aluno: %s \t|| Email: %s \n",
                e1.seqestudante,e1.numestudante, e1.nomeestudante, e1.emailestudante);
        }
        else{
            if(n!=1) printf("\n\t|| --Aluno não encontrado-- ||");
            n = 1;
        }
        }
        fclose(dadosEstudante);
        
    }while(i!=0);
    
}

void lerdadosficha(){
    fichaexercicios f1;
    int i,n=0;
    
    do{
        printf("\n\t--(Para sair insira '0')--\n\n\t|| --Insira a sequencia ou a data da ficha a ser consultada: ");
        scanf("%d",&i);
        FILE *dadosFichas = fopen("dadosficha.dat", "rb");
        while(fread(&f1, sizeof(fichaexercicios), 1, dadosFichas) == 1){
        if(f1.seqficha == i || f1.numexercicios == i){
            printf("\n\n\t\033[0;36m|| --Ficha encontrada-- \n\t|| Sequência da ficha: %d \n\t|| Nome Da ficha : %s \t|| Número de exercicios: %d \n\t|| Data da ficha: [%s] ",
                f1.seqficha, f1.nomeficha, f1.numexercicios, f1.dataficha);
        }
        else{
            if(n!=1) printf("\n\t|| --Ficha não encontrada-- ||");
            n = 1;
        }
        }
        fclose(dadosFichas);
        
    }while(i!=0);
    
}

int checkalunosnot100(){
    int i=0;
    estudante e1;
    FILE *dadosEstudante = fopen("dadosalunos.dat", "rb");
    while(fread(&e1, sizeof(estudante), 1, dadosEstudante) == 1){
        i++;
        if(i>=100){
            return 1;
        }
    }
    fclose(dadosEstudante);
}
int checkfichas(){
    int i=0;
    fichaexercicios f1;
    FILE *dadosFicha = fopen("dadosficha.dat", "rb");
    while(fread(&f1, sizeof(estudante), 1, dadosFicha) == 1){
        i++;
        if(i>=10){
            return 1;
        }
    }
    fclose(dadosFicha);
}
void registarDadosestudante(){
    int i,numcar=0;
    estudante e1;
    for(i=0;i<31;i++){
        e1.nomeestudante[i]=NULL;
        e1.emailestudante[i]=NULL;
    }
    if(checkalunosnot100()==1){
        printf("\n \t--Lista de alunos cheia !!! \n Prima Enter para voltar ao menu!");
        getch(); clearScreen();
    }
    else{
    FILE *dadosEstudante = fopen("dadosalunos.dat", "ab");
    printf("\n|| --Insira a sequência do estudante: ");
    scanf("%d",&e1.seqestudante);    
    printf("|| --Insira o número do estudante: ");
    scanf("%d",&e1.numestudante);    
    
    printf("|| --Insira o nome do estudante: ");
    getchar();
    fgets(e1.nomeestudante,Max_Size,stdin);
    printf("|| --Insira o email do estudante: ");
    scanf("%s",&e1.emailestudante);
    
    fwrite(&e1,1,sizeof(e1),dadosEstudante);
    printf("|| --Estudante registado com sucesso!-- ||\n\tPrima Enter para continuar...");
    getch(); clearScreen();
    fclose(dadosEstudante);
    }
}
void registarfichas(){
    int i,numcar=0;
    fichaexercicios f1;
    for(i=0;i<31;i++){
        f1.nomeficha[i]=NULL;
        f1.dataficha[i]=NULL;
    }
    if(checkfichas()==1){
        printf("\n \t--Lista de fichas cheia !!! \n Prima Enter para voltar ao menu!");
        getch(); clearScreen();
    }
    else{
    
    printf("\n|| --Insira a sequência da ficha: ");
    scanf("%d",&f1.seqficha);    
    printf("|| --Insira o nome da ficha: ");
    getchar();
    fgets(f1.nomeficha,Max_Size,stdin);   
    
    printf("|| --Insira o número de exercicios: ");
    scanf("%d",&f1.numexercicios);
    printf("|| --Insira a data da ficha 'Dia/Mês/Ano': ");
    getchar();
    fgets(f1.dataficha,Max_Size,stdin);;
    FILE *dadosFicha = fopen("dadosficha.dat", "ab");
    fwrite(&f1,1,sizeof(f1),dadosFicha);
    printf("|| --Dados da ficha registados com sucesso!-- ||\n\tPrima Enter para continuar...");
    getch(); clearScreen();
    fclose(dadosFicha);
    }
}



void manipularfichasexercicios(){
    int opcao;
    clearScreen();printf("\033[0;32m\n\n\t\t--Menu de manipulação das fichas de exercícios--\n\t 1 --Registar dados de uma ficha--\n\t 2 --Consultar dados de uma ficha--\n\t 3 --Ver todos os dados das fichas--\n");
    scanf("%d",&opcao);
    switch(opcao){
        case 1:
            registarfichas();
        break;
        case 2:
         lerdadosficha();
        break;
        default:
        printf("\n\t\t---Opção inválida.");
    }
}

void manipularestudantes(){
    int opcao1;
    clearScreen();
                do{
        clearScreen();//??????
        printf("\033[0;36m\n\t--Menu de manipulação de dados dos estudantes--\n\t1- Registar Um estudante\n\t2- Consultar dados dos estudantes\n\t3- Consultar a lista completa de estudantes\n\n\t 0- Para volrar ao menu inicial...\n\t Insira uma opção: ");
        scanf("%d",&opcao1);
    
        switch(opcao1){
            case 1:
                registarDadosestudante();
            break;
                
            case 2:
                lerdadosestudante();
            break;

            case 3:
                listartodosestudantes();
            break;
            default:
            if(opcao1!=0){
            clearScreen();
            printf("\n\t\tOpção inválida\n");
            }
            
        }
    }while(opcao1 != 0);

}




void menu(){
    int opcao,opcao1;
    do{
        
        printf("\033[0;33m\n\t\t--Menu Principal--\n \t1- Manipular dados de estudantes\n\t2- Manipular os dados das fichas de exercícios\n\tInsira uma opção: ");
        scanf("%d",&opcao);
        //printf("1-Manipular dados de estudantes\n");
        //printf("3-Registar dados das fichas de exercicios\n");
        //printf("4-Consultar dados das fichas de exercicios\n");
        //printf("5-Registar dados dos exercícios\n");
        //printf("6-Consultar dados dos exercícios\n");
        ///printf("7-Registar dados das submissões\n");
        //printf("8-Consultar dados das submissões\n");
        //printf("9-Estatisticas\n");
        //printf("0-Sair\n");
        

        switch(opcao){

            case 1:
            manipularestudantes();    
            break;

            case 2:
            manipularfichasexercicios();
            default:
            if(opcao!=0){
            clearScreen();
            printf("Opção inválida\n");
            }
            break;
}


        
    }while (opcao !=0);

}
    





int main(){
    

    menu();





    return 0;
}





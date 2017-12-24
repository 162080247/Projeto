#include<stdio.h>
#include<stdlib.h>
#include<conio.c>
#include<string.h>
#include<time.h>

typedef struct
{
    char nomel[21],nomea[21],area[16];
    int quant,codl;
} LIVRO;

typedef struct
{
    char nomeal[31],cpf[14];
    int matri;
} ALUNO;

typedef struct
{
    int codle,matrie;
    char data_sistema[15],data_dev[15],nomel[21];
} EMPRESTIMO;

void linha()
{
    int i;

    gotoxy(15,5);
    printf("%c",201);
    for (i=0; i<50; i++)
    {
        printf("%c",205);
    }
    printf("%c",187);
    gotoxy(15,20);
    printf("%c",200);

    for (i=0; i<50; i++)
    {
        printf("%c",205);
    }
    printf("%c",188);
}

void linhalateral ()
{
    int i;

    for (i=6; i<20; i++)
    {
        gotoxy(15,i);
        printf("%c",186);
        gotoxy (66,i);
        printf("%c",186);
    }
}

void menuprincipal ()
{
    system("cls");
    linha();
    linhalateral();
    gotoxy(34,7);
    printf("MENU PRINIPAL");
    gotoxy(20,10);
    printf("1- ACERVO");
    gotoxy(20,12);
    printf("2- MENU DO ALUNO");
    gotoxy(20,14);
    printf("3- EMPRESTIMOS");
    gotoxy(20,16);
    printf("4- SAIR");
    gotoxy(32,34);


}

void menulivro ()
{

    system("cls");
    linha();
    linhalateral();
    gotoxy(34,7);
    printf("MENU DO ACERVO");
    gotoxy(20,10);
    printf("1- CADASTRAR LIVRO");
    gotoxy(20,12);
    printf("2- EDITAR LIVRO");
    gotoxy(20,14);
    printf("3- REMOVER");
    gotoxy(20,16);
    printf("4- LISTAR LIVROS CADASTRADOS");
    gotoxy(20,18);
    printf("5- RETORNAR AO MENU PRINCIPAL");
    gotoxy(38,22);

}

void cadastrarl (LIVRO *pt)
{
    FILE *file;
    file= fopen("dadoslivro.dat","ab+");


    system("cls");
    int i;
    gotoxy (34,3);
    printf ("CADASTRO:\n");

    fseek (file,ftell(file)-sizeof(*pt),SEEK_END);

    if (fread(pt,sizeof(*pt),1,file)!=1)
    {
        pt->codl =1000;
    }
    else
    {
        fscanf(file,"%d",pt->codl);
        pt->codl=pt->codl +1;
    }

    gotoxy(34,7);
    printf("DIGITE O NOME DO LIVRO:");
    setbuf(stdin,NULL);
    gets(pt->nomel);


    gotoxy(34,9);
    printf("DIGITE O NOME DO AUTOR:");
    setbuf(stdin,NULL);
    gets(pt->nomea);

    gotoxy(34,11);
    printf("DIGITE A AREA DO CONHECIMENTO: ");
    setbuf(stdin,NULL);
    gets(pt->area);

    gotoxy(34,13);
    printf("QUANTIDADE DE EXEMPLARES:");
    setbuf(stdin,NULL);
    scanf("%d",&pt->quant);

    gotoxy(34,17);
    printf("CODIGO DO LIVRO: %d",pt->codl);
    gotoxy(34,20);

    fseek(file,0,SEEK_END);
    fwrite (pt,sizeof(LIVRO),1,file);
    setbuf(stdin,NULL);
    fclose(file);
    system("Pause");
}

void editarlivro (LIVRO *pt, EMPRESTIMO *ptr)
{
    char c;
    FILE *file;
    int cod2,i=0, j=0;
    system ("cls");

    setbuf(stdin,NULL);
    gotoxy (34,3);
    printf("EDITAR LIVRO");
    gotoxy(34,7);
    printf("DIGITE O CODIGO DO LIVRO: ");
    scanf("%d",&cod2);


    file = fopen("dadosemprestimo.dat","rb");
    while (fread(ptr,sizeof(*ptr),1,file)==1)
    {
        if (ptr->codle==cod2)
        {
            i++;
        }
    }
    fclose(file);
    if (i>0)
    {
        system("cls");
        gotoxy(34,5);
        printf ("LIVRO COM EXEMPLAR EMPRESTADO NAO PODE SER EDITADO");
        gotoxy(34,7);
        system("pause");
    }
    else
    {
        file = fopen ("dadoslivro.dat","r+b");

        while (fread(pt,sizeof(*pt),1,file)==1)
        {
            if (pt->codl == cod2)
            {
                j++;
            }
        }
        if (j==0)
        {
            system("cls");
            gotoxy (34,5);
            printf("LIVRO NAO CADASTRADO");
            gotoxy(34,7);
        }

        else
        {
            rewind(file);
            while (fread(pt,sizeof(*pt),1,file)==1)
            {
                if (cod2==pt->codl)
                {
                    gotoxy(34,9);
                    printf("NOME: %s",pt->nomel);
                    gotoxy(34,10);
                    printf("AUTOR: %s",pt->nomea);
                    gotoxy(34,11);
                    printf("AREA: %s\n",pt->area);
                    gotoxy(34,12);
                    printf("CODIGO DO LIVRO: %d\n",pt->codl);
                    gotoxy(34,13);
                    printf("QUANTIDADE: %d\n",pt->quant);
                    gotoxy(34,15);
                    printf("DESEJA FAZER ALTERACAO: S-SIM, N-NAO:");
                    c=getch();

                    if (c=='S'|| c=='s')
                    {
                        setbuf(stdin,NULL);
                        system("cls");
                        gotoxy(34,7);
                        printf("NOVO NOME:");
                        gets(pt->nomel);
                        setbuf(stdin,NULL);

                        gotoxy(34,8);
                        printf("NOME DO AUTOR:");
                        gets(pt->nomea);
                        setbuf(stdin,NULL);

                        gotoxy(34,9);
                        printf("AREA:");
                        gets(pt->area);
                        setbuf(stdin,NULL);

                        gotoxy(34,10);
                        printf("QUANTIDADE:");
                        scanf("%d",&pt->quant);
                        gotoxy(34,12);

                        fseek(file,ftell(file)-sizeof(*pt),0);
                        fwrite (pt,sizeof(*pt),1,file);
                        fclose(file);

                        printf("INFORMACOES MODIFICADAS COM SUCESSO");
                        gotoxy(34,14);

                    }
                }
            }
        }
    }
    system("Pause");
}

void removerlivro (LIVRO *pt,EMPRESTIMO *ptr)
{
    char c;
    FILE *file,*file2;
    int cod2,j=0,g=0;

    system("cls");
    setbuf(stdin,NULL);

    gotoxy(34,3);
    printf ("REMOVER LIVRO");

    gotoxy(34,7);
    printf("DIGITE O CODIGO DO LIVRO:");
    scanf("%d",&cod2);
    gotoxy(34,9);

    file = fopen ("dadosemprestimo.dat","rb");

    while (fread(ptr,sizeof(*ptr),1,file)==1)
    {
        if(ptr->codle==cod2)
        {
            j++;
        }
    }
    fclose(file);
    if(j>0)
    {
        system("cls");
        gotoxy(34,5);
        printf("LIVRO COM EXEMPLAR EMPRESTADO NAO PODE SER REMOVIDO");
        gotoxy (34,7);
    }
    else
    {


        file = fopen ("dadoslivro.dat","rb+");

        while (fread(pt,sizeof(*pt),1,file)==1)
        {
            if (pt->codl== cod2)
            {
                g++;
            }
        }
        if (g==0)
        {
            system("cls");
            gotoxy(34,5);
            printf("LIVRO NAO CADASTRADO");
            gotoxy(34,7);
        }
        else
        {

            rewind(file);
            file2= fopen ("livrosremo.dat","wb+");
            rewind(file);

            while  (fread(pt,sizeof(*pt),1,file)==1)
            {

                if (cod2 == pt->codl)
                {
                    printf("NOME: %s\n",pt->nomel);
                    gotoxy(34,10);
                    printf("AUTOR: %s\n",pt->nomea);
                    gotoxy(34,11);
                    printf("AREA: %s\n",pt->area);
                    gotoxy(34,12);
                    printf("CODIGO DO LIVRO: %d\n",pt->codl);
                    gotoxy(34,13);
                    printf("QUANTIDADE: %d\n",pt->quant);
                    gotoxy(34,15);
                    printf("DESEJA DELETAR O LIVRO: S-SIM, N-NAO:");
                    c=getch();
                    gotoxy(34,17);


                    if (c=='s'||c=='S')
                    {

                        rewind (file);

                        while (fread(pt,sizeof(*pt),1,file)==1)
                        {
                            if(cod2 != pt->codl)
                            {
                                fwrite (pt,sizeof(*pt),1, file2);
                                setbuf(stdin,NULL);
                            }
                        }
                        printf("LIVRO REMOVIDO");
                        fclose (file);
                        remove ("dadoslivro.dat");
                        fclose (file2);
                        rename ("livrosremo.dat","dadoslivro.dat");
                        gotoxy(34,19);
                    }
                }

            }

        }
    }
    fclose(file);
    system("Pause");
}

void listar (LIVRO *pt)
{
    int i=7,j=0;
    FILE *file;
    file=fopen("dadoslivro.dat","rb");
    system ("cls");

    while(fread(pt,sizeof(*pt),1,file)==1)
    {
        j++;
    }
    if (j<=0)
    {
        gotoxy (34,5);
        printf("NAO HA EXEMPLARES DISPONIVEIS");
    }
    else
    {
        rewind(file);
        gotoxy(34,3);
        printf ("LIVOS DISPONIVEIS\n");
        gotoxy(1,5);
        printf("NOME DO LIVRO");
        gotoxy(25,5);
        printf("AUTOR");
        gotoxy(45,5);
        printf("AREA");
        gotoxy(65,5);
        printf("CODIGO");
        gotoxy(75,5);
        printf("QUANTIDADE");

        while (fread(pt,sizeof(*pt),1,file)==1)
        {
            if(pt->quant>0)
            {


                gotoxy(1,i);
                printf("%s\t",pt->nomel);
                gotoxy(25,i);
                printf("%s\t",pt->nomea);
                gotoxy(45,i);
                printf("%s\t",pt->area);
                gotoxy(65,i);
                printf("%d\t",pt->codl);
                gotoxy(75,i);
                printf("%d",pt->quant);
                i++;
            }
        }
    }
    gotoxy(1,i+2);
    fclose (file);
}

void menudoaluno ()
{
    system("cls");
    linha();
    linhalateral();
    gotoxy(34,7);
    printf("MENU DO ALUNO");
    gotoxy(20,10);
    printf("1- CADASTRAR ALUNO");
    gotoxy(20,12);
    printf("2- REMOVER ALUNO");
    gotoxy(20,14);
    printf("3- EDITAR ALUNO");
    gotoxy(20,16);
    printf("4- LISTAR ALUNOS CADASTRADOS\n");
    gotoxy(20,18);
    printf("5- RETORNAR AO MENU PRINCIPAL\n");
    gotoxy(38,20);

}


void cadastraraluno(ALUNO *pt)
{
    FILE *file;
    file= fopen("dadosaluno.dat","ab+");


    system("cls");

    gotoxy(34,3);
    printf ("CADASTRO:\n");

    setbuf(stdin,NULL);

    fseek (file,ftell(file)-sizeof(*pt),SEEK_END);

    if (fread(pt,sizeof(*pt),1,file)!=1)
    {
        pt->matri =1000;
    }
    else
    {
        fscanf(file,"%d",pt->matri);
        pt->matri=pt->matri +1;
    }

    gotoxy (34,7);
    printf("DIGITE O NOME DO ALUNO:");
    gets(pt->nomeal);
    setbuf(stdin,NULL);

    gotoxy(34,9);
    printf("DIGITE O CPF:");
    gets(pt->cpf);
    setbuf(stdin,NULL);

    gotoxy(34,11);
    printf("MATRICULA DO ALUNO: %d",pt->matri);
    gotoxy(34,13);

    fseek(file,0,SEEK_END);
    fwrite (pt,sizeof (*pt),1,file);
    setbuf(stdin,NULL);

    fclose(file);
    system("Pause");
}

void removeraluno (ALUNO *pt,EMPRESTIMO *ptr)
{
    char c;
    FILE *file,*file2;
    int matri2,i=0,j=0;

    system("cls");
    setbuf(stdin,NULL);
    gotoxy(34,3);
    printf("REMOVER ALUNO");
    gotoxy(34,7);
    printf("DIGITE A MATRICULA DO ALUNO:");
    scanf("%d",&matri2);
    gotoxy(34,9);

    file = fopen ("dadosemprestimo.dat","rb");

    while (fread(ptr,sizeof(*ptr),1,file)==1)
    {
        if (ptr->matrie==matri2)
        {
            i++;
        }
    }
    fclose(file);
    if(i>0)
    {
        system("cls");
        gotoxy(34,5);
        printf("ALUNO COM EMPRESTIMO PENDENTE NAO PODE SER REMOVIDO");
        gotoxy(34,7);
    }

    else
    {


        file = fopen ("dadosaluno.dat","rb+");
        while (fread(pt,sizeof(*pt),1,file)==1)
        {
            if (pt->matri == matri2)
            {
                j++;
            }
        }
        if (j==0)
        {
            system("cls");
            gotoxy(34,5);
            printf("ALUNO NAO CADASTRADO");
            gotoxy(34,7);
        }

        else
        {
            rewind(file);
            file2= fopen ("alunoremo.dat","wb+");
            rewind(file);

            while  (fread(pt,sizeof(*pt),1,file)==1)
            {

                if (matri2==pt->matri)
                {
                    printf("NOME: %s",pt->nomeal);
                    gotoxy(34,10);
                    printf("CPF: %s",pt->cpf);
                    gotoxy(34,11);
                    printf("MATRICULA: %d\n",pt->matri);
                    gotoxy(34,13);
                    printf("DESEJA DELETAR O ALUNO: S-SIM, N-NAO:");
                    c=getch();
                    gotoxy(34,15);

                    if (c=='s'||c=='S')
                    {

                        rewind (file);

                        while (fread(pt,sizeof(*pt),1,file)==1)
                        {
                            if(matri2 != pt->matri)
                            {
                                fwrite (pt,sizeof(*pt),1, file2);
                                setbuf(stdin,NULL);
                            }
                        }
                        printf("ALUNO REMOVIDO");
                        gotoxy(34,17);
                        fclose (file);
                        remove ("dadosaluno.dat");
                        fclose (file2);
                        rename ("alunoremo.dat","dadosaluno.dat");
                    }
                }
            }
        }

    }
    fclose(file);
    system("Pause");
}

void editaraluno (ALUNO *pt, EMPRESTIMO *ptr)
{
    char c,i=0,j=0;
    FILE *file;
    int matri2;
    system ("cls");

    setbuf(stdin,NULL);
    gotoxy(34,3);
    printf("EDITAR ALUNO");
    gotoxy(34,7);
    printf("DIGITE A MATRICULA DO ALUNO: ");
    scanf("%d",&matri2);
    gotoxy(34,9);

    file = fopen ("dadosemprestimo.dat","rb");
    while (fread(ptr,sizeof(*ptr),1,file)==1)
    {
        if (matri2==ptr->matrie)
        {
            i++;
        }
    }
    fclose (file);
    if(i>0)
    {
        system("cls");
        gotoxy(34,5);
        printf("ALUNO COM EMPRETIMO PENDENTE NAO PODE SER EDITADO");
        gotoxy(34,7);
    }
    else
    {


        file = fopen ("dadosaluno.dat","r+b");

        while (fread(pt,sizeof(*pt),1,file)==1)
        {
            if (pt->matri == matri2)
            {

                j++;
            }
        }
        if (j==0)
        {
            system ("cls");
            gotoxy(34,5);
            printf("ALUNO NAO CADASTRADO");
            gotoxy (34,7);
        }

        else
        {

            rewind(file);

            while (fread(pt,sizeof(*pt),1,file)==1)
            {
                if (matri2 ==pt->matri)
                {
                    printf("NOME: %s",pt->nomeal);
                    gotoxy(34,10);
                    printf("MATRICULA: %d",pt->matri);
                    gotoxy(34,11);
                    printf("CPF: %s\n",pt->cpf);
                    gotoxy(34,13);
                    printf("DESEJA FAZER ALTERACAO: S-SIM, N-NAO:");
                    c=getch();

                    if (c=='S'|| c=='s')
                    {
                        system("cls");
                        setbuf(stdin,NULL);
                        gotoxy(34,5);
                        printf("NOVO NOME:");
                        gets(pt->nomeal);
                        setbuf(stdin,NULL);
                        gotoxy(34,6);
                        printf("CPF:");
                        gets(pt->cpf);
                        setbuf(stdin,NULL);

                        fseek(file,ftell(file)-sizeof(*pt),0);
                        fwrite (pt,sizeof(*pt),1,file);
                        gotoxy(34,8);

                        printf("INFORMACOES MODIFICADAS COM SUCESSO");
                        gotoxy(34,10);

                    }
                }

            }
        }

    }
    fclose(file);

    system("pause");

}

void listaraluno (ALUNO *pt)
{
    FILE *file;
    int i=6,j=0;
    file=fopen("dadosaluno.dat","rb");
    system ("cls");

    while (fread(pt,sizeof(*pt),1,file)==1)
    {
        j++;
    }

    if (j==0)
    {
        gotoxy(34,5);
        printf("NAO HA ALUNOS CADASTRADOS");
        gotoxy(34,6);
    }
    else
    {
        rewind (file);
        gotoxy(34,2);
        printf ("ALUNOS CADASTRADOS\n");
        gotoxy (1,4);
        printf("NOME");
        gotoxy (35,4);
        printf("MATRICULA");
        gotoxy (65,4);
        printf("CPF");

        while (fread(pt,sizeof(*pt),1,file)==1)
        {
            gotoxy(1,i);
            printf("%s\t",pt->nomeal);
            gotoxy(35,i);
            printf("%d\t",pt->matri);
            gotoxy(65,i);
            printf("%s\t\n",pt->cpf);
            i++;
        }
        gotoxy(1,i+2);
    }

    fclose (file);
    system("Pause");
}

void menuemprestimo()
{
    system ("cls");
    linha();
    linhalateral();
    gotoxy(32,7);
    printf("MENU DE EMPRESTIMO");
    gotoxy(20,11);
    printf("1- NOVO EMPRESTIMO");
    gotoxy(20,13);
    printf("2- DEVOLUCAO");
    gotoxy(20,15);
    printf("3- LISTAR EMPRESTIMO");
    gotoxy(20,17);
    printf("4- RETORNAR AO MENU PRINCIPAL");
    gotoxy(38,19);
}
/* Trecho de código feito por Paulo Marcos Trentin com adaptação
    Disponível em <https://www.vivaolinux.com.br/script/Funcao-em-C-retorna-a-data-do-sistema-ja-formatada>
    Contato: paulo@paulotrentin.com.br
             http://www.paulotrentin.com.br */

char *format(int number)
{
    char *retorno, ret[30];
    int i;

    if (number < 10)
    {
        sprintf(ret,"0%d",number);
        retorno = ret;
        return retorno;
    }
    else
    {
        sprintf(ret,"%d",number);
        retorno = ret;
        return retorno;
    }
}

char *data(void)
{

    int dia,mes,ano;
    char var1[6], var2[6], var3[6], var4[15], *dataPtr;

    struct tm *local;

    time_t t;

    t = time(NULL);
    local = localtime(&t);
    dia = local -> tm_mday;
    mes = local -> tm_mon + 1;
    ano = local -> tm_year + 1900;

    sprintf(var1,"%s",format(dia));
    sprintf(var2,"%s",format(mes));
    sprintf(var3,"%s",format(ano));


    sprintf(var4,"%s/%s/%s",var1,var2,var3);

    dataPtr = var4;
    return dataPtr;
} /* FIM DO TRECHO COPIADO. AUTOR: PAULO MARCOS TRENTIN */

char *data_dev(void)  //Trecho implementado baseado na função anterior : char *data(void)
{

    int dia,mes,ano;
    char var1[6], var2[6], var3[6], var4[15], *dataPtr;

    struct tm *local;

    time_t t;

    t = time(NULL);
    local = localtime(&t);

    dia = local -> tm_mday;
    mes = local -> tm_mon + 1;
    ano = local -> tm_year + 1900;

    dia = dia + 10;

    if(mes == 2)
    {
        if(ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0))    //Teste de Ano Bissexto
        {
            if(dia>29)
            {

                dia = dia - 29;
                mes++;
            }
        }
        else
        {
            if(dia>28)
            {
                dia = dia - 28;
                mes++;
            }
        }
    }
    else if((mes==1 || mes==3 || mes==5 || mes==7 || mes==8 || mes==10 || mes==12) && dia > 31)
    {
        dia = dia - 31;
        mes++;
    }
    else if(dia > 30)
    {
        dia = dia - 30;
        mes++;
    }

    if (mes > 12)
    {
        mes = mes - 12;
        ano++;
    }

    sprintf(var1,"%s",format(dia));
    sprintf(var2,"%s",format(mes));
    sprintf(var3,"%s",format(ano));

    sprintf(var4,"%s/%s/%s",var1,var2,var3);

    dataPtr = var4;
    return dataPtr;
}

void emprestimo (EMPRESTIMO *pt,LIVRO *pp,ALUNO *ptr){
FILE *file;
int cod,codl,i=0,q;
char c;

system("cls");

gotoxy(34,3);
printf("EMPRESTIMO");
gotoxy(34,7);

printf("DIGITE A MATRICULA DO ALUNO: ");
setbuf(stdin,NULL);
scanf("%d",&cod);
gotoxy(34,9);

file = fopen ("dadosaluno.dat","rb+");

while (fread(ptr,sizeof(*ptr),1,file)==1)
{
   if (cod == ptr->matri)
   {
     i++;
     printf("NOME DO ALUNO: %s",ptr->nomeal);
     gotoxy(34,10);
     printf("CPF: %s",ptr->cpf);
     gotoxy(34,12);
     system("pause");
   }
}

fclose(file);

if(i==0)
{  system("cls");
   gotoxy(34,5);
   printf("ALUNO NAO CADASTRADO");
   gotoxy(34,7);
}
else
{
       i=0;
       file = fopen ("dadosemprestimo.dat","ab+");

       while (fread(pt,sizeof(*pt),1,file)==1)
       {
         if(cod == pt->matrie)
         {
           i++;
         }
       }
       fclose(file);

       if(i==2){

         system("cls");
         gotoxy(34,5);
         printf("ALUNO EXCEDEU A QUANTIDADE DE EMPRESTIMOS");
         gotoxy(34,7);

       }
       else{
            i=0;
            system("cls");
            gotoxy(34,7);
            printf("DIGITE O CODIGO DO LIVRO: ");
            setbuf(stdin,NULL);
            scanf("%d",&codl);
            gotoxy (34,9);

            file = fopen ("dadoslivro.dat","rb+");

            while (fread(pp,sizeof(*pp),1,file)==1)
            {
                   if(codl == pp->codl)
                   {
                     i++;
                     printf("NOME DO LIVRO: %s",pp->nomel);
                     gotoxy(34,10);
                     printf("NOME DO AUTOR: %s",pp->nomea);
                     gotoxy(34,11);
                     printf("AREA DO CONHECIMENTO: %s",pp->area);
                     gotoxy(34,13);
                     q = pp->quant;
                    }
             }
             fclose (file);

             if (i==0)
             {
               system ("cls");
               gotoxy(34,5);
               printf("LIVRO NAO CADASTRADO");
               gotoxy(34,7);
             }
             else
             {
               i=0;

               if(q==0)
               {
                 system ("cls");
                 gotoxy(34,5);
                 printf("NAO HA EXEMPLARES DISPONIVEL");
                 gotoxy(34,7);
               }
               else{

                  file = fopen ("dadosemprestimo.dat","rb");

                  while (fread(pt,sizeof(*pt),1,file)==1)
                  {
                     if(cod == pt->matrie && codl == pt->codle)
                     {
                       i++;
                     }
                  }
                   fclose(file);

                   if(i==1){

                     system ("cls");
                     gotoxy(34,5);
                     printf("ALUNO JA POSSUI ESTE EXEMPLAR");
                     gotoxy(34,7);
                   }
                   else
                   {

                     printf("DESEJA REALIZA EMPRESTIMO: S-SIM, N-NAO ");
                     c =getch();
                     gotoxy(34,15);

                     if(c == 'S' || c == 's')
                     {
                        file = fopen ("dadoslivro.dat","rb+");
                        while (fread(pp,sizeof(*pp),1,file)==1)
                        {
                          if(codl == pp->codl)
                          {
                            pp->quant = pp->quant-1;
                            strcpy(pt->nomel,pp->nomel);
                            fseek(file,ftell(file)-sizeof(*pp),0);
                            fwrite (pp,sizeof(*pp),1,file);
                            fseek(file,0,SEEK_END);

                          }
                        }
                        fclose(file);

                        file = fopen ("dadosemprestimo.dat","ab+");
                         pt->matrie = cod;
                         pt->codle = codl;
                        sprintf(pt->data_sistema,"%s",data());
                        sprintf(pt->data_dev,"%s",data_dev());
                        fwrite(pt,sizeof(*pt),1,file);
                        fclose(file);
                        printf("EMPRESTIMO REALIZADO EM %s",pt->data_sistema);
                        gotoxy(34,16);
                        printf("DATA DE DEVOLUCAO: %s",pt->data_dev);
                        gotoxy(34,18);
                    }

                   }


               }
             }



       }



   }
   system("pause");
}


void devolucao (EMPRESTIMO *pt, LIVRO *ptr)
{
  FILE *file, *file2;
  int cod,codl,i=0;
  char c;


  system("cls");
  gotoxy (34,3);
  printf("DEVOLUCAO");
  gotoxy(34,7);
  printf("DIGITE MATRICULA DO ALUNO: ");
  setbuf(stdin,NULL);
  scanf("%d",&cod);

  gotoxy(34,8);
  printf("DIGITE CODIGO DO LIVRO: ");
  setbuf (stdin,NULL);
  scanf("%d",&codl);
  gotoxy(34,10);

  file = fopen ("dadosemprestimo.dat","rb+");

  while (fread(pt,sizeof(*pt),1,file)==1)
  {
    if (cod ==  pt->matrie && codl == pt->codle)
    {
      i++;

          printf("CODIGO DO LIVRO: %d",pt->codle);
          gotoxy(34,11);
          printf("NOME DO LIVRO: %s",pt->nomel);
          gotoxy(34,13);
          printf("MATRICULA: %d",pt->matrie);
          gotoxy(34,15);
    }
  }

  fclose(file);

  if(i==0)
  {
    system("cls");
    gotoxy(34,5);
    printf("SEM INFORMACAO DE EMPRESTIMO");
    gotoxy(34,7);
  }
  else{

     printf("DESEJA FAZER A DEVOLUCAO: S-SIM, N-NAO: ");
     c=getch();
     gotoxy(34,17);

     if (c== 's' || c== 'S')
     {

     file = fopen ("dadosemprestimo.dat","rb+");
     file2 = fopen ("remov.dat","w+b");

     while (fread(pt,sizeof(*pt),1,file)==1)
     {
       if(cod != pt->matrie || codl != pt->codle)
       {

         fwrite (pt,sizeof(*pt),1, file2);
         setbuf(stdin,NULL);

       }
     }

                    printf("DEVOLUCAO REALIZADA");
                    gotoxy(34,19);
                    fclose (file);
                    remove ("dadosemprestimo.dat");
                    fclose (file2);
                    rename ("remov.dat","dadosemprestimo.dat");

                  file =  fopen ("dadoslivro.dat","r+b");

                    while(fread(ptr,sizeof(*ptr),1,file)==1)
                    {
                        if (codl == ptr->codl)
                        {

                            ptr->quant= ptr->quant+1;
                            fseek(file,ftell(file)-sizeof(*ptr),0);
                            fwrite (ptr,sizeof(*ptr),1,file);
                            fseek(file,0,SEEK_END);
                        }
                    }
                    fclose (file);


     }

  }

  system("pause");

}
void listaremprestimo (EMPRESTIMO *pt)
{
    int i=6, j=0;
    FILE *file;
    file=fopen("dadosemprestimo.dat","rb");
    system ("cls");

    while (fread(pt,sizeof(*pt),1,file)==1)
    {
        j++;
    }
    if(j==0)
    {
        system ("cls");
        gotoxy(34,5);
        printf("NAO HA EMPRESTIMOS CADASTRADO");
        gotoxy(34,7);
    }
    else
    {
        rewind(file);
        gotoxy(34,2);
        printf ("LIVOS EMPRESTADOS");

        gotoxy(1,4);
        printf("COD. LIVRO");
        gotoxy(17,4);
        printf("NOME DO LIVRO");
        gotoxy(43,4);
        printf("MATRICULA");
        gotoxy(57,4);
        printf("DATA DO EMPRESTIMO");
        gotoxy(77,4);
        printf("DATA DE DEVOLUCAO");

        while (fread(pt,sizeof(*pt),1,file)==1)
        {

            gotoxy(1,i);
            printf("%d",pt->codle);
            gotoxy(17,i);
            printf("%s",pt->nomel);
            gotoxy(43,i);
            printf("%d",pt->matrie);
            gotoxy(57,i);
            printf("%s",pt->data_sistema);
            gotoxy(77,i);
            printf("%s",pt->data_dev);

            i++;
        }
        gotoxy(1,i+1);
        fclose (file);
    }
    system ("pause");
}

void listarcod(EMPRESTIMO *pt)
{
    int cod,j=0,i=5;
    FILE *file;
    system("cls");
    file = fopen ("dadosemprestimo.dat","rb+");
    while (fread(pt,sizeof(*pt),1,file)==1)
    {
        j++;
    }
    if(j==0)
    {
        system ("cls");
        gotoxy(34,5);
        printf("NAO HA EMPRESTIMOS CADASTRADO");
        gotoxy(34,7);
    }
    else
    {
        j=0;
        rewind(file);
        gotoxy(34,7);
        printf("DIGITE O CODIGO DO LIVRO: ");
        setbuf(stdin,NULL);
        scanf("%d",&cod);
        system("cls");
        while (fread(pt,sizeof(*pt),1,file)==1)
        {
            if(cod == pt->codle)
            {

                gotoxy(34,i);
                printf("CODIGO DO LIVRO: %d",pt->codle);
                gotoxy(34,i+1);
                printf("NOME DO LIVRO: %s",pt->nomel);
                gotoxy(34,i+2);
                printf("MATRICULA: %d",pt->matrie);
                gotoxy(34,i+3);
                printf("DATA DO EMPRESTIMO: %s",pt->data_sistema);
                gotoxy(34,i+4);
                printf("DATA DE DEVOLUCAO: %s",pt->data_dev);
                gotoxy(34,i+5);
                printf ("---------------------------------------");
                i=i+7;
                gotoxy(34,i+2);
                j++;
            }
        }

        if (j==0)
        {
            system("cls");
            gotoxy(34,5);
            printf("NAO FOI POSSIVEL ENCONTRAR O LIVRO");
            gotoxy(34,7);

        }
    }
    system("Pause");
    fclose(file);
}

void listaralu (EMPRESTIMO *pt)
{
    int matri,j=0,i=5;
    FILE *file;
    system("cls");
    file = fopen ("dadosemprestimo.dat","rb+");

    while (fread(pt,sizeof(*pt),1,file)==1)
    {
        j++;
    }
    if(j==0)
    {
        system ("cls");
        gotoxy(34,5);
        printf("NAO HA EMPRESTIMOS CADASTRADO");
        gotoxy(34,7);
    }
    else
    {
        j=0;
        rewind(file);
        gotoxy(34,7);
        printf("DIGITE O CODIGO DO ALUNO: ");
        setbuf(stdin,NULL);
        scanf("%d",&matri);
        system("cls");

        while (fread(pt,sizeof(*pt),1,file)==1)
        {
            if(matri== pt->matrie)
            {
                gotoxy(34,i);
                printf("CODIGO DO LIVRO: %d\n",pt->codle);
                gotoxy(34,i+1);
                printf("NOME DO LIVRO: %s",pt->nomel);
                gotoxy(34,i+2);
                printf("MATRICULA: %d\n",pt->matrie);
                gotoxy(34,i+3);
                printf("DATA DO EMPRESTIMO: %s\n",pt->data_sistema);
                gotoxy(34,i+4);
                printf("DATA DE DEVOLUCAO: %s\n",pt->data_dev);
                gotoxy(34,i+5);
                printf ("---------------------------------------");
                i=i+7;
                gotoxy(34,i+2);
                j++;
            }
        }


        if (j==0)
        {
            system("cls");
            gotoxy(34,5);
            printf("NAO FOI POSSIVEL ENCONTRAR O ALUNO");
            gotoxy(34,7);

        }
    }
    system("Pause");
    fclose(file);
}

main ()
{

    char c,d;
    LIVRO liv;
    ALUNO a;
    EMPRESTIMO b;

    do
    {
        menuprincipal();
        d=getch();

        switch (d)
        {
        case '1':
            do
            {
                menulivro();
                c=getch();

                switch (c)
                {
                case '1':
                    cadastrarl(&liv);
                    break;

                case '2':
                    editarlivro(&liv,&b);
                    break;

                case '3':
                    removerlivro (&liv,&b);
                    break;

                case '4':
                    listar(&liv);
                    system("Pause");
                    break;
                }
            }
            while (c!='5');
            break;

        case '2':
            do
            {
                menudoaluno();
                c=getch();

                switch (c)
                {
                case '1':
                    cadastraraluno(&a);
                    break;

                case '2':
                    removeraluno(&a,&b);
                    break;

                case '3':
                    editaraluno(&a,&b);
                    break;

                case '4':
                    listaraluno(&a);
                    break;
                }
            }
            while (c!='5');
            break;

        case '3':
            do
            {
                menuemprestimo();
                c=getch();

                switch (c)
                {

                case '1':
                    emprestimo(&b,&liv,&a);
                    break;
                case '2':
                    devolucao(&b,&liv);
                    break;

                case '3':
                    do
                    {
                        system ("cls");
                        linha();
                        linhalateral();
                        gotoxy (34,7);
                        printf("MENU LISTAGEM");
                        gotoxy (20,10);
                        printf("1- LISTAR TODOS OS EMPRESTIMOS");
                        gotoxy (20,12);
                        printf("2- LISTAR POR LIVRO");
                        gotoxy (20,14);
                        printf("3- LISTAR POR ALUNO");
                        gotoxy (20,16);
                        printf("4- RETORNAR AO MENU PRINCIPAL");
                        c=getch ();
                        switch (c)
                        {
                        case '1':
                            listaremprestimo(&b);
                            break;
                        case '2':
                            listarcod(&b);
                            break;
                        case '3':
                            listaralu (&b);
                            break;
                        case '4':
                            system("cls");
                            break;
                        }

                    }
                    while (c!='4');
                    break;
                case '4':
                    break;


                }


            }
            while (c!='4');
            break;

        case '4':
            system ("cls");
            gotoxy(10,10);
            printf("\t\tPROGRAMA ENCERRADO");
            gotoxy(17,17);
            break;
        }

    }
    while (d!='4');
}

#include<stdio.h>
#include<stdlib.h>
#include<conio.c>
#include<string.h>

typedef struct
{
    int codle,matrie;
    int data;
} EMPRESTIMO;

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
    gotoxy(20,11);
    printf("2- MENU DO ALUNO");
    gotoxy(20,12);
    printf("3- EMPRESTIMOS");
    gotoxy(20,13);
    printf("4- SAIR");
    gotoxy(32,10);


}

void menulivro ()
{

    system("cls");
    linha();
    linhalateral();
    gotoxy(34,7);
    printf("MENU DO ACERVO\n");
    gotoxy(20,10);
    printf("1- CADASTRAR LIVRO: \n");
    gotoxy(20,11);
    printf("2- EDITAR LIVRO: \n");
    gotoxy(20,12);
    printf("3- REMOVER: \n");
    gotoxy(20,13);
    printf("4- LISTAR LIVROS CADASTRADOS: \n");
    gotoxy(20,14);
    printf("5- RETORNAR AO MENU PRINCIPAL: \n");
    gotoxy(38,15);

}

void cadastrarl (LIVRO *pt)
{
    FILE *file;
    file= fopen("dadoslivro.dat","ab+");


    system("cls");
    int i;
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

    printf("DIGITE O NOME DO LIVRO:");
    setbuf(stdin,NULL);
    gets(pt->nomel);

    printf("DIGITE O NOME DO AUTOR:");
    setbuf(stdin,NULL);
    gets(pt->nomea);

    printf("DIGITE A AREA DO CONHECIMENTO: ");
    setbuf(stdin,NULL);
    gets(pt->area);

    printf("QUANTIDADE DE EXEMPLARES:");
    setbuf(stdin,NULL);
    scanf("%d",&pt->quant);


    fseek(file,0,SEEK_END);
    fwrite (pt,sizeof(LIVRO),1,file);
    setbuf(stdin,NULL);
    fclose(file);
}

void listar (LIVRO *pt)
{
    int i=6;
    FILE *file;
    file=fopen("dadoslivro.dat","rb");
    system ("cls");

    printf ("LIVOS CADASTRADOS\n");
    gotoxy(1,4);
    printf("NOME DO LIVRO");
    gotoxy(25,4);
    printf("AUTOR");
    gotoxy(45,4);
    printf("AREA");
    gotoxy(65,4);
    printf("CODIGO");
    gotoxy(75,4);
    printf("QUANTIDADE");

    while (fread(pt,sizeof(*pt),1,file)==1)
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
    gotoxy(1,i);
    fclose (file);
}

void listaraluno (ALUNO *pt)
{
    FILE *file;
    int i=6;
    file=fopen("dadosaluno.dat","rb");
    system ("cls");

    printf ("ALUNOS CADASTRADOS\n");
    gotoxy (1,4);
    printf("NOME");
    gotoxy (25,4);
    printf("MATRICULA");
    gotoxy (45,4);
    printf("CPF");

    while (fread(pt,sizeof(*pt),1,file)==1)
    {
        gotoxy(1,i);
        printf("%s\t",pt->nomeal);
        gotoxy(25,i);
        printf("%d\t",pt->matri);
        gotoxy(45,i);
        printf("%s\t\n",pt->cpf);
        i++;
    }
    fclose (file);
    system("Pause");
}

void menudoaluno ()
{
    system("cls");
    linha();
    linhalateral();
    gotoxy(34,7);
    printf("MENU DO ALUNO");
    gotoxy(20,10);
    printf("1- CADASTRAR ALUNO:");
    gotoxy(20,11);
    printf("2- REMOVER ALUNO:");
    gotoxy(20,12);
    printf("3- EDITAR ALUNO:");
    gotoxy(20,13);
    printf("4- LISTAR ALUNOS CADASTRADOS:\n");
    gotoxy(20,14);
    printf("5- RETORNAR AO MENU PRINCIPAL:\n");
    gotoxy(38,15);

}

void cadastraraluno(ALUNO *pt)
{
    FILE *file;
    file= fopen("dadosaluno.dat","ab+");


    system("cls");

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

    printf("DIGITE O NOME DO ALUNO:");
    gets(pt->nomeal);
    setbuf(stdin,NULL);

    printf("DIGITE O CPF:");
    gets(pt->cpf);
    setbuf(stdin,NULL);

    fseek(file,0,SEEK_END);
    fwrite (pt,sizeof (*pt),1,file);
    setbuf(stdin,NULL);

    fclose(file);
}

void removerlivro (LIVRO *pt)
{
    char c;
    FILE *file,*file2;
    int cod2;

    system("cls");
    setbuf(stdin,NULL);
    printf("DIGITE O CODIGO DO LIVRO:");
    scanf("%d",&cod2);

    file = fopen ("dadoslivro.dat","rb+");
    file2= fopen ("livrosremo.dat","wb+");
    rewind(file);

    while  (fread(pt,sizeof(*pt),1,file)==1)
    {

        if (cod2 == pt->codl)
        {
            printf("NOME: %s\n",pt->nomel);
            printf("AUTOR: %s\n",pt->nomea);
            printf("AREA: %s\n",pt->area);
            printf("CODIGO DO LIVRO: %d\n",pt->codl);
            printf("QUANTIDADE: %d\n",pt->quant);
            printf("DESEJA DELETAR O LIVRO: S-SIM, N-NAO:");
            c=getch();

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
                printf("\n\nLIVRO REMOVIDO\n");
                fclose (file);
                remove ("dadoslivro.dat");
                fclose (file2);
                rename ("livrosremo.dat","dadoslivro.dat");
            }

        }

    }

    system("Pause");
}

void removeraluno (ALUNO *pt)
{
    char c;
    FILE *file,*file2;
    int matri2;

    system("cls");
    setbuf(stdin,NULL);
    printf("DIGITE A MATRICULA DO ALUNO:");
    scanf("%d",&matri2);

    file = fopen ("dadosaluno.dat","rb+");
    file2= fopen ("alunoremo.dat","wb+");
    rewind(file);

    while  (fread(pt,sizeof(*pt),1,file)==1)
    {

        if (matri2==pt->matri)
        {
            printf("NOME: %s\n",pt->nomeal);
            printf("CPF: %s\n",pt->cpf);
            printf("MATRICULA: %d\n",pt->matri);
            printf("DESEJA DELETAR O ALUNO: S-SIM, N-NAO:");
            c=getch();

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
                printf("\n\nALUNO REMOVIDO\n");
                fclose (file);
                remove ("dadosaluno.dat");
                fclose (file2);
                rename ("alunoremo.dat","dadosaluno.dat");
            }
            system("Pause");
        }
    }
}

void editarlivro (LIVRO *pt)
{
    char c;
    FILE *file;
    int cod2;
    system ("cls");

    setbuf(stdin,NULL);
    printf("DIGITE O CODIGO DO LIVRO: ");
    scanf("%d",&cod2);

    file = fopen ("dadoslivro.dat","r+b");

    while (fread(pt,sizeof(*pt),1,file)==1)
    {
        if (cod2==pt->codl)
        {
            printf("NOME: %s\n",pt->nomel);
            printf("AUTOR: %s\n",pt->nomea);
            printf("AREA: %s\n",pt->area);
            printf("CODIGO DO LIVRO: %d\n",pt->codl);
            printf("QUANTIDADE: %d\n",pt->quant);
            printf("DESEJA FAZER ALTERACAO: S-SIM, N-NAO:");
            c=getch();

            if (c=='S'|| c=='s')
            {
                setbuf(stdin,NULL);
                printf("\n\nNOVO NOME:");
                gets(pt->nomel);
                setbuf(stdin,NULL);

                printf("NOME DO AUTOR:");
                gets(pt->nomea);
                setbuf(stdin,NULL);

                printf("AREA:");
                gets(pt->area);
                setbuf(stdin,NULL);

                printf("QUANTIDADE:");
                scanf("%d",&pt->quant);

                fseek(file,ftell(file)-sizeof(*pt),0);
                fwrite (pt,sizeof(*pt),1,file);
                fclose(file);

                printf("INFORMCOES MODIFICADAS COM SUECESSO\n\n");
                system("Pause");
            }
        }
    }

}

void editaraluno (ALUNO *pt)
{
    char c;
    FILE *file;
    int matri2;
    system ("cls");

    setbuf(stdin,NULL);
    printf("DIGITE A MATRICULA DO ALUNO");
    scanf("%d",&matri2);

    file = fopen ("dadosaluno.dat","r+b");

    while (fread(pt,sizeof(*pt),1,file)==1)
    {
        if (matri2 ==pt->matri)
        {
            printf("NOME: %s\n",pt->nomeal);
            printf("MATRICULA: %d\n",pt->matri);
            printf("CPF: %s\n",pt->cpf);
            printf("DESEJA FAZER ALTERACAO: S-SIM, N-NAO:");
            c=getch();

            if (c=='S'|| c=='s')
            {

                setbuf(stdin,NULL);
                printf("NOME:");
                gets(pt->nomeal);
                setbuf(stdin,NULL);

                printf("CPF:");
                gets(pt->cpf);
                setbuf(stdin,NULL);

                fseek(file,ftell(file)-sizeof(*pt),0);
                fwrite (pt,sizeof(*pt),1,file);
                fclose(file);

                printf("INFORMCOES MODIFICADAS COM SUECESSO");

            }
        }
    }

}

void menuemprestimo()
{
    system ("cls");
    linha();
    linhalateral();
    gotoxy(32,7);
    printf("MENU DE EMPRESTIMO.");
    gotoxy(20,11);
    printf("1-NOVO EMPRESTIMO.");
    gotoxy(20,12);
    printf("2-DEVOLUCAO.");
    gotoxy(20,13);
    printf("3-LISTAR EMPRESTIMO.");
    gotoxy(20,14);
    printf("4-RETORNAR AO MENU PRINCIPAL.");
    gotoxy(38,16);
}

void emprestimo(EMPRESTIMO *pt,LIVRO *ptr, ALUNO *pp)
{
    FILE *file,*file2;
    int i=0;
    int g=0;
    char c;
    int e;

    system("cls");

    printf("DIGITE O CODIGO DO ALUNO:");
    setbuf(stdin,NULL);
    scanf("%d",&e);

    file = fopen ("dadosaluno.dat","rb");

    while (fread(pp,sizeof(*pp),1,file)==1)
    {
        if(e == pp->matri)
        {
            i++;
        }
    }
    fclose (file);

    if (i==0)
    {
        printf("ALUNO NÂO MATRICULADO");
    }
    else
    {
        i=0;
        file = fopen ("dadosemprestimo.dat","ab+");
        while (fread (pt,sizeof(*pt),1,file)==1)
        {
            if (pt->matrie == e)
            {
                i++;
            }
        }

        fclose (file);

        if (i==2)
        {

            printf("QUANTIDADE DE EMPRESTIMOS EXCEDIDA");
        }
        else
        {
            i=0;
            printf("DIGITE O CODIGO DO LIVRO:\n");
            setbuf(stdin,NULL);
            scanf("%d",&pt->codle);

            file = fopen ("dadoslivro.dat","r+b");

            while(fread(ptr,sizeof(*ptr),1,file)==1)
            {
                if (pt->codle == ptr->codl)
                {
                    i++;
                    g= ptr->quant;
                }
            }

            if (i==0)
            {
                printf("LIVRO NAO CADASTRADO\n");
            }

            else
            {
                if (g<=0)
                {
                    printf("NAO TEM EXEMPLARES DISPONIVEIS\n");
                }
                else
                {
                    //pegardata();

                    printf("DESEJA FAZER O EMPRESTIMO: S-SIM,N-NAO\n");
                    c=getch();

                    if (c=='s'|| c=='S')
                    {

                        rewind(file);
                        while(fread(ptr,sizeof(*ptr),1,file)==1)
                        {
                            if (pt->codle == ptr->codl)
                            {

                                ptr->quant= ptr->quant-1;
                                fseek(file,ftell(file)-sizeof(*ptr),0);
                                fwrite (ptr,sizeof(*ptr),1,file);
                                fseek(file,0,SEEK_END);


                            }
                        }

                        file2 = fopen ("dadosemprestimo.dat","ab+");
                        pt->matrie=e;
                        fwrite(pt,sizeof(*pt),1,file2);
                        fclose(file2);

                    }

                }

            }
            fclose(file);
        }

    }
    system("Pause");
}

void devolucao (EMPRESTIMO *pt,LIVRO *ptr)
{
    FILE *file,*file2;
    int cod,i=0,matri;
    char c;
    system("cls");
    file = fopen("dadosemprestimo.dat","rb+");
    file2 = fopen ("removeremprestimo.dat","wb+");

    printf("DIGITE O CODIGO DO ALUNO");
    setbuf(stdin,NULL);
    scanf("%d",&matri);

    printf("DIGITE O CODIGO DO LIVRO");
    setbuf(stdin,NULL);
    scanf("%d",&cod);

    while (fread(pt,sizeof(*pt),1,file)==1)
    {
        if(matri == pt->matrie && cod == pt->codle)
        {
            i++;
        }
    }
    if (i<=0)
    {
        printf("SEM INFORMACAO DE EMPRESTIMO");
    }
    else
    {
        rewind (file);
        while (fread(pt,sizeof(*pt),1,file)==1)
        {
            if (matri == pt->matrie && cod == pt->codle )
            {
                printf("CODIGO DO LIVRO: %d\n",pt->codle);
                printf("MATRICULA: %d\n",pt->matrie);
                printf("DESEJA FAZER A DEVOLUCAO: S-SIM, N-NAO:");
                c=getch();

                if (c=='s'||c=='S')
                {

                    rewind (file);
                    while (fread(pt,sizeof(*pt),1,file)==1)
                    {
                        if(matri != pt->matrie || cod != pt->codle)
                        {
                            fwrite (pt,sizeof(*pt),1, file2);
                            setbuf(stdin,NULL);
                        }
                    }
                    printf("\n\nDEVOLUCAO REALIZADO\n");
                    fclose (file);
                    remove ("dadosemprestimo.dat");
                    fclose (file2);
                    rename ("removeremprestimo.dat","dadosemprestimo.dat");

                    FILE *file3 = fopen ("dadoslivro.dat","r+b");
                    rewind(file3);
                    while(fread(ptr,sizeof(*ptr),1,file3)==1)
                    {
                        if (cod == ptr->codl)
                        {

                            ptr->quant= ptr->quant+1;
                            fseek(file3,ftell(file3)-sizeof(*ptr),0);
                            fwrite (ptr,sizeof(*ptr),1,file3);
                            fseek(file,0,SEEK_END);
                        }
                    }
                    fclose (file3);
                }



            }
        }
    }
    system("Pause");
}



void listaremprestimo (EMPRESTIMO *pt)
{
    int i=6;
    FILE *file;
    file=fopen("dadosemprestimo.dat","rb");
    system ("cls");

    printf ("LIVOS CADASTRADOS\n");

    gotoxy(1,4);
    printf("CODIGO DO LIVRO");
    gotoxy(25,4);
    printf("MATRICULA");

    while (fread(pt,sizeof(*pt),1,file)==1)
    {

        gotoxy(1,i);
        printf("%d\t",pt->codle);
        gotoxy(25,i);
        printf("%d\t",pt->matrie);
        i++;
    }
    gotoxy(1,i);
    system("Pause");
    fclose (file);
}

void listarcod(EMPRESTIMO *pt)
{
    int cod;
    FILE *file;
    system("cls");
    file = fopen ("dadosemprestimo.dat","rb+");
    printf("DIGITE O CODIGO DO LIVRO");
    setbuf(stdin,NULL);
    scanf("%d",&cod);
    while (fread(pt,sizeof(*pt),1,file)==1)
    {
        if(cod== pt->codle)
        {
            printf("CODIGO DO LIVRO: %d\n",pt->codle);
            printf("MATRICULA: %d\n",pt->matrie);
        }
    }
    fclose(file);
    system("Pause");
}

void listaralu (EMPRESTIMO *pt)
{
    int matri;
    FILE *file;
    system("cls");
    file = fopen ("dadosemprestimo.dat","rb+");
    printf("DIGITE O CODIGO DO LIVRO");
    setbuf(stdin,NULL);
    scanf("%d",&matri);
    while (fread(pt,sizeof(*pt),1,file)==1)
    {
        if(matri== pt->matrie)
        {
            printf("CODIGO DO LIVRO: %d\n",pt->codle);
            printf("MATRICULA: %d\n",pt->matrie);
        }
    }
    fclose(file);
    system("Pause");
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
                    editarlivro(&liv);
                    break;

                case '3':
                    removerlivro (&liv);
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
                    removeraluno(&a);
                    break;

                case '3':
                    editaraluno(&a);
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
                        printf("1-LISTAR TODOS OS EMPRESTIMOS\n");
                        printf("2-LISTAR POR LIVRO\n");
                        printf("3-LISTAR POR ALUNO\n");
                        printf("4-RETORNAR AO MENU PRINCIPAL\n");
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



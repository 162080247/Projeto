#include<stdio.h>
#include<stdlib.h>
#include<conio.c> 
#include<string.h>

typedef struct {
	char codle[21];
	int data,ativo;
}EMPRESTIMO;

typedef struct {
 char nomel[21],nomea[21],area[16],codl[11];
 int quant;
}LIVRO;

typedef struct {
	char nomeal[31],matri[11],cpf[14];
}ALUNO;




void linha(){
int i;

gotoxy(15,5); printf("%c",201);
  for (i=0;i<50;i++)
	{
	 printf("%c",205);
	}
	 printf("%c",187);
 gotoxy(15,20); printf("%c",200);
 
   for (i=0;i<50;i++)
   {
	  printf("%c",205);
	}
	  printf("%c",188);
}

void linhalateral (){
int i;
for (i=6;i<20;i++){
	gotoxy(15,i);
	printf("%c",186);
	gotoxy (66,i);
	printf("%c",186);
}
}


void menuprincipal (){
system("cls");
linha();
linhalateral();
gotoxy(34,7);   printf("MENU PRINIPAL");
gotoxy(20,10);  printf("1- ACERVO");
gotoxy(20,11);	printf("2- MENU DO ALUNO");
gotoxy(20,12);	printf("3- EMPRESTIMOS");
gotoxy(20,13);	printf("4- SAIR");
gotoxy(32,10);
		
	
}

void menulivro ()
{
	
system("cls");
linha();
linhalateral();	
gotoxy(34,7);	printf("MENU DO ACERVO\n");
gotoxy(20,10);	printf("1- CADASTRAR LIVRO: \n");
gotoxy(20,11);	printf("2- EDITAR LIVRO: \n");
gotoxy(20,12);	printf("3- REMOVER: \n");
gotoxy(20,13);	printf("4- LISTAR LIVROS CADASTRADOS: \n");
gotoxy(20,14);	printf("5- RETORNAR AO MENU PRINCIPAL: \n");
gotoxy(38,15);
		
}

void cadastrarl (LIVRO *pt){
	FILE *file;
	file= fopen("dadoslivro.dat","ab+");
	
	
system("cls");
  int i;
	printf ("CADASTRO:\n");
	
	     
		printf("DIGITE O NOME DO LIVRO:");
		setbuf(stdin,NULL);
		 gets(pt->nomel);
	
		printf("DIGITE O NOME DO AUTOR:");
		 setbuf(stdin,NULL);
		 gets(pt->nomea);
		 
		printf("DIGITE A AREA DO CONHECIMENTO: ");
		setbuf(stdin,NULL);
		 gets(pt->area);
		 
		printf("DIGITE O CODIGO DO LIVRO: ");
		setbuf(stdin,NULL);
		 gets(pt->codl);
		 
		 printf("QUANTIDADE DE EXEMPLARES:");
		 setbuf(stdin,NULL);
		 scanf("%d",&pt->quant);
		 
	fwrite (pt,sizeof(LIVRO),1,file);
		  setbuf(stdin,NULL);
	fclose(file);
}

void listar (LIVRO *pt){
	int i=6;
	FILE *file;
	file=fopen("dadoslivro.dat","rb");
	system ("cls");
	
	printf ("LIVOS CADASTRADOS\n");	
	gotoxy(1,4); printf("NOME DO LIVRO");
	gotoxy(25,4); printf("AUTOR");
	gotoxy(45,4); printf("AREA");
	gotoxy(65,4); printf("CODIGO");
	gotoxy(75,4); printf("QUANTIDADE");
	
	while (fread(pt,sizeof(*pt),1,file)==1)
	{
		
		gotoxy(1,i);	printf("%s\t",pt->nomel);
		gotoxy(25,i);	printf("%s\t",pt->nomea);
		gotoxy(45,i);	printf("%s\t",pt->area);
		gotoxy(65,i);	printf("%s\t",pt->codl);
		gotoxy(75,i);	printf("%d",pt->quant);
		i++;
	}
	gotoxy(1,i);
fclose (file);
}

void listaraluno (ALUNO *pt)
{
    FILE *file;
	file=fopen("dadosaluno.dat","rb");
	system ("cls");
	
	printf ("ALUNOS CADASTRADOS\n");	
	
	while (fread(pt,sizeof(*pt),1,file)==1)
	{
		printf("%s\t",pt->nomeal);
		printf("%s\t",pt->matri);
		printf("%s\t\n",pt->cpf);	
	}
fclose (file);
system("Pause");
}

void menudoaluno ()
{
	system("cls");
	printf("MENU DO ALUNO\n\n");
	printf("1- CADASTRAR ALUNO:\n");
	printf("2- REMOVER ALUNO:\n");
	printf("3- EDITAR ALUNO:\n");
	printf("4- LISTAR ALUNOS CADASTRADOS:\n");
	printf("5- RETORNAR AO MENU PRINCIPAL:\n");
	
}

void cadastraraluno(ALUNO *pt)
{
  	FILE *file;
	file= fopen("dadosaluno.dat","ab+");
	
	
system("cls");

	printf ("CADASTRO:\n");
	
	    setbuf(stdin,NULL);
	
		printf("DIGITE O NOME DO ALUNO:");
		 gets(pt->nomeal);
	     setbuf(stdin,NULL);
	     
		printf("DIGITE O CPF:");
		 gets(pt->cpf);
		 setbuf(stdin,NULL);
		 
		printf("DIGITE A MATRICULA: ");
		 gets(pt->matri);
		 setbuf(stdin,NULL);
		 
	fwrite (pt,sizeof (*pt),1,file);
		  setbuf(stdin,NULL);
		  
	fclose(file);
}

void removerlivro (LIVRO *pt)
{
	char cod2 [11],c;
	FILE *file,*file2;
	
	system("cls");
	setbuf(stdin,NULL);
	printf("DIGITE O CODIGO DO LIVRO:");
	gets(cod2);

	file = fopen ("dadoslivro.dat","rb+");
	file2= fopen ("livrosremo.dat","wb+");
    rewind(file);
     
	while  (fread(pt,sizeof(*pt),1,file)==1)
	{  
	
	    if (strcmp(cod2,pt->codl)==0)
		{
	      	printf("NOME: %s\n",pt->nomel);
	      	printf("AUTOR: %s\n",pt->nomea);
	      	printf("AREA: %s\n",pt->area);
	      	printf("CODIGO DO LIVRO: %s\n",pt->codl);
	      	printf("QUANTIDADE: %d\n",pt->quant);
	      	printf("DESEJA DELETAR O LIVRO: S-SIM, N-NAO:");
	      	c=getch();
	      	
	    	if (c=='s'||c=='S')
			{
			
	      	    rewind (file);
	
	     		while (fread(pt,sizeof(*pt),1,file)==1)
		  		{
		      		if(strcmp(cod2,pt->codl)!=0)
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
	char matri2[11],c;
	FILE *file,*file2;
	
	system("cls");
	setbuf(stdin,NULL);
	printf("DIGITE A MATRICULA DO ALUNO:");
	gets(matri2);
	
	file = fopen ("dadosaluno.dat","rb+");
	file2= fopen ("alunoremo.dat","wb+");
    rewind(file);
    
		while  (fread(pt,sizeof(*pt),1,file)==1)
	{  
	
	    if (strcmp(matri2,pt->matri)==0)
		{
	      	printf("NOME: %s\n",pt->nomeal);
	      	printf("CPF: %s\n",pt->cpf);
	      	printf("MATRICULA: %s\n",pt->matri);
	      	printf("DESEJA DELETAR O ALUNO: S-SIM, N-NAO:");
	      	c=getch();
	      	
	    	if (c=='s'||c=='S')
			{
			
	      	    rewind (file);
	
	     		while (fread(pt,sizeof(*pt),1,file)==1)
		  		{
		      		if(strcmp(matri2,pt->matri)!=0)
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
	char c,cod2[11];
	FILE *file;
	system ("cls");
	printf("DIGITE O CODIGO DO LIVRO");
	gets(cod2);
	file = fopen ("dadoslivro.dat","r+b");
	while (fread(pt,sizeof(*pt),1,file)==1){
		if (strcmp(cod2,pt->codl)==0){
			printf("NOME: %s\n",pt->nomel);
			printf("AUTOR: %s\n",pt->nomea);
			printf("AREA: %s\n",pt->area);
			printf("CODIGO DO LIVRO: %s\n",pt->codl);
			printf("QUANTIDADE: %d\n",pt->quant);
			printf("DESEJA FAZER ALTERACAO: S-SIM, N-NAO:");
			c=getch();
			if (c=='S'|| c=='s'){
				printf("\n\nNOVO NOME:");
				gets(pt->nomel);
				setbuf(stdin,NULL);
				printf("NOME DO AUTOR:");
				gets(pt->nomea);
				setbuf(stdin,NULL);
				printf("AREA:");
				gets(pt->area);
				setbuf(stdin,NULL);
				printf("CODIGO:");
				gets(pt->area);
				setbuf(stdin,NULL);
				printf("QUANTIDADE:");
				scanf("%d",&pt->quant);
				fseek(file,ftell(file)-sizeof(*pt),0);
				fwrite (pt,sizeof(*pt),1,file);
				fclose(file);
				
			}
		}
	}
	
}



main ()
{
char c;
LIVRO liv;
ALUNO a;

	do{
		menuprincipal();
		c=getch();
	switch (c){
	
		case '1': do{
			           menulivro();
		               c=getch();
		               
		            	   switch (c)
				     	 {
		                  	 case '1':  cadastrarl(&liv);
							            
					               		break;
					          
					      	 case '2': editarlivro(&liv);
					                 	break;	  
					                 	
							  case '3': removerlivro (&liv);
							            break;
							            
				           	 case '4': listar(&liv);
				           	           system("Pause");
				                       break;
						}
					}while (c!='5');
					
					break;
					
		case '2': do{  menudoaluno();
		               c=getch();
		           
				     switch (c)
				     	 {
		                  	case '1': cadastraraluno(&a);
					               	    break;
					          
					      	case '2': removeraluno(&a);
					                 	break;
										 	  
							case '3': //editar aluno
							            break;
							            
				           	case '4': listaraluno(&a);
				           	           break;
				         }
				     }while (c!='5');
				       
				       break;
				       
			case '4': system ("cls");
			          gotoxy(10,17); printf("\t\tPROGRAMA ENCERRADO");
			          break;
		}
					
} while (c!='4'); 
	
}



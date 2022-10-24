#include <stdio.h>
#include <stdlib.h>

typedef struct Estudiante
{
	char Nombre[20];
	char Apellido[20];
	int Matricula;
	struct Estudiante *PSiguiente;
	struct Estudiante *PAnterior;
}EST;

void FMenu(int *PMenu)
{
	printf("\n|||||||||||||| SISTEMA DE ALTAS Y BAJAS DE ALUMNOS |||||||||||||");
	printf("\nIngrese el valor segun la opcion del menu al que quiera acceder.");
	printf("\n\t[1] Dar de alta a un alumno.");
	printf("\n\t[2] Buscar un alumno");
	printf("\n\t[3] Dar de baja a un alumno.");
	printf("\n\t[4] Imprimir la lista de alumnos.");
	printf("\n\t[5] Borrar la lista.");
	printf("\n\t[6] Guardar la lista en un archivo.");
	printf("\n\t[7] Importar una lista de alumnos desde un archivo.");
	printf("\n\t[0] Salir del programa.");
	printf("\n\tIngrese la opcion: ");
	scanf("%i", PMenu);
}

EST *Abrir(EST *PInicial)
{
	FILE *PTR;
	char Archivo[20], ch;
	EST *PQ=PInicial;

	printf("\nInserta el nombre del archivo en el que deseas abrir la lista, incluyendo la extencion .txt: ");
	scanf("%s", &Archivo[0]);
	if((PTR= fopen(&Archivo[0], "r"))==NULL)
	{
		printf("\nEl archivo que estas bucando no existe.\n");
	}
	else if((PTR= fopen(&Archivo[0], "r"))!=NULL)
	{
		PTR= fopen(&Archivo[0], "r");
		while(!feof(PTR))
		{
			if(PQ==NULL)
			{
				PQ=(EST*)malloc(1*sizeof(EST));
				if(PQ==NULL)
				{
					printf("\nNo hay memoria disponible en el disco. Volviendo al menu principal...");
				}
				else
				{
					fscanf(PTR,"%s",PQ->Nombre);
					fscanf(PTR,"%c",&ch);
					fscanf(PTR,"%s",PQ->Apellido);
					fscanf(PTR,"%c",&ch);
					fscanf(PTR,"%d",&PQ->Matricula);
					fscanf(PTR,"%c",&ch);
					PQ->PSiguiente=NULL;
					PQ->PAnterior=NULL;
					PInicial=PQ;
				}
			}
			else
			{
				while(PQ->PSiguiente!=NULL)
				{
					PQ=PQ->PSiguiente;
				}
				PQ->PSiguiente=(EST*)malloc(1*sizeof(EST));
				fscanf(PTR,"%s",PQ->PSiguiente->Nombre);
				fscanf(PTR,"%c",&ch);
				fscanf(PTR,"%s",PQ->PSiguiente->Apellido);
				fscanf(PTR,"%c",&ch);
				fscanf(PTR,"%d",&PQ->PSiguiente->Matricula);
				fscanf(PTR,"%c",&ch);
				PQ->PSiguiente->PSiguiente=NULL;
				PQ->PSiguiente->PAnterior=PQ;
			}
		}
		fclose(PTR);
		PQ->PSiguiente=NULL;
		free(PQ->PSiguiente);
		printf("\nLista actualizada con exito. Volviendo al menu...\n");
	}
	return PInicial;
}

EST *Alta(EST *PInicial)
{
	EST *PQ=PInicial;

	if(PQ==NULL)
	{
		PQ=(EST*)malloc(1*sizeof(EST));
		if(PQ==NULL)
		{
			printf("\nNo hay memoria disponible en el disco. Volviendo al menu principal...");
		}
		else
		{
			printf("\nIngresa el nombre del alumno: ");
			scanf("%s", PQ->Nombre);
			printf("Ingresa el apellido paterno del alumno: ");
			scanf("%s", PQ->Apellido);
			printf("Ingresa la matricula del alumno: ");
			scanf("%d", &PQ->Matricula);
			printf("\nAlumno dado de alta con exito. Volviendo al menu principal...\n\n");
			PQ->PSiguiente=NULL;
			PQ->PAnterior=NULL;
			PInicial=PQ;
		}
	}
	else
	{
		while(PQ->PSiguiente!=NULL)
		{
			PQ=PQ->PSiguiente;
		}
		PQ->PSiguiente=(EST*)malloc(1*sizeof(EST));
		printf("\nIngresa el nombre del alumno: ");
		scanf("%s", PQ->PSiguiente->Nombre);
		printf("Ingresa el apellido paterno del alumno: ");
		scanf("%s", PQ->PSiguiente->Apellido);
		printf("Ingresa la matricula del alumno: ");
		scanf("%d", &PQ->PSiguiente->Matricula);
		printf("\nAlumno dado de alta con exito. Volviendo al menu principal...\n\n");
		PQ->PSiguiente->PSiguiente=NULL;
		PQ->PSiguiente->PAnterior=PQ;
	}
	return PInicial;
}

EST *Buscar(EST *PInicial)
{
	int Opcion, BuscarMatricula;
	char BuscarNombre[20];

	do
	{
		if(PInicial==NULL)
		{
			printf("\nLa lista de alumnos se encuentra vacia. Volviendo al menu principal...\n\n");
			break;
		}
		printf("\n\nComo deseas buscar al estudiante?\nIngresa 0 para buscarlo por nombre.\nIngresa 1 para buscarlo por matricula.\nOpcion: ");
		scanf("%d", &Opcion);
		if(Opcion==0)
		{
			printf("Ingrese el nombre del alumno: ");
			scanf("%s", &BuscarNombre[0]);
			while(PInicial!=NULL)
			{
				if(*PInicial->Nombre == BuscarNombre[0])
				{
					printf("\n\nEl alumno %s se encuentra registrado en la lista con la matricula %i.\n\n", PInicial->Nombre, PInicial->Matricula);
					break;
				}
				else
				{
					PInicial=PInicial->PSiguiente;
				}
				if(PInicial==NULL)
				{
					printf("\n\nEl alumno que busca no se encuentra en la lista.\n\n");
					PInicial=NULL;
				}
			}
		}
		else if(Opcion==1)
		{
			printf("Ingrese la matricula del alumno: ");
			scanf("%d", &BuscarMatricula);
			while(PInicial!=NULL)
			{
				if(PInicial->Matricula == BuscarMatricula)
				{
					printf("\n\nEl alumno con la matricula %d se encuentra registrado con el nombre de %s.\n\n", PInicial->Matricula, PInicial->Nombre);
					break;
				}
				else
				{
					PInicial=PInicial->PSiguiente;
				}
				if(PInicial==NULL)
				{
					printf("\n\nEl alumno que busca no se encuentra en la lista. Volviendo al menu principal...\n\n");
					PInicial=NULL;
				}
			}
		}
		else
		{
			printf("\nElegiste una opcion incorrecta, vuelve a ingresar la opcion.\n");
		}
	}while(Opcion!=0 && Opcion!=1);
	return PInicial;
}

EST *Baja(EST *PInicial)
{
	EST *BajaAlumno=NULL;
	int Opcion=1;

	if(PInicial==NULL)
	{
		printf("\nLa lista de alumnos se encuentra vacia. Volviendo al menu principal...\n\n");
	}
	else
	{
		BajaAlumno=Buscar(PInicial);
		if(BajaAlumno!=NULL)
		{
			printf("\n\nEstas seguro de querer dar de baja al alumno %s?\nIngresa 0 si quieres dar de baja al alumno.\nIngresa cualquier otro numero si NO quieres dar de baja al alumno.\nOpcion: ", BajaAlumno->Nombre);
			scanf("%d", &Opcion);
		}
		if(Opcion==0)
		{
			printf("\nAlumno dado de baja con exito. Volviendo al menu principal...\n\n");
			if(BajaAlumno->PSiguiente == NULL && BajaAlumno->PAnterior == NULL)
			{
				free(BajaAlumno);
				PInicial= NULL;
			}
			else if(BajaAlumno->PSiguiente != NULL && BajaAlumno->PAnterior == NULL)
			{
				PInicial=BajaAlumno->PSiguiente;
				free(BajaAlumno);
				PInicial->PAnterior=NULL;
			}
			else if(BajaAlumno->PSiguiente != NULL && BajaAlumno->PAnterior != NULL)
			{
				BajaAlumno->PAnterior->PSiguiente=BajaAlumno->PSiguiente;
				BajaAlumno->PSiguiente->PAnterior=BajaAlumno->PAnterior;
				free(BajaAlumno);
			}
			else if(BajaAlumno->PSiguiente == NULL && BajaAlumno->PAnterior != NULL)
			{
				BajaAlumno->PAnterior->PSiguiente=NULL;
				free(BajaAlumno);
			}
		}
	}
	return PInicial;
}

void Imprime(EST *PInicial)
{
	int i=0;

	printf("\n\n||||||||||||||||||||||||| LISTA DE ALUMNOS |||||||||||||||||||||||||||||||\n\n[#]\t\tNombre\t\tApellido Paterno\t\tMatricula\n");
	if(PInicial==NULL)
	{
		printf("\nLa lista de alumnos se encuentra vacia. Volviendo al menu principal...\n\n");
	}
	else
	{
		while(PInicial!=NULL)
		{
			printf("[%d]\t\t%s\t\t%s\t\t\t\t%d \n", (i+1), PInicial->Nombre, PInicial->Apellido, PInicial->Matricula);
			i++;
			PInicial=PInicial->PSiguiente;
		}
	}
}

EST *Borrar_Lista(EST *PInicial)
{
	int Opcion;

	if(PInicial==NULL)
	{
		printf("\nLa lista de alumnos se encuentra vacia. Volviendo al menu principal...\n\n");
	}
	else
	{
		printf("\n\nEstas seguro de querer BORRAR la lista?\nIngresa 0 si quieres BORRAR la lista.\nIngresa cualquier otro numero si NO quieres borrar la lista.\nOpcion: ");
		scanf("%d", &Opcion);
		if(Opcion==0)
		{
			while(PInicial->PSiguiente!=NULL)
			{
				PInicial=PInicial->PSiguiente;
				free(PInicial->PAnterior);
				PInicial->PAnterior=NULL;
			}
			free(PInicial);
			PInicial=NULL;
			printf("\nLista de alumnos borrada con exito. Volviendo al menu principal...\n\n");
		}
	}
	return PInicial;
}

int Salir(EST *PInicial)
{
	int Opcion;

	printf("\n\nEstas seguro de querer SALIR y BORRAR la lista?\nIngresa 0 si quieres SALIR y BORRAR la lista.\nIngresa cualquier otro numero si NO quieres salir y borrar la lista.\nOpcion: ");
	scanf("%d", &Opcion);
	if(Opcion==0)
	{
		if(PInicial==NULL)
		{
			printf("\nLa lista de alumnos ya se encuentra vacia.\nSaliendo del programa...\n");
		}
		else
		{
			while(PInicial->PSiguiente!=NULL)
			{
				PInicial=PInicial->PSiguiente;
				free(PInicial->PAnterior);
				PInicial->PAnterior=NULL;
			}
			free(PInicial);
			printf("\nLista borrada.\nSaliendo del programa...");
		}
	}
	return Opcion;
}

void Salvar(EST *PInicial)
{
	FILE *PTR;
	char Archivo[20];
	int Opcion;

	if(PInicial==NULL)
	{
		printf("\nLa lista de alumnos se encuentra vacia. Volviendo al menu principal...\n\n");
	}
	else
	{
		printf("\nInserta el nombre del archivo en el que deseas guardar la lista, incluyendo la extencion .txt: ");
		scanf("%s", &Archivo[0]);
		if((PTR= fopen(&Archivo[0], "r"))==NULL)
		{
			printf("\nEl archivo que estas bucando no existe. Deseas crearlo? \n\tInserta 0 para crearlo.\n\tInserta cualquier otro numero para volver al menu.\n\tIngrese la opcion: ");
			scanf("%i", &Opcion);
			if(Opcion!=0) printf("\nVolviendo al menu principal...\n");
			if(Opcion==0)
			{
				PTR= fopen(&Archivo[0], "w");
				while(PInicial->PSiguiente!=NULL)
				{
					fprintf(PTR,"%s", PInicial->Nombre);
					fprintf(PTR,"%c", ' ');
					fprintf(PTR,"%s", PInicial->Apellido);
					fprintf(PTR,"%c", ' ');
					fprintf(PTR,"%d", PInicial->Matricula);
					fprintf(PTR,"%c", '\n');
					PInicial=PInicial->PSiguiente;
				}
				fprintf(PTR,"%s", PInicial->Nombre);
				fprintf(PTR,"%c", ' ');
				fprintf(PTR,"%s", PInicial->Apellido);
				fprintf(PTR,"%c", ' ');
				fprintf(PTR,"%d", PInicial->Matricula);
				fprintf(PTR,"%c", '\n');
				fclose(PTR);
				printf("\nARCHIVO GUARDADO CON EXITO. Volviendo al menu...\n");
			}
		}
		else if((PTR= fopen(&Archivo[0], "r"))!=NULL)
		{
			printf("\nALERTA: El archivo al que estas intentando acceder ya existe. Deseas sobreescribirlo?\n\tInserta 0 para sobreescribirlo.\n\tInserta cualquier otro numero para volver al menu.\n\tIngrese la opcion: ");
			scanf("%i", &Opcion);
			if(Opcion!=0) printf("\nVolviendo al menu principal...\n");
			if(Opcion==0)
			{
				PTR= fopen(&Archivo[0], "w");
				while(PInicial->PSiguiente!=NULL)
				{
					fprintf(PTR,"%s", PInicial->Nombre);
					fprintf(PTR,"%c", ' ');
					fprintf(PTR,"%s", PInicial->Apellido);
					fprintf(PTR,"%c", ' ');
					fprintf(PTR,"%d", PInicial->Matricula);
					fprintf(PTR,"%c", '\n');
					PInicial=PInicial->PSiguiente;
				}
				fprintf(PTR,"%s", PInicial->Nombre);
				fprintf(PTR,"%c", ' ');
				fprintf(PTR,"%s", PInicial->Apellido);
				fprintf(PTR,"%c", ' ');
				fprintf(PTR,"%d", PInicial->Matricula);
				fprintf(PTR,"%c", '\n');
				fclose(PTR);
				printf("\nARCHIVO SOBREESCRITO CON EXITO. Volviendo al menu...\n");
			}
		}
	}
}


int main()
{
	EST *PInicial=NULL;
	int Menu, *PMenu=&Menu;

	do
	{
		FMenu(PMenu);
		switch(Menu)
		{
			case 1:
				PInicial = Alta(PInicial);
				break;
			case 2:
				Buscar(PInicial);
				break;
			case 3:
				PInicial = Baja(PInicial);
				break;
			case 4:
				Imprime(PInicial);
				break;
			case 5:
				PInicial = Borrar_Lista(PInicial);
				break;
			case 6:
				Salvar(PInicial);
				break;
			case 7:
				PInicial = Abrir(PInicial);
				break;
			case 0:
				Menu=Salir(PInicial);
				break;
			default:
				printf("\nSelecciono una opcion incorrecta, vuelva a intertarlo.");
		}
	}while(Menu!=0);
	return 0;	
}

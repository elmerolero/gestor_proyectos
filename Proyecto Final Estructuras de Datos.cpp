 /* Fecha lìmite de entrega: 2 de Diciembre de 2019         *
 * Nombre del Autor: Ismael Salas López MinMax™ Software   *
 * Proyecto Final: Sistema de Información para la Gestión  *
 *                 de Proyectos                            *
 * Objetivo: Demostrar las habilidades adquiridas en clase *
 *            en un trabajo final.                         */

// Biblioteca de Entrada y Salida estándar de C++
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <string>
#include <ctime>
using namespace std;

// Estructura de Datos Abstracta Persona, permite almacenar los datos
// de las personas participantes en el proyecto.
struct Persona
{
	int  codigo;				// Código asignado a la Persona
	char nombre[ 125 ];			// Nombre y
	char apellidos[ 125 ]; 		// Apellidos de la persona
	char telefono[ 11 ];		// Teléfono
	char calle[ 125 ];			// Calle donde reside
	char numeroExt[ 7 ];		// Número en formato NNNN-L donde las N representan dígitos y la L una letra (A o B)
	char numeroInt[ 7 ];		// Número interior
	int  codigoPostal;			// Código Postal
	int  municipio;				// Código del municipio en el que se resida
	int  estado;				// Código del estado en el que resida

	Persona * siguiente;		// Apuntador a la siguiente persona
};

// Estructura de Datos Abstracta Herramientas, permite guardar los datos
// de las herramientas utilizadas en el proyecto
struct Herramienta
{
	char  nombre[ 255 ];    	// Nombre de la herramienta
	int   cantidad;				// Cantidad de unidades que se requieren de esa herramienta (por ejemplo 5 computadoras)
	float valorApreciado;   	// Valor por unidad
	float costoTotal;			// Costo total de las herramientas

	Herramienta * siguiente;	// Apuntador a la siguiente herramienta
};

// Estructura de Datos Abstracta Proyecto, esta estructura es la base de todo el
// programa, pues registra los datos de todos los proyectos administrados por el sistema
struct Proyecto
{
	int  codigo;				// Código del proyecto registrado
	char nombre[ 125 ];         // Nombre del proyecto
	Persona * responsable;		// Responsable del proyecto
	Persona * colaboradores;		// Lista de integrantes
	char  areaInvestigacion[ 50 ];	// Código del área de estudio
	float presupuesto;			// Presupuesto destinado al proyecto
	Herramienta * herramientas; // Lista de herramientas
	int   situacion;			// Situación del proyecto "Avance", "Pausado", "Finalizado" los proyectos cancelados son eliminados
	char  fecha[ 9 ];			// Fecha en formato de caracteres 'dd/mm/aaaa' de cuando se registro el proyecto
	char  descripcion[ 250 ];  // Descripción del proyecto

	Proyecto * siguiente;	// Apuntado al siguiente proyecto
};

// Estructura para almacenar los estados y los municipios
struct Estado
{
	char *nombre;			// Nombre del estado
	int inicio;				// Determina donde empiezan los municipios que pertenecen a ese estado
	int fin;				// Donde terminan los municipios que pertenecen a ese estado
};

// Para la fecha
int dia;
int mes;
int anio;

// Gestor de codigos
int codigo = 1;

// Lista Principal
Proyecto * ptrListaProyectos;

// Estados de la republica
const int NUMERO_ESTADOS = 32;
Estado estados[ NUMERO_ESTADOS ];

// Municipios de la republica
const int NUMERO_MUNICIPIOS = 2457;
char * ptrMunicipios[ NUMERO_MUNICIPIOS ];

void presentacion();
void mostrarMenu();

Proyecto * proyectoNuevo( void );
void proyectoAgregarALista( Proyecto * ); 					// Agrega proyectos a la lista
void proyectoEliminarDeLista( void ); 						// Elimin proyectos de la lista
void proyectoConsultar( void );								// Muestra todos los proyectos registrados
Proyecto * proyectoBuscarCodigo( int codigo );				// Buscar proyectos por codigo
Proyecto * proyectoBuscarNombre( const char * nombre );			// Buscar proyecto por nombre
void proyectoImprimir( Proyecto * );						// Imprime el proyectodado
void proyectoImprimirDetalles( Proyecto * );

void proyectoSetNombre( Proyecto *, const char * ); 		// Establece el nombre del proyecto, el char indica la operación dada (NuevoProyecto o  modificacion)
void proyectoSetArea( Proyecto *, const char * );			// Establece el area
void proyectoSetPresupuesto( Proyecto *, const char * );
void proyectoSetSituacion( Proyecto *, const char * );
void proyectoSetDescripcion( Proyecto *, const char * );
void proyectoGuardar();

Persona * personaNueva( void );
void personaAgregarALista( Persona **, Persona * );
void personaEliminarLista( Persona ** );			// Este elimina la lista con todo y sus nodos (TODO)
void personaEliminarDeLista( Persona ** );			// Este permite eliminar nodos de la lista personas (SOLO UN NODO)
void personaImprimir( Persona * );

Herramienta * herramientaNueva( void );
void herramientaImprimir( Herramienta * herramienta );
void herramientaAgregarALista( Herramienta **, Herramienta * );
void herramientaEliminarLista( Herramienta ** );	// Elimina TODO
void herramientaEliminarDeLista( Herramienta ** );  // Elimina SOLO UN NODO

bool cargarEstados( void );			// Carga los estados de la republica
bool cargarMunicipios( void );		// Carga los municipios de la republica
int seleccionarEstado( void );      // Selecciona el estado
int seleccionarMunicipio( int );    // Selecciona uno de los municipios
void imprimirEstado( int );         // Imprime el estado recibido
void imprimirMunicipio( int );      // Imprime el municipio dado
void establecerFecha();				// Inicializa la fecha

int main()
{
	int opcion;			// Selección del usuario
	int codigo;			// Codigo usado para la busqueda
	char nombre[125];  // Nombre usado para la busqueda
	establecerFecha();
	// Carga los archivos
	if( cargarEstados() && cargarMunicipios() ){
		system( "cls" );
		presentacion();
		cout << "Cargado correctamente." << endl;
		system( "pause" );
		do{
			system( "cls" );
			mostrarMenu();
			cin >> opcion;
			switch( opcion ){
				// Caso 1: Nuevo Proyecto
				case 1:
					proyectoAgregarALista( proyectoNuevo() );
					break;
				
				// Caso 2: Eliminar proyecto
				case 2:
					proyectoEliminarDeLista();
					break;
					
				// Caso 3: Consultar Proyectos (mostrar todos los elementos en memoria)
				case 3:
					proyectoConsultar();
					break;
					
				//	Caso 4: Buscar un proyecto con código, este muestra resultados mas a detalle
				case 4:
					system( "cls" );
					cout << "***************** Consultar Proyecto por Codigo *******************" << endl;
					cout << "Introduce el codigo del a buscar: ";
					cin >> codigo;
					proyectoImprimirDetalles( proyectoBuscarCodigo(codigo) );
					break;
					
				// Caso 5: Buscar proyecto con nombre, este muestra los mismos resultados y opciones que los anteriores
				case 5:
					system( "cls" );
					cout << "***************** Consultar Proyecto por Nombre *******************" << endl;
					cout << "Introduce el nombre del proyecto a buscar: ";
					cin.ignore();
					cin.getline( nombre, 125, '\n' );
					proyectoImprimirDetalles( proyectoBuscarNombre( nombre ) );
					break;
					
				case 7:
					proyectoGuardar();
					break;

				// Caso 0: Salir
				case 0:
					cout << (char)168 << "Estas seguro de que deseas salir? (1-Si/0-No): ";
					cin >> opcion;
					if( opcion )
						cout << "Saliendo... Buen dia!" << endl;
					opcion = !opcion;
					break;

				// Cualquier opción distinta
				default:
					cout << "Opcion no valida." << endl;
					break;
			}

			// Pausa
			system( "pause" );
		}while( opcion != 0 );
	}else{
		std::cout << "Error al cargar los Estados." << std::endl;
	}

	return 0;
}

void presentacion()
{
	system( "cls" );
	cout << "*****************     Investigacion y Desarrollo *****************      " << endl
		 << "*****************          *************         ******************     " << endl
         << "******************        ****************       *******************    " << endl
         << "****           ****     ******       *******     *****        *******   " << endl
         << "****             ***   ******         *******    *****          ******  " << endl
	     << "****            ****   ******         *******    *****           ****** " << endl
	     << "****           ****    *******       *******     *****           ****** " << endl
	     << "*****************       *******     *******      *****           *******" << endl
	     << "***************          ****************        *****           *******" << endl
	     << "***************         ***********************  *****           *******" << endl
	     << "*****     ******       ******       **********   *****           ****** " << endl
	     << "*****      ******     ******         ******      *****          ******  " << endl
	     << "*****       ******     *****        ********     *****        *******   " << endl
	     << "*****        ******     *********************    *******************    " << endl 
		 <<	"*****        *******     ***********  ********   ******************     " << endl;
}

// Muestra el menu
void mostrarMenu( void )
{
	std::cout << "*********************** Menu ***********************\n"
			  << "1. Nuevo proyecto." 				 << endl
			  << "2. Eliminar proyecto."			 << endl
			  << "3. Ver proyectos."				 << endl
			  << "4. Consultar proyecto por codigo." << endl
			  << "5. Consultar proyecto por nombre." << endl
			  << "6. Ordenar proyectos. (No disponible)."<< endl
			  << "7. Respaldar proyectos en el disco duro." << endl
			  << "8. Consultar los proyectos respaldados.(No disponible)" << endl
			  << "0. Salir" 						 << endl;
	std::cout << "Selecciona una opcion: ";
} // Fin

// Crea un nuevo proyecto
Proyecto * proyectoNuevo( void )
{
	// Estructura nueva
	Proyecto *ptrNuevo = NULL;

	// Opcion
	int opcion;

	// Reservamos memoria para el apuntador
	ptrNuevo = ( Proyecto * )malloc( sizeof( Proyecto ) );
	if( ptrNuevo == NULL ){
		cout << "No hay memoria suficiente para continuar." << endl;
		return NULL;
	}
	
	// Presentación nuevo proyecto
	system( "cls" );
	cout << "*************** Nuevo Proyecto ***************" << endl;

	// Asigna código
	ptrNuevo -> codigo = codigo++;
	
	// Introduce un nombre
	proyectoSetNombre( ptrNuevo, "Nuevo Proyecto");

	// Asigna una persona responsable del proyecto
	cout << "Es necesario asignar una persona responsable al proyecto." << endl;
	cout << (char)168 << "Desea continuar? ( 1-Si/0-No(Cancelar) ): ";
	cin >> opcion;
	if( !opcion ){
		cout << "Cancelado..." << endl;
        free( ptrNuevo );
        return NULL;   
	}
	
	// Registramos los datos de la persona
	ptrNuevo -> responsable = personaNueva();
	
	// Asigna colaboradores al proyecto
	std::cout << (char)168 << "Desea agregar colaboradores al proyecto? ( 1-Si/0-No ): ";
	std::cin >> opcion;
	ptrNuevo -> colaboradores = NULL;
	while( opcion ){
		personaAgregarALista( &(ptrNuevo -> colaboradores), personaNueva() );
		std::cout << (char)168 << "Desea agregar otro colaborador al proyecto? ( 1-Si/0-No ): ";
		std::cin >> opcion;
	}
	
	// Registra herrmienta necesaria para el proyecto
	cout << (char)168 << "Desea registrar herramienta necesaria para el proyecto? ( 1-Si/0-No ): ";
	cin >> opcion;
	ptrNuevo -> herramientas = NULL;
	while( opcion ){
		herramientaAgregarALista( &(ptrNuevo -> herramientas), herramientaNueva() );
		cout << (char)168 << "Desea registrar otra herramientas al proyecto? ( 1-Si/0-No ): ";
		cin >> opcion;
	}
	
	proyectoSetArea( ptrNuevo, "Nuevo Proyecto" );
	
	proyectoSetPresupuesto( ptrNuevo, "Nuevo Proyecto" );
	
	proyectoSetSituacion( ptrNuevo, "Nuevo Proyecto" );
	
	proyectoSetDescripcion( ptrNuevo, "Nuevo Proyecto");
	
	sprintf( ptrNuevo -> fecha, "%d/%d/%d", dia, mes, anio );
	
	return ptrNuevo;
} // Fin 

// Agregar proyecto a la lista
void proyectoAgregarALista( Proyecto * proyectoNuevo )
{
    // Si no es un proyecto vacío !(proyecto == NULL)
    if( proyectoNuevo != NULL ){
        // Si lista no está vacía
        if( ptrListaProyectos != NULL ){
           // ¿Añadir al inicio?
           	proyectoNuevo -> siguiente = ptrListaProyectos -> siguiente;
        }
        // Si no, entonces hay al menos un elemento y si se quiere insertar al inicio (posicion == 1)
        else{
        	// Añadimos el primer elemento de la lista
            ptrListaProyectos = proyectoNuevo;
		}
        ptrListaProyectos -> siguiente = proyectoNuevo;
    }
}

// Elimina elemento de la lista
void proyectoEliminarDeLista( void )
{
	// variable iteradora
	Proyecto * ptrAEliminar = ptrListaProyectos;
	
	// Opcion
	int opcion;
	
	// Seccion
	system( "cls" );
	cout << "******************* Eliminar Proyecto ***************************" << endl;
	
	// ¿No está vacia la lista?
	if( ptrListaProyectos != NULL ){
		// Un solo nodo en la lista
		if( ptrListaProyectos -> siguiente == ptrListaProyectos ){
			cout << "Detalles de proyecto: " << endl;
			proyectoImprimir( ptrAEliminar );
			cout << "Deseas eliminar este proyecto? (1-Si/0-No): ";
			cin >> opcion;
			if( opcion ){
				ptrListaProyectos = NULL;
				personaEliminarLista( &(ptrAEliminar -> colaboradores) );
				herramientaEliminarLista( &(ptrAEliminar -> herramientas) );
				free( ptrAEliminar );
				cout << "Proyecto eliminado." << endl;
			}
			else{
				cout << "Proyecto no eliminado." << endl;
			}
		}
		// Varios elementos
		else{
			do{
				cout << "Detalles de proyecto: " << endl;
				proyectoImprimir( ptrAEliminar );
				cout << "Deseas eliminar este proyecto? (1-Si/0-No): ";
				cin >> opcion;
				if( opcion ){
					while( ptrListaProyectos -> siguiente != ptrAEliminar ){
						ptrListaProyectos = ptrListaProyectos -> siguiente;
					}
					ptrListaProyectos -> siguiente = ptrAEliminar -> siguiente;
					personaEliminarLista( &(ptrAEliminar -> colaboradores) );
					herramientaEliminarLista( &(ptrAEliminar -> herramientas) );
					free( ptrAEliminar );
					cout << "Proyecto eliminado." << endl;
					return;
				}
				ptrAEliminar = ptrAEliminar -> siguiente;
			}while( ptrAEliminar != ptrListaProyectos );
			cout << "Proyecto no eliminado." << endl;
		}
	}
	else{
		cout << "No hay elementos que eliminar." << endl;
	}
	
}

void proyectoConsultar( void )
{
	// Variable iteradora
	Proyecto * ptrAux = NULL;
	ptrAux = ptrListaProyectos;
	
	system( "cls" );
	cout << "***************** Consultar Proyectos *****************" << endl;
	if( ptrAux != NULL ){
		do{
			proyectoImprimir( ptrAux );
			ptrAux = ptrAux -> siguiente;
		}while( ptrAux != ptrListaProyectos );
	}
	else{
		cout << "No hay un proyecto registrado." << endl;
	}
}

Proyecto * proyectoBuscarCodigo( int codigo )
{
	// Apuntador a la persona buscada
	Proyecto * proyectoBuscado;
	
	if( ptrListaProyectos != NULL ){
		// Inicializa el elemento en el primer elemento de la lista
		proyectoBuscado = ptrListaProyectos;
		
		// Itera a traves de los elementos
		do{
			// ¿El código introducido coincide con el codigo de alguno de los proyectos?
			if( proyectoBuscado -> codigo == codigo ){
				// Retorna un apuntador hacia el proyecto buscado
				return proyectoBuscado;
			}
			
			// Continua iterando a través de la lista.
			proyectoBuscado = proyectoBuscado -> siguiente;
		}while( proyectoBuscado != ptrListaProyectos );
	}
	
	// No encontró nada retorna NULL
	return NULL;
}

// Buscar proyecto por nombre
Proyecto * proyectoBuscarNombre( const char * nombre )
{
	// Apuntador a la persona buscada
	Proyecto * proyectoBuscado;
	
	if( ptrListaProyectos != NULL ){
		// Inicializa el elemento en el primer elemento de la lista
		proyectoBuscado = ptrListaProyectos;
		
		// Itera a traves de los elementos
		do{
			// ¿El código introducido coincide con el codigo de alguno de los proyectos?
			if( strcmp( proyectoBuscado -> nombre, nombre ) == 0 ){
				// Retorna un apuntador hacia el proyecto buscado
				return proyectoBuscado;
			}
			
			// Continua iterando a través de la lista.
			proyectoBuscado = proyectoBuscado -> siguiente;
		}while( proyectoBuscado != ptrListaProyectos );
	}
	
	// No encontró nada retorna NULL
	return NULL;
}

// Imprimir detalles del proyecto
void proyectoImprimir( Proyecto * proyecto )
{
	// Validamos que no sea un proyecto vacío
	if( proyecto != NULL ){
		cout << "****************************************************************" << endl;
		cout << "Nombre del proyecto: " << proyecto -> nombre << "\tCodigo: " << proyecto -> codigo << endl;
		cout << "\nPersona a cargo:\n ->" << proyecto -> responsable -> nombre << " " << proyecto -> responsable -> apellidos << endl 
			 << "\nColaboradores: " << endl;
			 
		// Obtiene el apuntador a las personas que colaboran en el proyecto y las imprime
		Persona * auxPtr = proyecto -> colaboradores;
		if( auxPtr != NULL ){
			do{
				cout << " ->" << auxPtr -> nombre << " " << auxPtr -> apellidos << endl;
				auxPtr = auxPtr -> siguiente;
			}while( auxPtr != proyecto -> colaboradores );
		}
		else{
			cout << " -No hay colaboradores registrados." << endl;
		}
		
		cout << "\nArea de investigacion:\n -" << proyecto -> areaInvestigacion << endl;
		cout << "\nPresupuesto asignado:\n -" << proyecto -> presupuesto << endl;
		cout << "\nHerramientas: " << endl;
		// Obtiene el apuntador a las herramientas registradas en el proyecto y las imprime
		Herramienta * auxPtr2 = proyecto -> herramientas;
		if( auxPtr2 != NULL ){
			do{
				cout << " ->Nombre: " << auxPtr2 -> nombre << " Cantidad: " << auxPtr2 -> cantidad << " Costo por unidad: " << auxPtr2 -> valorApreciado << " Costo total: " << auxPtr2 -> costoTotal << endl;
				auxPtr2 = auxPtr2 -> siguiente;
			}while( auxPtr2 != proyecto -> herramientas );
		}
		else{
			cout << " -No hay herramientas registradas." << endl;
		}
		
		cout << "\nSituacion: ";
		switch( proyecto -> situacion ){
			case 1:
				cout << "\n ->En Avance" << endl;
				break;
			case 2:
				cout << "\n ->En Pausa" << endl;
				break;
			case 3:
				cout << "\n ->Finalizado" << endl;
				break;
			default:
				cout << "\n ->Desconocido" << endl;
				break;
		}
		
		cout << "\nFecha de registro:\n ->" << proyecto -> fecha << endl;
		cout << "\nDescripcion: ";
		cout << proyecto -> descripcion << endl;
		cout << "****************************************************************" << endl;
	}
}

// Imprimir aún detalles del proyecto
void proyectoImprimirDetalles( Proyecto * proyecto )
{
	// Validamos que no sea un proyecto vacío
	if( proyecto != NULL ){
		system( "cls" );
		cout << "********************* Proyecto: " << proyecto -> nombre << " *********************" << endl; 
		cout << "Codigo: " << proyecto -> codigo << endl;
		cout << "\n***************** Informacion del responsable ***************** \n";
		personaImprimir( proyecto -> responsable ); 
		cout << endl;		
		cout << "\n*********************** Colaboradores ***********************" << endl;
			 
		// Obtiene el apuntador a las personas que colaboran en el proyecto y las imprime
		Persona * auxPtr = proyecto -> colaboradores;
		if( auxPtr != NULL ){
			do{
				personaImprimir( auxPtr ); cout << endl;
				auxPtr = auxPtr -> siguiente;
			}while( auxPtr != proyecto -> colaboradores );
		}
		else{
			cout << " -No hay colaboradores registrados." << endl;
		}
		
		// Obtiene el apuntador a las herramientas registradas en el proyecto y las imprime
		cout << "\n****************** Tecnologia y Herramientas *****************" << endl;
		Herramienta * auxPtr2 = proyecto -> herramientas;
		if( auxPtr2 != NULL ){
			do{
				herramientaImprimir( auxPtr2 );
				auxPtr2 = auxPtr2 -> siguiente;
			}while( auxPtr2 != proyecto -> herramientas );
		}
		else{
			cout << " -No hay herramientas registradas." << endl;
		}
		
		cout << "\nArea de investigacion:\n -" << proyecto -> areaInvestigacion << endl;
		cout << "\nPresupuesto asignado:\n -" << proyecto -> presupuesto << endl;
		cout << "\nHerramientas: " << endl;
		
		cout << "\nSituacion: ";
		switch( proyecto -> situacion ){
			case 1:
				cout << "\n ->En Avance" << endl;
				break;
			case 2:
				cout << "\n ->En Pausa" << endl;
				break;
			case 3:
				cout << "\n ->Finalizado" << endl;
				break;
			default:
				cout << "\n ->Desconocido" << endl;
				break;
		}
		
		cout << "\nFecha de registro:\n ->" << proyecto -> fecha << endl;
		cout << "\nDescripcion: ";
		cout << proyecto -> descripcion << endl;
		cout << "****************************************************************" << endl;
		// Opcion para el usuario
		int opcion;
		
		cout << "Opciones: " << endl
			 << "1. Cambiar nombre." << endl
			 << "2. Asignar otro responsable del proyecto." << endl
			 << "3. Agregar colaboradores." << endl
			 << "4. Eliminar colaboradores." << endl
			 << "5. Agregar herramientas." << endl
			 << "6. Eliminar herramientas." << endl
			 << "7. Cambiar presupuesto asignado." << endl
			 << "8. Cambiar situacion del proyecto." << endl
			 << "0. Volver al menu principal." << endl
			 << "Selecciona una opcion: ";
		cin >> opcion;
		switch( opcion ){
			case 1:
				proyectoSetNombre( proyecto, "Modificar Proyecto" );
				break;
			case 2:
				free( proyecto -> responsable );
				proyecto -> responsable = personaNueva();
				break;
			case 3:
				// Asigna colaboradores al proyecto
				cout << (char)168 << "Desea agregar colaboradores al proyecto? ( 1-Si/0-No ): ";
				cin >> opcion;
				while( opcion ){
					personaAgregarALista( &(proyecto -> colaboradores), personaNueva() );
					cout << (char)168 << "Desea agregar otro colaborador al proyecto? ( 1-Si/0-No ): ";
					cin >> opcion;
				}
				break;
				
			case 4:
				personaEliminarDeLista( &(proyecto -> colaboradores) );
				break;
				
			case 5:
				cout << (char)168 << "Desea registrar herramienta necesaria para el proyecto? ( 1-Si/0-No ): ";
				cin >> opcion;
				while( opcion ){
					herramientaAgregarALista( &(proyecto -> herramientas), herramientaNueva() );
					cout << (char)168 << "Desea registrar otra herramientas al proyecto? ( 1-Si/0-No ): ";
					cin >> opcion;
				}
				break;
				
			case 6:
				herramientaEliminarDeLista( &(proyecto -> herramientas) );
				break;
				
			case 7:
				proyectoSetPresupuesto( proyecto, "Modificar Proyecto" );
				break;
			case 8:
				proyectoSetSituacion( proyecto, "Modificar Proyecto" );
				break;
			case 0:	
				cout << "Regresando..." << endl;
				break;
			default:
				cout << "Opcion no valida." << endl;
				break;
		}
	}
	else{
		cout << "Proyecto no encontrado." << endl;
	}
}

// Establece un nombre al proyecto
void proyectoSetNombre( Proyecto * proyecto, const char * operacion )
{
	// Opcion de confirmacion
	int opcion;
	
	do{
		system( "cls" );
		if( operacion != NULL )
			cout << "*************************** " << operacion << " ***************************" << endl;
			
		cout << "************************* Establecer Nombre **************************" << endl;
		cout << "Introduce nombre: ";
		cin.ignore(); cin.getline( proyecto -> nombre, 125, '\n' );
		system( "cls" );
		if( operacion != NULL )
			cout << "*************************** " << operacion << " ***************************" << endl;
		cout << "************************* Establecer Nombre **************************" << endl;
		cout << (char)168 << "Este nombre es correcto?" << endl;
		cout << "Nombre: " << proyecto -> nombre << endl;
		cout << "Introduzca opcion (1-Si/0-No): ";
		cin >> opcion;
	}while( !opcion );
}

// Establecer area
void proyectoSetArea( Proyecto * proyecto, const char * operacion )
{
	// Opcion de confirmacion
	int opcion;
	
	do{
		system( "cls" );
		if( operacion != NULL )
			cout << "*************************** " << operacion << " ***************************" << endl;
		cout << "************************* Establecer Area **************************" << endl;
		cout << "Area: ";
		cin.ignore(); cin.getline( proyecto -> areaInvestigacion, 50, '\n' );
		system( "cls" );
		if( operacion != NULL )
			cout << "*************************** " << operacion << " ***************************" << endl;
		cout << "************************* Establecer Area **************************" << endl;
		cout << (char)168 << "El area dada es correcto?" << endl;
		cout << "Area: " << proyecto -> areaInvestigacion << endl;
		cout << "Introduzca opcion (1-Si/0-No): ";
		cin >> opcion;
	}while( !opcion );
}

// Establecer presupuesto
void proyectoSetPresupuesto( Proyecto * proyecto, const char * operacion )
{
	// Opcion de confirmacion
	int opcion;
	
	do{
		system( "cls" );
		if( operacion != NULL )
			cout << "*************************** " << operacion << " ***************************" << endl;
		cout << "************************* Establecer Presupuesto **************************" << endl;
		cout << "Presupuesto: ";
		cin >> proyecto -> presupuesto;
		system( "cls" );
		if( operacion != NULL )
			cout << "*************************** " << operacion << " ***************************" << endl;
		cout << "************************* Establecer Presupuesto **************************" << endl;
		cout << (char)168 << "El presupuesto introducido es correcto?" << endl;
		cout << "Presupuesto: " << proyecto -> presupuesto << endl;
		cout << "Introduzca opcion (1-Si/0-No): ";
		cin >> opcion;
	}while( !opcion );
}

// Establecer presupuesto
void proyectoSetSituacion( Proyecto * proyecto, const char * operacion )
{
	// Opcion de confirmacion
	int opcion;
	
	do{
		system( "cls" );
		if( operacion != NULL )
			cout << "*************************** " << operacion << " ***************************" << endl;
		cout << "************************* Situacion del Proyecto **************************" << endl;
		do{
			cout << "En que situacion se encuentra el proyecto?" << endl
				<< "1. En Avance" << endl
		 		<< "2. En Pausa" << endl
		 		<< "3. Finalizado" << endl
		 		<< "Introduzca una opcion: ";
			cin >> proyecto -> situacion;
		}while( proyecto -> situacion < 1 || proyecto -> situacion > 3 );
		if( operacion != NULL )
			cout << "*************************** " << operacion << " ***************************" << endl;
		cout << "************************* Situacion del Proyecto **************************" << endl;
		cout << (char)168 << "La situacion del proyecto es correcta?" << endl;
		cout << "Situacion del proyecto: " << endl;
		switch( proyecto -> situacion ){
			case 1:
				cout << "En Avance" << endl;
				break;
			case 2:
				cout << "En Pausa" << endl;
				break;
			case 3:
				cout << "Finalizado" << endl;
				break;
			default:
				cout << "Desconocido" << endl;
				break;
		}
		cout << "Introduzca opcion (1-Si/0-No): ";
		cin >> opcion;
	}while( !opcion );
}

// Establecer presupuesto
void proyectoSetDescripcion( Proyecto * proyecto, const char * operacion )
{
	// Opcion de confirmacion
	int opcion;
	
	do{
		system( "cls" );
		if( operacion != NULL )
			cout << "*************************** " << operacion << " ***************************" << endl;
		cout << "*********************** Descripcion del Proyecto ************************" << endl;
		cout << "Descripcion: ";
		cin.ignore(); cin.getline( proyecto -> descripcion, 250, '\n' );
		system( "cls" );
		if( operacion != NULL )
			cout << "*************************** " << operacion << " ***************************" << endl;
		cout << "*********************** Descripcion del Proyecto ************************" << endl;
		cout << (char)168 << "La descripcion dada es correcta?" << endl;
		cout << "Descripcion: " << endl
			 <<  "\t" << proyecto -> descripcion << endl;
		cout << "Introduzca opcion (1-Si/0-No): ";
		cin >> opcion;
	}while( !opcion );
}


// Crea una nueva persona
Persona * personaNueva( void )
{
    // Nueva persona
    Persona *ptrNuevo = NULL;

    // Opcion del usuario
    int opcion;

    // Reserva de memoria para registrar a la personas
    ptrNuevo = ( Persona * )malloc( sizeof( Persona ) );
    if( ptrNuevo == NULL ){
        cout << "No se puede crear a la persona." << endl;
        return NULL;
    }
	
	// Nueva Persona
	system( "cls" );
	cout << "*************** Nueva Persona ***************" << endl;

    // Nombre o nomrbes
	cout << "Introduce los datos." << endl;
	cout << "Nombre(s): ";
	cin.ignore();
	cin.getline( ptrNuevo -> nombre, 125, '\n' );

	// Apellidos
	cout << "Apellido(s): ";
	cin.getline( ptrNuevo -> apellidos, 125, '\n' );

	// Teléfono
	cout << "Telefono (10 digitos): ";
	cin.ignore();
	cin.getline( ptrNuevo -> telefono, 10, '\n' );

    cout << "************* Datos de domicilio ************" << endl;
    
    cout << "Calle: ";
	cin.getline( ptrNuevo -> calle, 125, '\n' );

	cout << "Numero exterior: ";
	cin.getline( ptrNuevo -> numeroExt, 6, '\n' );

    cout << "Numero interior (0 para omitir): ";
    cin.ignore();
	cin.getline( ptrNuevo -> numeroInt, 6, '\n' );

    cout << "Codigo Postal: ";
    cin >> ptrNuevo -> codigoPostal;

	ptrNuevo -> estado = seleccionarEstado();

	ptrNuevo -> municipio = seleccionarMunicipio( ptrNuevo -> estado );

	cout << "Datos registrados correctamente." << endl;

	return ptrNuevo;
}

void personaEliminarLista( Persona ** lista )
{
	if( (*lista) != NULL ){
		Persona * ptrAux = (*lista) -> siguiente;
		Persona * ptrAEliminar = NULL;
	
		while( ptrAux != (*lista) ){
			ptrAEliminar = ptrAux;
			ptrAux = ptrAux -> siguiente;
			free( ptrAEliminar );
		}
	
		(*lista) = NULL;
	}
}

void personaImprimir( Persona * persona )
{
    cout << "Nombre:    " << persona -> nombre << endl
         << "Apellidos: " << persona -> apellidos << endl
         << "Telefono:  " << persona -> telefono << endl
         << "Calle:     " << persona -> calle << endl
         << "Numero:    " << persona -> numeroExt << endl;

    if( persona -> numeroInt[ 0 ] != '0' || persona -> numeroInt[ 0 ] == '\0' )
        cout << "Numero Interior: " << persona -> numeroInt << std::endl;

	cout << "C.P.:\t" << persona -> codigoPostal << endl;
    std::cout << "Municipio: ";
    imprimirMunicipio( persona -> municipio );

    std::cout << "Estado: ";
    imprimirEstado( persona -> estado );
}

// Agregar
void personaAgregarALista( Persona **lista, Persona * persona )
{
	if( persona != NULL ){
		// Si la lista no esta vacía
		if( (*lista) != NULL ){
			cout << "Lista no vacia" << endl;
			persona -> siguiente = (*lista) -> siguiente;
		}
		// Si lo esta
		else{
			cout << "Lista vacia" << endl;
			(*lista) = persona;
		}
		(*lista) -> siguiente = persona;
		
		cout << "Persona agregada exitosamente." << endl;
	}
	else{
		cout << "Persona no agregada a la lista." << endl;
	}
}

// Elimina elemento de la lista
void personaEliminarDeLista( Persona ** persona)
{
	// variable iteradora
	Persona * ptrAEliminar = (*persona);
	
	// Opcion
	int opcion;
	
	// Seccion
	system( "cls" );
	cout << "******************* Eliminar Colaborador ***************************" << endl;
	
	// ¿No está vacia la lista?
	if( (*persona) != NULL ){
		// Un solo nodo en la lista
		if( (*persona) -> siguiente == (*persona) ){
			cout << "Datos de la persona: " << endl;
			personaImprimir( ptrAEliminar );
			cout << "Deseas eliminar a esta persona? (1-Si/0-No): ";
			cin >> opcion;
			if( opcion ){
				(*persona) = NULL;
				free( ptrAEliminar );
				cout << "Persona eliminada eliminado." << endl;
			}
			else{
				cout << "Persona no eliminada." << endl;
			}
		}
		// Varios elementos
		else{
			do{
				system( "cls" );
				cout << "******************* Eliminar Colaborador ***************************" << endl;
				cout << "Datos de la persona: " << endl;
				personaImprimir( ptrAEliminar );
				cout << "Deseas eliminar esta persona? (1-Si/0-No): ";
				cin >> opcion;
				if( opcion ){
					while( (*persona) -> siguiente != ptrAEliminar ){
						(*persona) = (*persona) -> siguiente;
					}
					(*persona) -> siguiente = ptrAEliminar -> siguiente;
					free( ptrAEliminar );
					cout << "Persona eliminada." << endl;
					return;
				}
				ptrAEliminar = ptrAEliminar -> siguiente;
			}while( ptrAEliminar != (*persona) );
			cout << "Persona no eliminada." << endl;
		}
	}
	else{
		cout << "No hay personas que eliminar." << endl;
	}
}

// Herramientas
Herramienta * herramientaNueva()
{
	// Variable auxiliar
	Herramienta * ptrAux;
	
	// Reserva espacio par la variable
	ptrAux = (Herramienta *)malloc( sizeof( Herramienta ) );
	if( ptrAux == NULL ){
		cout << "No hay memoria suficiente. " << endl;
		return NULL;
	}
	
	system( "cls" );
	cout << "************* Nueva Herramienta *************" << endl;
	
	// Nombre de la herramienta
	cout << "Nombre herramienta: ";
	cin.ignore(); cin.getline( ptrAux -> nombre, 125, '\n' );
	
	// Cantidad
	cout << "Numero de unidades: ";
	cin >> ptrAux -> cantidad;
	
	// Costo por unidad
	cout << "Costo por unidad: ";
	cin >> ptrAux -> valorApreciado;
	
	// Costo total
	ptrAux -> costoTotal = ptrAux -> cantidad * ptrAux -> valorApreciado;
	cout << "Costo total: " << ptrAux -> costoTotal << endl;
	
	return ptrAux;
}

void herramientaImprimir( Herramienta * herramienta )
{
	cout << "Nombre: " << herramienta -> nombre << endl;
	cout << "Cantidad: " << herramienta -> cantidad << endl;
	cout << "Costo por unidad: " << herramienta -> valorApreciado << endl;
	cout << "Costo total del equipo: " << herramienta -> costoTotal << endl;
	cout << endl;
}

void herramientaAgregarALista( Herramienta ** lista, Herramienta * herramienta )
{
	if( herramienta != NULL ){
		if( (*lista) != NULL ){
			herramienta -> siguiente = (*lista) -> siguiente;
		}
		else{
			(*lista) = herramienta;
		}
		(*lista) -> siguiente = herramienta;
	
		cout << "Herramienta registrada correctamente." << endl;
	}else{
		cout << "Herramienta no registrada." << endl;
	}
}

void herramientaEliminarLista( Herramienta ** lista )
{
	if( (*lista) != NULL ){
		Herramienta * ptrAux = (*lista) -> siguiente;
		Herramienta * ptrAEliminar = NULL;
	
		while( ptrAux != (*lista) ){
			ptrAEliminar = ptrAux;
			ptrAux = ptrAux -> siguiente;
			free( ptrAEliminar );
		}
	
		(*lista) = NULL;
	}
}

// Elimina elemento de la lista
void herramientaEliminarDeLista( Herramienta ** herramienta )
{
	// variable iteradora
	Herramienta * ptrAEliminar = (*herramienta);
	
	// Opcion
	int opcion;
	
	// Seccion
	system( "cls" );
	cout << "******************* Eliminar Herramienta ***************************" << endl;
	
	// ¿No está vacia la lista?
	if( (*herramienta) != NULL ){
		// Un solo nodo en la lista
		if( (*herramienta) -> siguiente == (*herramienta) ){
			cout << "Datos de la herramienta: " << endl;
			herramientaImprimir( ptrAEliminar );
			cout << "Deseas eliminar esta herramienta? (1-Si/0-No): ";
			cin >> opcion;
			if( opcion ){
				(*herramienta) = NULL;
				free( ptrAEliminar );
				cout << "Herramienta eliminada eliminado." << endl;
			}
			else{
				cout << "Herramienta no eliminada." << endl;
			}
		}
		// Varios elementos
		else{
			do{
				system( "cls" );
				cout << "******************* Eliminar Herramienta ***************************" << endl;
				cout << "Datos de la herramienta: " << endl;
				herramientaImprimir( ptrAEliminar );
				cout << "Deseas eliminar esta herramienta? (1-Si/0-No): ";
				cin >> opcion;
				if( opcion ){
					while( (*herramienta) -> siguiente != ptrAEliminar ){
						(*herramienta) = (*herramienta) -> siguiente;
					}
					(*herramienta) -> siguiente = ptrAEliminar -> siguiente;
					free( ptrAEliminar );
					cout << "Herramienta eliminada." << endl;
					return;
				}
				ptrAEliminar = ptrAEliminar -> siguiente;
			}while( ptrAEliminar != (*herramienta) );
			cout << "Herramienta no eliminada." << endl;
		}
	}
	else{
		cout << "No hay herramienta que eliminar." << endl;
	}
}

void proyectoGuardar()
{
	// Descriptor de archivo
	ofstream ptrArchivo;
	Proyecto * ptrPrAux = ptrListaProyectos;
	Persona * ptrPAux = NULL;
	Herramienta * ptrHAux = NULL;
	int size = 0; // Numero de colaboradores
	
	// La lista de proyectos tiene al menos un elemento
	if( ptrListaProyectos != NULL ){
		
		// Abrimos elarchivo
		ptrArchivo.open( "Proyecto.proy", ios_base::out );
		if ( !ptrArchivo ){
        	cout << "Problema al abrir archivo --> Proyecto.proy" <<endl;
        	return;
    	}
		
    	ptrPrAux = ptrListaProyectos;
   		do{
   			ptrArchivo << ptrPrAux -> codigo << endl; // Codigo
   			ptrArchivo << ptrPrAux -> nombre << endl; // Nombre
   			ptrArchivo << ptrPrAux -> responsable -> nombre << endl
   					   << ptrPrAux -> responsable -> apellidos << endl
   					   << ptrPrAux -> responsable -> telefono << endl
   					   << ptrPrAux -> responsable -> calle << endl
   					   << ptrPrAux -> responsable -> numeroExt << endl
   					   << ptrPrAux -> responsable -> codigoPostal << endl
   					   << ptrPrAux -> responsable -> municipio << endl
   					   << ptrPrAux -> responsable -> estado << endl;
   			
   			size = 0;
   			// Obtenemos la cantidad de colaboradores de ese proyecto
   			if( ptrPrAux -> colaboradores != NULL ){
   				ptrPAux = ptrPrAux -> colaboradores;
   				do{
   					size++;
   					ptrPAux = ptrPAux -> siguiente;
				}while( ptrPAux != ptrPrAux -> colaboradores );
			}
			
			// Guardamos el tamaño
			ptrArchivo << size << endl;
			
			// Guardamos los datos de los colaboradores
   			if( ptrPrAux -> colaboradores != NULL ){
   				ptrPAux = ptrPrAux -> colaboradores;
   				do{
   					ptrArchivo << ptrPAux -> nombre << endl
   					   		   << ptrPAux -> apellidos << endl
   					   		   << ptrPAux -> telefono << endl
   					   		   << ptrPAux -> calle << endl
   					   		   << ptrPAux -> numeroExt << endl
   					   	       << ptrPAux -> codigoPostal << endl
   					   		   << ptrPAux -> municipio << endl
   					   		   << ptrPAux -> estado << endl;
   					ptrPAux = ptrPAux -> siguiente;
				}while( ptrPAux != ptrPrAux -> colaboradores );
			}
			
			size = 0;
   			// Obtenemos la cantidad de herramientas
   			if( ptrPrAux -> herramientas != NULL ){
   				ptrHAux = ptrPrAux -> herramientas;
   				do{
   					size++;
   					ptrHAux = ptrHAux -> siguiente;
				}while( ptrHAux != ptrPrAux -> herramientas );
			}
			
			// Guardamos el tamaño
			ptrArchivo << size << endl;
			
			// Guardamos los datos de las herramientas
   			if( ptrPrAux -> herramientas != NULL ){
   				ptrHAux = ptrPrAux -> herramientas;
   				do{
   					ptrArchivo << ptrHAux -> nombre << endl
   					   		   << ptrHAux -> cantidad << endl
   					   		   << ptrHAux -> valorApreciado << endl
   					   		   << ptrHAux -> costoTotal << endl;
   					ptrHAux = ptrHAux -> siguiente;
				}while( ptrHAux != ptrPrAux -> herramientas );
			}
			
			ptrArchivo << ptrPrAux -> areaInvestigacion << endl
					   << ptrPrAux -> presupuesto << endl
					   << ptrPrAux -> situacion << endl
					   << ptrPrAux -> fecha << endl
					   << ptrPrAux -> descripcion << endl;
			
			ptrPrAux = ptrPrAux -> siguiente;
		}while( ptrPrAux != ptrListaProyectos );
		
		ptrArchivo.close();	
	}
}

/*void proyectoLeerArchivo()
{
	// Descriptor de archivo
	ifstream ptrArchivo;
	Proyecto proyecto;
	Persona persona;
	Herramienta herramienta;
	int i = 0;
	int size = 0; // Numero de colaboradores
	
	// La lista de proyectos tiene al menos un elemento
	if( ptrListaProyectos != NULL ){
		
		// Abrimos elarchivo
		ptrArchivo.open( "Proyecto.proy" );
		if ( !ptrArchivo.is_open() ){
        	cout << "Problema al abrir archivo --> Proyecto.proy" <<endl;
        	return;
    	}
    	
    	while( !ptrArchivo.eof() ){
    		ptrArchivo >> proyecto.codigo;
    		getline( ptrArchivo, proyecto.nombre );
    		cout << "Codigo: " << proyecto.codigo;
    		cout << "Nombre del proyecto " << proyecto.nombre;
    		
    		getline( ptrArchivo, proyecto.nombre );
    		getline( ptrArchivo, persona.apellidos );
    		getline( ptrArchivo, persona.telefono );
    		getline( ptrArchivo, persona.calle );
    		getline( ptrArchivo, persona.numeroExt );
    		getline( ptrArchivo, persona.codigoPostal );
    		getline( ptrArchivo, persona.municipio );
    		getline( ptrArchivo, persona.estado );
    		
    		cout << "Datos del responsable: " << endl;
    		cout << "Nombre:    " << persona.nombre;
    		cout << "Apellidos: " << persona.apellidos;
    		cout << "Telefono:  " << persona.telefono;
    		cout << "Calle:     " << persona.calle;
    		cout << "Numero:    " << persona.numeroExt;
    		cout << "C.P.       : " << persona.codigoPostal;
    		cout << "Municipio: " << imprimirMunicipio( persona.municipio );
    		cout << "Estado: " << imprimirEstados( persona.estado );
    		
    		cout << "Colaboradores del proyecto: " << endl;
    		ptrArchivo >> size;
    		for( i = 0; i < size; i++ ){
    			getline( ptrArchivo, proyecto.nombre );
    			getline( ptrArchivo, persona.apellidos );
    			getline( ptrArchivo, persona.telefono );
    			getline( ptrArchivo, persona.calle );
    			getline( ptrArchivo, persona.numeroExt );
    			getline( ptrArchivo, persona.codigoPostal );
    			getline( ptrArchivo, persona.municipio );
    			getline( ptrArchivo, persona.estado );
    			
    			cout << "Nombre:    " << persona.nombre;
    			cout << "Apellidos: " << persona.apellidos;
    			cout << "Telefono:  " << persona.telefono;
    			cout << "Calle:     " << persona.calle;
    			cout << "Numero:    " << persona.numeroExt;
    			cout << "C.P.       : " << persona.codigoPostal;
    			cout << "Municipio: " << imprimirMunicipio( persona.municipio );
    			cout << "Estado: " << imprimirEstados( persona.estado ); cout << endl;
			}
			
			cout << "Herramientas utilizadas: " << endl;
			ptrArchivo >> size;
			for(i = 0; i < size; i++){
				getline( ptrArchivo, herramienta.nombre );
    			getline( ptrArchivo, herramienta.cantidad );
    			getline( ptrArchivo, herramienta.valorApreciado );
    			getline( ptrArchivo, herramienta.costoTotal );
    			
    			cout << "Nombre  : " << herramienta.nombre;
    			cout << "Cantidad: " << herramienta.cantidad;
    			cout << "Precio por unidad: " << herramienta.valorApreciado;
    			cout << "Costo total:  " << herramienta.costoTotal;
			}
			
			getline( ptrArchivo, proyecto.areaInvestigacion );
			getline( ptrArchivo, proyecto.presupuesto );
			getline( ptrArchivo, proyecto.situacion );
			getline( ptrArchivo, proyecto.fecha );
		}
		
		ptrArchivo.close();	
	}
}*/

// Cargar Estados de la Republica
bool cargarEstados( void )
{
	presentacion();
	std::cout << "Cargando Estados..." << std::endl;
	std::ifstream archivo;		// Descriptor de archivo
	std::size_t largoString;	// Largo de string, se usara más adelante
	std::string linea;

	// Intentamos abrir archivo
	archivo.open( "Estados.dat" );
	if( !archivo.is_open() ){
		std::cout << "Error. Es necesario el archivo \"info\\Estados.dat\"" << std::endl;
		return false;
	}

	// Carga los estados de la republica
	for( int i = 0; i < NUMERO_ESTADOS; i++ ){
		// Obtenemos el largo del string
		archivo >> largoString;

		// Obtenemos el limite de municipios
		archivo >> estados[ i ].inicio;
		archivo >> estados[ i ].fin;

		// Creamos espacio para guardar el estado
		estados[ i ].nombre = ( char * )std::malloc( largoString );

		// Obtenemos la linea
		std::getline( archivo, linea );

		// Copiamos la linea al arreglo
		std::strcpy( estados[i].nombre, linea.c_str() );
	}

	// Cerramos el archivo
	archivo.close();

	return true;
} // Fin

// Cargar Estados de la Republica
bool cargarMunicipios()
{
	presentacion();
	std::cout << "Cargando Municipios" << std::endl;
	std::ifstream archivo;		// Descriptor de archivo
	std::size_t largoString;	// Largo de string, se usara más adelante
	std::string linea;

	// Intentamos abrir archivo
	archivo.open( "Municipios.dat" );
	if( !archivo.is_open() ){
		std::cout << "Error. Es necesario el archivo \"info\\Municipios.dat\"" << std::endl;
		return false;
	}

	// Carga los estados de la republica
	for( int i = 0; i < NUMERO_MUNICIPIOS; i++ ){
		// Obtenemos el largo del string
		archivo >> largoString;

		// Creamos espacio para guardar el estado
		ptrMunicipios[ i ] = ( char * )std::malloc( largoString + 1 );

		// Obtenemos la linea
		std::getline( archivo, linea );

		// Copiamos la linea al arreglo
		std::strcpy( ptrMunicipios[i], linea.c_str() );
	}

	// Cerramos el archivo
	archivo.close();

	return true;
} // Fin

int seleccionarEstado( void )
{
    int opcion;
    do{
        system( "cls" );
        std::cout << "Seleccionar Estado: " << std::endl;
        for( int i= 0; i < NUMERO_ESTADOS; i += 2 ){
            std::cout << (i + 1 < 10 ? " " : "" ) << i + 1 << " - " << estados[ i ].nombre << "\t\t\t"
                      << i + 2 << " - " << estados[ i + 1 ].nombre
                      << std::endl;
        }

        std::cout << "Escribe el numero del estado elegido: ";
        std::cin >> opcion;
    }while( opcion < 1 || opcion > 32 );

    return opcion - 1;
}

int seleccionarMunicipio( int estado )
{
	// El estado dado es un estado valido
	if( estado >= 0 && estado <= 31 ){
        int opcion;

		// Establecemos una variable límite (solo por optimización)
		int inicio =  estados[ estado ].inicio;
		int limite = estados[ estado ].fin;


        // Imprime el Estado y los municipios
        do{
            system( "cls" );
            std::cout << "Seleccionar Municipio: " << std::endl;
            for( int i = inicio; i <= limite; i++ )
                std::cout << i + 1 << " - " << ptrMunicipios[ i ] << std::endl;

            std::cout << "Escribe el numero del municipio elegido: ";
            std::cin >> opcion;
            opcion--;
        }while( opcion < inicio || opcion > limite );

        return opcion;
	}

	return -1;
}

void imprimirEstado( int codigo )
{
    // El código se encuentra en un rango adecuado
    if( codigo >= 0 && codigo < NUMERO_ESTADOS ){
        std::cout << estados[ codigo ].nombre << std::endl;
    }
}

void imprimirMunicipio( int codigo )
{
    // El código se encuentra en un rango adecuado
    if( codigo >= 0 && codigo < NUMERO_MUNICIPIOS ){
        std::cout << ptrMunicipios[ codigo ] << std::endl;
    }
}

void establecerFecha()
{
	// Obtiene la fecha
	time_t t = time( NULL );
	struct tm tiempo = *localtime( &t );
	
	// La establece
	dia = tiempo.tm_mday;
	mes = tiempo.tm_mon + 1;
	anio = tiempo.tm_year + 1900;
}

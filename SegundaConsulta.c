#include <stdio.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>

//Programa que devuelve el numero de partidas ganadas por un jugador introducido como parámetro y a su vez devuelve la puntuacion acumulada que tiene.
int main(int argc, char *argv[]) {
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//Inicializamos la conexion
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "datos_juego",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//Empezazmos coon la consulta como tal
	char Nombre[20];
	printf ("Introduzca el nombre del jugador: \n");
	scanf ("%s", Nombre);
	char consultando1 [300];
	strcpy (consultando1, "SELECT JUGADOR.ID FROM (JUGADOR,PARTIDA,DATOS) WHERE JUGADOR.NOMBRE ='");
	strcat (consultando1, Nombre);
	strcat (consultando1,"'AND JUGADOR.ID = DATOS.ID_J AND DATOS.ID_P = PARTIDA.ID AND PARTIDA.GANADOR ='");
	strcat (consultando1, Nombre);
	strcat (consultando1,"'");
	
	err=mysql_query (conn, consultando1);
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	resultado = mysql_store_result (conn);
	row = mysql_fetch_row (resultado);
	int counter;
	int linea;
	if (row == NULL)
		printf ("No se ha podido obtener datos de la consulta\n");
	else
		while (row !=NULL) {
			counter = counter + 1;
			row = mysql_fetch_row (resultado);
		}
	
		printf("El jugdor: %s ha ganado: %i partidas",Nombre,counter);
		mysql_close (conn);
		exit(0);
}

		
		
		
		
		
		
		

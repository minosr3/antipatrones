#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include "winbgim.h"
#define N 4

using namespace std;

void DibujarTablero();
void AsignarVector();
void RandomFichas();
void VerificarLleno();
void Arriba1();
void Abajo1();
void Derecha1();
void Izquierda1();
void Puntaje();
void ComprobarDOV();

/*
int MatrizEntrada[N][N]={
	{0,0,0,2},
	{0,0,0,2},
	{0,2048,0,2},
	{0,0,0,2}
};
*/
int MatrizEntrada[N][N]={
	{4,2,4,2},
	{2,4,2,4},
	{8,2,4,2},
	{16,32,16,4}
};

int c,d,v,w,x,y,cuax,cuay,movitab,juego=0,tecla,movim=0,movimok,band1=0,lleno,detener,final=0;
int M = N-2;
int estadoJuego = 0; //0 Jugando, 1 Gano, -1 Perdio

int numeroGanador = 2048; //ESTe es el numero con el que se gana (Poner a 2048)

int numeroMovimientos = 0; //Con esta variable se asigna el nivel al jugador

const string nombreArchivo ="puntajes.txt";

void vaciaMatriz()
{
  	for(x=0;x<N;x++){
	 for(y=0;y<N;y++){	
	  MatrizEntrada[x][y]=0;	
    }
   }
 } 

void recortarString(string in,string &nombre,int &puntaje)
{
  int posEspacio = in.find(" ");
  
  nombre = in.substr(0,posEspacio);//copia de 0 hasta la posicion del espacio
  puntaje = atoi(in.substr(posEspacio+1,in.length()).c_str() ) ;//Copia el resto
 }

int main(int argc, char** argv) {					

	//Pintar Pantalla de Inicio	
	initwindow(700, 700);
	srand(time(NULL));
	DibujarTablero();
	vaciaMatriz();
	RandomFichas();
 	RandomFichas();
	AsignarVector();
	srand(time(NULL));
	stringstream ss;
	do{
		
	   ComprobarDOV();//Actualiza la variable estadoJuego

	   
	    if(estadoJuego!=0)	
			break;
			 
		VerificarLleno(); //Actualiza la variable Lleno (Con esto sabemos si agregar o no fichas)
		
		tecla=getch();
		
		switch(tecla){			
			case KEY_UP:
				if(lleno==0){
					cleardevice();
					Arriba1();
					Arriba1();
					Arriba1();
				    RandomFichas();
				    numeroMovimientos++;
					DibujarTablero();
					AsignarVector();
				}else{				
					cleardevice();
					Arriba1();
					Arriba1();
					Arriba1();
					numeroMovimientos++;
					DibujarTablero();
					AsignarVector();	
				}
			break;
			
			case KEY_DOWN:
				if(lleno==0){
					cleardevice();
					Abajo1();
					Abajo1();
					Abajo1();
					RandomFichas();
					numeroMovimientos++;
					DibujarTablero();
					AsignarVector();
				}else{
					cleardevice();
					Abajo1();
					Abajo1();
					Abajo1();
					numeroMovimientos++;
					DibujarTablero();
					AsignarVector();	
				}
			break;
			
			case KEY_LEFT:
				if(lleno==0){
					cleardevice();
					Izquierda1();
					Izquierda1();
					Izquierda1();
					RandomFichas();
					numeroMovimientos++;
					DibujarTablero();
					AsignarVector();
				}else{
					cleardevice();
					Izquierda1();
					Izquierda1();
					Izquierda1();
					numeroMovimientos++;
					DibujarTablero();
					AsignarVector();	
				}
			break;
			
			case KEY_RIGHT:
				if(lleno==0){
					cleardevice();
					Derecha1();
					Derecha1();
					Derecha1();
					RandomFichas();
					numeroMovimientos++;
					DibujarTablero();
					AsignarVector();
				}else{
					cleardevice();
					Derecha1();
					Derecha1();
					Derecha1();
					numeroMovimientos++;
					DibujarTablero();
					AsignarVector();		
				}
			break;

			case KEY_ESC:
				exit(0); // salir del programa		
		}			
	}while(final==0);
	
	
  while(final==0){
  cleardevice();
  int x = 100;
  int y = 200;
  
	if(estadoJuego==-1){
	 //Letrero de perdio
	 	setcolor(YELLOW);
		settextstyle(1,0,3);
		stringstream ss;
		ss<<"Perdiste con : "<<(numeroMovimientos)<<" Movimientos";
		
		string msg = ss.str();
		outtextxy(x,y+50,msg.c_str());
		tecla=getch();
	}
	else
	{
	 //Letrero de gano
	 	setcolor(BLUE);
		settextstyle(2,0,10);
		stringstream ss;
		ss<<"¡Lo Lograste!";
		string msg = ss.str();
		outtextxy(x,y-120,msg.c_str());
		
	    
		settextstyle(2,0,9);
		ss.str("");
		ss<<"Con: "<<(numeroMovimientos)<<" Movimientos";
	    msg = ss.str();
		outtextxy(x,y-50,msg.c_str());
		
		setcolor(RED);
	    msg = "Los mejores puntajes son: ";
		outtextxy(x,y+10,msg.c_str());
		
		ifstream archivo(nombreArchivo.c_str());
		
		if(archivo.is_open()){
			
		//Con esto se almacenan los puntajes y nombres por si hay que hacer alguna modificacion
		int mejorPuntaje[5];
	    string nombrePuntaje[5];
	    	
			
		  int numLinea = 0;
		  string linea;
		  
		  bool puntajeMayor = false; // es verdadera si el puntaje Obtenido es menor que alguno de los anteriores
		  int pos = -1; //almacena la posicion en la que el jugador actual fue mejor que el otro
		  
		  setcolor(YELLOW);
		    while(getline(archivo,linea)){
		     recortarString(linea,nombrePuntaje[numLinea],mejorPuntaje[numLinea]); //Guarda el nombre y el puntaje para modificarlo mas facil
		     
		      if(numeroMovimientos<mejorPuntaje[numLinea] && pos == -1){ //Solo se muestra que le gano a uno
		     	 puntajeMayor = true;
		     	 pos = numLinea;
		     	 linea+="---->(Le ganaste)";
		     	 setcolor(BLUE);
		     	 outtextxy(x,y+60*(numLinea+1),linea.c_str());
		     	 setcolor(YELLOW);
		      }
			  else 
			   outtextxy(x,y+60*(numLinea+1),linea.c_str());
			 
			 numLinea++;	
		   }
		   
		   if(pos!=-1)//Le gano a algun jugador
		   {
		   	//Que ingrese su nombre
		   	string linea = "Ingresa tu nombre y presiona Enter";
		   	setcolor(GREEN);
		   	outtextxy(x,y+350,linea.c_str());
		   	linea="";
		   	char key='0';
		   	
		   	while(key!=KEY_ENTER){	
		   	 key  = getch();
		   	 if(key!=' ')
		        linea+=key;
			 outtextxy(x,y+450,linea.c_str());		
			}
		   	//Reemplazarlo el el archivo
		   	
		   	nombrePuntaje[pos] = linea; //guarda el nombre
		   	mejorPuntaje[pos] = numeroMovimientos;
		   	
		   	ofstream archivoSalida;
		   	archivoSalida.open(nombreArchivo.c_str());
		   	 for(int a = 0; a < 5; a++){
		   	  archivoSalida<<nombrePuntaje[a]<<" "<<mejorPuntaje[a]<<"\n"; 	
			}
		   	archivoSalida.close();
		   	
		   }
		   else{//No le gano a ninguno
		    string linea = "No alcanzaste a ganarles, intentalo nuevamente!";
		     setcolor(GREEN);
		   	 outtextxy(x,y+400,linea.c_str());
		   	 tecla = getch();
		   }
		   
		 archivo.close();	
		}
		else
		{
		 string msg = "ERROR ABRIENDO EL FICHERO, Contacte al administrador";
		 outtextxy(0,500,msg.c_str());	
		 tecla = getch();
		}
		
	}
	return 0;
  }
  
//	closegraph();
	return 0;
}
//***************************************************FUNCIONES*************************************************************//

void ComprobarDOV(){

	int X00=MatrizEntrada[0][0];
	int X01=MatrizEntrada[0][1];
	int X02=MatrizEntrada[0][2];
	int X03=MatrizEntrada[0][3];
	int X10=MatrizEntrada[1][0];
	int X11=MatrizEntrada[1][1];
	int X12=MatrizEntrada[1][2];
	int X13=MatrizEntrada[1][3];
	int X20=MatrizEntrada[2][0];
	int X21=MatrizEntrada[2][1];
	int X22=MatrizEntrada[2][2];
	int X23=MatrizEntrada[2][3];
	int X30=MatrizEntrada[3][0];
	int X31=MatrizEntrada[3][1];
	int X32=MatrizEntrada[3][2];
	int X33=MatrizEntrada[3][3];
	
			if(
			X00!=X10&&X10!=X20&&X20!=X30&&X30!=X31&&X31!=X32&&X32!=X33&&X33!=X23&&X23!=X13&&X13!=X03&&X03!=X02&&X02!=X01&&X01!=X00&&X11!=X12&&X12!=X22&&X22!=X21&&X21!=X11&&X11!=X01&&X11!=X10&&X12!=X02&&X12!=X13&X22!=X23&&X22!=X32&&X21!=X31&&X21!=X20
			){
	
				estadoJuego = -1; //PERDIO
				return;
			}
			
			for(int x=0;x<N;x++){
			  for(int y=0;y<N;y++){	
			    if(MatrizEntrada[x][y]==numeroGanador) {
			      estadoJuego = 1; //GANO
			   	  return;
			   }
			  }
			}
 estadoJuego = 0; //No ha pasado nada		
}


void DibujarTablero(){
	int cuax=9,cuay=9,movitab=0;
	int dibx=0,diby=0;
	
	
	setcolor( BLUE );
	rectangle(0, 0, 449, 449);
	setfillstyle(SOLID_FILL, BLUE);
	floodfill(5, 5, BLUE);

	for(dibx=0;dibx<N;dibx++){
		for(diby=0;diby<N;diby++){
			setcolor( LIGHTGRAY );
			rectangle(cuax+movitab, cuay, cuax+movitab+100, cuay+100);
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			floodfill(cuax+movitab+1, cuay+1, LIGHTGRAY);		
			movitab=movitab+110;
		}
		movitab=0;
		cuax=9;
		cuay=cuay+110;
	}
}

void AsignarVector(){
	int x=0,y=0;
	int v=40,w=40;
	
	settextstyle(2,0,10);
	stringstream ss;
	ss<<"Numero de movimientos: "<<numeroMovimientos;
	outtextxy(10,450,ss.str().c_str());
	
	ss.str("");
	setcolor(YELLOW);
	ss<<"Meta: "<<numeroGanador;
	outtextxy(500,100,ss.str().c_str());
	
	for(x=0;x<N;x++){
		for(y=0;y<N;y++){
			switch (MatrizEntrada[x][y]){
			
			case 0:
				setcolor(RED);
				settextstyle(2,0,10);
				outtextxy(v,w,"0");
			break;
			
			case 2:
				setcolor(BLACK);
				settextstyle(2,0,10);
				outtextxy(v,w,"2");
			break;
			
			case 4:
				setcolor(BLACK);
				settextstyle(2,0,10);
				outtextxy(v,w,"4");
			break;
			
			case 8:
				setcolor(BLACK);
				settextstyle(2,0,10);
				outtextxy(v,w,"8");
			break;
			
			case 16:
				setcolor(BLUE);
				settextstyle(2,0,10);
				outtextxy(v,w,"16");
			break;
			
			case 32:
				setcolor(BLACK);
				settextstyle(2,0,10);
				outtextxy(v,w,"32");
			break;
	
			case 64:
				setcolor(BLACK);
				settextstyle(2,0,10);
				outtextxy(v,w,"64");
			break;
			
			case 128:
				setcolor(BLACK);
				settextstyle(2,0,10);
				outtextxy(v,w,"128");
			break;
			
			case 256:
				setcolor(BLACK);
				settextstyle(2,0,10);
				outtextxy(v,w,"256");
			break;
			
			case 512:
				setcolor(BLUE);
				settextstyle(2,0,10);
				outtextxy(v,w,"512");
				break;
			
			case 1024:
				setcolor(BLACK);
				settextstyle(2,0,10);
				outtextxy(v,w,"1024");
				break;
			
			case 2048:
				setcolor(YELLOW);
				settextstyle(2,0,9);
				outtextxy(v-20,w,"2048");
				break;
			}
			v=v+110;		
		}
		v=40;
		w=w+110;
	}

}

void RandomFichas(){
	
	bool cambio = false;
	
	for(x=0;x<N;x++){
		for(y=0;y<N;y++){
		   if(MatrizEntrada[x][y]==0){
		     int a = (int)rand()%100;
		   	 	if(a%2==0){					
		          MatrizEntrada[x][y]=2;
		          cambio = true;
		          break;
		       }
	     	}
		 }
		 if(cambio)
		 	break;
	}
	if(cambio)
		return;
    else
    RandomFichas(); //No se hizo ningun cambio en la matriz
	
}

void VerificarLleno(){
lleno = 1;
	for(int x=0;x<N;x++){
		for(int y=0;y<N;y++){
	    	if(MatrizEntrada[x][y]==0){
				lleno=0;	
				return;
			}
	   }
	}
}


//Izquierda
void Izquierda1(){
	int x=0,y=0;
	
	for(x=0;x<=N-1;x++){
		for(y=0;y<N-1;y++){
			if(MatrizEntrada[x][y]==0&&MatrizEntrada[x][y+1]!=0){
				MatrizEntrada[x][y]=MatrizEntrada[x][y+1];
				MatrizEntrada[x][y+1]=0;
				
			}else if(MatrizEntrada[x][y]==MatrizEntrada[x][y+1]){
				MatrizEntrada[x][y]=MatrizEntrada[x][y]+MatrizEntrada[x][y+1];
				MatrizEntrada[x][y+1]=0;
				
			}else if(MatrizEntrada[x][y]!=0&&MatrizEntrada[x][y+1]==0){
				MatrizEntrada[x][y]=MatrizEntrada[x][y];
				MatrizEntrada[x][y+1]=MatrizEntrada[x][y+1];
				
				
			}else if(MatrizEntrada[x][y]!=0&&MatrizEntrada[x][y+1]!=0&&MatrizEntrada[x][y]!=MatrizEntrada[x][y+1]){
				MatrizEntrada[x][y+1]=MatrizEntrada[x][y+1];
				MatrizEntrada[x][y]=MatrizEntrada[x][y];
			}
		}
	}
}

//Derecha
void Derecha1(){
	int x=3,y=3;
	
	for(x=3;x>=0;x--){
		for(y=3;y>0;y--){
			if(MatrizEntrada[x][y]==0&&MatrizEntrada[x][y-1]!=0){
				MatrizEntrada[x][y]=MatrizEntrada[x][y-1];
				MatrizEntrada[x][y-1]=0;
				
			}else if(MatrizEntrada[x][y]==MatrizEntrada[x][y-1]){
				MatrizEntrada[x][y]=MatrizEntrada[x][y]+MatrizEntrada[x][y-1];
				MatrizEntrada[x][y-1]=0;
				
			}else if(MatrizEntrada[x][y]!=0&&MatrizEntrada[x][y-1]==0){
				MatrizEntrada[x][y]=MatrizEntrada[x][y];
				MatrizEntrada[x][y-1]=MatrizEntrada[x][y-1];
				
				
			}else if(MatrizEntrada[x][y]!=0&&MatrizEntrada[x][y-1]!=0&&MatrizEntrada[x][y]!=MatrizEntrada[x][y-1]){
				MatrizEntrada[x][y-1]=MatrizEntrada[x][y-1];
				MatrizEntrada[x][y]=MatrizEntrada[x][y];
			}
		}
	}
}

//Arriba
void Arriba1(){
	int x=0,y=0;
	
	for(y=0;y<=N-1;y++){
		for(x=0;x<N-1;x++){
			if(MatrizEntrada[x][y]==0&&MatrizEntrada[x+1][y]!=0){
				MatrizEntrada[x][y]=MatrizEntrada[x+1][y];
				MatrizEntrada[x+1][y]=0;
				
			}else if(MatrizEntrada[x][y]==MatrizEntrada[x+1][y]){
				MatrizEntrada[x][y]=MatrizEntrada[x][y]+MatrizEntrada[x+1][y];
				MatrizEntrada[x+1][y]=0;
				
			}else if(MatrizEntrada[x][y]!=0&&MatrizEntrada[x+1][y]==0){
				MatrizEntrada[x][y]=MatrizEntrada[x][y];
				MatrizEntrada[x+1][y]=MatrizEntrada[x+1][y];
				
				
			}else if(MatrizEntrada[x][y]!=0&&MatrizEntrada[x+1][y]!=0&&MatrizEntrada[x][y]!=MatrizEntrada[x+1][y]){
				MatrizEntrada[x+1][y]=MatrizEntrada[x+1][y];
				MatrizEntrada[x][y]=MatrizEntrada[x][y];
			}
		}
	}
}

//Abajo
void Abajo1(){
	int x=3,y=3;
	
	for(y=3;y>=0;y--){
		for(x=3;x>0;x--){
			if(MatrizEntrada[x][y]==0&&MatrizEntrada[x-1][y]!=0){
				MatrizEntrada[x][y]=MatrizEntrada[x-1][y];
				MatrizEntrada[x-1][y]=0;
				
			}else if(MatrizEntrada[x][y]==MatrizEntrada[x-1][y]){
				MatrizEntrada[x][y]=MatrizEntrada[x][y]+MatrizEntrada[x-1][y];
				MatrizEntrada[x-1][y]=0;
				
			}else if(MatrizEntrada[x][y]!=0&&MatrizEntrada[x-1][y]==0){
				MatrizEntrada[x][y]=MatrizEntrada[x][y];
				MatrizEntrada[x-1][y]=MatrizEntrada[x-1][y];
				
				
			}else if(MatrizEntrada[x][y]!=0&&MatrizEntrada[x-1][y]!=0&&MatrizEntrada[x][y]!=MatrizEntrada[x-1][y]){
				MatrizEntrada[x-1][y]=MatrizEntrada[x-1][y];
				MatrizEntrada[x][y]=MatrizEntrada[x][y];
			}
		}
	}
}


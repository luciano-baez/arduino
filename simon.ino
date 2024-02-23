  int rojo = 13;
  int amarillo = 12;
  int verde = 11;
  int azul = 10;
  int btn1 = 6;
  int btn2 = 5;
  int btn3 = 4;
  int btn4 = 3;
  int buzz = 7;
  int brojo, bamarillo, bverde, bazul;
 // secuancia mas grande a recordar
  const int max = 20; 
  int ULTcolor;
  int secuencia[max];
  int velocidad = 500;
  int valoraleatorio;
  bool resultado;


void setup()
{
  pinMode(rojo, OUTPUT);
  pinMode(amarillo, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(azul, OUTPUT);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  pinMode(btn4, INPUT_PULLUP);
  pinMode(buzz, OUTPUT);
  Serial.begin(9600);
  // generar semilla aleatoria para random
  // la semilla es primer numero de la secuencia de numeros aleatorios
  randomSeed(analogRead(0));
 // generarnum();
}

//FUNCIONES PARA LOS LEDS Y SONIDOS ------------------------------------------

void mostrarrojo(){
  digitalWrite(rojo, HIGH);
  tone(buzz, 7000, velocidad);
  delay (velocidad);
  digitalWrite(rojo, LOW);
}

void mostraramarillo(){
  digitalWrite(amarillo, HIGH);
  tone(buzz, 5000, velocidad);
  delay (velocidad); 
  digitalWrite(amarillo, LOW);
}

void mostrarverde(){
 digitalWrite(verde, HIGH);
  tone(buzz, 3000, velocidad);
  delay (velocidad); 
  digitalWrite(verde, LOW);
  
}

void mostrarazul(){
 digitalWrite(azul, HIGH);
  tone(buzz, 1000, velocidad);
  delay (velocidad); 
  digitalWrite(azul, LOW);

}

void perdiste(){
	tone(buzz,400,800);
  	Serial.println("--------------PERDISTE------------");

}

void ganaste(){
	tone(buzz,800,400);
  	Serial.println("--------------GANASTE-------------");
}

//FUNCIONES DEL JUEGO -------------------------------------------------------

void generarnum(){
  for (int i= 0; i < max; i++ ) {
    secuencia[i] = random(4);
    Serial.print(secuencia[i]);
    Serial.print(" ");
    Serial.println(i); 
    delay(20);
  }
}

void mostrarsec (int niv){
  for (int i= 0; i <= niv; i++ ){
    switch (secuencia[i]){
   	   case 0:
  	     mostrarrojo();
         delay (20);
         ULTcolor = 0;
         Serial.print("ultimo color mostrado: ");
         Serial.println(ULTcolor);
  	     break;
 	   case 1:
 	     mostraramarillo();
         delay (20);
         ULTcolor = 1;
         Serial.print("ultimo color mostrado: ");
         Serial.println(ULTcolor);
         break;
       case 2:
      	 mostrarverde();
         delay (20);
         ULTcolor = 2;
         Serial.print("ultimo color mostrado: ");
         Serial.println(ULTcolor);
         break;
       case 3:
      	 mostrarazul();
      	 delay (20);
         ULTcolor =3;
         Serial.print("ultimo color mostrado: ");
         Serial.println(ULTcolor);
      	 break;
    }
  }
}



int resultadoboton(){
  int btn = 0, estado = 0;
  while(estado == 0){
 	  if(digitalRead(btn1) == LOW){
         btn = 0;
         estado = 1;
         delay(200);
	  } 
      if(digitalRead(btn2) == LOW){
         btn = 1;
         estado = 1;
         delay(200);
	  }
	  if(digitalRead(btn3) == LOW){
         btn = 2;
         estado = 1;
         delay(200);
	  }
	   if(digitalRead(btn4) == LOW){
	     btn = 3;
         estado = 1;
         delay(200);
	  }
  }
  Serial.print("ESTADO");
  Serial.println(estado);
  Serial.print("BTN");
  Serial.println(btn);
  return btn;

}

void inicio(){
 generarnum();  
}  


bool jugar(){
 int nivel = 0, pos = 0, fin = 0, boton;
 bool res = false;
 while ((nivel < max) && (fin == 0)){
   mostrarsec(nivel);
   while ((pos <= nivel) && (fin == 0) ){
     boton = resultadoboton();
     Serial.print(boton);
     Serial.print(" ");
     Serial.println(secuencia[pos]);
     if(boton == secuencia[pos]){
       pos++;
       Serial.print("pos: ");
       Serial.println(pos);
       Serial.print("nivel: ");
       Serial.println(nivel);
     }else{
   		fin = 1;
     }
   
    }
   nivel++;
  }
  if (fin == 0){
    res = true;
  }
 return res;
} 

void mostrarresultadofinal(bool rest){
  if (rest == true){
    ganaste();
  }else{
  	 perdiste();
   }
}
  
void loop() {
  inicio();
  resultado = jugar();
  mostrarresultadofinal(resultado);
}

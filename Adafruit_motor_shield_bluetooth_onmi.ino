#include <AFMotor.h>
/*
Frequecia para canais 1 e 2 são: 
MOTOR12_64KHZ 
MOTOR12_8KHZ 
MOTOR12_2KHZ 
MOTOR12_1KHZ
Frequecia para canais 3 e 4 são:
MOTOR34_64KHZ 
MOTOR34_8KHZ 
MOTOR34_1KHZ
*/
AF_DCMotor motorDC1(1, MOTOR12_64KHZ);//Frente direito
AF_DCMotor motorDC2(2, MOTOR12_64KHZ);//Tras direito

AF_DCMotor motorDC3(3, MOTOR34_64KHZ);//Frente esquerdo
AF_DCMotor motorDC4(4, MOTOR34_64KHZ);//Tras esquerdo

int freq = 2;// variavel para setar a frequencia do motor 0 para 1KHz, 1 para 8KHz e 2 para 64KHz
int velocidade = 255;// velocidade geral
char command;
String string;

void setup(){
  Serial.begin(9600);
  
  motorDC1.setSpeed(velocidade); // regulando voltagem do motor para 100 se tem 1 volt  
  motorDC1.run(RELEASE);// parar motor 1

  motorDC2.setSpeed(velocidade); // regulando voltagem do motor para 100 se tem 1 volt
  motorDC2.run(RELEASE);// parar motor 2

  motorDC3.setSpeed(velocidade); // regulando voltagem do motor para 100 se tem 1 volt
  motorDC3.run(RELEASE);// parar motor 3

  motorDC4.setSpeed(velocidade); // regulando voltagem do motor para 100 se tem 1 volt
  motorDC4.run(RELEASE);// parar motor 4
}

void loop() 
{ 
    
   
    while(Serial.available() > 0)
    {
        command = (Serial.read());
        
        if(command == ':')
        {
            break;
        }
        
        else
        {
            string += command;

        }
        
        delay(1);
    }

  
   if (string == "Tras") {
       Serial.write("Tras\n");
       moverParaFrente();
   }
   else if (string == "Frente") {
       Serial.write("Frente\n");
       moverParaTras();
   }
   else if (string == "Esquerda"){
       Serial.write("Girar Anti-Horario\n");
       girarHorario();
   }   
   else if (string == "Direita"){
       Serial.write("Girar Horario\n");
       girarAntHorario();
   }     
   else if (string == "Parar"){
       Serial.write("Parar\n");
       pararMotores();
    }    
   else if (string == "Freq"){
       mudarFrequencia();
   }
   else if (string == "Diagonal"){
       Diagonal();
   }   
   else if (string.substring(0,1) == "V"){
       int i;
       i = string.substring(1).toInt();  
       Serial.write("Velocidade: ");
       Serial.print(i, DEC);
       Serial.write("\n");
       setVelocidade(i);
   }
   
   
   string = "";
   delay(20);
}


void mudarFrequencia(){
  if(freq == 0){
    freq = 1;
    AF_DCMotor motorDC1(1, MOTOR12_8KHZ); 
    AF_DCMotor motorDC2(2, MOTOR12_8KHZ);
    AF_DCMotor motorDC3(3, MOTOR34_8KHZ); 
    AF_DCMotor motorDC4(4, MOTOR34_8KHZ);
    Serial.write("Frequencia : 8KHz\n");
  }else if(freq == 1){
    freq = 2;
    AF_DCMotor motorDC1(1, MOTOR12_64KHZ); 
    AF_DCMotor motorDC2(2, MOTOR12_64KHZ);
    AF_DCMotor motorDC3(3, MOTOR34_64KHZ); 
    AF_DCMotor motorDC4(4, MOTOR34_64KHZ);
    Serial.write("Frequencia : 64KHz\n");
  }else if(freq == 2){
    freq=0;
    AF_DCMotor motorDC1(1, MOTOR12_1KHZ); 
    AF_DCMotor motorDC2(2, MOTOR12_1KHZ);
    AF_DCMotor motorDC3(3, MOTOR34_1KHZ); 
    AF_DCMotor motorDC4(4, MOTOR34_1KHZ);
    Serial.write("Frequencia : 1KHz\n");
  }
}

void pararMotores(){
  motorDC1.run(RELEASE);// parar motor 
  motorDC2.run(RELEASE);// parar motor
  motorDC3.run(RELEASE);// parar motor
  motorDC4.run(RELEASE);// parar motor
}

void moverParaFrente(){
    motorDC1.setSpeed(velocidade);
    motorDC2.setSpeed(velocidade);
    motorDC3.setSpeed(velocidade);
    motorDC4.setSpeed(velocidade);
    
    motorDC1.run(FORWARD);
    motorDC2.run(FORWARD);
    motorDC3.run(BACKWARD);
    motorDC4.run(BACKWARD);
}

void moverParaTras(){
    motorDC1.setSpeed(velocidade);
    motorDC2.setSpeed(velocidade);
    motorDC3.setSpeed(velocidade);
    motorDC4.setSpeed(velocidade);
    
    motorDC1.run(BACKWARD);
    motorDC2.run(BACKWARD);
    motorDC3.run(FORWARD);
    motorDC4.run(FORWARD);
}


void girarHorario(){
    motorDC1.setSpeed((velocidade));
    motorDC2.setSpeed((velocidade));
    motorDC3.setSpeed((velocidade));
    motorDC4.setSpeed((velocidade));
    
    motorDC1.run(FORWARD);
    motorDC2.run(FORWARD);
    motorDC3.run(FORWARD);
    motorDC4.run(FORWARD);
}

void girarAntHorario(){
    motorDC1.setSpeed((velocidade));
    motorDC2.setSpeed((velocidade));
    motorDC3.setSpeed((velocidade));
    motorDC4.setSpeed((velocidade));
    
    motorDC1.run(BACKWARD);
    motorDC2.run(BACKWARD);
    motorDC3.run(BACKWARD);
    motorDC4.run(BACKWARD);
}

void Diagonal(){
    motorDC1.setSpeed((velocidade));
    motorDC2.setSpeed((velocidade));
    motorDC3.setSpeed((velocidade));
    motorDC4.setSpeed((velocidade));
    
    motorDC1.run(FORWARD);
    motorDC2.run(RELEASE);
    motorDC3.run(RELEASE);
    motorDC4.run(FORWARD);
}

void setVelocidade(int NovaVelocidade){
    velocidade = NovaVelocidade;// velocidade geral
}

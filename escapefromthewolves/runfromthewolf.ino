
// dimensione matrice

int size=15;
int room[15][15] = {
              {0,0,1,1,1,1,1,1,0,1,0,1,0,1,1},
              {1,1,1,1,0,1,0,0,1,1,1,1,1,1,0},
              {0,1,1,0,0,1,1,1,1,1,0,0,1,1,1},
              {1,1,1,0,1,1,1,1,0,0,1,1,1,0,0},
              {1,0,1,1,1,0,0,1,1,1,0,0,1,1,1},
              {0,1,1,1,0,1,1,1,1,0,1,1,1,0,0},
              {1,1,1,0,1,1,0,1,1,1,0,1,1,1,1},
              {0,1,0,1,1,1,0,0,1,0,0,0,0,1,0},
              {1,1,1,1,1,1,1,0,1,1,0,0,0,1,0},
              {0,0,1,1,1,0,0,0,1,1,1,1,1,1,1},
              {1,1,1,1,0,1,1,1,1,0,0,0,0,0,1},
              {0,0,1,0,1,0,0,1,0,0,0,0,1,1,1},
              {1,1,1,0,1,0,1,1,1,0,0,0,0,1,0},
              {0,0,1,1,1,1,0,1,0,0,1,1,1,1,1},
              {1,1,1,0,0,0,0,0,0,0,0,1,0,1,1},
              };


//variabili sistema
int led1=10; //est.
int led2=11; //ovest.
int led3=12; // nord.
int led4=13; //sud. 
int led5=8;  // led verde.
int led6=9;  // led rosso.
int led7=7; //led blu
int botton1=2; 
int botton2=3;
int botton3=4;
int botton4=5;
int herox,heroy;
int keyx,keyy;
bool herokey=false;
// variabili gioco.
int wolfx[4];
int wolfy[4];
bool checkpos=false;
bool verify=false;
int end=false;
int wolfdice=0;



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);
pinMode(led3,OUTPUT);
pinMode(led4,OUTPUT);
pinMode(led5,OUTPUT);
pinMode(led6,OUTPUT);
pinMode(led7,OUTPUT);
pinMode(botton1,INPUT);
pinMode(botton2,INPUT);
pinMode(botton3,INPUT);
pinMode(botton4,INPUT);
randomSeed(analogRead(0));
              
}

void loop() {
  // put your main code here, to run repeatedly:
//Accensione led che segnalano l'inizializzazione.
Serial.println("Ciao");
checkpos=false;
verify=false;
end=false;
herokey=false;
int nwolves=0;
digitalWrite(led5,HIGH);
digitalWrite(led6,HIGH);
int exitx=0;
int exity=0;

while (room[exity][exitx]==0)
{
 exitx=random(0,size);
 exity=random(0,size);
}
Serial.println("Posizione uscita");
Serial.println(exitx);
Serial.println(exity);
while (nwolves==0)
{
  if (digitalRead(botton1)==HIGH) nwolves=1;
  if (digitalRead(botton2)==HIGH) nwolves=2;
  if (digitalRead(botton3)==HIGH) nwolves=3;
  if (digitalRead(botton4)==HIGH) nwolves=4;
}
Serial.println("lupi scelti");
Serial.println(nwolves);
if (nwolves==1) 
{
digitalWrite(led1,HIGH);
delay(3000);
}
if (nwolves==2) 
{
digitalWrite(led2,HIGH);
delay(3000);
}
if (nwolves==3) 
{
digitalWrite(led3,HIGH);
delay(3000);
}
if (nwolves==4) 
{
digitalWrite(led4,HIGH);
delay(3000);
}

int cont=0;
digitalWrite(led5,LOW);
digitalWrite(led6,LOW);
digitalWrite(led7,LOW);

while (cont<nwolves)
{
  int randNumber = random(4);
  //Serial.println(randNumber);
  int xwolf = random(0,size);
  int ywolf = random (0,size);

  
  if (room[ywolf][xwolf]==1)
  {
    wolfx[cont]=xwolf;
    wolfy[cont]=ywolf;
    cont=cont+1;
  Serial.println(xwolf);
  Serial.println(ywolf);
  }
  
}
Serial.println("Lupi piazzati");
while (checkpos==false)
{
//Serial.println("sono dentro");
do
{

herox=random(0,size);
heroy=random(0,size);


} while (room[heroy][herox]!=1 || (herox==exitx && heroy==exity));
verify=false;
Serial.println("Eroe piazzato");
Serial.println(herox);
Serial.println(heroy);
delay(2000);
for (int i=0;i<nwolves;i++)
{
if (herox==wolfx[i] && heroy==wolfy[i])
{
  verify=true;

}
if  (herox==exitx && heroy==exity) verify=true;
}
if (verify!=true)
{
checkpos=true;

}
}

keyx=random(0,size);
keyy=random(0,size);
while ((keyx==herox && keyy==heroy) || (keyx==exitx && keyy==exity)|| (room[keyy][keyx]==0))
{
keyx=random(0,size);
keyy=random(0,size);
}
Serial.println("posizione chiave");
Serial.println(keyx);    
Serial.println(keyy);    

delay(5000);
digitalWrite(led5,HIGH);
digitalWrite(led6,LOW);
delay(1000);
digitalWrite(led5,LOW);
digitalWrite(led6,LOW);

while (end==false)
{
//Serial.print("sono nel ciclo gioco");  
delay(200);
if (herox==size-1) digitalWrite(led2,LOW);
if (herox==0) digitalWrite(led1,LOW);
if (heroy==0) digitalWrite(led3,LOW);
if (heroy==size-1) digitalWrite(led4,LOW);


if (herox<size-1)
{
if (room[heroy][herox+1]==1)
{ 
digitalWrite(led2,HIGH);
}
else
{
digitalWrite(led2,LOW);
}

}
if (herox>0)
{
if (room[heroy][herox-1]==1)
{ 
digitalWrite(led1,HIGH);
}
else
{
digitalWrite(led1,LOW);
}

}
if (heroy>0)
{
if (room[heroy-1][herox]==1)
{ 
digitalWrite(led3,HIGH);
}
else
{
digitalWrite(led3,LOW);
}

}
if (heroy<size-1)
{
if (room[heroy+1][herox]==1)
{ 
digitalWrite(led4,HIGH);
}
else
{
digitalWrite(led4,LOW);
}

}

if (digitalRead(botton2) && digitalRead(led2))
{
  herox++;
  Serial.println("Ti sei mosso di x+1");
}
if (digitalRead(botton1) && digitalRead(led1))
{
  herox--;
  Serial.println("Ti sei mosso di x-1");
}
if (digitalRead(botton3) && digitalRead(led3))
{
  heroy--;
  Serial.println("Ti sei mosso di y-1");
}
if (digitalRead(botton4) && digitalRead(led4))
{
  heroy++;
  Serial.println("Ti sei mossi di y+1");
}
for (int j=0;j<nwolves;j++)
{
 wolfdice=random(0,4);
 if ((wolfdice==0) && (wolfx[j]<size-1)) 
 {
if (room[wolfy[j]][wolfx[j]+1]==1)  wolfx[j]++;
 }
 if ((wolfdice==1) && (wolfx[j]>0)) 
 {
if (room[wolfy[j]][wolfx[j]-1]==1) wolfx[j]--;
 }
 if ((wolfdice==2) && (wolfy[j]<size-1)) 
 {
if (room[wolfy[j]+1][wolfx[j]]==1) wolfy[j]++;
 }
 if ((wolfdice==3) && (wolfy[j]>0)) 
 {
if (room[wolfy[j]-1][wolfx[j]]==1) wolfy[j]--;


 }
Serial.println(j) ;  
Serial.println("Il lupo numero è nella posizione");
Serial.println(wolfx[j]);

Serial.println(wolfy[j]);

}
for (int k=0;k<nwolves;k++)
{
if (wolfx[k]==herox && wolfy[k]==heroy)

{
digitalWrite(led6,HIGH);
digitalWrite(led7,LOW);
digitalWrite(led5,LOW);

Serial.println("Il lupo ti ha preso");
delay(4000);
end=true;
checkpos=false;
digitalWrite(led1,LOW);
digitalWrite(led2,LOW);
digitalWrite(led3,LOW);
digitalWrite(led4,LOW);
digitalWrite(led5,LOW);
digitalWrite(led6,LOW);
}
}

if ((herox==keyx && heroy==keyy) && (herokey==false))
{
  herokey=true;
  Serial.println("chiave presa");
  delay(3000);
  digitalWrite(led7,HIGH);


}
if (herox==exitx && heroy==exity)

{
Serial.println("Hai trovato l'uscita"); 
if (herokey==true)
{ 
digitalWrite(led5,HIGH);
delay(4000);  
end=true;
checkpos=false;
digitalWrite(led1,LOW);
digitalWrite(led2,LOW);
digitalWrite(led3,LOW);
digitalWrite(led4,LOW);
digitalWrite(led5,LOW);
digitalWrite(led6,LOW);
}
else
{
int h=0;   
for (h=0;h<5;h++)
{
  Serial.println("cavolo");
  digitalWrite(led5,HIGH);
  delay(200);
  digitalWrite(led5,LOW);
}
}
}
} 

} 





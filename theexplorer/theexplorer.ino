// The explorer

int analogPin = A3;     // manopola del potenziometro (terminale centrale) connessa ad A3
                        // terminali esterni connessi a massa e +5V
int val = 0;            // variabile per conservare il valore letto
bool buttonval=false;
float alfa=0;
int naliens=2;
int ngaiser=1;
int nstorm=1;
int centeralienx[2]={0.15,1.5};
int centeralieny[2]={1.5,0.2};
int centergaiserx[2]={1};
int centergaisery[2]={1};
int centerstormx[2]={1.5};
int centerstormy[2]={1.5};
int led1=2;
int led2=3;
int led3=4;
int led4=5;
int led5=6;
int led6=7;
int led7=8;
int led8=9;
float x=1;
float y=1;
float v=0.01;
int button1=13;
int life=500;
int fuel=100;
bool stop=false;
int cont=0;
float prob;
int casual;
float basex1,basey1,basex2,basey2;
bool basecheck1=true;
bool basecheck2=true;


void aliens()

{
Serial.println("Sono l'alieno");
digitalWrite(led2,HIGH);
delay(1000);
casual= random(6);
if (casual>4)
{
digitalWrite(led5,HIGH);
delay(1000);
life=life-1;
digitalWrite(led5,LOW);


}

digitalWrite(led2,LOW);

}
void gaiser()

{
Serial.println("Gaiser");
digitalWrite(led3,HIGH);
delay(1000);
casual= random(6);
if (casual>4)
{
digitalWrite(led5,HIGH);
delay(1000);
life=life-1;
digitalWrite(led5,LOW);


}
digitalWrite(led3,LOW);

}

void storm()
{
Serial.println("Storm");
digitalWrite(led4,HIGH);
delay(1000);
casual= random(6);
if (casual>3)
{
digitalWrite(led5,HIGH);
delay(1000);
life=life-1;
digitalWrite(led5,LOW);


}

digitalWrite(led4,LOW);


}
void setup() 
{
  // put your setup code here, to run once:
 Serial.begin(9600); 
pinMode(led1,OUTPUT);
pinMode(button1,INPUT);
pinMode(led2,OUTPUT);
pinMode(led3,OUTPUT);
pinMode(led4,OUTPUT);
pinMode(led5,OUTPUT);
pinMode(led6,OUTPUT);
pinMode(led7,OUTPUT);
pinMode(led8,OUTPUT);
randomSeed(analogRead(0));
basex1=random(200);
basey1=random(200);
basex2=random(200);
basey2=random(200);
basex1=basex1/100;
basey1=basey1/100;
basex2=basex2/100;
basey2=basey2/100;

if ((basex1>x-0.2 && basex1<x+0.2) && (basey1>y-0.2 && basey1<y+0.2))
{
  basex1=0.2;
  basey1=0.2;
}

if ((basex2>x-0.2 && basex2<x+0.2) && (basey2>y-0.2 && basey2<y+0.2))
{
  basex2=1.8;
  basey2=1.8;
}
Serial.println(basex1);
Serial.println(basey1);
delay(1000);
Serial.println(basex2);
Serial.println(basey2);
delay(1000);

}

void loop() 
{
  // put your main code here, to run repeatedly:
 fuel=fuel-1; 
 val = analogRead(analogPin); 
//Serial.println(alfa);
alfa=(2*3.14/1023)*val;
if (life<=0)
{
  exit(0);
}
if (stop==false)
{
digitalWrite(led1,LOW);
delay(200);
x=x+v*cos(alfa);
y=y+v*sin(alfa);
Serial.println(x);
Serial.println(y);
//digitalWrite(led6,HIGH);
cont=cont+1;
if (x>2)
{
x=x-2;  
}
if (x<0)
{
x=x+2;  
}
if (y>2)
{
y=y-2;  
}
if (y<0)
{
y=y+2;  
}

digitalWrite(led1,HIGH);
}
if ((stop==true) && (digitalRead(button1)==HIGH) )
{
stop=false;
delay(500);
}
if (digitalRead(button1)==HIGH)
{
 Serial.println("ops");
 digitalWrite(led1,LOW);
 stop=true;
 delay(500);  
}
if ((stop==false) && (cont==10))
{
cont=0;
for (int i=0;i<naliens;i++)
{
prob=pow(2.718,-5*((centeralienx[i]-x)*(centeralienx[i]-x)+(centeralieny[i]-y)*(centeralieny[i]-y)))*100;
Serial.println(prob);
casual= random(100);
Serial.println(casual);
if (casual<prob)
{
aliens();
}
}
for (int i=0;i<ngaiser;i++)
{
prob=pow(2.718,-5*((centergaiserx[i]-x)*(centergaiserx[i]-x)+(centergaisery[i]-y)*(centergaisery[i]-y)))*100;
Serial.println(prob);
casual= random(100);
Serial.println(casual);
if (casual<prob)
{
gaiser();
}
}
for (int i=0;i<nstorm;i++)
{
prob=pow(2.718,-5*((centerstormx[i]-x)*(centerstormx[i]-x)+(centerstormy[i]-y)*(centerstormy[i]-y)))*100;
Serial.println(prob);
casual= random(100);
Serial.println(casual);
if (casual<prob)
{
storm();
}
}

}
if ((x>basex1-0.2 && x<basex1+0.2) && (y>basey1-0.2 && y<basey1+0.2) && (basecheck1==false)) 
{
  digitalWrite(led6,HIGH);
  Serial.println("Base1");
  fuel=fuel+100;
  Serial.println(basex1);
  Serial.println(basey1);
  basecheck1=true;
  delay(1000);
  
}
if ((x>basex2-0.2 && x<basex2+0.2) && (y>basey2-0.2 && y<basey2+0.2) && (basecheck2==false))
{
  digitalWrite(led7,HIGH);
  Serial.println("Base2");
  fuel=fuel+100;
  Serial.println(basex2);
  Serial.println(basey2);
  delay(1000);
  basecheck2=true;


}
if (digitalRead(led6) && digitalRead(led7))
{
delay(3000);
exit(0);
}
if (fuel<=20)
{
digitalWrite(led8,HIGH);
if (fuel<=0)
{
  exit(0);
}
}
delay(200);
}



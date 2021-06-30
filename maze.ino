#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
int LS1 =4;
int LS2 =7 ;
int RS1 = A1;
int RS2 =A0 ;
int FS = 3;
int FLS = A3;
int MS = A2;
int RM1 = 10;
int RM2 = 9;
int ENR = 8;
int ENL = 13;
int LM1 = 12;
int LM2 = 11;
int led=5;
char a[200];
char b[150];
int i, j,flag;
int m=0;

int k[200];
int switch_flag ;
int dryrun_switch = 0;
int actualrun_switch = 1;
int path_length;
int count;
int not_the_shortest;
int c=0;
void fwd()
{
  digitalWrite(LM1, HIGH);
  digitalWrite(RM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM2, LOW);
}

void back()
{
  digitalWrite(LM1, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM2, HIGH);
}

void stop()
{
  digitalWrite(LM1, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM2, LOW);
}

void TL()
{
  digitalWrite(LM1, LOW);
  digitalWrite(RM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM2, LOW);
}

void TR()
{
  digitalWrite(LM1, HIGH);
  digitalWrite(RM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM2, LOW);
}

void BR()
{
  digitalWrite(LM1, HIGH);
  digitalWrite(RM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM2, HIGH);
}

void BL()
{
  digitalWrite(LM1, LOW);
  digitalWrite(RM1, HIGH);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM2, LOW);
}

void setup()
{
  pinMode(LS1, INPUT);
  pinMode(LS2, INPUT);
  pinMode(RS1, INPUT);
  pinMode(RS2, INPUT);
  pinMode(FS, INPUT);
  pinMode(FLS, INPUT);
  pinMode(MS, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(ENL, OUTPUT);
  pinMode(ENR, OUTPUT);
  pinMode(dryrun_switch, INPUT);
  pinMode(actualrun_switch, INPUT);
  digitalWrite(dryrun_switch,1);
  digitalWrite(actualrun_switch,1);
lcd.begin();//Initializing display
lcd.backlight();
}

void loop()
{
  lcd.setCursor(0,0);
  int dryrun = digitalRead(dryrun_switch);
  int actualrun = digitalRead( actualrun_switch);
  lcd.print("Press Button");
  if ( dryrun == 0 && actualrun == 1)
  {
    switch_flag = 1;
    
  }
  else if ( dryrun == 1 && actualrun == 0)
  {
    switch_flag = 2;
   
  }
  
  if ( switch_flag == 1)
  {
    i=0;
    IR1();
  }

  if ( switch_flag == 2)
  {
    j=0;
    IR2();
  }

}

// 0 - MEANS WHITE
// 1 - MEANS BLACK

void short_path_algorithm()
{
  lcd.clear();
  lcd.setCursor(0,0);
  
  
  if (not_the_shortest == 1)
  {
    count = 0;
    
    j = 0;
    while(j <=path_length)
    {
      
      if (k[j] == 'L' && k[j + 1] == 'B' && k[j + 2] == 'L') //LBL
      {
        b[count] = 'S';
        count++;
        j=j+3;
      }
      else if (k[j] == 'R' && k[j + 1] == 'B' && k[j + 2] == 'L') //RBL
      {
        b[count] = 'B';
        count++;
        j=j+3;
      }
      else if (k[j] == 'L' && k[j + 1] == 'B' && k[j + 2] == 'R') //LBR
      {
        b[count] = 'B';
        count++;
        j=j+3;
      }
      else if (k[j] == 'L' && k[j + 1] == 'B' && k[j + 2] == 'S') //LBS
      {
        b[count] = 'R';
        count++;
        j=j+3;
      }
      else if (k[j] == 'S' && k[j + 1] == 'B' && k[j + 2] == 'L') //SBL
      {
        b[count] = 'R';
        count++;
        j=j+3;
      }
      else if ( k[j] == 'S' && k[j + 1] == 'B' && k[j + 2] == 'S')//SBS
      {
        b[count] = 'B';
        count++;
        j=j+3;
      }
      else
      {
        b[count] = k[j];
        count++;
        j++;
      }
      
    }
    for (int i = 0; k[i] != '\0'; i++)
    {
      k[i] = '\0'; 
    }
    for (i = 0; b[i] != '\0'; i++)
    {
      k[i] = b[i]; 
    lcd.setCursor(0,1);
    lcd.print(k[i]);
    
    
    path_length=i;
    }
    not_the_shortest=0;
    short_path_algorithm();
    
  }

  else
  {
    //not_the_shortest=0;
    for (i = 0; i < path_length; i++)
    {
      if (k[i] == 'B')
      {
        not_the_shortest = 1;
      }
    }
    if (not_the_shortest == 1)
    {
       for(int i=0; b[i] != '\0'; i++)
      {
        b[i] = '\0';
        
      }
      short_path_algorithm();
    }
    lcd.clear();
    lcd.print("Shortest Array");
    lcd.setCursor(0,1); 
    

   
    for(i=0;i<path_length;i++)
    {
      lcd.print(b[i]);
      delay(200);
    }
  }

}
void IR1()
{ 
  lcd.clear();
  lcd.print("Dry Run Started");
//   delay(300);
while(c<16)
{
  lcd.setCursor(c,1);

  //000111
  if(digitalRead(LS1) == 0 && digitalRead(LS2) == 0 && digitalRead(MS) == 0 && digitalRead(RS1) == 1 && digitalRead(RS2) == 1 && digitalRead(FS) == 1 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140); 
    BL();
    
    if(flag==0)
    { 
    a[i] = 'L';
    i = i + 1;
    flag=1;
    lcd.print('L');
    
    c++;
    }
  }
    
  
  //000110
  else if(digitalRead(LS1) == 0 && digitalRead(LS2) == 0 && digitalRead(MS) == 0 && digitalRead(RS1) == 1 && digitalRead(RS2) == 1 && digitalRead(FS) == 0 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);
    // RIGHT MOTOR SPEED (0-254)
    BL();
    
    if(flag==0)
    {
    a[i] = 'L';
    i = i + 1;
    flag=1;
    lcd.print('L'); 
    c++;
    }
    
  }
  //001110
  else if(digitalRead(LS1) == 0 && digitalRead(LS2) == 0 && digitalRead(MS) == 1 && digitalRead(RS1) == 1 && digitalRead(RS2) == 1 && digitalRead(FS) == 0 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    BL();
  }
  //001111
  else if(digitalRead(LS1) == 0 && digitalRead(LS2) == 0 && digitalRead(MS) == 1 && digitalRead(RS1) == 1 && digitalRead(RS2) == 1 && digitalRead(FS) == 1 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    BL();
   
  }
  //000000
  else if(digitalRead(LS1) == 0 && digitalRead(LS2) == 0 && digitalRead(MS) == 0 && digitalRead(RS1) == 0 && digitalRead(RS2) == 0 && digitalRead(FS) == 0 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    BL();
    
    if(flag==0)
    {
    
    a[i] = 'L';
    i = i + 1;
    flag=1;
    lcd.print('L');
     c++;
    }
     
  }
  //000001
  else if(digitalRead(LS1) == 0 && digitalRead(LS2) == 0 && digitalRead(MS) == 0 && digitalRead(RS1) == 0 && digitalRead(RS2) == 0 && digitalRead(FS) == 1 )
  {
    analogWrite(ENL, 130);   
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    BL();
    
    if(flag==0)
    {
    
    a[i] = 'L';
    i = i + 1;
    flag=1;
    lcd.print('L');
    
    c++;
    }
     
  }
  //000010
  else if(digitalRead(LS1) == 0 && digitalRead(LS2) == 0 && digitalRead(MS) == 0 && digitalRead(RS1) == 0 && digitalRead(RS2) == 1 && digitalRead(FS) == 0 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR,55);     // RIGHT MOTOR SPEED (0-254)
    BL();
    
  }
  //000011
  else if(digitalRead(LS1) == 0 && digitalRead(LS2) == 0 && digitalRead(MS) == 0 && digitalRead(RS1) == 0 && digitalRead(RS2) == 1 && digitalRead(FS) == 1 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    BL();
   
  }
  //100001
  else if(digitalRead(LS1) == 1 && digitalRead(LS2) == 0 && digitalRead(MS) == 0 && digitalRead(RS1) == 0 && digitalRead(RS2) == 0 && digitalRead(FS) == 1 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    BR();
    
  }  
  //100000
  else if(digitalRead(LS1) == 1 && digitalRead(LS2) == 0 && digitalRead(MS) == 0 && digitalRead(RS1) == 0 && digitalRead(RS2) == 0 && digitalRead(FS) == 0 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    fwd();
    if(flag==0)
    {
    
    a[i] = 'S';
    i = i + 1;
    flag=1;
    lcd.print('S');
    
    c++;
    }
    
  }  
  //110000
  else if(digitalRead(LS1) == 1 && digitalRead(LS2) == 1 && digitalRead(MS) == 0 && digitalRead(RS1) == 0 && digitalRead(RS2) == 0 && digitalRead(FS) == 0 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    fwd();
    if(flag==0)
    {
   
    a[i] = 'S';
    i = i + 1;
    flag=1;
    
    lcd.print('S');
    
    
    c++;
    }
    
  }
  //110001
  else if(digitalRead(LS1) == 1 && digitalRead(LS2) == 1 && digitalRead(MS) == 0 && digitalRead(RS1) == 0 && digitalRead(RS2) == 0 && digitalRead(FS) == 1 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    BR();
    if(flag==0)
    {
    
    a[i] = 'R';
    i = i + 1;
    flag=1;
    lcd.print('R');
    
    c++;
    }
     
  }
  //111110
  else if(digitalRead(LS1) == 1 && digitalRead(LS2) == 1 && digitalRead(MS) == 1 && digitalRead(RS1) == 1 && digitalRead(RS2) == 1 && digitalRead(FS) == 0 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    fwd();
  }
  //111111
  else if(digitalRead(LS1) == 1 && digitalRead(LS2) == 1 && digitalRead(RS1) == 1 && digitalRead(RS2) == 1 && digitalRead(FS) == 1 )
  {
    if(digitalRead(MS) == 1)
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    BR();
    if(flag==0)
    { 
    a[i] = 'B';
    i = i + 1;
    flag=1;
    lcd.print('B');
    
    c++;
    }
  }
  }
  //111000
  else if(digitalRead(LS1) == 1 && digitalRead(LS2) == 1 && digitalRead(MS) == 1 && digitalRead(RS1) == 0 && digitalRead(RS2) == 0 && digitalRead(FS) == 0 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    fwd();
   
  }
  //111001
  else if(digitalRead(LS1) == 1 && digitalRead(LS2) == 1 && digitalRead(MS) == 1 && digitalRead(RS1) == 0 && digitalRead(RS2) == 0 && digitalRead(FS) == 1)
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    BR();
    
  }
   //111101
  else if(digitalRead(LS1) == 1 && digitalRead(LS2) == 1 && digitalRead(MS) == 1 && digitalRead(RS1) == 1 && digitalRead(RS2) == 0 && digitalRead(FS) == 1)
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    BR();
    
  }
  //10011
  else if(digitalRead(LS1) == 1 && digitalRead(LS2) == 0 && digitalRead(MS) == 0 && digitalRead(RS1) == 1 && digitalRead(RS2) == 1)
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    BL();
  }
  //01111
  else if(digitalRead(LS1) == 0 && digitalRead(LS2) == 1 && digitalRead(MS) == 1 && digitalRead(RS1) == 1 && digitalRead(RS2) == 1  )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    BL();
  }
  //11011
  else if(digitalRead(LS1) == 1 && digitalRead(LS2) == 1 && digitalRead(MS) == 0 && digitalRead(RS1) == 1 && digitalRead(RS2) == 1)
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    fwd();
    flag=0;
  }
   //110110
  else if(digitalRead(LS1) == 1 && digitalRead(LS2) == 1 && digitalRead(MS) == 0 && digitalRead(RS1) == 1 && digitalRead(RS2) == 1 &&digitalRead(FS)==0)
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    fwd();
    
  }
  //11110
  else if(digitalRead(LS1) == 1 && digitalRead(LS2) == 1 && digitalRead(MS) == 1 && digitalRead(RS1) == 1 && digitalRead(RS2) == 0)
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    BR();
  }
  //11001
  else if(digitalRead(LS1) == 1 && digitalRead(LS2) == 1 && digitalRead(MS) == 0 && digitalRead(RS1) == 0 && digitalRead(RS2) == 1)
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    BR();
  }
  //0000000
  if(digitalRead(LS1) == 0 && digitalRead(LS2) == 0 && digitalRead(MS) == 0 && digitalRead(RS1) == 0 && digitalRead(RS2) == 0 && digitalRead(FS) == 0&& digitalRead(FLS)== 0 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    stop();
    c++;
    
    digitalWrite(led,HIGH);
  
    for (i = 0; a[i] != '\0'; i++)
    {
      k[i] = a[i];
      path_length = i;
    }
    goto label;
  }
  if(c>=16)
  {
    lcd.clear();
    c=0;
  }

}
label:short_path_algorithm();
}


void IR2()
{
  lcd.clear();
  lcd.print("actual run started");
  //000111
  if (digitalRead(LS1) == 0 && digitalRead(LS2) == 0 && digitalRead(MS) == 0 && digitalRead(RS1) == 1 && digitalRead(RS2) == 1 &&digitalRead(FS) == 1 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);
  if(flag==0)
  {
   if(b[j]=='L')
    {
      BL();
      flag=1;
      lcd.print(b[j]);
      j = j + 1;
    }
  } 
  }
  //000110
  else if(digitalRead(LS1) == 0 && digitalRead(LS2) == 0 && digitalRead(MS) == 0 && digitalRead(RS1) == 1 && digitalRead(RS2) == 1 &&digitalRead(FS) == 0 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
   if(flag==0)
  {
    if (b[j] == 'L')
    {
      BL();
      flag=1;
      lcd.print(b[j]);
      j = j + 1;
    }
    if (b[j] == 'S')
    {
      fwd();
      flag=1;
      lcd.print(b[j]);
      j = j + 1;
    }
  }
    
  }
  //001110
  else if(digitalRead(LS1) == 0 && digitalRead(LS2) == 0 && digitalRead(MS) == 1&& digitalRead(RS1) == 1 && digitalRead(RS2) == 1 &&digitalRead(FS) == 0 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    BL();
  }
  //001111
  else if(digitalRead(LS1) == 0 && digitalRead(LS2) == 0 && digitalRead(MS) == 1&& digitalRead(RS1) == 1 && digitalRead(RS2) == 1 &&digitalRead(FS) == 1 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    BL();
  }
  //000000
  else if(digitalRead(LS1) == 0 && digitalRead(LS2) == 0 && digitalRead(MS) == 0&& digitalRead(RS1) == 0 && digitalRead(RS2) == 0 &&digitalRead(FS) == 0)
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
   if(flag==0)
  { 
    if (b[j] == 'L')
    {
      BL();
      flag=1; 
      lcd.print(b[j]);
      j = j + 1;
    }
    if (b[j] == 'S')
    {
      fwd();
      flag=1;
      lcd.print(b[j]);
      j = j + 1;
    }
    if(b[j]=='R')
    {
      BR();
      flag=1;
      lcd.print(b[j]);
      j = j + 1;
    }
   }
  }
  //000001
  else if(digitalRead(LS1) == 0 && digitalRead(LS2) == 0 && digitalRead(MS) == 0&& digitalRead(RS1) == 0 && digitalRead(RS2) == 0 &&digitalRead(FS) == 1 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
   if(flag==0)
  {  
    if (b[j] == 'L')
    {
      BL();
      flag=1;
      lcd.print(b[j]);
      j = j + 1;
    }
    
    if(b[j]=='R')
    {
      BR();
      flag=1;
      lcd.print(b[j]);
      j = j + 1;
    }
  }
    
  }
  //000010
  else if(digitalRead(LS1) == 0 && digitalRead(LS2) == 0 && digitalRead(MS) == 0&& digitalRead(RS1) == 0 && digitalRead(RS2) == 1 &&digitalRead(FS) == 0 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    BL();
    
  }
  //000011
  else if(digitalRead(LS1) == 0 && digitalRead(LS2) == 0 && digitalRead(MS) == 0&& digitalRead(RS1) == 0 && digitalRead(RS2) == 1 &&digitalRead(FS) == 1 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    BL();
  }
  //100001
  else if(digitalRead(LS1) == 1 && digitalRead(LS2) == 0 && digitalRead(MS) == 0&& digitalRead(RS1) == 0 && digitalRead(RS2) == 0 &&digitalRead(FS) == 1 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    BR();
  }
  //100000
  else if(digitalRead(LS1) == 1 && digitalRead(LS2) == 0 && digitalRead(MS) == 0&& digitalRead(RS1) == 0 && digitalRead(RS2) == 0 &&digitalRead(FS) == 0 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    if(flag==0)
  { 
    if (b[j] == 'S')
    {
      fwd(); 
      flag=1;
      lcd.print(b[j]);
      j = j + 1;
    }
    if(b[j]=='R')
    {
      BR();
      flag=1;
      lcd.print(b[j]);
      j = j + 1;
    }
  }
  }
  //110000
  else if(digitalRead(LS1) == 1 && digitalRead(LS2) == 1 && digitalRead(MS) == 0&& digitalRead(RS1) == 0 && digitalRead(RS2) == 0 &&digitalRead(FS) == 0 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
   if(flag==0)
  { 
    if (b[j] == 'S')
    {
      fwd(); 
      flag=1;
      lcd.print(b[j]);
      j = j + 1;
    }
    if(b[j]=='R')
    {
      BR();
      flag=1;
      lcd.print(b[j]);
      j = j + 1;
    }
  }
  }
  //110001
  else if(digitalRead(LS1) == 1 && digitalRead(LS2) == 1 && digitalRead(MS) == 0&& digitalRead(RS1) == 0 && digitalRead(RS2) == 0 &&digitalRead(FS) == 1 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
   if(flag==0)
  {
    if(b[j]=='R')
    {
      BR();
      flag=1;
      lcd.print(b[j]);
      j = j + 1;
    }
  }
  }
  //111110
  else if(digitalRead(LS1) == 1 && digitalRead(LS2) == 1 && digitalRead(MS) == 1&& digitalRead(RS1) == 1 && digitalRead(RS2) == 1 &&digitalRead(FS) == 0 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    fwd();
  }
  //111111
  else if(digitalRead(LS1) == 1 && digitalRead(LS2) == 1 && digitalRead(MS) == 1&& digitalRead(RS1) == 1 && digitalRead(RS2) == 1 &&digitalRead(FS) == 1 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
   BL();
    
    //lcd.print(b[j]);
  }
  //111000
  else if(digitalRead(LS1) == 1 && digitalRead(LS2) == 1 && digitalRead(MS) == 1&& digitalRead(RS1) == 0 && digitalRead(RS2) == 0 &&digitalRead(FS) == 0 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
   fwd();
  }
  //111001
  else if(digitalRead(LS1) == 1 && digitalRead(LS2) == 1 && digitalRead(MS) == 1&& digitalRead(RS1) == 0 && digitalRead(RS2) == 0 &&digitalRead(FS) == 1)
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    BR();
  }
  //10011
  else if(digitalRead(LS1) == 1 && digitalRead(LS2) == 0 && digitalRead(MS) == 0&& digitalRead(RS1) == 1 && digitalRead(RS2) == 1)
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    BL();
  }
  //01111
  else if(digitalRead(LS1) == 0 && digitalRead(LS2) == 1 && digitalRead(MS) == 1&& digitalRead(RS1) == 1 && digitalRead(RS2) == 1  )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    BL();
  }
  //11011
  else if(digitalRead(LS1) == 1 && digitalRead(LS2) == 1 && digitalRead(MS) == 0&& digitalRead(RS1) == 1 && digitalRead(RS2) == 1)
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);
    // RIGHT MOTOR SPEED (0-254)
    fwd();
    flag=0;
  }
  //11110
  else if(digitalRead(LS1) == 1&& digitalRead(LS2) == 1 && digitalRead(MS) == 1&& digitalRead(RS1) == 1 && digitalRead(RS2) == 0)
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    BR();
  }
  //11001
  else if(digitalRead(LS1) == 1 && digitalRead(LS2) == 1 && digitalRead(MS) == 0&& digitalRead(RS1) == 0 && digitalRead(RS2) == 1)
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    BR();
  }
  //0000000
  if(digitalRead(LS1) == 0 && digitalRead(LS2) == 0 && digitalRead(MS) == 0&& digitalRead(RS1) == 0 && digitalRead(RS2) == 0 &&digitalRead(FS) == 0&& digitalRead(FLS)==0 )
  {
    analogWrite(ENL, 130);    // LEFT MOTOR SPEED (0-254)
    analogWrite(ENR, 140);     // RIGHT MOTOR SPEED (0-254)
    stop();
    
    digitalWrite(led,HIGH);
    //delay(1000);
    //digitalWrite(led,LOW);
    
  }
}

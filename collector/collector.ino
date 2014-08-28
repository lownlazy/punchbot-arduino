//in
int resetBtnPin = 1;
int startContactPin = 3;

//out
int reactionPin = 13;
int triggerPin = 3;

//encoder vars
volatile int segCounter = 0; 
volatile int segCountMax = 50; 
volatile unsigned long segArray0[50];
volatile unsigned long segArray1[50];
volatile unsigned long segArray2[50];
volatile unsigned long segArray3[50];
volatile int segPos[100];
unsigned long start = 550;
//volatile int pos = 0;

//vars
volatile int isOpen = 0;
int openState = 0;    
int lastOpenState = 0;  

void setup() {
 pinMode(triggerPin, INPUT);
  pinMode(resetBtnPin, INPUT);
  attachInterrupt(0,  encoderInterupt0R, RISING);
  attachInterrupt(0,  encoderInterupt0F, FALLING);
  attachInterrupt(1,  encoderInterupt1R, RISING);
  attachInterrupt(1,  encoderInterupt1F, FALLING);
 setup_T2();
 Serial.begin(9600);
}

void loop() 
{
  setIsOpen();
  
  if(isOpen == 0 )
  {
    start = micros();
    
    if(segCounter == 999)
    {
       Serial.println("reset");
    }
    
    //pos=0;
    segCounter=0;    
  }
  
  int resetBtnVal = analogRead(resetBtnPin);
  
  if(resetBtnVal > 700){
      reset();
    }

  if( segCounter == segCountMax) 
  {
      Serial.println(0);
      //remember: the time between 0 and index[0] is unknown and
      //should never be used for a calculation
      for (int i = 0; i < segCountMax; i++) 
      { 
        //todo:
        //find array with soonest acceleration loss
        //return that array 
        
        //unsigned long val = segArray[i] - start;      
        //Serial.println(val); 
      }
      
      Serial.print("end-");
      Serial.println(pos);
      
      segCounter = 999;
      isOpen = 0;  
  }

  //delay(50);
} 

// helpers -------------------

void reset()
{
   //pos=0;
   segCounter=0;
   Serial.println("reset");
}

void setIsOpen()
{
  float openVal = analogRead(startContactPin);
  isOpen = openVal<200?1:0;
}

//interupts--------------------

void encoderInterupt0R()
{
  if(segCounter < segCountMax) 
  {
     segArray[segCounter] = get_T2_count(); //micros();
     segCounter++;
     pos++;
  } 
}

void encoderInterupt0F()
{
  if(segCounter < segCountMax) 
  {
     segArray1[segCounter] = micros();
  } 
}

void encoderInterupt1R()
{
  if(segCounter < segCountMax) 
  {
     segArray2[segCounter] = micros();
  } 
}

void encoderInterupt1F()
{
  if(segCounter < segCountMax) 
  {
     segArray3[segCounter] = micros();
  } 
}




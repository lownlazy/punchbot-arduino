//in
int resetBtnPin = 1;
int startContactPin = 3;

//out
int reactionPin = 13;
int triggerPin = 3;

//encoder vars
volatile int segCounter = 0; 
volatile int segCountMax = 100; 
volatile float segArray0[100];
//volatile float segArray1[50];
//volatile float segArray2[50];
//volatile float segArray3[50];
//volatile int segPos[100];
unsigned long start = 0;

//vars
volatile int isOpen = 0;
//int openState = 0;    
//int lastOpenState = 0;  

void setup() {
 pinMode(triggerPin, INPUT);
  pinMode(resetBtnPin, INPUT);
  attachInterrupt(0,  encoderInterupt0R, CHANGE);
  attachInterrupt(1,  encoderInterupt0R, CHANGE);
  //attachInterrupt(0,  encoderInterupt0F, FALLING);
  //attachInterrupt(1,  encoderInterupt1R, RISING);
  //attachInterrupt(1,  encoderInterupt1F, FALLING);
 setup_T2();
 Serial.begin(9600);
}

void loop() 
{
  setIsOpen();
  
  if(isOpen == 0 )
  {
    start = get_T2_micros(); //micros();
    
    if(segCounter == 999)
    {
       Serial.println("reset");
    }
    
    segCounter=0;    
    reset_T2();
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
        
        float val = segArray0[i] - start;      
        Serial.println(val);
       delay(10);
 
      }
      
      Serial.println("end");
      
      segCounter = 999;
      isOpen = 0;  
      reset_T2();
  }

  //delay(50);
} 

// helpers -------------------

void reset()
{
   segCounter=0;
   Serial.println("reset");
   reset_T2();
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
     segArray0[segCounter] = get_T2_micros(); //micros();
     segCounter++;
  } 
}

/*void encoderInterupt0F()
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
*/



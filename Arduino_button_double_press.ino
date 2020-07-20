#define MIDFREQUENCY  30 //Hz

// variables declaration //////////////////////////
static uint32_t tTime_2;

bool single_press, double_press, hold; //output
bool rise_trig_2, fall_trig_2,prev_trig_2; //state change
uint32_t observe_time = 1000; //time
bool prev_state;
uint32_t start_time;

// setup() ///////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(29, INPUT);
  double_press = false;
  rise_trig_2 = false;
  fall_trig_2 = false;
  prev_state = LOW;
  start_time = 0;
}


// loop ///////////////////////////////////////////
void loop() {
  // put your main code here, to run repeatedly:
  uint32_t t = millis();

  if ((t - tTime_2) >= (1000 / MIDFREQUENCY))
  {
    //Horn
    //Speed up/speed down
    //Speed indicator
    //Button reset press
    buttonResetThread();
    tTime_2 = t;
  }
}


void buttonResetThread()
{
  bool cur_state = digitalRead(29);
  uint32_t cur_time = millis();

  //monitor trigger
  if (cur_state != prev_state && prev_state == LOW) //rising trig?
  {
    rise_trig_2 = true;
    start_time = millis();
  }
   if (cur_state = prev_state && prev_state == HIGH) //prev trig?
  {
    prev_trig_2 = true;
    start_time = millis();
  }
  else if (cur_state != prev_state && prev_state == HIGH) //falling trig?
  {
    fall_trig_2 = true;
  }

  //observe time
  if(rise_trig_2 && ((cur_time - start_time) > observe_time)) //observe time reach
  {
    if(fall_trig_2)
    {
      single_press = false;  
      double_press = true; //yes double press
      hold = false;
    }
    else
    {
      double_press = false;
    }
  }
  
}

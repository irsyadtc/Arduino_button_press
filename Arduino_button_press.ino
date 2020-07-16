#define MIDFREQUENCY  30 //Hz

// variables declaration //////////////////////////
static uint32_t tTime_2;

bool single_press, double_press, hold; //output
bool rise_trig_1, fall_trig_1; //state change
uint32_t observe_time = 2000; //time
bool prev_state;
uint32_t start_time;

// setup() ///////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(29, INPUT);
  single_press = false;
  rise_trig_1 = false;
  fall_trig_1 = false;
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
    rise_trig_1 = true;
    start_time = millis();
  }
  else if (cur_state != prev_state && prev_state == HIGH) //falling trig?
  {
    fall_trig_1 = true;
  }

  //observe time
  if(rise_trig_1 && ((cur_time - start_time) > observe_time)) //observe time reach
  {
    if(fall_trig_1)
    {
      single_press = true;  //yes single press
      double_press = false;
      hold = false;
    }
    else
    {
      single_press = false;
    }
  }
  
}

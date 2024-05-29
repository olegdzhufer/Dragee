#ifndef ENCODER_H
#define ENCODER_H


EncButton en(CLK, DT, SW);
PIDController pid;


void encoder_setup(){
  pid.begin();          
  pid.setpoint(150);  
  pid.tune(__Kp, __Ki,__Kd);  
  pid.limit(0, 255);    
  en.setEncType(EB_STEP4_LOW);
  en.setBtnLevel(HIGH);
}

int getResult(){
  REG_FLAG &= ~(1 << 2);
  return enc_pre; 
}


void read_encoder(){

  int currtime;
  if(!currtime)currtime = 0;
  if( millis() > currtime + 10){
    currtime += millis();
    
    en.tick();

    if(en.leftH()){
      enc_pre = 0x01;
      REG_FLAG |= (1 << 2);
    }
    else if(en.rightH()){
      enc_pre = 0x02;
      REG_FLAG |= (1 << 2);
    }

    else if (en.left()) {
        enc_pre = 0x03;
        REG_FLAG |= (1 << 2);
    }
    else if(en.right()){
        enc_pre = 0x04;
        REG_FLAG |= (1 << 2);
    }
     else if (en.press())  
    {
        enc_pre = 0x05;
        REG_FLAG |= (1 << 2);
    }
  }
}


#endif
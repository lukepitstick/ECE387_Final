unsigned long TimerA    "ALWAYS use unsigned long for timers..."
unsigned long TimerB  

if digitalReadA==Down
  then  TimerA= millis() , digitalWriteA ON
if millis()-TimerA >= 15000UL
  then digitalWriteA Off
if digitalReadB==Down
  then  TimerB= millis() , digitalWriteB ON
if millis()-TimerB >= 15000UL
  then digitalWriteB Off

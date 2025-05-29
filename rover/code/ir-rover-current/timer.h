#pragma once


typedef void (*timer_isr_fn)(void*);

typedef struct {
  timer_isr_fn fn = nullptr;
  unsigned long counterReset = 0;
  void *data = nullptr;
} timer_isr_t;

#define CLOCK_SPEED 16 // MHz


int getPrescalerIndex(
  unsigned long period, 
  unsigned long *count,
  unsigned long maxCount,
  unsigned int *prescaler, 
  unsigned int numPrescalers
) {
  for (int i=0; i<numPrescalers; i++) {
    *count = (period * CLOCK_SPEED) / prescaler[i];
    if (*count <= maxCount) {
      *count = maxCount - *count;
      return i;
    }
  }
  return -1;
}


extern timer_isr_t timer1;
int setTimer1(timer_isr_fn fn, void *data, unsigned long us) {
  unsigned int prescalers[] = { 1, 8, 64, 256, 1024 };
  int prescalerIdx = getPrescalerIndex(
    us, &(timer1.counterReset), 65535, 
    prescalers, sizeof(prescalers)/sizeof(unsigned int)
  );
  if (prescalerIdx < 0) {
    return -1;
  }
  Serial.println(prescalers[prescalerIdx]);

  timer1.fn = fn;
  timer1.data = data;

  cli();
  TCNT1 = timer1.counterReset;
  TCCR1A = 0;
  TCCR1B = 1+prescalerIdx;
  TIMSK1 = (1<<TOIE1);
  sei();
}
ISR (TIMER1_OVF_vect) {
  timer1.fn(timer1.data);
  TCNT1 = timer1.counterReset;
}


// extern timer_isr_t timer2;
// int setTimer2(timer_isr_fn fn, void *data, unsigned long us) {
//   unsigned int prescalers[] = { 1, 8, 64, 256, 1024 };
//   int prescalerIdx = getPrescalerIndex(
//     us, &(timer1.counterReset), 255, 
//     prescalers, sizeof(prescalers)/sizeof(unsigned int)
//   );
//   if (prescalerIdx < 0) {
//     return -1;
//   }
//   Serial.println(prescalers[prescalerIdx]);
// 
//   timer2.fn = fn;
//   timer2.data = data;
// 
//   cli();
//   TCNT2 = timer2.counterReset;
//   TCCR2A = 0;
//   TCCR2B = 1+prescalerIdx;
//   TIMSK2 = (1<<TOIE2);
//   sei();
// }
// ISR (TIMER2_OVF_vect) {
//   timer2.fn(timer2.data);
//   TCNT2 = timer2.counterReset;
// }

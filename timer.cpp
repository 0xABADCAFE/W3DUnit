
#include "amiga.hpp"
#include "timer.hpp"

uint32  Timer::clockFreq = 0;

struct Device *TimerBase;
struct TimerIFace *ITimer;

Timer::Timer()
{
	if (!clockFreq) {
		TimerBase = (Device*)     IExec->FindName(&SysBase->DeviceList, "timer.device");
		ITimer    = (TimerIFace*) IExec->GetInterface((struct Library *)TimerBase, "main", 1, 0);
		clockFreq = ITimer->ReadEClock(&mark);
	}
}

uint32 Timer::elapsed() const
{
  EClockVal current;
  ITimer->ReadEClock(&current);
  uint32 ticks;
  if (current.ev_hi == mark.ev_hi) {
    ticks = current.ev_lo - mark.ev_lo;
  }
  else {
    ticks = 0xFFFFFFFF-mark.ev_lo + current.ev_lo;
  }
  return (1000*ticks)/clockFreq;
}

float64 Timer::elapsedFrac() const
{
  EClockVal current;
  ITimer->ReadEClock(&current);
  float64 ticks;
  static float64 cF = 1000.0/(float64)clockFreq;
  if (current.ev_hi == mark.ev_hi) {
    ticks = (current.ev_lo - mark.ev_lo);
  }
  else {
    ticks = (0xFFFFFFFF-mark.ev_lo + current.ev_lo);
  }
  return (cF*ticks);
}


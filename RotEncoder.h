#ifndef RotEncoder_h
#define RotEncoder_h

#include "Arduino.h"

//Port D används digital pin 20,21 PD00 PD01
class RotEncoder
{
	public:
		RotEncoder();
		int16_t getRot();
		void setRot(int16_t value);
	private:
		int8_t readEncoder();
		int _pinA;
		int _pinB;
		int16_t _counter;
		int8_t _last1;
		int8_t _lasttemp;
};
#endif

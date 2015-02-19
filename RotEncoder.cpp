#include "Arduino.h"
#include "RotEncoder.h"

RotEncoder::RotEncoder()
{	
	_pinA=20;
	_pinA=21;
	pinMode(_pinA,INPUT);
	digitalWrite(_pinA,LOW);
	pinMode(_pinB,INPUT);
	digitalWrite(_pinB,LOW);
	
	_counter = 0;
	_last1 = 0;
	_lasttemp = 0;
}

int16_t RotEncoder::getRot()
{	

	/*this variable will be changed by encoder input*/
	int8_t _tmpdata = readEncoder();
	
 	/*Om resultat*/
  		if( _tmpdata ) 
		{
   		 	/*kolla om resultat var lika med de två föregående i sådana fall ändra värdet på counter*/
    			if( _tmpdata == _lasttemp & _lasttemp == _last1)
        		{
        		_counter += _tmpdata;
        		}
        	/*flytta föregånde värdet till föregående föregående värde*/
        	_last1 = _lasttemp;
        	/*flytta senaste till föregående*/
        	_lasttemp = _tmpdata;
      		}
	return _counter;
}

void RotEncoder::setRot(int16_t set_counter)
{
	_counter=set_counter;
}

int8_t RotEncoder::readEncoder()
{
	/*lagra föregående föregående mätning*/
   	static uint8_t _old_AB;
       	/*Alla godgända mönster är -1 eller 1 ej godkända 0*/
  	static int8_t enc_states[] = {0,-1,0,1,1,0,0,-1,0,0,0,0,-1,1,0,0};
  	/*Gör plats i variablen för mönstret med två till värden*/
  	_old_AB <<= 2;                   //remember previous state
  	/*Läs av i det här fallet portd maska ut port 2,3 lägg till dom på mönstret*/
  	_old_AB |= (( PIND & 0b11 )>>2);  //add current state
  	/*Kolla vilket värde mönstret motsvar med masken 1111 och returnera det.*/
  	return ( enc_states[( _old_AB & 0x0f )]);
}

#include "sdata.h"

sdata::sdata(){
	this->a.setPercision(SIGNED, 12, 11, ROUND);
	this->b.setPercision(SIGNED, 12, 11, ROUND);
	this->c.setPercision(SIGNED, 12, 11, ROUND);
}
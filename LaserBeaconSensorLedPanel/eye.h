#ifndef EYE_H_
#define EYE_H_

#include <stdint.h>



void initEye() ;
int convert(float time, int base_value, int target_value);
void eyeLoop();
void setNewPosition(int newX, int newY, int newSevere) ;
void setEyeBrow(int xx[8]) ;
void setPxl(int x, int y, uint32_t color) ;
void redraw() ;
void doBlink() ;
void lookAt(int x, int y, int newSevere) ;




#endif /* EYE_H_ */

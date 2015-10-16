#ifndef SERVO_H
#define SERVO_H


/*
    attach()
    write()
    writeMicroseconds() - new function takes parameters in Microseconds
    read() - returns the angle in degrees)
    readMicroseconds() - returns angle in uS, renamed from read_us
    attached()
    detach()
*/
void servo_write(float val);
void servo_init(void);

#endif /* SERVO_H */


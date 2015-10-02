#ifndef CAN_CONTROL_H_
#define CAN_CONTROL_H_



char can_read (char addr);
void can_write(char addr, char data);
void can_request_to_send(int reg);
void can_bit_modify(char addr, char mask_byte, char data);
void can_reset();
char can_read_status();

#endif /* CAN_CONTROL_H_ */
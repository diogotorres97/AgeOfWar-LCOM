#include "mouse.h"

static int mouse_hook_id;

int mouse_subscribe_int(void) {

	mouse_hook_id = MOUSE_HOOK_ID; // atualiza hook_id, passando a ser 5

	if (sys_irqsetpolicy(IRQ12, (IRQ_REENABLE | IRQ_EXCLUSIVE), &mouse_hook_id)
			!= OK) {
		printf("ERROR: subscribe notification failed!\n");
		return -1;
	}

	if (sys_irqenable(&mouse_hook_id) != OK) {
		printf("ERROR: enables interrupts has failed!\n");
		return -1;
	}
	return MOUSE_HOOK_ID;
}

int mouse_unsubscribe_int() {

	if (sys_irqdisable(&mouse_hook_id) != OK) {
		printf("ERROR: disables interrupts failed!\n");
		return 1;
	}

	if (sys_irqrmpolicy(&mouse_hook_id) != OK) {
		printf("ERROR: unsubscribes a previous subscription failed!\n");
		return 1;
	}
	return 0;
}

int mouse_get_packets() {

	unsigned long data;
	int i = 0;

	while (i < TRIES) {
		if (sys_inb(OUT_BUF, &data) != OK)
			return -1;
		return data;
	}
	tickdelay(micros_to_ticks(DELAY_US));
	i++;
}


int mouse_send_command() {

	unsigned long stat;

	while( 1 ) {
		sys_inb(STAT_REG, &stat);
		if( (stat & IBF ) == 0 ) {
			sys_outb(STAT_REG, M_ARGS);
			tickdelay(micros_to_ticks(DELAY_US));
			return 0;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
}

int mouse_send_args(unsigned long cmd) {
	unsigned long stat;

	while( 1 ) {
		sys_inb(STAT_REG, &stat);
		if( (stat & IBF) == 0 ) {
			sys_outb(OUT_BUF, cmd);
			tickdelay(micros_to_ticks(DELAY_US));
			return 0;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
}

int mouse_int_handler(unsigned long cmd){
	unsigned char code;

	do{
		mouse_send_command();
		mouse_send_args(cmd);
		code=mouse_get_packets();
		//printf("0x%x \n",code);
	}while(code!=KBD_ACK);

}



/*
int mouse_int_handler(unsigned long cmd)
{
	unsigned long cmd_receive;
	int i = 0;

	while(1)
	{
		mouse_send_command();
		while(i<TRIES)
		{
			mouse_send_args(cmd);
			cmd_receive= mouse_get_packets(); //para ver se é do Mouse

			if(READ_COMM_BYTE==(READ_COMM_BYTE & cmd_receive)) //se for igual, quer dizer que o byte vem do mouse
			{
				if (cmd_receive == MOUSE_NACK) // repete o comando enviado
				{
					i++;
					continue;
				}
				else break;
			}
			else continue;
		}
		if (cmd_receive == MOUSE_ERROR) //erro, volta a repetir todo o processo
		{
			continue;
		}
		break;
	}

}*/


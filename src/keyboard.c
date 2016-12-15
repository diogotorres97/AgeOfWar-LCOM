#include "keyboard.h"

static int kbd_hook_id;
unsigned long kbd_counter;
unsigned long received_two;

unsigned long caps_lock=0x00;
unsigned long numeric_lock=0x00;
unsigned long scroll_lock=0x00;



int kbd_subscribe_int(void) {

	kbd_hook_id = KEYBOARD_HOOK_ID; // atualiza hook_id, passando a ser 4

	if (sys_irqsetpolicy(IRQ1, (IRQ_REENABLE | IRQ_EXCLUSIVE), &kbd_hook_id)
			!= OK) {
		printf("ERROR: subscribe notification failed!\n");
		return -1;
	}

	if (sys_irqenable(&kbd_hook_id) != OK) {
		printf("ERROR: enables interrupts has failed!\n");
		return -1;
	}
	return KEYBOARD_HOOK_ID;
}

int kbd_unsubscribe_int() {

	if (sys_irqdisable(&kbd_hook_id) != OK) {
		printf("ERROR: disables interrupts failed!\n");
		return -1;
	}

	if (sys_irqrmpolicy(&kbd_hook_id) != OK) {
		printf("ERROR: unsubscribes a previous subscription failed!\n");
		return -1;
	}

	return 0;
}

int kbc_get_status_codes() {
	unsigned long stat;
	unsigned long data;
	int i = 0;

	while (i < TRIES) {

		if (sys_inb(STAT_REG, &stat) != OK)
			return -1;

		/*loop while 8042 output buffer is empty*/

		if ((stat & OBF) == 1) {

			if ((stat & (PARITY | TIMEOUT)) == 0) {
				if (sys_inb(OUT_BUF, &data) != OK)
					return -1;
				return data; // ACK or Resend or Error or codes
			}

			else
				return -1;
		}
		tickdelay(micros_to_ticks(DELAY_US));
		i++;
	}
}


int kbc_send_command(unsigned long cmd) {

	long unsigned int stat;

	while( 1 ) {
		sys_inb(STAT_REG, &stat);

		if( (stat & IBF) == 0 ) {
			//sys_outb(KBC_CMD_REG, cmd); se descomentar este entra em loop infinito
			sys_outb(OUT_BUF, cmd);
			return 0;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
}


int check_command() {

	unsigned long response;
	response = kbc_get_status_codes();

	if( response == KBD_ACK )
	{
		return 0;
	}

	if( response == KBD_RESEND)
	{
		return 1;
	}
	if( response == KBD_ERROR)
	{
		return 2;
	}

}

int send_args(unsigned long args) {

	long unsigned int stat;

	while( 1 ) {
		sys_inb(STAT_REG, &stat);

		if( (stat & IBF) == 0 ) {
			sys_outb(OUT_BUF, args);
			return 0;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
}

int kbd_print_codes(unsigned long code) {
	if (code == FIRST_OF_TWO_BYTE_SCANCODES) {
		received_two = code;
		return -1;
	}

	if (received_two == FIRST_OF_TWO_BYTE_SCANCODES) {
		if ((code & BIT(7)) != 0)
			printf("Break Code: 0x%x%x \n", FIRST_OF_TWO_BYTE_SCANCODES, code);
		else
			printf("Make Code: 0x%x%x \n", FIRST_OF_TWO_BYTE_SCANCODES, code);
		received_two = 0;
	} else {
		if ((code & BIT(7)) != 0)
			printf("Break Code: 0x%x \n", code);
		else
			printf("Make Code: 0x%x \n", code);

	}
	return 0;
}


int kbd_switch_led(unsigned int led)
{

	do{
		unsigned long code;

		do{
		kbc_send_command(CLEAR_BFR_ENABLE_KBD);
		unsigned long trash;
		sys_inb(OUT_BUF, &trash); //break code do enter
		kbc_send_command(SWITCH_KBD_LEDS);
		code =kbc_get_status_codes();
		}while(code!=KBD_ACK);



		switch(led)
		{
		case 0:
			if(scroll_lock==0)
			{
				printf("Scroll Lock: ON \n");
				scroll_lock=SCROLL_LOCK;
			}
			else
			{
				printf("Scroll Lock: OFF \n");
				scroll_lock=0;
			}
			break;
		case 1:
			if(numeric_lock==0)
			{
				printf("Numeric Lock: ON \n");
				numeric_lock=NUMERIC_LOCK;
			}
			else
			{
				printf("Numeric Lock: OFF \n");
				numeric_lock=0;
			}
			break;
		case 2:
			if(caps_lock==0)
			{
				printf("Caps Lock: ON \n");
				caps_lock=CAPS_LOCK;
			}
			else
			{
				printf("Caps Lock: OFF \n");
				caps_lock=0;
			}
			break;
		default:
			break;
		}

		unsigned long args;
		args = (scroll_lock | numeric_lock | caps_lock);


		do{

			if(send_args(args)!=0)
				return 1;


		}while(kbc_get_status_codes()==KBD_RESEND); //resend


	}while(kbc_get_status_codes()==KBD_ERROR); //ERROR


	return 0;

}

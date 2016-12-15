#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include "const.h"

static int hook_id;
unsigned long counter;

int timer_set_square(unsigned long timer, unsigned long freq) {

	if(timer<0||freq<=0||timer>2)
	{
		printf("ERROR: Timer invalid or Freq invalid!\n");
		return -1;
	}

	unsigned long control_word;
	unsigned long msb = MASK_ZERO;
	unsigned long lsb = MASK_ZERO;
	unsigned char st;
	timer_get_conf(timer,&st); //read timer config

	//to preserve 4 LSB
	control_word |= MASK_4LSB_1; // 0x0F
	control_word = ((unsigned long)st & control_word); //0x0X


	//Select timer and configure Control Word
	switch (timer)
	{
	case 0:

		control_word |= TIMER_SEL0;
		control_word |= TIMER_LSB_MSB;
		/*control_word |= TIMER_SQR_WAVE;
	control_word |= TIMER_BCD; */
		break;
	case 1:
		control_word |= TIMER_SEL1;
		control_word |= TIMER_LSB_MSB;
		/*control_word |= TIMER_SQR_WAVE;
		control_word |= TIMER_BCD; */
		break;
	case 2:
		control_word |= TIMER_SEL2;
		control_word |= TIMER_LSB_MSB;
		/*control_word |= TIMER_SQR_WAVE;
		control_word |= TIMER_BCD; */
		break;
	default:
		printf("ERROR!\n");
		return 1;
	}

	//frenquency to insert
	unsigned int new_freq;
	new_freq=TIMER_FREQ/freq;

	lsb=new_freq & BIT_MASK_EIGHT; // 0000 0000 XXXX XXXX
	msb=(new_freq >> 8) & BIT_MASK_EIGHT; // 0000 0000 XXXX XXXX

	//Send lsb first, then msb

	if (new_freq <= TIMER_FREQ)
	{
		//send information to read to controler, send lsb and send msb but first check if the operation is valid
		if (sys_outb(TIMER_CTRL, control_word) != OK || sys_outb(TIMER_0+timer, lsb) != OK || sys_outb(TIMER_0+timer, msb) != OK)
		{
			printf("ERROR: send message to timer failed! \n");
			return 1;
		}
		else;
		return 0;
	}
	else
	{
		printf("ERROR!\n");
		return 1;
	}
}



int timer_subscribe_int(void ) {

	hook_id= TIMER_HOOK_ID; // atualiza hook_id, passando a ser 1

	if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id) != OK)
	{
		printf("ERROR: subscribe notification failed!\n");
		return -1;
	}

	if (sys_irqenable(&hook_id) != OK)
	{
		printf("ERROR: enables interrupts has failed!\n");
		return -1;
	}
	return TIMER_HOOK_ID;
}

int timer_unsubscribe_int() {

	if (sys_irqdisable(&hook_id) != OK)
		{
			printf("ERROR: disables interrupts failed!\n");
			return -1;
		}

	if (sys_irqrmpolicy(&hook_id) != OK)
	{
		printf("ERROR: unsubscribes a previous subscription failed!\n");
		return -1;
	}

	return 0;
}

void timer_int_handler() {

	counter++; // Incrementa a variavel global counter
}

int timer_get_conf(unsigned long timer, unsigned char *st) {

	if(timer<0||timer>2)
	{
		printf("ERROR: Timer invalid!\n");
		return -1;
	}

	unsigned long read_back=MASK_ZERO; // variable for configure Read-back Command
	read_back |= TIMER_RB_CMD; // bit 7,6 = 1 ; SC=Read-Back Command
	read_back |= TIMER_RB_COUNT_; //Bit 5  Counter
	read_back |= TIMER_RB_SEL(timer); // bit 3,2,1 selected depend on timer used


	if(sys_outb(TIMER_CTRL,read_back)!=OK) //Check if control word was be copied to timer_ctrl correctly
	{
		printf("ERROR: send control word to timer_ctrl failed!\n");
		return 1;
	}

	if(sys_inb(TIMER_0 + timer, (unsigned long *)st)!=OK)
	{
		printf("ERROR: received information about timer failed!\n");
		return 1;
	}

	return 0;
}

int timer_display_conf(unsigned char conf) {


	printf("Timer status byte: 0x%x \n",conf);


	if((conf & BIT(7)) ==0)
		printf("Output value: 0\n");
	else
		printf("Output value: 1\n");


	if((conf & BIT(6)) ==0)
		printf("Null count: 0\n");
	else
		printf("Null count: 1\n");


	if((conf & MASK_ACESS_TIME) ==1)
		printf("Access time: Read/Write LSB first, then MSB \n");
	else
		if((conf & BIT(5)) == 1)
			printf("Read/Write MSB \n");
		else
			printf("Read/Write LSB \n");


	switch(conf & MASK_PROGRAMMED_MODE)
	{
	case TIMER_INT_COUNT:
		printf("Programmed Mode: 0 - TIMER_INT_COUNT\n");
		break;
	case TIMER_HW_RETR:
		printf("Programmed Mode: 1 - TIMER_HW_RETR\n");
		break;
	case TIMER_RATE_GEN:
		printf("Programmed Mode: 2 - TIMER_RATE_GEN\n");
		break;
	case TIMER_SQR_WAVE:
		printf("Programmed Mode: 3 - TIMER_SQR_WAVE\n");
		break;
	case TIMER_SW_TRIG:
		printf("Programmed Mode: 4 - TIMER_SW_TRIG\n");
		break;
	case TIMER_HW_TRIG:
		printf("Programmed Mode: 5 - TIMER_HW_TRIG\n");
		break;
	}

	if((conf & BIT(0))==1)
		printf("BCD: 1\n");
	else
		printf("BCD: 0\n");


	return 0;
}

int timer_test_square(unsigned long freq) {

	if(freq<=0)
	{
		printf("ERROR: Freq invalid!\n");
		return 1;
	}

	if (timer_set_square(0, freq)==1)
	{
		return 1;
	}
	else
		return 0;

}

int timer_test_int(unsigned long time) {

	if(time<0)
	{
		printf("ERROR: Timer invalid!\n");
		return 1;
	}


	int irq_set = timer_subscribe_int();

	if(irq_set==-1)
		return 1;

	counter=0;
	irq_set = BIT(irq_set);
	int ipc_status, r;
	message msg;
	int seconds=0;

	while (counter < TIMER_DEFAULT_FREQ * time) { // condição verdadeira, sempre que é multiplo de 60

		if ((r = driver_receive(ANY, &msg, &ipc_status) != 0)) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & irq_set) {
					timer_int_handler();
					if (counter % TIMER_DEFAULT_FREQ == 0)
					{
						seconds++;
						printf("Seconds passed: %d !\n", seconds);
					}
				}
				break;
			default:

				break;
			}
		} else {

		}
	}

	if(timer_unsubscribe_int()==1)
		return 1;


	return 0;
}

int timer_test_config(unsigned long timer) {
	unsigned char st;


	if(timer<0||timer>2)
	{
		printf("ERROR: Timer invalid!");
		return 1;
	}

	timer_get_conf(timer, &st);

	if (timer_display_conf(st)==1)
		return 1;

	return 0;

}

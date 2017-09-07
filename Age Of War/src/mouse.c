#include "mouse.h"

/******************************************** Mouse functions *****************************************/

static int mouse_hook_id;

//Mouse central coordinates
int x = 512;
int y = 284;

Mouse* InitMouse() {
	Mouse *mouse = (Mouse *)malloc(sizeof(Mouse));
	mouse->x = 512;
	mouse->y = 284;

	mouse->leftButton_P = 0;
	mouse->middleButton_P = 0;
	mouse->rightButton_P = 0;

	mouse->packetCounter = 0;

	mouse->mouseWidth = 22;
	mouse->mouseHeight = 22;
	mouse->MouseBMP = loadBitmap(getImagePath("Cursor"));

	return mouse;
}

void deleteMouse(Mouse* mouse) {
	deleteBitmap(mouse->MouseBMP);
	free(mouse);
}

void drawMouse(Mouse* mouse, char* doubleBuffer) {
	drawBitmap(mouse->MouseBMP, mouse->x, mouse->y, ALIGN_LEFT, doubleBuffer);
}

void SetPacket(Mouse* mouse) {
	mouse->packet[mouse->packetCounter] = mouse_get_packets();
	if (mouse->packetCounter == 0 && !(mouse->packet[mouse->packetCounter] & BIT(3)))
		return;

	mouse->packetCounter++;
}

void updateMouse(Mouse* mouse, int menu_flag) {
	mouse->Xsign = mouse->packet[0] & BIT(4);
	mouse->Ysign = mouse->packet[0] & BIT(5);
	mouse->Xdelta = mouse->packet[1];
	mouse->Ydelta = mouse->packet[2];
	if (mouse->Xsign)
		mouse->Xdelta |= (-1 << 8);
	if (mouse->Ysign)
		mouse->Ydelta |= (-1 << 8);

	mouse->leftButton_P = mouse->packet[0] & BIT(0);
	mouse->rightButton_P = mouse->packet[0] & BIT(1);
	mouse->middleButton_P = mouse->packet[0] & BIT(2);

	if (mouse->Xdelta != 0) {
		mouse->x += mouse->Xdelta;


		if (mouse->x < 5)
			mouse->x = 5;
		else if (mouse->x + mouse->mouseWidth > H_RES - 5)
			mouse->x = H_RES - 5 - mouse->mouseWidth;


	}

	if (mouse->Ydelta != 0) {
		mouse->y -= mouse->Ydelta;


		if (mouse->y < 5)
			mouse->y = 5;
		else if (mouse->y + mouse->mouseHeight > V_RES - 5)
			mouse->y = V_RES - 5 - mouse->mouseHeight;


	}

	mouse->Xdelta = mouse->x - x;
	mouse->Ydelta = mouse->y - y;
	x = mouse->x;
	y = mouse->x;
}

void resetButtons(Mouse* mouse) {
	mouse->leftButton_P = 0;
	mouse->rightButton_P = 0;
	mouse->middleButton_P = 0;
}

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
		return -1;
	}

	if (sys_irqrmpolicy(&mouse_hook_id) != OK) {
		printf("ERROR: unsubscribes a previous subscription failed!\n");
		return -1;
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

	while (1) {
		sys_inb(STAT_REG, &stat);
		if ((stat & IBF) == 0) {
			sys_outb(STAT_REG, M_ARGS);
			tickdelay(micros_to_ticks(DELAY_US));
			return 0;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
}

int mouse_send_args(unsigned long cmd) {
	unsigned long stat;

	while (1) {
		sys_inb(STAT_REG, &stat);
		if ((stat & IBF) == 0) {
			sys_outb(OUT_BUF, cmd);
			tickdelay(micros_to_ticks(DELAY_US));
			return 0;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
}

int mouse_int_handler(unsigned long cmd) {
	unsigned char code;

	do {
		mouse_send_command();
		mouse_send_args(cmd);
		code = mouse_get_packets();
		//printf("0x%x \n",code);
	} while (code != KBD_ACK);

}




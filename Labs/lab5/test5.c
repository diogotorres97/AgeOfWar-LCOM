#include "test5.h"

#include <string.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <stdint.h>

#include "timer.h"
#include "i8042.h"
#include "i8254.h"
#include "keyboard.h"
#include "lmlib.h"
#include "vbe.h"
#include "video_gr.h"
#include "sprite.h"


void *test_init(unsigned short mode, unsigned short delay) {

    void *video_mem = vg_init(mode); //enable mode graphic


    int irq_set = timer_subscribe_int();
    if (irq_set == -1) {
        printf("Subscribe failed\n");
        return NULL;
    }


    irq_set = BIT(irq_set);

    int ipc_status, r;
    message msg;

    int timer_counter = 0;
    int seconds = 0;

    while (seconds < delay) {
        if (r = driver_receive(ANY, &msg, &ipc_status) != 0) {
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) {
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    if (msg.NOTIFY_ARG & irq_set) {
                        timer_counter++;
                        if (timer_counter % TIMER_DEFAULT_FREQ == 0) {
                            seconds++;
                        }
                    }
                    break;
                default:
                    break;
            }

        }
    }

    if (timer_unsubscribe_int() == 1) {
        printf("Unsubscribe Failed");
        return NULL;
    }

    //disable graphic
    if (vg_exit() == 1) {
        return NULL;
    }

    vbe_mode_info_t vmi_p;
    vbe_get_mode_info(mode, &vmi_p);

    printf("Physical Address of VRAM: 0x%x\n", vmi_p.PhysBasePtr);

    return (void *) video_mem;

}


int test_square(unsigned short x, unsigned short y, unsigned short size, unsigned long color) {

    if (vg_init(VBE_MODE_GRAPHICS_1024_786_256) == NULL)
        return 1;

    vg_fill_square(x, y, size, color);

    int irq_set = kbd_subscribe_int();

    if (irq_set == -1)
        return 1;

    unsigned long trash;
    sys_inb(OUT_BUF, &trash);

    irq_set = BIT(irq_set);
    int ipc_status, r;
    message msg;
    unsigned long code = 0x00;

    while (code != ESC_BREAKCODE) {
        /* Get a request message. */
        if (r = driver_receive(ANY, &msg, &ipc_status) != 0) {
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) { /* received notification*/
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: /* hardware interrupt notification */
                    if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
                        code = kbc_get_status_codes(); //C handler
                    }
                    break;
                default:
                    break; /* no other notifications expected: do nothing */
            }

        }
    }

    if (kbd_unsubscribe_int() == 1)
        return 1;

    if (vg_exit() == 1)
        return 1;

    return 0;

}

int test_line(unsigned short xi, unsigned short yi,
              unsigned short xf, unsigned short yf, unsigned long color) {

    if (vg_init(VBE_MODE_GRAPHICS_1024_786_256) == NULL)
        return 1;

    vg_set_line(xi, yi, xf, yf, color);

    int irq_set = kbd_subscribe_int();

    if (irq_set == -1)
        return 1;

    unsigned long trash;
    sys_inb(OUT_BUF, &trash);

    irq_set = BIT(irq_set);
    int ipc_status, r;
    message msg;
    unsigned long code = 0x00;

    while (code != ESC_BREAKCODE) {
        /* Get a request message. */
        if (r = driver_receive(ANY, &msg, &ipc_status) != 0) {
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) { /* received notification*/
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: /* hardware interrupt notification */
                    if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
                        code = kbc_get_status_codes(); //C handler
                    }
                    break;
                default:
                    break; /* no other notifications expected: do nothing */
            }

        }
    }

    if (kbd_unsubscribe_int() == 1)
        return 1;

    if (vg_exit() == 1)
        return 1;

    return 0;

}

int test_xpm(unsigned short xi, unsigned short yi, char *xpm[]) {

    vg_init(VBE_MODE_GRAPHICS_1024_786_256);

    vbe_mode_info_t vmi_p;
    vbe_get_mode_info(VBE_MODE_GRAPHICS_1024_786_256, &vmi_p);

    int width, height;
    char *pixmap = (char *) read_xpm(xpm, &width, &height, vmi_p.XResolution, vmi_p.YResolution);
    vg_set_xpm(xi, yi, pixmap, width, height);


    int irq_set = kbd_subscribe_int();

    if (irq_set == -1)
        return 1;

    unsigned long trash;
    sys_inb(OUT_BUF, &trash);

    irq_set = BIT(irq_set);
    int ipc_status, r;
    message msg;
    unsigned long code = 0x00;

    while (code != ESC_BREAKCODE) {
        /* Get a request message. */
        if (r = driver_receive(ANY, &msg, &ipc_status) != 0) {
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) { /* received notification*/
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: /* hardware interrupt notification */
                    if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
                        code = kbc_get_status_codes(); //C handler
                    }
                    break;
                default:
                    break; /* no other notifications expected: do nothing */
            }

        }
    }

    if (kbd_unsubscribe_int() == 1)
        return 1;

    vg_exit();

    return 0;

}

int test_move(unsigned short xi, unsigned short yi, char *xpm[],
              unsigned short hor, short delta, unsigned short time) {

    void *video_mem = vg_init(VBE_MODE_GRAPHICS_1024_786_256); //enable mode graphic
    float xspeed = 0;
    float yspeed = 0;

    vbe_mode_info_t vmi_p;
    vbe_get_mode_info(VBE_MODE_GRAPHICS_1024_786_256, &vmi_p);

    if (hor == 0) {
        xspeed = (double) delta / (time * TIMER_DEFAULT_FREQ);
        yspeed = 0;
    } else {
        xspeed = 0;
        yspeed = (double) delta / (time * TIMER_DEFAULT_FREQ);
    }

    Sprite *sprite = create_sprite(xpm, xi, yi, xspeed, yspeed, vmi_p.XResolution, vmi_p.YResolution);

    int irq_set1 = kbd_subscribe_int();
    if (irq_set1 == -1)
        return 1;

    int irq_set2 = timer_subscribe_int();
    if (irq_set2 == -1)
        return 1;

    unsigned long trash;
    sys_inb(OUT_BUF, &trash);

    irq_set1 = BIT(irq_set1);
    irq_set2 = BIT(irq_set2);

    int ipc_status, r;
    message msg;
    unsigned long code = 0x00;
    int counter = 0;
    int seconds = 0;

    while (code != ESC_BREAKCODE) {
        if (r = driver_receive(ANY, &msg, &ipc_status) != 0) {
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) {
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    if (msg.NOTIFY_ARG & irq_set1) {
                        code = kbc_get_status_codes();
                    }
                    if ((msg.NOTIFY_ARG & irq_set2) && (counter < TIMER_DEFAULT_FREQ * time)) {
                        counter++;
                        move_sprite(sprite);
                    }
                    break;
                default:
                    break;
            }

        }
    }

    if (kbd_unsubscribe_int() == 1)
        return 1;

    if (timer_unsubscribe_int() == 1)
        return 1;

    vg_exit(); //disable graphic

    return 0;

}

int test_controller() {

    vbe_info_block_t vib_p;

    if (vbe_get_info_block(&vib_p)) {
        return 1;
    }

    printf("\n Controller capabilities: 0x%X\n", vib_p.Capabilities);
    if ((vib_p.Capabilities[0] & VBE_CONTROLLER_CAPABILITIES_DAC_SWITCH_WIDTH) != 0) {
        printf("\tDAC width is switchable to 8 bits per primary color\n");
    } else {
        printf("\tDAC is fixed width, with 6 bits per primary color\n");
    }
    if ((vib_p.Capabilities[1] & VBE_CONTROLLER_CAPABILITIES_NOT_VGA) != 0) {
        printf("\tController is not VGA compatible\n");
    } else {
        printf("\tController is VGA compatible\n");
    }
    if ((vib_p.Capabilities[2] & VBE_CONTROLLER_CAPABILITIES_RAMDAC_USE_BLANK) != 0) {
        printf("\tWhen programming large blocks of information to the RAMDAC, the blank bit must be used in function 0x09\n");
    } else {
        printf("\tNormal RAMDAC operation\n");
    }


    printf("\nVideo modes: \n");

    int i;
    int line = 0;
    for (i = 0; i < 221; i += 2) {

        if ((vib_p.Reserved[i + 1] << 8 | vib_p.Reserved[i]) == 0xFFFF)
            break;
        else {
            if (line < 5) {
                printf("0x%x   ", ((vib_p.Reserved[i + 1] << 8) | vib_p.Reserved[i]));
                line++;
            } else {
                printf("0x%x \n", ((vib_p.Reserved[i + 1] << 8) | vib_p.Reserved[i]));
                line = 0;
            }

        }

    }


    printf("\n\nSize of VRAM memory: %lu KB\n", vib_p.TotalMemory * 64);

    return 0;
}					


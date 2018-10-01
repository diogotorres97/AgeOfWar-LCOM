#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>

/******************************************** Vbe functions *****************************************/

#include "vbe.h"
#include "lmlib.h"

#define LINEAR_MODEL_BIT 14

#define PB2BASE(x) (((x) >> 4) & 0x0F000)
#define PB2OFF(x) ((x) & 0x0FFFF)


/*
adjust physical address; boot code runs with %ds having a 64k offset
#define VBEPHYPTR(x) ((uint8_t *)((x) - (64 * 1024)))
*/
int vbe_get_mode_info(unsigned short mode, vbe_mode_info_t *vmi_p) {

    mmap_t map;

    lm_init();

    if (lm_alloc(sizeof(vbe_mode_info_t), &map) == NULL) {
        return 1;
    }

    struct reg86u r;

    r.u.w.ax = 0x4F01;          /*VBE get mode info	*/
    /*translate the buffer linear address to a far pointer	*/
    r.u.w.es = PB2BASE(map.phys);    /*set a segment base*/
    r.u.w.di = PB2OFF(map.phys);     /*set the offset accordingly*/
    r.u.w.cx = mode;
    r.u.b.intno = 0x10;
    if (sys_int86(&r) != OK) { /*call BIOS	*/
        printf("get_mode_info: sys_int86() failed \n");
        return 1;
    }

    memcpy(vmi_p, map.virtual, map.size);

    lm_free(&map);
    return 0;

}


int vbe_get_info_block(vbe_info_block_t *vib_p) {

    mmap_t map;

    lm_init();

    if (lm_alloc(sizeof(vbe_info_block_t), &map) == NULL) {
        return 1;
    }

    struct reg86u r;
    r.u.w.ax = VBE_CONTROLLER_INFO;          /*VBE Controller info	*/
    /*translate the buffer linear address to a far pointer	*/
    r.u.w.es = PB2BASE(map.phys);    /*set a segment base*/
    r.u.w.di = PB2OFF(map.phys);     /*set the offset accordingly*/
    r.u.w.cx = VBE_MODE_GRAPHICS_1024_786_256;
    r.u.b.intno = VBE_INTERRUPT;

    if (sys_int86(&r) != OK) { /*call BIOS	*/
        printf("get_info_block: sys_int86() failed \n");
        return 1;
    }

    memcpy(vib_p, map.virtual, map.size);

    lm_free(&map);
    return 0;

}

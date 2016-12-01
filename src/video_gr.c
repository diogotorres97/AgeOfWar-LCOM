#include <minix/syslib.h>

#include <minix/drivers.h>

#include <machine/int86.h>

#include <sys/mman.h>

#include <sys/types.h>

#include <stdint.h>

#include "vbe.h"

#include "video_gr.h"

#include "pixmap.h"

#include "read_xpm.h"

/* Constants for VBE 0x105 mode */

/* The physical address may vary from VM to VM.

 * At one time it was 0xD0000000

 *  #define VRAM_PHYS_ADDR    0xD0000000 

 * Currently on lab B107 is 0xF0000000

 * Better run my version of lab5 as follows:

 *     service run `pwd`/lab5 -args "mode 0x105"

 */



/* Private global variables */

static char *double_buffer; /* the double buffer */

static char *video_mem;                /* Process address to which VRAM is mapped */

static unsigned h_res;                /* Horizontal screen resolution in pixels */

static unsigned v_res;                /* Vertical screen resolution in pixels */

static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */

void *vg_init(unsigned short mode){

	//VBE graphics mode 105h, 1024x768@256,        linear mode

	vbe_mode_info_t vmi_p;

	struct reg86u r;

	int r1;

	struct mem_range mr;

	r.u.w.ax = VBE_VBE_MODE; // VBE call, function 02 -- set VBE mode

	r.u.w.bx = 1<<14|mode; // set bit 14: linear framebuffer

	r.u.b.intno = VBE_INTERRUPT;

	if( sys_int86(&r) != OK ) {

		printf("set_vbe_mode: sys_int86() failed \n");

		return NULL;

	}

	if(vbe_get_mode_info(mode, &vmi_p)!=0)

		return NULL;

	unsigned int vram_base=vmi_p.PhysBasePtr;

	unsigned int vram_size;

	h_res=vmi_p.XResolution;

	v_res=vmi_p.YResolution;

	bits_per_pixel=vmi_p.BitsPerPixel;

	/*Allow memory mapping*/

	mr.mr_base = (phys_bytes) vram_base;

	vram_size = h_res*v_res*(bits_per_pixel/8);

	//screen_buffer=malloc(h_res*v_res*(bits_per_pixel/8));

	mr.mr_limit = mr.mr_base + vram_size;

	if( OK != (r1 = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))

		panic("sys_privctl (ADD_MEM) failed: %d\n", r1);

	/*Map memory*/

	video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);
	double_buffer=(char*)malloc(vram_size);

	if(video_mem == MAP_FAILED)

		panic("couldn't map video memory");


	return (void*) video_mem;

}

int vg_set_pixel(unsigned short x, unsigned short y,unsigned long color){

	unsigned char *adress_temp;

	adress_temp=video_mem;

	if((x<h_res) && (y<v_res)){

		if(color!=VIDEO_256_TRANSPARENT){

			adress_temp += (x+y*h_res)*(bits_per_pixel/8);

			*adress_temp=color;

		}

		return 0;

	}

	return 1;

}

int vg_fill_square(unsigned short x, unsigned short y, unsigned short size, unsigned long color){

	unsigned short xi;

	unsigned short yi;

	for (yi=0; yi< size;yi++){

		for(xi=0; xi< size;xi++){

			vg_set_pixel(x+xi, y+yi,color);

		}

	}

}

int vg_set_line(unsigned short xi, unsigned short yi,

		unsigned short xf, unsigned short yf, unsigned long color){

	float dx = xf - xi;

	float dy = yf - yi;

	float xt;

	float yt;

	for( xt=xi; xt<xf;xt++) {

		yt= (dy/dx)*(xt-xi)+yi;

		vg_set_pixel(xt,yt,color);

	}

}

int vg_exit() {

	struct reg86u reg86;

	reg86.u.b.intno = VBE_INTERRUPT; /* BIOS video services */

	reg86.u.b.ah = VBE_RETURN_VBE_CONTROLLER_INFO;    /* Set Video Mode function */

	reg86.u.b.al = VBE_RETURN_CURRENT_VBE_MODE;    /* 80x25 text mode*/

	if( sys_int86(&reg86) != OK ) {

		printf("\tvg_exit(): sys_int86() failed \n");

		return 1;

	}

	else

	{

		return 0;

	}

}

int vg_set_xpm (unsigned short xi, unsigned short yi,  char *pixmap, unsigned short width, unsigned short height){

	int i,j;

	// copy it to graphics memory

	for(i=0; i< height; i++){

		for(j=0; j< width; j++){

			unsigned long color = *(pixmap + (j + i * width) * bits_per_pixel / 8);

			vg_set_pixel(xi+j,yi+i, color);

		}

	}

	return 0;

}

int vg_set_color(unsigned short xi, unsigned short yi, unsigned short width, unsigned short height, unsigned long color){

	int i, j;

	for (i = xi; i < xi + width; i++){

		for (j = yi; j < yi + height; j++)        {

			vg_set_pixel(i, j, color);

		}

	}

	return 0;

}

void* getDoubleBuffer() {
	return double_buffer;
}

void* getVideoMem(){
	return video_mem;
}


void updateScreenBuffer(){
	memcpy(video_mem, double_buffer, h_res * v_res*bits_per_pixel/8);
}

void clearDoubleBuffer(){
	memset(double_buffer, 0, h_res * v_res * bits_per_pixel/8);
}

void clearVideoMem(){
	memset(video_mem, 0, h_res * v_res * bits_per_pixel/8);
}

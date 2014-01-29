/*****************************************************
* r3dfb -- 3D rendering library framebuffer for SDL  *
* author: rene-dev, Andreas Mantler (ands)           *
*****************************************************/

#ifndef R3DFB_H
#define R3DFB_H

#define R3DFB_PIXEL_WIDTH ((uint16_t)800)
#define R3DFB_PIXEL_HEIGHT ((uint16_t)600)

#define R3DFB_COLOR_BUFFER_SIZE (R3DFB_PIXEL_WIDTH * R3DFB_PIXEL_HEIGHT * sizeof(uint32_t))
#define R3DFB_DEPTH_BUFFER_SIZE (R3DFB_PIXEL_WIDTH * R3DFB_PIXEL_HEIGHT * sizeof(float))

void r3dfb_init(void);
void r3dfb_clear(void); // clears color back buffer and depth buffer
void r3dfb_swap_buffers(void); // flushes back to front color buffer

#endif

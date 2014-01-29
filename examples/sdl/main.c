#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "r3d.h"
#include "r3dfb.h"

// vertex format
typedef struct
{
	uint16_t x, y, z;
	uint8_t nx, ny, nz;
	uint8_t u, v;
} vertex_t;

#include "teapot.h" // mesh
#include "nyan.h" // texture

static const r3d_drawcall_t mesh =
{
	R3D_PRIMITIVE_TYPE_TRIANGLES,
	vertices0, // vertex data
	sizeof(vertex_t), // vertex size
	sizeof(vertices0) / sizeof(vertex_t), // count
	0 // indices
};

static mat4_t model, view, projection, mv, mvp;

// shader
typedef struct
{
	vec3_t position;
	vec3_t normal;
	vec2_t uv;
} vs_to_fs_t;

static void vertex_shader(const vertex_t *in, vs_to_fs_t *out)
{
	// decode vertex
	const vec3_t pc = { 0.5f, 0.5f, 0.5f }, nc = { 1.0f, 1.0f, 1.0f };
	const float pi = 1.0f / 65535.0f, ni = 2.0f / 255.0f, uvi = 1.0f / 255.0f;
	vec3_t position = vec3_sub(vec3_mul(vec3(in->x, in->y, in->z), pi), pc);
	vec3_t normal = vec3_sub(vec3_mul(vec3(in->nx, in->ny, in->nz), ni), nc);
	vec2_t uv = vec2_mul(vec2(in->u, in->v), uvi);
	// transform vertex
	out->position = mat4_transform_position(mvp, position);
	out->normal = mat4_transform_vector(mv, normal);
	out->uv = uv;
}

static vec4_t fragment_shader(const vs_to_fs_t *in)
{
	const vec3_t E = { 0, 0, 1 };
	const vec3_t L = { -0.577350269f, 0.577350269f, 0.577350269f };
	vec3_t N = vec3_normalize(in->normal);
	vec3_t H = vec3_normalize(vec3_add(E, L));

	const float ambient = 0.05f;
	float diffuse = vec3_dot(N, L) * 0.6f;
	float specular = vec3_dot(N, H);
	specular *= specular; specular *= specular;	specular *= specular;
	specular *= specular; specular *= specular; specular *= specular * 0.6f;

	vec3_t c = r3d_texture_nearest((r3d_texture_t*)&nyan, in->uv); // read texel
	return vec4(ambient + diffuse * c.r + specular,
			ambient + diffuse * c.g + specular,
			ambient + diffuse * c.b + specular, 1.0f);
}

static r3d_shader_t shader =
{
	(r3d_vertexshader_func)vertex_shader,
	(r3d_fragmentshader_func)fragment_shader,
	sizeof(vs_to_fs_t) / sizeof(float)
};

int main(int argc, char **argv)
{
	r3dfb_init();

	projection = mat4_perspective(60.0f, (float)R3DFB_PIXEL_WIDTH / (float)R3DFB_PIXEL_HEIGHT, 0.5f, 5.0f);
	view = mat4_lookat(vec3(0.0f, 0.25f, 1.5f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

	r3d_viewport(0, 0, R3DFB_PIXEL_WIDTH, R3DFB_PIXEL_HEIGHT);
	r3d_backface_culling = R3D_ENABLE;
	r3d_primitive_winding = R3D_PRIMITIVE_WINDING_CW;
	
	int frame = 0;

	while(42)
	{
		model = mat4_mul(
				mat4_rotation(frame, vec3(1.0f, 0.0f, 0.0f)),
				mat4_rotation(frame++, vec3(0.0f, 1.0f, 0.0f)));
		mv = mat4_mul(view, model);
		mvp = mat4_mul(projection, mv);
	
		r3dfb_clear();
		r3d_shader = shader;
		r3d_draw(&mesh);
		r3dfb_swap_buffers();
	}
	
	return 0;
}

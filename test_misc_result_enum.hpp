

//#define W3D_Z_NEVER             1       /* discard incoming pixel */
//#define W3D_Z_LESS              2       /* draw, if value < Z(Z_Buffer) */
//#define W3D_Z_GEQUAL            3       /* draw, if value >= Z(Z_Buffer) */
//#define W3D_Z_LEQUAL            4       /* draw, if value <= Z(Z_Buffer) */
//#define W3D_Z_GREATER           5       /* draw, if value > Z(Z_Buffer) */
//#define W3D_Z_NOTEQUAL          6       /* draw, if value != Z(Z_Buffer) */
//#define W3D_Z_EQUAL             7       /* draw, if value == Z(Z_Buffer) */
//#define W3D_Z_ALWAYS            8       /* always draw */

enum {

	RES_MISC_BLOCK_FILL_RED_PASSED   = 0x00000001,
	RES_MISC_BLOCK_FILL_GREEN_PASSED = 0x00000002,
	RES_MISC_BLOCK_FILL_BLUE_PASSED  = 0x00000004,

	RES_MISC_SCISSOR_PASSED          = 0x00000010,
	RES_MISC_FLAT_SHADING_PASSED     = 0x00000020,
	RES_MISC_GOURAUD_SHADING_PASSED  = 0x00000040,

	RES_MISC_ZCMP_N_PASSED           = 0x00000100,
	RES_MISC_ZCMP_LT_PASSED          = 0x00000200,
	RES_MISC_ZCMP_LE_PASSED          = 0x00000400,
	RES_MISC_ZCMP_EQ_PASSED          = 0x00000800,
	RES_MISC_ZCMP_GE_PASSED          = 0x00001000,
	RES_MISC_ZCMP_GT_PASSED          = 0x00002000,
	RES_MISC_ZCMP_NE_PASSED          = 0x00004000,
	RES_MISC_ZCMP_A_PASSED           = 0x00008000,

};

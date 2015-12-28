/*
 * dx9cc.c
 *
 * author:demonMOE-s
 */

#define WIN32_LEAN_AND_MEAN

#include <SDKDDKVer.h>
#include <windows.h>
#include <d3d9.h>
#include <dinput.h>
#include <xaudio2.h>

#define SURFACE_MAX 256 
#define TEXTURE_MAX 512 

#define RELEASE_COMC($) { \
	\
	if ( $ != NULL ) { \
		$->lpVtbl->Release ($); $ = NULL; \
	} \
}

#define TRY_COMC($) { \
	\
	if( ($) != S_OK ) goto __final;	\
	\
}

typedef struct $screen {

	IDirect3DDevice9 *direct3d_device9;
	IDirect3DSurface9 *direct3d_surface9_primary;

	UINT width;
	UINT height;
	UINT pitch_byte;
	UINT pitch_dword;
	HWND window_handle;
	BOOL bwindowed;
	UINT present_flag;
	PUINT video_buffer;
	PUINT source_surface;

} screen_s;

typedef struct $texture {

	UINT width;
	UINT height;
	UINT pitch_byte;
	UINT pitch_dword;
	PUINT pixel_buffer;

} texture_s;

/* ------ keyboard $ input dev interface ------ */ 
static IDirectInput8 *sg_directinput8 = NULL;
static IDirectInputDevice8 *sg_directinput_device8_primary = NULL;
static IDirectInputDevice8 *sg_directinput_device8_secondary = NULL;

/* ------ graphisc $ video dev interface ------ */
static IDirect3D9 *sg_direct3d9 = NULL;
static screen_s sgsa_screen[SURFACE_MAX] = {0};
static texture_s sgsa_texture[TEXTURE_MAX] = {0};

/* ------ audio/wave $ sound dev interface ------ */
static IXAudio2 *sg_xaudio2 = NULL;
static IXAudio2MasteringVoice *sg_mastering_voice = NULL;
static IXAudio2SourceVoice *sg_source_voice = NULL;

/*
  ---------- DllMain ----------
*/
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

/*
  ---------- init_directx_base ----------
*/ 
static 
BOOL sf_init_directx_base (HINSTANCE arg_instance_handle) {

	if ( S_OK != CoInitializeEx (NULL, COINIT_MULTITHREADED) ) 
	/* --- init multithread com - for IXAudio2 ready --- */ {
		return FALSE; 
	}
	/* --- IDirect3D base interface get --- */ 
	sg_direct3d9 = Direct3DCreate9 (D3D_SDK_VERSION);	

	if ( NULL == sg_direct3d9 ) {
		
		goto __final;
	}

	/* --- IXAudio2 base interface get && test enable --- */ 
	if ( S_OK != XAudio2Create (&sg_xaudio2, 0, XAUDIO2_DEFAULT_PROCESSOR) ) {
		
		goto __final;  
	} else if ( S_OK != sg_xaudio2->lpVtbl->CreateMasteringVoice ( sg_xaudio2, 
																  &sg_mastering_voice, 
																   XAUDIO2_DEFAULT_CHANNELS,
																   XAUDIO2_DEFAULT_SAMPLERATE, 
																   0, 
																   0, 
																   NULL 
																 )
			 ) {
		goto __final;
	}
	/* --- IDirectInput8 base interface get && test enable --- */ 
	if ( S_OK != DirectInput8Create (arg_instance_handle, DIRECTINPUT_VERSION, &IID_IDirectInput8, (void **)&sg_directinput8, NULL) ) {

		goto __final; 
	}

	return TRUE; /* do ret - successful */

__final:
	if ( sg_mastering_voice != NULL ) {
		 sg_mastering_voice->lpVtbl->DestroyVoice (sg_mastering_voice); 
	}
	
	RELEASE_COMC (sg_xaudio2);
	RELEASE_COMC (sg_directinput8);
	RELEASE_COMC (sg_direct3d9);

	CoUninitialize();		return FALSE; /* do ret - failed */
}

/*
  ---------- init_directinput8 ----------
*/ 
static 
BOOL sf_init_directinput8 (HWND arg_window_handle) {

	TRY_COMC ( sg_directinput8->lpVtbl->CreateDevice (sg_directinput8, &GUID_SysKeyboard, &sg_directinput_device8_primary,NULL) );
	TRY_COMC ( sg_directinput_device8_primary->lpVtbl->SetCooperativeLevel (sg_directinput_device8_primary, arg_window_handle, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND) );
	TRY_COMC ( sg_directinput_device8_primary->lpVtbl->SetDataFormat (sg_directinput_device8_primary, &c_dfDIKeyboard) );
	TRY_COMC ( sg_directinput_device8_primary->lpVtbl->Acquire (sg_directinput_device8_primary) );

	return TRUE;

__final:
	RELEASE_COMC (sg_directinput_device8_primary);
	return FALSE;
}

/*
  ---------- uninit_directinput8 ----------
*/ 
static 
void sf_uninit_directinput8 (void) {

	if (sg_directinput_device8_primary)
		sg_directinput_device8_primary->lpVtbl->Unacquire (sg_directinput_device8_primary);
	if (sg_directinput_device8_secondary)
		sg_directinput_device8_secondary->lpVtbl->Unacquire (sg_directinput_device8_secondary);

	RELEASE_COMC (sg_directinput_device8_primary);
	RELEASE_COMC (sg_directinput_device8_secondary);
}

/*
  ---------- cc_get_key ----------
*/
__declspec(dllexport) 
void *cc_get_key (void) {

	__declspec(align(32)) static sl_keyset_buf[256];

	if ( S_OK != sg_directinput_device8_primary->lpVtbl->GetDeviceState (sg_directinput_device8_primary, 256, &sl_keyset_buf[0]) ) {
	/* --- maybe lost device --- */ 
		if ( S_OK != sg_directinput_device8_primary->lpVtbl->Acquire (sg_directinput_device8_primary) ) {
		/* --- direct input crash !!! --- */ 
			MessageBox (NULL, TEXT ("IDirectInput8 Crash!!!"), TEXT ("OUT CRASH"), MB_ICONERROR);
			goto crash_deal;
		} else {
			if ( S_OK != sg_directinput_device8_primary->lpVtbl->GetDeviceState (sg_directinput_device8_primary, 256, &sl_keyset_buf[0]) ) {
				MessageBox (NULL, TEXT ("IDirectInput8 Crash!!!"), TEXT ("IN CRASH"), MB_ICONERROR);
			crash_deal:
				/* --- todo --- */;
			}
		}
	}
	return &sl_keyset_buf[0];
}

/*
  ---------- init_directsurface9 ----------
*/ 

/*
  ---------- cc_inline_draw ----------
*/ 
__declspec(dllexport) 
void cc_inline_draw (int arg_surface_id) {

	size_t ry;
	size_t mctemp= 0;
	size_t width = sgsa_screen[arg_surface_id].width << 2;
	size_t height= sgsa_screen[arg_surface_id].height;
	size_t pitch = sgsa_screen[arg_surface_id].pitch_dword;
	DWORD *src_ptr = sgsa_screen[arg_surface_id].video_buffer;
	DWORD *des_ptr = sgsa_screen[arg_surface_id].source_surface;

	for (ry = 0; ry != height; ry ++) {

		memcpy (&des_ptr[mctemp], &des_ptr[mctemp], width);
		mctemp += pitch;
	}
}

/*
  ---------- cc_inline_draw_flush ----------
*/ 
__declspec(dllexport) 
void cc_inline_draw_flush (int arg_surface_id) {

	size_t ry;
	size_t mctemp= 0;
	size_t width = sgsa_screen[arg_surface_id].width << 2;
	size_t height= sgsa_screen[arg_surface_id].height;
	size_t pitch = sgsa_screen[arg_surface_id].pitch_dword;
	DWORD *src_ptr = sgsa_screen[arg_surface_id].video_buffer;
	DWORD *des_ptr = sgsa_screen[arg_surface_id].source_surface;
	IDirect3DDevice9 *ref_ddev = sgsa_screen[arg_surface_id].direct3d_device9;

	for (ry = 0; ry != height; ry ++) {

		memcpy (&des_ptr[mctemp], &des_ptr[mctemp], width);
		mctemp += pitch;
	}
	ref_ddev->lpVtbl->Present (ref_ddev, 0, 0, 0, 0);
}

/*
  ---------- cc_inline_bitblt ----------
*/ 
__declspec(dllexport) 
void cc_inline_bitblt (	int arg_surface_id, 
						int arg_src_pos_x,
						int arg_src_pos_y,
						int arg_des_pos_x,
						int arg_des_pos_y,
						int arg_copy_width,
						int arg_copy_height
					) {

	size_t ry;
	size_t mctemp= 0;
	size_t width = arg_copy_width << 2;
	size_t height= arg_copy_height;
	size_t pitch = sgsa_screen[arg_surface_id].pitch_dword;
	DWORD *src_ptr = &sgsa_screen[arg_surface_id].video_buffer[arg_src_pos_x + arg_src_pos_y * pitch];
	DWORD *des_ptr = &sgsa_screen[arg_surface_id].source_surface[arg_des_pos_x + arg_des_pos_y * pitch];
	IDirect3DDevice9 *ref_ddev = sgsa_screen[arg_surface_id].direct3d_device9;

	for (ry = 0; ry != height; ry ++) {

		memcpy (&des_ptr[mctemp], &des_ptr[mctemp], width);
		mctemp += pitch;
	}
}

/*
  ---------- cc_inline_bitblt_flush ----------
*/ 
__declspec(dllexport) 
void cc_inline_bitblt_flush ( int arg_surface_id, 
							  int arg_src_pos_x,
							  int arg_src_pos_y,
							  int arg_des_pos_x,
							  int arg_des_pos_y,
							  int arg_copy_width,
							  int arg_copy_height
						  ) {
/*
 * main surface copy overlapping can cause flicker
*/
	size_t ry;
	size_t mctemp= 0;
	size_t width = arg_copy_width << 2;
	size_t height= arg_copy_height;
	size_t pitch = sgsa_screen[arg_surface_id].pitch_dword;
	DWORD *src_ptr = &sgsa_screen[arg_surface_id].video_buffer[arg_src_pos_x + arg_src_pos_y * pitch];
	DWORD *des_ptr = &sgsa_screen[arg_surface_id].source_surface[arg_des_pos_x + arg_des_pos_y * pitch];
	IDirect3DDevice9 *ref_ddev = sgsa_screen[arg_surface_id].direct3d_device9;

	for (ry = 0; ry != height; ry ++) {

		memcpy (&des_ptr[mctemp], &des_ptr[mctemp], width);
		mctemp += pitch;
	}
	ref_ddev->lpVtbl->Present (ref_ddev, 0, 0, 0, 0);
}

/*
  ---------- cc_bitblt_texture_to_surface_buffer ----------
*/ 
__declspec(dllexport) 
void cc_bitblt_texture_to_surface_buffer (	int arg_surface_id, 
											int arg_texture_id,
											int arg_src_pos_x,
											int arg_src_pos_y,
											int arg_des_pos_x,
											int arg_des_pos_y,
											int arg_copy_width,
											int arg_copy_height
										) {

	size_t ry;
	size_t smctemp= 0;
	size_t dmctemp= 0;
	size_t width = arg_copy_width << 2;
	size_t height= arg_copy_height;
	size_t spitch = sgsa_texture[arg_texture_id].pitch_dword;
	size_t dpitch = sgsa_screen[arg_surface_id].pitch_dword;
	DWORD *src_ptr = &sgsa_texture[arg_texture_id].pixel_buffer[arg_src_pos_x + arg_src_pos_y * spitch];
	DWORD *des_ptr = &sgsa_screen[arg_surface_id].video_buffer[arg_des_pos_x + arg_des_pos_y * dpitch];
	IDirect3DDevice9 *ref_ddev = sgsa_screen[arg_surface_id].direct3d_device9;

	for (ry = 0; ry != height; ry ++) {

		memcpy (&des_ptr[smctemp], &des_ptr[dmctemp], width);
		smctemp += spitch;
		dmctemp += dpitch;
	}
}

/*
  ---------- cc_bitblt_texture_to_surface_buffer_flush ----------
*/ 
__declspec(dllexport) 
void cc_bitblt_texture_to_surface_buffer_flush (int arg_surface_id, 
												int arg_texture_id,
												int arg_src_pos_x,
												int arg_src_pos_y,
												int arg_des_pos_x,
												int arg_des_pos_y,
												int arg_copy_width,
												int arg_copy_height
											) {

	size_t ry;
	size_t smctemp= 0;
	size_t dmctemp= 0;
	size_t width = arg_copy_width << 2;
	size_t height= arg_copy_height;
	size_t spitch = sgsa_texture[arg_texture_id].pitch_dword;
	size_t dpitch = sgsa_screen[arg_surface_id].pitch_dword;
	DWORD *src_ptr = &sgsa_texture[arg_texture_id].pixel_buffer[arg_src_pos_x + arg_src_pos_y * spitch];
	DWORD *des_ptr = &sgsa_screen[arg_surface_id].video_buffer[arg_des_pos_x + arg_des_pos_y * dpitch];
	IDirect3DDevice9 *ref_ddev = sgsa_screen[arg_surface_id].direct3d_device9;

	for (ry = 0; ry != height; ry ++) {

		memcpy (&des_ptr[smctemp], &des_ptr[dmctemp], width);
		smctemp += spitch;
		dmctemp += dpitch;
	}
	ref_ddev->lpVtbl->Present (ref_ddev, 0, 0, 0, 0);
}

/*
  ---------- cc_bitblt_texture_to_surface_direct ----------
*/ 
__declspec(dllexport) 
void cc_bitblt_texture_to_surface_direct (	int arg_surface_id, 
											int arg_texture_id,
											int arg_src_pos_x,
											int arg_src_pos_y,
											int arg_des_pos_x,
											int arg_des_pos_y,
											int arg_copy_width,
											int arg_copy_height
										) {

	size_t ry;
	size_t smctemp= 0;
	size_t dmctemp= 0;
	size_t width = arg_copy_width << 2;
	size_t height= arg_copy_height;
	size_t spitch = sgsa_texture[arg_texture_id].pitch_dword;
	size_t dpitch = sgsa_screen[arg_surface_id].pitch_dword;
	DWORD *src_ptr = &sgsa_texture[arg_texture_id].pixel_buffer[arg_src_pos_x + arg_src_pos_y * spitch];
	DWORD *des_ptr = &sgsa_screen[arg_surface_id].source_surface[arg_des_pos_x + arg_des_pos_y * dpitch];
	IDirect3DDevice9 *ref_ddev = sgsa_screen[arg_surface_id].direct3d_device9;

	for (ry = 0; ry != height; ry ++) {

		memcpy (&des_ptr[smctemp], &des_ptr[dmctemp], width);
		smctemp += spitch;
		dmctemp += dpitch;
	}
}

/*
  ---------- cc_bitblt_texture_to_surface_direct_flush ----------
*/ 
__declspec(dllexport) 
void cc_bitblt_texture_to_surface_direct_flush (int arg_surface_id, 
												int arg_texture_id,
												int arg_src_pos_x,
												int arg_src_pos_y,
												int arg_des_pos_x,
												int arg_des_pos_y,
												int arg_copy_width,
												int arg_copy_height
											) {

	size_t ry;
	size_t smctemp= 0;
	size_t dmctemp= 0;
	size_t width = arg_copy_width << 2;
	size_t height= arg_copy_height;
	size_t spitch = sgsa_texture[arg_texture_id].pitch_dword;
	size_t dpitch = sgsa_screen[arg_surface_id].pitch_dword;
	DWORD *src_ptr = &sgsa_texture[arg_texture_id].pixel_buffer[arg_src_pos_x + arg_src_pos_y * spitch];
	DWORD *des_ptr = &sgsa_screen[arg_surface_id].source_surface[arg_des_pos_x + arg_des_pos_y * dpitch];
	IDirect3DDevice9 *ref_ddev = sgsa_screen[arg_surface_id].direct3d_device9;

	for (ry = 0; ry != height; ry ++) {

		memcpy (&des_ptr[smctemp], &des_ptr[dmctemp], width);
		smctemp += spitch;
		dmctemp += dpitch;
	}
	ref_ddev->lpVtbl->Present (ref_ddev, 0, 0, 0, 0);
}

/*
  ---------- cc_graph_flush ----------
*/ 
__declspec(dllexport) 
void cc_graph_flush (int arg_surface_id) {

	sgsa_screen[arg_surface_id].direct3d_device9->lpVtbl->Present (sgsa_screen[arg_surface_id].direct3d_device9, 0, 0, 0, 0);
}



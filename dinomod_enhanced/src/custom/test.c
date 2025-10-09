#include "modding.h"
#include "recomputils.h"

#include "functions.h"
#include "sys/gfx/gx.h"
#include "sys/gfx/texture.h"
#include "sys/main.h"
#include "sys/objects.h"

extern Gfx *gCurGfx;

#define FADE_SPEED 12

static Texture *mapTexture;
static f32 opacity = 0;
static s32 bFadeIn = TRUE;
static s32 fadesLeft = 0;

RECOMP_HOOK_RETURN("game_init") void _init(void) {
    mapTexture = queue_load_texture_proxy(-663);
}

RECOMP_CALLBACK("*", recomp_on_game_tick) void _test(void) {
    if (get_player() == NULL) {
        return;
    }

    if (fadesLeft > 0) {
        u32 res = get_some_resolution_encoded();
        u32 screenWidth = RESOLUTION_WIDTH(res);
        u32 screenHeight = RESOLUTION_HEIGHT(res);

        func_8003825C(&gCurGfx, mapTexture, 
            screenWidth - mapTexture->width - 16, 
            screenHeight - mapTexture->height - 16, 
            0, 0, 
            opacity, 
            0);

        if (!bFadeIn) {
            opacity -= FADE_SPEED * delayFloat;
            
            if (opacity <= 0) {
                fadesLeft--;
                opacity = 0;
                bFadeIn = TRUE;
            }
        } else {
            opacity += FADE_SPEED * delayFloat;

            if (opacity >= 255.0f) {
                opacity = 255.0f;
                bFadeIn = FALSE;
            }
        }
    }
}

#include "recomp/dlls/engine/29_gplay_recomp.h"

RECOMP_HOOK_RETURN_DLL(gplay_checkpoint) void _checkpoint(Vec3f *position, s16 yaw, s32 param3, s32 mapLayer) {
    fadesLeft = 3;
    recomp_printf("checkpoint(%d)\n", param3);
}

RECOMP_HOOK_RETURN_DLL(gplay_restart_set) void _restart_set(void) {
    recomp_printf("restart_set\n");
}

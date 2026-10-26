#include "dlls/engine/29_gplay.h"
#include "game/gamebits.h"
#include "sys/main.h"
#include "sys/map_enums.h"
#include "sys/math.h"
#include "macros.h"

#include "chapter_select.h"

static void ch_ship_battle(void) { }

// krystal intro
static void ch_wl_1(void) {
    chselect_set_location(PLAYER_KRYSTAL, 13630.91f, 211.0f, -620.5f, M_180_DEGREES, 0);
    PlayerLightActions lact = DEFAULT_LACTIONS;
    lact.unk0[0] = 120;
    lact.unk0[1] = 119;
    lact.unkC[1] = 93;
    chselect_set_light_actions(PLAYER_KRYSTAL, &lact);
    PlayerEnvActions env = DEFAULT_ENVACTIONS;
    env.unk4 = 165;
    env.unk6 = 166;
    env.unk8 = 168;
    // the rest might be overkill? ship battle leftovers?
    env.unkA = 100;
    env.unkC = 150;
    env.unkE = 151;
    env.unk10 = -11319; env.unk14 = 786; env.unk18 = -14984;
    env.unk1C = -13714; env.unk20 = 79; env.unk24 = -16441;
    env.unk28 = -14363; env.unk2C = 14; env.unk30 = -16480;
    chselect_set_env_actions(PLAYER_KRYSTAL, &env);
    chselect_set_music(PLAYER_KRYSTAL, 54, -1, 285, -1);
    chselect_set_map_state(MAP_WARLOCK_MOUNTAIN, 1, G1);

    // tutorials completed on the Galleon
    mainSetBits(BIT_Tutorial_Magic_Crystal, 1);
    mainSetBits(BIT_Tutorial_Collected_Energy_Egg, 1);

    mainSetBits(BIT_SB_Battle_Started, 1);
    mainSetBits(BIT_SB_Found_Kyte, 1);
    mainSetBits(BIT_Galleon_Arrived_at_Warlock_Mountain, 1);
    mainSetBits(BIT_WL_Load_Unload_Galleon, 1);
}

static void ch_ice_mountain(void) {
    /* ---- during WL ---- */
    // move WL_Column_Top onto the pressure switch
    chselect_move_setup(0x428E0, MAP_WARLOCK_MOUNTAIN, 12357.0f, -83.7f, 154.53f);

    mainSetBits(BIT_Spell_Projectile, 1);
    mainSetBits(BIT_Play_Seq_00EF_Scales_Escapes_With_Kyte, 1);
    mainSetBits(BIT_Krystal_Used_Warp_Crystal, 1);
    mainSetBits(BIT_WM_EarthWalker_Died, 1);
    mainSetBits(BIT_Krystal_Warp_Crystal, 1);
    mainSetBits(BIT_WM_Played_Randorn_First_Meeting, 1);
    mainSetBits(BIT_WL_Load_Unload_Galleon, 0);
    mainSetBits(BIT_WM_Near_Cave_Exit_Krystal_Side, 1); // ?
    mainSetBits(BIT_SP_Foodbag_S, 1);
    mainSetBits(BIT_53A, 1); // what in the world sets this
    mainSetBits(BIT_8B0, 1); // WL_seqpoint (which one)
    mainSetBits(BIT_8F4, 1); // WL_seqpoint cond (which one)
    mainSetBits(BIT_903, 1); // projectile switch
    mainSetBits(BIT_Shown_ZLock_Interact_Message, 1);
    mainSetBits(BIT_Tutorial_Magic_Plant, 1);
    mainSetBits(BIT_Tutorial_ZLock_Talk, 1);

    //chselect_set_map_state(MAP_WARLOCK_MOUNTAIN, 1, G2); // before warp

    mainSetBits(BIT_Kyte_Flight_Curve, 121); // needed?

    /* ---- warp to SC ---- */
    mainSetBits(BIT_Talking_to_Rocky, 1);
    chselect_set_map_state(MAP_WARLOCK_MOUNTAIN, 1, G_None);
    chselect_set_map_state(MAP_SWAPSTONE_CIRCLE, 2, G0);

    chselect_set_location(PLAYER_KRYSTAL, -1057.8f, 304.0f, 17436.0f, M_180_DEGREES, 0);
    {
        PlayerLightActions lact = DEFAULT_LACTIONS;
        lact.unk0[0] = 485;
        lact.unk0[1] = 486;
        lact.unkC[1] = 128;
        chselect_set_light_actions(PLAYER_KRYSTAL, &lact);
        PlayerEnvActions env = DEFAULT_ENVACTIONS;
        env.unk4 = 79;
        env.unk6 = 80;
        env.unk8 = 81;
        chselect_set_env_actions(PLAYER_KRYSTAL, &env);
    }
    chselect_set_music(PLAYER_KRYSTAL, 185, -1, 203, -1);

    /* ---- swap to sabre ---- */
    chselect_set_player(PLAYER_SABRE);
    //chselect_set_location(PLAYER_SABRE, 370.72f, 6382.78f, 2406.9f, 0, 2); // before cutscene

    // skip intro cutscene
    {
        mainSetBits(BIT_Play_Seq_0063_IM_Sabre_Intro, 1);
        mainSetBits(BIT_Played_Seq_0063_IM_Sabre_Intro, 1);
        
        chselect_set_map_state(MAP_ICE_MOUNTAIN_1, 1, G0 | G3 | G4 | G5 | G7);
        
        PlayerLightActions lact = DEFAULT_LACTIONS;
        lact.unk0[0] = 347;
        lact.unk0[1] = 348;
        lact.unk4 = 380;
        lact.unk6 = 356;
        lact.unkC[1] = 379;
        chselect_set_light_actions(PLAYER_SABRE, &lact);
        
        PlayerEnvActions env = DEFAULT_ENVACTIONS;
        env.unk4 = 260;
        env.unk6 = 158;
        env.unk8 = 163;
        env.unkA = 256;
        env.unkC = 42;
        env.unk10 = 496; env.unk14 = 6488; env.unk18 = 2236;
        env.unk1C = 553; env.unk20 = 6485; env.unk24 = 2252;
        env.unk3D = 1;
        chselect_set_env_actions(PLAYER_SABRE, &env);
        
        chselect_set_music(PLAYER_SABRE, 155, -1, 151, -1);

        chselect_set_location(PLAYER_SABRE, 493.75f, 6488.87f, 2232.4f, M_90_DEGREES, 2);
    }
}

static void ch_snowhorn_wastes_1(void) {
    /* ice mountain/race */
    mainSetBits(BIT_6F, 1); // IMMultiSeq
    mainSetBits(BIT_IM_MultiSeq_2, 1);
    mainSetBits(BIT_IM_MultiSeq_3, 1);
    mainSetBits(BIT_377, 1); // IMPrisonGate restore bit
    mainSetBits(BIT_382, 1); // ice mountain projectile switch
    mainSetBits(BIT_3AE, 1); // IMMultiSeq
    mainSetBits(BIT_3B9, 1); // IMFence openA
    mainSetBits(BIT_3BA, 1); // IMIcicle enabled bit

    chselect_set_map_state(MAP_ICE_MOUNTAIN_1, 2, G1);

    /* snowhorn wastes */
    mainSetBits(BIT_Play_Seq_00EA_IM_Sabre_Falls_Into_Hot_Spring, 1);
    mainSetBits(BIT_37A, 1); // BIT_Played_Seq_00EA_IM_Sabre_Falls_Into_Hot_Spring
    mainSetBits(BIT_IM_Race_Ended, 1);
    mainSetBits(BIT_Tricky_Talk_Sequence, 1);
    mainSetBits(BIT_4E3, 255); // tricky related

    chselect_set_map_state(MAP_SNOWHORN_WASTES, 1, G_None);

    chselect_set_location(PLAYER_SABRE, -2420.59f, -73.43f, 936.64f, M_90_DEGREES, 0);

    PlayerLightActions lact = DEFAULT_LACTIONS;
    lact.unk0[0] = 389;
    lact.unk0[1] = 390;
    lact.unk4 = 394;
    lact.unk6 = 356;
    lact.unkC[1] = 379;
    lact.unk12 = 1;
    chselect_set_light_actions(PLAYER_SABRE, &lact);

    PlayerEnvActions env = DEFAULT_ENVACTIONS;
    env.unk4 = 180;
    env.unk6 = 182;
    env.unk8 = 181;
    env.unkA = 38;
    env.unkC = 42;
    env.unk10 = 162; env.unk14 = 6530; env.unk18 = 1921;
    chselect_set_env_actions(PLAYER_SABRE, &env);

    chselect_set_music(PLAYER_SABRE, 66, -1, 151, -1);
}

static void ch_swapstone_hollow_1(void) {
    /* snowhorn wastes tutorial area */
    mainSetBits(BIT_6, 1); // NWtree 0xF0C falls
    mainSetBits(BIT_7, 1); // NWtree 0x30312 falls
    mainSetBits(BIT_8, 1); // set by NWtricky after the tutorial SharpClaw is defeated, enables some TriggerPoint in every shrine?
    mainSetBits(BIT_SW_Grumpy_SnowHorn_Stopped_Geyser, 1);
    mainSetBits(BIT_SW_Tricky_Ball_Collected, 1);
    mainSetBits(BIT_SnowHorn_Tutorial_GotAlpineRoot1, 1);
    mainSetBits(BIT_A8, 1); // WallAnimator 0x30637 dug bit
    mainSetBits(BIT_AB, 1); // WallAnimator 0x30A21 dug bit
    mainSetBits(BIT_SnowHorn_Tutorial_Defeated_SharpClaw, 1);
    mainSetBits(BIT_SW_Tricky_Toy_Unearthed, 1);
    mainSetBits(BIT_112, 1); // GroundAnimator 0x1743 dug bit
    mainSetBits(BIT_113, 1); // GroundAnimator 0x3047F dug bit
    mainSetBits(BIT_SnowHorn_Tutorial_GotAlpineRoot2, 1);
    mainSetBits(BIT_Tutorial_Collected_Blue_Mushroom, 1);
    mainSetBits(BIT_188, 1); // snowhorn wastes levelname shown
    mainSetBits(BIT_Tricky_Ball_Unlocked, 1);
    mainSetBits(BIT_4D3, 1); // NWboulder 0x30398
    mainSetBits(BIT_4D4, 1); // set/used by NWtricky
    mainSetBits(BIT_Tricky_Talk_Sequence, 145);
    mainSetBits(BIT_4E3, 1); // tricky related
    mainSetBits(BIT_Tricky_Unlocked_Sidekick_Commands, 1);
    mainSetBits(BIT_SnowHorn_Tutorial_NumRootsFed, 2);
    mainSetBits(BIT_587, 1); // ?? what sets this
    mainSetBits(BIT_Map_SW, 1);
    mainSetBits(BIT_90F, 1); // ?? what sets this
    mainSetBits(BIT_Tutorial_Collected_Scarab, 1);
    mainSetBits(BIT_913, 1); // push/pull tutorial?
    mainSetBits(BIT_916, 1); // GroundAnimator 0x42E3F dug bit
    mainSetBits(BIT_UI_Scarab_Counter_Enabled, 1);

    chselect_set_min_scarabs(PLAYER_SABRE, 10);

    chselect_set_map_state(MAP_ICE_MOUNTAIN_1, 2, G_None);
    chselect_set_map_state(MAP_SNOWHORN_WASTES, 1, G_None);

    /* snowhorn wastes */
    mainSetBits(BIT_26, 1); // NWtreebridge

    chselect_set_location(PLAYER_SABRE, -6984.36f, -830.41f, -569.07f, M_90_DEGREES, 0);

    PlayerLightActions lact = DEFAULT_LACTIONS;
    lact.unk0[0] = 389;
    lact.unk0[1] = 390;
    lact.unk4 = 394;
    lact.unk6 = 356;
    lact.unkC[1] = 1;
    lact.unk12 = 61;
    chselect_set_light_actions(PLAYER_SABRE, &lact);

    PlayerEnvActions env = DEFAULT_ENVACTIONS;
    env.unk4 = 180;
    env.unk6 = 182;
    env.unk8 = 181;
    env.unkA = 100;
    //env.unkC = 42; // the evil snow that never goes away
    chselect_set_env_actions(PLAYER_SABRE, &env);

    chselect_set_music(PLAYER_SABRE, 281, -1, 65, -1);
}

static void ch_crf_start(void) {
    //set_map(MAP_CLOUDRUNNER_FORTRESS, 0, PLAYER_KRYSTAL);

    // TODO: move
    chselect_set_min_magic(PLAYER_KRYSTAL, 15);
    mainSetBits(BIT_Spell_Forcefield, 1);
    mainSetBits(BIT_Krystal_Foodbag_L, 1);
    mainSetBits(BIT_CC_Rescued_Kyte, 1);
}

static void ch_crf_dungeon_start(void) {
    //set_map(MAP_CLOUDRUNNER_DUNGEON, 0, PLAYER_KRYSTAL);
    chselect_set_music(PLAYER_KRYSTAL, 204, -1, 3, -1);

    mainSetBits(BIT_Play_Seq_017C_CF_This_Is_CloudRunner_Fortress, 1);
    mainSetBits(BIT_Played_Seq_017C_CF_This_Is_CloudRunner_Fortress, 1);
    mainSetBits(BIT_CF_Entrance_Trigger_Passed, 1); // load entrance stairwell

    mainSetBits(BIT_213, 1); // crf entrance stairwell seq play
    mainSetBits(BIT_214, 1); // crf entrance stairwell seq played

    mainSetBits(BIT_CRF_Scales_And_Queen_In_Courtyard, 0);
    mainSetBits(BIT_Play_Seq_0041_Scales_Kills_The_Queen, 1);
    mainSetBits(BIT_Played_Seq_0041_Scales_Kills_The_Queen, 1);
}

static Chapter chapters[] = {
    { "Ship Battle", ch_ship_battle },
    { "Warlock Mountain 1", ch_wl_1 },
    { "Ice Mountain", ch_ice_mountain },
    { "SnowHorn Wastes 1", ch_snowhorn_wastes_1 },
    { "SwapStone Hollow 1", ch_swapstone_hollow_1 },
    { "(WIP) CloudRunner Fortress Start", ch_crf_start },
    { "CloudRunner Dungeon", ch_crf_dungeon_start },
};

Chapter* chselect_get_chapters(s32* count) {
    if (count != NULL) {
        *count = ARRAYCOUNT(chapters);
    }
    
    return chapters;
}

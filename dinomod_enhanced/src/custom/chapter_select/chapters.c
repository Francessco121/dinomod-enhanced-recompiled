#include "dlls/engine/29_gplay.h"
#include "game/gamebits.h"
#include "sys/main.h"
#include "sys/map_enums.h"
#include "sys/math.h"
#include "macros.h"

#include "chapter_select.h"

static void ch_stub(void) { }

static void ch_ship_battle(void) { }

// krystal intro
static void ch_wl_1(void) {
    chselect_set_location(PLAYER_KRYSTAL, 13630.91f, 211.0f, -620.5f, M_180_DEGREES, 0);
    PlayerLightActions light = DEFAULT_LACTIONS;
    light.unk0[0] = 120;
    light.unk0[1] = 119;
    light.unkC[1] = 93;
    chselect_set_light(PLAYER_KRYSTAL, &light);
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
    chselect_set_env(PLAYER_KRYSTAL, &env);
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

    mainSetBits(BIT_Kyte_Flight_Curve, 121);

    /* ---- warp to SC ---- */
    mainSetBits(BIT_Talking_to_Rocky, 1);
    chselect_set_map_state(MAP_WARLOCK_MOUNTAIN, 1, G_None);
    chselect_set_map_state(MAP_SWAPSTONE_CIRCLE, 2, G0);

    chselect_set_location(PLAYER_KRYSTAL, -1057.8f, 304.0f, 17436.0f, M_180_DEGREES, 0);
    {
        PlayerLightActions light = DEFAULT_LACTIONS;
        light.unk0[0] = 485;
        light.unk0[1] = 486;
        light.unkC[1] = 128;
        chselect_set_light(PLAYER_KRYSTAL, &light);
        PlayerEnvActions env = DEFAULT_ENVACTIONS;
        env.unk4 = 79;
        env.unk6 = 80;
        env.unk8 = 81;
        chselect_set_env(PLAYER_KRYSTAL, &env);
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
        
        PlayerLightActions light = DEFAULT_LACTIONS;
        light.unk0[0] = 347;
        light.unk0[1] = 348;
        light.unk4 = 380;
        light.unk6 = 356;
        light.unkC[1] = 379;
        chselect_set_light(PLAYER_SABRE, &light);
        
        PlayerEnvActions env = DEFAULT_ENVACTIONS;
        env.unk4 = 260;
        env.unk6 = 158;
        env.unk8 = 163;
        env.unkA = 256;
        env.unkC = 42;
        env.unk10 = 496; env.unk14 = 6488; env.unk18 = 2236;
        env.unk1C = 553; env.unk20 = 6485; env.unk24 = 2252;
        env.unk3D = 1;
        chselect_set_env(PLAYER_SABRE, &env);
        
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

    PlayerLightActions light = DEFAULT_LACTIONS;
    light.unk0[0] = 389;
    light.unk0[1] = 390;
    light.unk4 = 394;
    light.unk6 = 356;
    light.unkC[1] = 379;
    light.unk12 = 1;
    chselect_set_light(PLAYER_SABRE, &light);

    PlayerEnvActions env = DEFAULT_ENVACTIONS;
    env.unk4 = 180;
    env.unk6 = 182;
    env.unk8 = 181;
    env.unkA = 38;
    env.unkC = 42;
    env.unk10 = 162; env.unk14 = 6530; env.unk18 = 1921;
    chselect_set_env(PLAYER_SABRE, &env);

    chselect_set_music(PLAYER_SABRE, 66, -1, 151, -1);
}

static void ch_swapstone_hollow_1(void) {
    chselect_set_min_magic(PLAYER_SABRE, 5);

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

    PlayerLightActions light = DEFAULT_LACTIONS;
    light.unk0[0] = 389;
    light.unk0[1] = 390;
    light.unk4 = 394;
    light.unk6 = 356;
    light.unkC[1] = 1;
    light.unk12 = 61;
    chselect_set_light(PLAYER_SABRE, &light);

    PlayerEnvActions env = DEFAULT_ENVACTIONS;
    env.unk4 = 180;
    env.unk6 = 182;
    env.unk8 = 181;
    env.unkA = 100;
    //env.unkC = 42; // the evil snow that never goes away
    chselect_set_env(PLAYER_SABRE, &env);

    chselect_set_music(PLAYER_SABRE, 281, -1, 65, -1);
}

static void ch_swapstone_circle_1(void) {
    /* swapstone hollow 1 (queen earthwalker quest) */
    mainSetBits(BIT_13, 1); // SHbluemushroom 0x308F3 collected bit
    mainSetBits(BIT_A1, 1); // DINOMOD SPECIFIC: stops SHseqobject 0x34841 from replaying
    mainSetBits(BIT_SH_Queen_EW_Quest_Progress, 7);
    mainSetBits(BIT_SH_Move_Thorntail_Blocking_Hollow_Log, 1);
    mainSetBits(BIT_SH_Queen_EW_White_Mushrooms_Eaten, 10);
    mainSetBits(BIT_F4, 1); // SHbluemushroom 0x308F6 collected bit
    mainSetBits(BIT_F5, 1); // SHbluemushroom 0x308F2 collected bit
    mainSetBits(BIT_15C, 1); // SHbluemushroom 0x308F4 collected bit
    mainSetBits(BIT_177, 1); // SHbluemushroom 0x308F5 collected bit
    //mainSetBits(BIT_2B2, 1); // SC_sequences 0x2733 played bit
    mainSetBits(BIT_460, 1); // SHbluemushroom 0x307D5 collected bit
    mainSetBits(BIT_461, 1); // SHbluemushroom 0x429E9 collected bit
    mainSetBits(BIT_462, 1); // SHbluemushroom 0x307D4 collected bit
    mainSetBits(BIT_463, 1); // SHbluemushroom 0x30832 collected bit
    mainSetBits(BIT_464, 1); // SHbluemushroom 0x30844 collected bit
    mainSetBits(BIT_484, 1); // VFP SHseqobject 0x30AFA played bit
    mainSetBits(BIT_485, 1); // VFP SHseqobject 0x30AFC played bit
    mainSetBits(BIT_Play_Seq_0298_Queen_Shows_VFPT, 1); // VFP SHseqobject 0x30AFA played bit
    mainSetBits(BIT_Play_Seq_0299_Queen_Shows_SpellStones, 1); // VFP SHseqobject 0x30AFC played bit
    mainSetBits(BIT_Tricky_Talk_Sequence, 201);
    mainSetBits(BIT_4E3, 255); // tricky related
    mainSetBits(BIT_658, 1); // ExplodeAnimator 0x348E6
    mainSetBits(BIT_659, 1); // ExplodeAnimator 0x348E9
    mainSetBits(BIT_65A, 1); // ExplodeAnimator 0x348EE
    mainSetBits(BIT_8D2, 1); // SwapStone Hollow levelname shown
    mainSetBits(BIT_SH_Move_Thorntail_Blocking_Swapstone, 1);

    //chselect_set_map_state(MAP_SWAPSTONE_HOLLOW, 1, G0);
    chselect_set_map_state(MAP_VOLCANO_FORCE_POINT_TEMPLE, 11, G_None);

    chselect_set_min_scarabs(PLAYER_SABRE, 30);

    chselect_set_location(PLAYER_SABRE, -6571.54f, -632.0f, -1607.57f, 0, 0);

    {
        PlayerLightActions light = DEFAULT_LACTIONS;
        light.unk0[0] = 389;
        light.unk0[1] = 401;
        light.unk4 = 402;
        light.unk6 = 403;
        light.unkC[1] = 1;
        light.unk12 = 1;
        chselect_set_light(PLAYER_SABRE, &light);

        PlayerEnvActions env = DEFAULT_ENVACTIONS;
        env.unk4 = 97;
        env.unk6 = 95;
        env.unk8 = 96;
        env.unkA = 100;
        chselect_set_env(PLAYER_SABRE, &env);

        chselect_set_music(PLAYER_SABRE, 281, -1, 1 /*5*/, -1);
    }

    mainSetBits(BIT_Talked_to_Rocky, 1);
    mainSetBits(BIT_883, 1); // ?
    mainSetBits(BIT_Play_Seq_035F_Rocky_Intro, 1);
    mainSetBits(BIT_Talking_to_Rocky, 1);

    /* swap to krystal */
    chselect_set_player(PLAYER_KRYSTAL);

    mainSetBits(BIT_2B2, 0);

    chselect_set_map_state(MAP_SWAPSTONE_HOLLOW, 1, G_None);
    chselect_set_map_state(MAP_SWAPSTONE_CIRCLE, 2, G0);

    chselect_set_location(PLAYER_KRYSTAL, -1048.82f, 307.0f, 17424.86f, 0, 0);

    {
        PlayerLightActions light = DEFAULT_LACTIONS;
        light.unk0[0] = 485;
        light.unk0[1] = 486;
        light.unkC[1] = 128;
        chselect_set_light(PLAYER_KRYSTAL, &light);

        PlayerEnvActions env = DEFAULT_ENVACTIONS;
        env.unk4 = 79;
        env.unk6 = 80;
        env.unk8 = 81;
        chselect_set_env(PLAYER_KRYSTAL, &env);

        chselect_set_music(PLAYER_KRYSTAL, 185, -1, 18, -1);
    }
}

static void ch_cape_claw_1(void) {
    /* swapstone circle */
    mainSetBits(BIT_Talking_to_Rocky, 0);
    mainSetBits(BIT_Kyte_Flight_Curve, 50);
    mainSetBits(BIT_8C3, 1); // SwapStone Circle levelname shown

    chselect_set_map_state(MAP_SWAPSTONE_CIRCLE, 2, G1 | G6);
    
    chselect_set_min_scarabs(PLAYER_KRYSTAL, 20);

    /* cc start */
    chselect_set_location(PLAYER_KRYSTAL, 1403.51f, 158.35f, 16944.01f, -M_90_DEGREES, 0);

    PlayerLightActions light = DEFAULT_LACTIONS;
    light.unk0[0] = 485;
    light.unk0[1] = 486;
    light.unk12 = 1;
    chselect_set_light(PLAYER_KRYSTAL, &light);

    PlayerEnvActions env = DEFAULT_ENVACTIONS;
    env.unk4 = 434;
    env.unk6 = 435;
    env.unk8 = 9;
    chselect_set_env(PLAYER_KRYSTAL, &env);

    chselect_set_music(PLAYER_KRYSTAL, 218, -1, 187, -1);
}

static void ch_cape_claw_1_courtyard(void) {
    // gas room "CCboulder"s
    chselect_move_setup(0x42DEA, MAP_CAPE_CLAW, 3563.9375f,   -102.0f, 18277.742188f);
    chselect_move_setup(0x42DE9, MAP_CAPE_CLAW, 3606.336914f, -102.0f, 18309.619141f);
    chselect_move_setup(0x42DE8, MAP_CAPE_CLAW, 3531.695313,  -102.0f, 18309.619141f);
    chselect_move_setup(0x42DE7, MAP_CAPE_CLAW, 3563.9375f,   -102.0f, 18342.292969f);

    mainSetBits(BIT_CC_Bribed_GuardClaw, 1);
    mainSetBits(BIT_8B, 1); // CCseqpoint 0x2CD9
    mainSetBits(BIT_CC_Completed_Gas_Chamber_Puzzle, 1);
    mainSetBits(BIT_168, 1); // CClogpush
    mainSetBits(BIT_187, 1); // Cape Claw levelname shown
    mainSetBits(BIT_Spell_Forcefield, 1);
    mainSetBits(BIT_Played_Seq_022F_CC_Lightfoot_Gives_Spellpage, 1);
    mainSetBits(BIT_246, 1); // ?? what sets this
    mainSetBits(BIT_295, 1); // ?? what sets this
    mainSetBits(BIT_Gold_Nugget_CC, 1);
    mainSetBits(BIT_3A0, 1); // ?
    mainSetBits(BIT_Play_Seq_022F_CC_Lightfoot_Gives_Spellpage, 1);
    mainSetBits(BIT_3B8, 1); // CCclawdoor restore bit
    mainSetBits(BIT_3C1, 1); // CCclawdoor open bit B
    mainSetBits(BIT_3C2, 1); // CCclawdoor open bit A
    mainSetBits(BIT_CC_Shot_Down_Lightfoot_Cage, 1);
    mainSetBits(BIT_3E6, 1); // CCdockdoor1 0x3032D
    mainSetBits(BIT_3E7, 1); // CCdockdoor2 0x3435D
    mainSetBits(BIT_Kyte_Flight_Curve, 1);
    mainSetBits(BIT_603, 1); // CCseqobject 0x34046 played bit
    mainSetBits(BIT_627, 1); // golden nugget count

    //mainSetBits(BIT_CC_Courtyard_Gate_Left_Lever_or_Lantern, 1);
    //mainSetBits(BIT_CC_Courtyard_Gate_Right_Lever_or_Lantern, 1);
    //mainSetBits(BIT_CC_Gate_Opened, 1);

    chselect_set_map_state(MAP_CAPE_CLAW, 1, G3 | G4 | G13);
    chselect_set_map_state(MAP_SWAPSTONE_CIRCLE, 2, G_None);

    /* courtyard start (before gate) */
    chselect_set_location(PLAYER_KRYSTAL, 4336.79f, -8.0f, 17994.89f, -M_90_DEGREES, 0);

    PlayerLightActions light = DEFAULT_LACTIONS;
    light.unk0[0] = 485;
    light.unk0[1] = 498;
    light.unk12 = 1;
    chselect_set_light(PLAYER_KRYSTAL, &light);

    PlayerEnvActions env = DEFAULT_ENVACTIONS;
    env.unk4 = 302;
    env.unk6 = 304;
    env.unk8 = 303;
    chselect_set_env(PLAYER_KRYSTAL, &env);

    chselect_set_music(PLAYER_KRYSTAL, 218, -1, 115, -1);
}

// LightFoot ambush
static void ch_lightfoot_village_1(void) {
    /* cape claw courtyard */
    mainSetBits(BIT_CC_Courtyard_Gate_Left_Lever_or_Lantern, 1);
    mainSetBits(BIT_CC_Courtyard_Gate_Right_Lever_or_Lantern, 1);
    mainSetBits(BIT_CC_Gate_Opened, 1);

    mainSetBits(BIT_5, 1); // grub tutorial bit (will break shrine FXemits without dinomod patches)
    mainSetBits(BIT_CC_Rescued_Kyte, 1);
    //mainSetBits(BIT_372, 1); // sharpclaw 0x34566 defeated
    //mainSetBits(BIT_390, 1); // sharpclaw 0x34561 defeated
    mainSetBits(BIT_CC_Kyte_Pulled_All_Four_Levers, 1);
    mainSetBits(BIT_3CB, 1); // kyte commands enabled
    mainSetBits(BIT_CC_Cell_Door_Key, 1);
    mainSetBits(BIT_Kyte_Flight_Curve, 50);
    mainSetBits(BIT_Kyte_Flight_Talk_Sequence, 4);
    mainSetBits(BIT_CC_Courtyard_Gate_Reopened, 1);

    /* cape claw exit */
    chselect_set_map_state(MAP_CAPE_CLAW, 2, G1); // set on the way out
    chselect_set_map_state(MAP_SWAPSTONE_CIRCLE, 2, G1 | G6);

    chselect_set_location(PLAYER_KRYSTAL, 1403.51f, 158.35f, 16944.01f, M_90_DEGREES, 0);

    PlayerLightActions light = DEFAULT_LACTIONS;
    light.unk0[0] = 485;
    light.unk0[1] = 497;
    light.unk12 = 1;
    chselect_set_light(PLAYER_KRYSTAL, &light);

    PlayerEnvActions env = DEFAULT_ENVACTIONS;
    env.unk4 = 302;
    env.unk6 = 304;
    env.unk8 = 303;
    chselect_set_env(PLAYER_KRYSTAL, &env);

    chselect_set_music(PLAYER_KRYSTAL, 218, -1, 280, -1);
}

static void ch_swapstone_circle_2(void) {
    /* lightfoot ambush */
    mainSetBits(BIT_SC_Encountered_Baby_Lightfoot, 1);
    mainSetBits(BIT_2BB, 1); // TriggerPlane 0x33977 restore bit
    mainSetBits(BIT_2CC, 1); // SC_sequences 0x281F played bit
    mainSetBits(BIT_2D0, 1); // SC_sequences 0x2829 played bit
    mainSetBits(BIT_Kyte_Flight_Curve, 8);
    mainSetBits(BIT_SC_Ambushed, 1);
    chselect_set_map_state(MAP_SWAPSTONE_CIRCLE, 3, G0);

    /* path from lfv to sc */
    chselect_set_location(PLAYER_KRYSTAL, -287.468f, 286.740f, 16947.609f, 17920, 0);

    PlayerLightActions light = DEFAULT_LACTIONS;
    light.unk0[0] = 485;
    light.unk0[1] = 486;
    light.unk12 = 1;
    chselect_set_light(PLAYER_KRYSTAL, &light);

    PlayerEnvActions env = DEFAULT_ENVACTIONS;
    env.unk4 = 79;
    env.unk6 = 80;
    env.unk8 = 9;
    env.unkA = 451;
    env.unk10 = -1073; env.unk14 = 394; env.unk18 = 17380;
    chselect_set_env(PLAYER_KRYSTAL, &env);

    chselect_set_music(PLAYER_KRYSTAL, 185, -1, 18, -1);
}

static void ch_discovery_falls(void) {
    /* swapstone circle beacons */
    mainSetBits(BIT_SC_Beacon_Lit_1, 1);
    mainSetBits(BIT_SC_Beacon_Lit_2, 1);
    mainSetBits(BIT_SC_Beacon_Lit_3, 1);
    mainSetBits(BIT_SC_Beacon_Added_Twigs_1, 1);
    mainSetBits(BIT_SC_Beacon_Added_Twigs_2, 1);
    mainSetBits(BIT_SC_Beacon_Added_Twigs_3, 1);
    mainSetBits(BIT_SC_All_Beacons_Lit, 1);
    mainSetBits(BIT_2D8, 1); // set by seq 0x77
    mainSetBits(BIT_2D9, 1); // HitAnimator 0xBE0400D activate bit

    chselect_set_map_state(MAP_CAPE_CLAW, 2, G_None); // for some reason this gets cleared during the beacon quest?

    /* discovery falls start */
    mainSetBits(BIT_Kyte_Flight_Curve, 61);

    chselect_set_map_state(MAP_DISCOVERY_FALLS, 1, G1);
    chselect_set_map_state(MAP_SWAPSTONE_CIRCLE, 3, G_None);

    chselect_set_location(PLAYER_KRYSTAL, -2097.08f, 160.27f, 18309.26f, 17408, 0);

    PlayerLightActions light = DEFAULT_LACTIONS;
    light.unk0[0] = 485;
    light.unk0[1] = 36;
    light.unkC[1] = 90;
    light.unk12 = 1;
    chselect_set_light(PLAYER_KRYSTAL, &light);

    PlayerEnvActions env = DEFAULT_ENVACTIONS;
    env.unk4 = 55;
    env.unk6 = 53;
    env.unk8 = 54;
    env.unkA = 451;
    env.unk10 = -1073; env.unk14 = 394; env.unk18 = 17380;
    chselect_set_env(PLAYER_KRYSTAL, &env);

    chselect_set_music(PLAYER_KRYSTAL, 218, -1, 13, -1);
}

static void ch_df_shrine(void) {
    /* discovery falls */
    mainSetBits(BIT_DF_Demolition_Cave_Destroy_Whirlpool_Wall_2, 1);
    mainSetBits(BIT_DF_Demolition_Cave_Destroyed_Whirlpool_Wall_2, 1);
    mainSetBits(BIT_DF_Demolition_Cave_Destroy_Whirlpool_Wall_3, 1);
    mainSetBits(BIT_DF_Demolition_Cave_Destroyed_Whirlpool_Wall_3, 1);
    mainSetBits(BIT_DF_Shrine_Door_Light_Activated_One, 1);
    mainSetBits(BIT_DF_Shrine_Door_Light_Activated_Two, 1);
    mainSetBits(BIT_DF_Shrine_Door_Light_Activated_Three, 1);
    mainSetBits(BIT_DF_Shrine_Door_Light_Activated_Four, 1);
    mainSetBits(BIT_DF_Played_Seq_0167_Arrival_So_This_Is_Discovery_Falls, 1);
    mainSetBits(BIT_DF_Played_Seq_0168_Krystal_Meets_HighTop_Archaeologist, 1);
    mainSetBits(BIT_DF_Cradle_Powered, 1);
    mainSetBits(BIT_DF_Toxic_Cave_Destroy_Gas_Vent, 1);
    mainSetBits(BIT_DF_Toxic_Cave_Destroyed_Gas_Vent, 1);
    mainSetBits(BIT_DF_Played_Seq_003E_Mole_Cave_SharpClaw_Hides, 1);
    mainSetBits(BIT_DF_Toxic_Cave_Destroy_Wall, 1);
    mainSetBits(BIT_DF_Toxic_Cave_Destroyed_Wall, 1);
    mainSetBits(BIT_DF_Played_Seq_002E_Demolition_Cave_SharpClaw_Antics, 1);
    mainSetBits(BIT_DF_Played_Seq_002C_Mole_Cave_Hatch_Opens, 1);
    mainSetBits(BIT_DF_Whirlpool_Cave_Wall_Demolished, 1);
    mainSetBits(BIT_DF_Whirlpool_Cave_Wall_Demolition_Finished, 1);
    mainSetBits(BIT_DF_Shrine_Door_Opened, 1);
    mainSetBits(BIT_DF_Demolition_Cave_Destroy_Crate_Wall, 1);
    mainSetBits(BIT_DF_Demolition_Cave_Destroyed_Crate_Wall, 1);
    mainSetBits(BIT_DF_Demolition_Cave_Destroy_Whirlpool_Wall_1, 1);
    mainSetBits(BIT_DF_Demolition_Cave_Destroyed_Whirlpool_Wall_1, 1);
    mainSetBits(BIT_Krystal_Foodbag_S, 1);
    mainSetBits(BIT_Krystal_Foodbag_M, 1);
    mainSetBits(BIT_Krystal_Foodbag_L, 1);
    mainSetBits(BIT_190, 1); // this was a type 0 bit before, does it do anything?
    mainSetBits(BIT_DF_Played_Seq_000F_Kyte_Secures_Rope_Upper_Falls, 1);
    mainSetBits(BIT_DF_Mole_Cave_Destroyed_Door, 1);
    mainSetBits(BIT_DF_Demolition_Cave_Destroy_Whirlpool_Wall_4, 1);
    mainSetBits(BIT_DF_Demolition_Cave_Destroy_Plant_Wall_1, 1);
    mainSetBits(BIT_DF_Demolition_Cave_Destroyed_Plant_Wall_1, 1);
    mainSetBits(BIT_DF_Demolition_Cave_Destroy_Plant_Wall_2, 1);
    mainSetBits(BIT_DF_Demolition_Cave_Destroyed_Plant_Wall_2, 1);
    mainSetBits(BIT_DF_Demolition_Cave_Destroyed_Whirlpool_Wall_4, 1);
    mainSetBits(BIT_DF_Demolition_Cave_Destroy_Far_Wall, 1);
    mainSetBits(BIT_DF_Demolition_Cave_Destroyed_Far_Wall, 1);
    mainSetBits(BIT_DF_Demolition_Cave_Destroy_SharpClaw_Wall, 1);
    mainSetBits(BIT_DF_Demolition_Cave_Destroyed_SharpClaw_Wall, 1);
    mainSetBits(BIT_Kyte_Flight_Curve, 201);
    mainSetBits(BIT_Kyte_Flight_Talk_Sequence, 255);
    mainSetBits(BIT_DF_Seq_0035_Shrine_Door_Opened, 1);
    mainSetBits(BIT_DF_Played_Seq_02AD_Krystal_Meets_Foodbag_SharpClaw, 1);
    mainSetBits(BIT_CapyTunnel1, 1);
    mainSetBits(BIT_CapyTunnel2, 1);
    mainSetBits(BIT_CapyTunnel3, 1);
    mainSetBits(BIT_7DF, 1); // ?? what sets this
    //mainSetBits(BIT_879, 1); // SharpClaw 0x2043 defeated bit
    //mainSetBits(BIT_87A, 1); // SharpClaw 0x2042 defeated bit
    //mainSetBits(BIT_888, 1); // SharpClaw 0x2056 defeated bit
    //mainSetBits(BIT_889, 1); // SharpClaw 0x2055 defeated bit
    mainSetBits(BIT_8B1, 1); // Discovery Falls levelname shown
    // we don't want the shrine entrance sharpy to be there when exiting the shrine
    // (a type 0 bit controls their defeated state, so only a timesave can stop them from spawning)
    chselect_set_timesave(0x1F82, 72 * 60); // shrine entrance sharpy

    chselect_set_min_scarabs(PLAYER_KRYSTAL, 30);

    chselect_set_map_state(MAP_DISCOVERY_FALLS, 1, G3 | G7 | G11);

    /* shrine entrance */
    // chselect_set_location(PLAYER_KRYSTAL, -4048.695313f, 218.0f, 16215.4375f, -8192, 0);

    // PlayerLightActions light = DEFAULT_LACTIONS;
    // light.unk0[0] = 485;
    // light.unk0[1] = 35;
    // light.unk8[0] = 495;
    // light.unkC[1] = 493;
    // light.isInside = 1;
    // light.unk12 = 1;
    // chselect_set_light(PLAYER_KRYSTAL, &light);

    // PlayerEnvActions env = DEFAULT_ENVACTIONS;
    // env.unk4 = 394;
    // env.unk6 = 53;
    // env.unk8 = 54;
    // env.unkA = 451;
    // env.unk10 = -1073; env.unk14 = 394; env.unk18 = 17380;
    // chselect_set_env(PLAYER_KRYSTAL, &env);

    // chselect_set_music(PLAYER_KRYSTAL, 23, -1, 13, -1);

    /* warp */
    chselect_set_min_magic(PLAYER_KRYSTAL, 15);

    chselect_set_location(PLAYER_KRYSTAL, 15847.602f, 56.0f, -16792.164f, 0, 0);

    PlayerLightActions light = DEFAULT_LACTIONS;
    light.unk0[0] = 19;
    light.unk0[1] = 18;
    light.unk8[0] = 495;
    light.unkC[1] = 63;
    light.isInside = 1;
    light.unk12 = 1;
    chselect_set_light(PLAYER_KRYSTAL, &light);

    PlayerEnvActions env = DEFAULT_ENVACTIONS;
    env.unk4 = 120;
    env.unk6 = 53;
    env.unk8 = 121;
    env.unkA = 451;
    env.unk10 = -1073; env.unk14 = 394; env.unk18 = 17380;
    chselect_set_env(PLAYER_KRYSTAL, &env);

    chselect_set_music(PLAYER_KRYSTAL, 41, -1, 13, -1);
}

static void ch_warlock_mountain_spirit_1(void) {
    /* discovery falls/the walk back to sc */
    mainSetBits(BIT_DF_Play_Seq_003C_Krystal_Returns_From_The_Shrine, 1);
    mainSetBits(BIT_DF_Played_Seq_003C_Krystal_Returns_From_The_Shrine, 1);
    mainSetBits(BIT_DF_Shrine_SharpClaw_Drop_Magic_Gems, 1);
    mainSetBits(BIT_Play_Seq_0107_Rocky_Intro_Unused, 1);
    mainSetBits(BIT_Kyte_Flight_Curve, 117);
    mainSetBits(BIT_Spirit_Bits, (1 << 0));
    mainSetBits(BIT_Talking_to_Rocky, 1);

    chselect_set_map_state(MAP_WARLOCK_MOUNTAIN, 2, G_None);
    chselect_set_map_state(MAP_SWAPSTONE_CIRCLE, 8, G0);
    //chselect_set_map_state(MAP_ICE_MOUNTAIN_1, 1, G_None); // this seems like a mistake/temp thing in the swapstone dll
    chselect_set_map_state(MAP_DISCOVERY_FALLS, 1, G_None);

    /* warlock mountain krystal transporter room */
    chselect_set_location(PLAYER_KRYSTAL, 13711.855469f, 210.710876f, 144.656250f, M_90_DEGREES, 0);

    PlayerLightActions light = DEFAULT_LACTIONS;
    light.unk0[0] = 108;
    light.unk0[1] = 119;
    light.unk8[0] = 495;
    light.unkC[1] = 90;
    light.unk12 = 1;
    chselect_set_light(PLAYER_KRYSTAL, &light);

    PlayerEnvActions env = DEFAULT_ENVACTIONS;
    env.unk4 = 517;
    env.unk6 = 516;
    env.unk8 = 518;
    env.unkA = 451;
    env.unk10 = -1073; env.unk14 = 394; env.unk18 = 17380; // leftovers from a while ago now?
    chselect_set_env(PLAYER_KRYSTAL, &env);

    chselect_set_music(PLAYER_KRYSTAL, 266, -1, 187, -1);
}

// sabre DIM act start
static void ch_swapstone_hollow_2(void) {
    /* warlock mountain spirit 1 */
    mainSetBits(BIT_Play_Seq_0170_WM_Return_to_Randorn_Quan_Ata_Lachu_Speaks, 1);
    mainSetBits(BIT_Set_During_Spirit_Release_1, 1);
    mainSetBits(BIT_Play_Seq_0180_Release_Spirit_1, 1);
    mainSetBits(BIT_Spirit_Bits, 0);
    mainSetBits(BIT_4CF, 1); // WL_seqpoint 0x30D75 condition bit (set by seq 0x170)

    /* swapstone circle*/
    mainSetBits(BIT_Kyte_Flight_Curve, 55);

    {
        // krystal's last state
        chselect_set_location(PLAYER_KRYSTAL, -1048.82f, 307.0f, 17424.86f, 0, 0);

        PlayerLightActions light = DEFAULT_LACTIONS;
        light.unk0[0] = 485;
        light.unk0[1] = 486;
        light.unk8[0] = 495;
        light.unkC[1] = 2;
        light.unk12 = 1;
        chselect_set_light(PLAYER_KRYSTAL, &light);

        PlayerEnvActions env = DEFAULT_ENVACTIONS;
        env.unk4 = 434;
        env.unk6 = 435;
        env.unk8 = 436;
        env.unkA = 141;
        env.unk10 = 13685; env.unk14 = 202; env.unk18 = -169;
        chselect_set_env(PLAYER_KRYSTAL, &env);

        chselect_set_music(PLAYER_KRYSTAL, 185, -1, 5, -1);
    }

    /* swap */
    chselect_set_player(PLAYER_SABRE);

    /* swapstone hollow */
    mainSetBits(BIT_Play_Seq_01FD_Rocky_Teaches_Distract, 1);
    mainSetBits(BIT_Tricky_Learned_Distract, 1);
    mainSetBits(BIT_Play_Seq_035F_Rocky_Intro, 0); // unset by the swapstone during the swap?
    mainSetBits(BIT_2B2, 1); // SC_sequences 0x2733 played bit

    chselect_set_map_state(MAP_SWAPSTONE_HOLLOW, 1, G0);

    {
        chselect_set_location(PLAYER_SABRE, -6571.54f, -632.0f, -1607.57f, 0, 0);

        PlayerLightActions light = DEFAULT_LACTIONS;
        light.unk0[0] = 389;
        light.unk0[1] = 401;
        light.unk4 = 402;
        light.unk6 = 403;
        light.unkC[1] = 1;
        light.unk12 = 1;
        chselect_set_light(PLAYER_SABRE, &light);

        PlayerEnvActions env = DEFAULT_ENVACTIONS;
        env.unk4 = 97;
        env.unk6 = 438;
        env.unk8 = 439;
        env.unkA = 100;
        chselect_set_env(PLAYER_SABRE, &env);

        chselect_set_music(PLAYER_SABRE, 218, -1, 1, -1);
    }
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
    // Krystal Act 1 (Intro)
    { "Krystal's Intro", NULL },
    { "Ship Battle", ch_ship_battle },
    { "Warlock Mountain 1", ch_wl_1 },
    
    // Sabre Act 1 (Intro)
    { "Sabre's Intro", NULL },
    { "Ice Mountain", ch_ice_mountain },
    { "SnowHorn Wastes 1", ch_snowhorn_wastes_1 },
    { "SwapStone Hollow 1", ch_swapstone_hollow_1 },
    
    // Krystal Act 2 (Spirit 1)
    { "Kyte Rescue", NULL },
    { "SwapStone Circle 1", ch_swapstone_circle_1 },
    { "Cape Claw 1", ch_cape_claw_1 },
    { "Cape Claw 1 Courtyard", ch_cape_claw_1_courtyard },
    { "LightFoot Village Ambush", ch_lightfoot_village_1 },
    { "SwapStone Circle 2 (Beacons)", ch_swapstone_circle_2 },
    { "Discovery Falls", ch_discovery_falls },
    { "Test of Combat", ch_df_shrine },
    { "Warlock Mountain Spirit 1", ch_warlock_mountain_spirit_1 },
    
    // Sabre Act 2 (SpellStone 1, Spirit 2)
    { "SnowHorn Peril", NULL },
    { "SwapStone Hollow 2", ch_swapstone_hollow_2 },
    { "DarkIce Mines 1", ch_stub },
    { "DarkIce Mines 2", ch_stub },
    { "Boss Galadon", ch_stub },
    { "SwapStone Hollow 2 (River)", ch_stub },
    { "Diamond Bay 1", ch_stub },
    { "Volcano Force Point 1", ch_stub },
    { "Test Of Strength", ch_stub },
    { "Warlock Mountain Spirit 2", ch_stub },

    // Krystal Act 3 (SpellStone 2)
    { "A Birdy Reunion", NULL },
    { "SwapStone Circle 3", ch_stub },
    { "CloudRunner Fortress", ch_crf_start },
    { "CloudRunner Dungeon", ch_crf_dungeon_start },

    // Sabre Act 3 (SpellStone 3)
    { "RedEye Rampage", NULL },
    
    // Krystal Act 4 (Spirit 3)
    { "To The Moon", NULL },

    // Sabre Act 4 (Spirit 4)
    { "Sun and Moon", NULL },
    
    // Krystal Act 5 (SpellStone 4, Spirit 5)
    { "Chief's Trials", NULL },

};

Chapter* chselect_get_chapters(s32* count) {
    if (count != NULL) {
        *count = ARRAYCOUNT(chapters);
    }
    
    return chapters;
}

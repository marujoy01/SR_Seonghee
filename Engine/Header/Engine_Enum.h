#ifndef Engine_Enum_h__
#define Engine_Enum_h__

namespace Engine
{
	enum WINMODE { MODE_FULL, MODE_WIN };

	// Dynamic 컴포넌트 경우 매 프레임마다 갱신해야하는 컴포넌트 집단
	enum COMPONENTID { ID_DYNAMIC, ID_STATIC, ID_END };

	enum INFO {	INFO_RIGHT, INFO_UP, INFO_LOOK, INFO_POS, INFO_END };
	enum ROTATION { ROT_X, ROT_Y, ROT_Z, ROT_END };

	enum TEXTUREID { TEX_NORMAL, TEX_CUBE, TEX_VOLUME, TEX_END };

	enum RENDERID { RENDER_PRIORITY, RENDER_ALPHATEST, RENDER_NONALPHA, RENDER_ALPHA, RENDER_UI, RENDER_END };

	enum CHANNELID { SOUND_EFFECT, SOUND_BGM, SYSTEM_EFFECT, SOUND_PLAYER, SOUND_ENEMY, SOUND_VFX, MAXCHANNEL };

	enum CHANNEL_GROUP_ID { BGM_GROUP, SND1_GROUP, SND2_GROUP, MAX_CHANNEL_GROUP };

	enum MOUSEKEYSTATE { DIM_LB, DIM_RB, DIM_MB, DIM_MWU, DIM_MWD, DIM_END };

	enum MOUSEMOVESTATE {	DIMS_X, DIMS_Y, DIMS_Z, DIMS_END };

	enum EBIT_FLAG_32 : unsigned long
	{
		EBIT_FLAG32_0 = 1UL << 0,
		EBIT_FLAG32_1 = 1UL << 1,
		EBIT_FLAG32_2 = 1UL << 2,
		EBIT_FLAG32_3 = 1UL << 3,
		EBIT_FLAG32_4 = 1UL << 4,
		EBIT_FLAG32_5 = 1UL << 5,
		EBIT_FLAG32_6 = 1UL << 6,
		EBIT_FLAG32_7 = 1UL << 7,
		EBIT_FLAG32_8 = 1UL << 8,
		EBIT_FLAG32_9 = 1UL << 9,
		EBIT_FLAG32_10 = 1UL << 10,
		EBIT_FLAG32_11 = 1UL << 11,
		EBIT_FLAG32_12 = 1UL << 12,
		EBIT_FLAG32_13 = 1UL << 13,
		EBIT_FLAG32_14 = 1UL << 14,
		EBIT_FLAG32_15 = 1UL << 15,
		EBIT_FLAG32_16 = 1UL << 16,
		EBIT_FLAG32_17 = 1UL << 17,
		EBIT_FLAG32_18 = 1UL << 18,
		EBIT_FLAG32_19 = 1UL << 19,
		EBIT_FLAG32_20 = 1UL << 20,
		EBIT_FLAG32_21 = 1UL << 21,
		EBIT_FLAG32_22 = 1UL << 22,
		EBIT_FLAG32_23 = 1UL << 23,
		EBIT_FLAG32_24 = 1UL << 24,
		EBIT_FLAG32_25 = 1UL << 25,
		EBIT_FLAG32_26 = 1UL << 26,
		EBIT_FLAG32_27 = 1UL << 27,
		EBIT_FLAG32_28 = 1UL << 28,
		EBIT_FLAG32_29 = 1UL << 29,
		EBIT_FLAG32_30 = 1UL << 30,
		EBIT_FLAG32_31 = 1UL << 31,
	};
	 
	// 나중에 정리하겠지만 지금은 일단 충돌해야하는애들 떄려박아서 테스트 돌리겠습니다. //소영 
	enum ELAYER : unsigned long
	{
		ELAYER_PLAYER = EBIT_FLAG32_0,
		ELAYER_MONSTER = EBIT_FLAG32_1,
		ELAYER_WALL = EBIT_FLAG32_2,
		ELAYER_FACTORY_FOOD = EBIT_FLAG32_3, 
		ELAYER_PROJECTILE = EBIT_FLAG32_4, // 투사체 
		//ELAYER_FACTORY_FOOD_SLIDING = EBIT_FLAG32_4;
		//ELAYER_FACTORY_WEAPON = EBIT_FLAG32_0;
	};

	// 아 귀찮아 안해
	enum EBIT_FLAG_64 : unsigned long long
	{

	};
}
#endif // Engine_Enum_h__

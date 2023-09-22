#pragma once

#include "GameObject.h"

#include "Engine_Macro.h"

BEGIN(Engine)

class CRcBufferComp;
class CTextureComponent;
class CTransformComponent;
class CCameraComponent;
class CCalculatorComponent;
class CSphereColComp;

END
// 7시 지호==============================================
class CDynamicCamera;

class CPlayer : public Engine::CGameObject
{
	DERIVED_CLASS(CGameObject, CPlayer)
private:
	explicit CPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPlayer(const CPlayer& rhs);
	virtual ~CPlayer();

public:
	static CPlayer*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

public:
	virtual _int		Update_GameObject(const _float& fTimeDelta) override;
	virtual void		LateUpdate_GameObject() override;

	// ===============================랜 더================================
	virtual void		Render_GameObject() override;
	// ====================================================================

	// =============================상태 추가==============================
	virtual HRESULT		Ready_GameObject() override;
	// ====================================================================

	// ============================손 상태 체크============================
	void				Hand_Check();
	// ====================================================================

	// =============================양손 주먹==============================
	void				Two_Hand();
	// ====================================================================

	// ===========================양손 오브젝트============================
	void				Two_Object();
	// ====================================================================

	// ===========================한손 오브젝트============================
	void				Right_Object();
	// ====================================================================

	// ============================키보드 입력=============================
	bool				Keyboard_Input(const _float& fTimeDelta);	// 키보드 입력
	// ====================================================================


public: // Camera
	GETSET_EX2(CDynamicCamera*, m_pCamera, Camera, GET, SET)

public: // Get_Set
	GETSET_EX2(CRcBufferComp*, m_pBufferComp, BufferComponent, GET, SET)
	GETSET_EX2(CTransformComponent*, m_pTransformComp, TransformComponent, GET, SET)
	GETSET_EX2(CTextureComponent*, m_pLeftHandComp, m_pLeftHandComp, GET, SET)
	GETSET_EX2(CTextureComponent*, m_pRightHandComp, m_pRightHandComp, GET, SET)
	GETSET_EX2(CCalculatorComponent*, m_pCalculatorComp, CalculatorComponent, GET, SET)
	GETSET_EX2(CSphereColComp*, m_pColliderComp, SphereColComponent, GET, SET)


public:// 플레이어 상태 값
	// 플레이어
	enum class STATE_PLAYER { NONE, IDLE, MOVE, RUN, DOWN, ATTACK, KICK, DIE };
	// 왼손
	enum class STATE_LEFTHAND { NONE, HAND, OPEN_HAND, RUN_HAND, RIGHTER, RUN_RIHGTER };
	// 오른손
	enum class STATE_RIGHTHAND { NONE, HAND, RUN_HAND, GUN, THOMPSON, STEELPIPE, BEERBOTLE, FRYINGPAN, KICK };
	
// TEST
	enum class OBJECT_TYPE { NONE, TWO_HAND, TWO_OBJECT, RIGHT_OBJECT }; // 테스트(오브젝트)
	enum class OBJECT_NAME { NONE, GUN, THOMPSON, STEELPIPE, BEERBOTLE, FRYINGPAN };
// TEST
private: // 플레이어의 상태 머신
	STATE_SET<STATE_PLAYER, void(CPlayer*, float)> m_tPlayer_State;

	void Idle(float fTimeDelta);
	void Move(float fTimeDelta);
	void Run(float fTimeDelta);
	void Down(float fTimeDelta);
	void Attack(float fTimeDelta);
	void Kick(float fTimeDelta);
	void Die(float fTimeDelta);

private: // 플레이어의 왼손 상태 머신
	STATE_SET<STATE_LEFTHAND, void(CPlayer*, float)> m_tLeftHand_State;

	void	Left_None(float fTimeDelta);
	void	Left_Hand(float fTimeDelta);
	void	Left_RunRighter(float fTimeDelta);
	void	Left_OpenHand(float fTimeDelta);
	void	Left_RunHand(float fTimeDelta);
	void	Left_Righter(float fTimeDelta);

private: // 플레이어의 오른손 상태 머신
	STATE_SET<STATE_RIGHTHAND, void(CPlayer*, float)> m_tRightHand_State;

	void	Right_None(float fTimeDelta);
	void	Right_Hand(float fTimeDelta);
	void	Right_RunHand(float fTimeDelta);
	void	Right_Gun(float fTimeDelta);
	void	Right_Thompson(float fTimeDelta);
	void	Right_Steelpipe(float fTimeDelta);
	void	Right_BeerBotle(float fTimeDelta);
	void	Right_FryingPan(float fTimeDelta);
	void	Right_Kick(float fTimeDelta);

private: // 함수
	HRESULT				Add_Component();							// 컴포넌트 추가
	//bool				Keyboard_Input(const _float& fTimeDelta);	// 키보드 입력
	bool				Attack_Input(const _float& fTimeDelta);		// 공격 입력(마우스)
	void				Mouse_Move();								// 마우스 움직임
	void				Height_On_Terrain();						// 지형타기
	//void				Hand_Check();								// 플레이어 손 상태 체크
	
	//// ==============================양손 주먹=============================
	//void				Two_Hand();
	//// ====================================================================
	//
	//// ===========================양손 오브젝트============================
	//void				Two_Object();
	//// ====================================================================
	//
	//// ===========================한손 오브젝트============================
	//void				Right_Object();
	//// ====================================================================

private:
	void State_Update(float fTimeDelta);	// 상태 업데이트(상태 체크)

private: // 컴포넌트
	// 기능
	CRcBufferComp*				m_pBufferComp = nullptr;			// Rc버퍼
	CTransformComponent*		m_pTransformComp = nullptr;			// 이동행렬 버퍼
	CCalculatorComponent*		m_pCalculatorComp = nullptr;		// 지형 타기 컴포넌트
	CSphereColComp*				m_pColliderComp = nullptr;			// 구 충돌 콜라이더

	// 플레이어 손
	CTextureComponent*			m_pLeftHandComp = nullptr;			// 왼손 텍스처(담을곳)
	CTextureComponent*			m_pRightHandComp = nullptr;			// 오른손 텍스처(담을곳)

private: // 스위치
	_bool		bAttackOn = false;		// 공격 On/Off
	_bool		bLeftFrameOn = false;	// 왼손 프레임 On/Off
	_bool		bRightFrameOn = false;	// 오른손 프레임 On/Off
	_bool		bGunOn = false;			// 총 On/Off
	_bool		bSpinOn = false;		// 총 회전 On/Off
	_bool		bRighter = false;		// 라이터 On/Off
	_bool		bRighterSwitch = false; // 라이터 스위치 On/Off
	_bool		bLeftHandOn = true;		// 왼손 출력 On/Off
	_bool		bRightHandOn = true;	// 오른손 출력 On/Off

	// 주먹 공격 작업용 변수 (테스트중)
	_bool		bLeftHandFist = false;	// 왼손 주먹상태
	_bool		bRightHandFist = false; // 오른손 주먹상태

	_bool		bChargingReady = true;	// 차징 가능 여부
	_bool		bDead = false;			// 플레이어 사망 여부
	_bool		bMove = false;			// 플레이어가 움직이는지 여부
	_bool		bMouse_Button = false;	// 마우스 클릭 여부
	_bool		bFootAttack = false;	// 발차기 여부
	_bool		bRunOn = false;			// 플레이어가 뛰는지 여부

	_float		fStraightSpeed = 5.f;	// 플레이어 전진 속도
	_float		fSpeed = 5.f;			// 플레이어 속도
	_float		fDash = 20.f;			// 플레이어 대쉬

	// 플레이어 상태
	STATE_PLAYER	m_ePlayerState;	// 플레이어
	STATE_LEFTHAND	m_eLeftState;	// 왼손

	// Test
	OBJECT_TYPE m_eObjectType;	// 오브젝트 타입
	OBJECT_NAME m_eObjectName;	// 오브젝트 이름


private:
	_long			dwMouseMove = 0;		// 마우스 무브

	_float			m_fLeftFrame = 0.f;		// 왼손 현재 프레임
	_float			m_fLeftMaxFrame = 0.f;	// 왼손 최대 프레임

	_float			m_fRightFrame = 0.f;	// 오른손 현재 프레임
	_float			m_fRightMaxFrame = 0.f; // 오른손 최대 프레임

private:
	virtual void		Free();

protected:
	CDynamicCamera*		m_pCamera = nullptr;

protected:
	_matrix		m_matRot;

private: //빛
	//HRESULT			SetUp_Material();
	_bool			bTorch = false;

};

/*	현재 키 설명

================ 카메라 ================
F1 : 1인칭 카메라
F2 : 3인칭 카메라
F3 : 자유시점 카메라

방향키 : 카메라 이동
========================================

=============== 플레이어 ===============

-이동-
W : 전진
S : 후진
A : 좌회전
D : 우회전

W + LShift : 달리기
A, S, D + LShift : 대쉬(작업중)

-플레이어 기능-
Q : 발차기
V : 라이터 (양손 오브젝트일 경우 불가능)
R : 권총 회전(권총 상태일때만 가능)

-오브젝트 변경-
1 : 주먹
2 : 권총
3 : 톰슨 기관총
4 : 쇠파이프
5 : 맥주병
6 : 프라이팬

-공격-
MouseLB : 공격

========================================

*/
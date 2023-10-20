#pragma once
#include "AceObjectFactory.h"
#include "AceUnit.h"
#include "Engine_Enum.h"

#include "Serialize_BaseClass.h"

BEGIN(Engine)

class CRcBufferComp;
class CTextureComponent;
class CTransformComponent;
class CCalculatorComponent;
class CColliderComponent;

END

class CAceFood : public CAceUnit
{
	DERIVED_CLASS(CAceUnit, CAceFood)



private:
	explicit CAceFood(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CAceFood(const CAceFood& rhs);
	virtual ~CAceFood();

public:
	static CAceFood* Create(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* pObjTag, const _float _fx, const _float _fy, const _float _fz);
	static CAceFood* Create(LPDIRECT3DDEVICE9 pGraphicDev, const FSerialize_GameObject& tObjectSerial);

	enum class FOOD_NAME {
		APPLE, BANANA, COLA, MEDIKIT,
		EATENAPPLE, BANANAPEEL,
		FOOD_END
	};

private:
	virtual void		Free();

public:
	PRIVATE virtual HRESULT		Ready_GameObject() override;
	PUBLIC	virtual HRESULT		Ready_GameObject(const _tchar* pObjTag, const _float _fx, const _float _fy, const _float _fz);
	PUBLIC	virtual HRESULT		Ready_GameObject(const FSerialize_GameObject& tObjectSerial);

	virtual _int		Update_GameObject(const _float& fTimeDelta) override;
	virtual void		LateUpdate_GameObject() override;
	virtual void		Render_GameObject() override;
	
protected:
	virtual void		OnCollision(CGameObject* pDst, const FContact* const pContact);
	virtual void		OnCollisionEntered(CGameObject* pDst, const FContact* const pContact);
	virtual void		OnCollisionExited(CGameObject* pDst);

protected:
	HRESULT				Add_Component(); // 컴포넌트 추가 
	HRESULT				BillBoard(const _float& fTimeDelta); // 플레이어쪽으로 향하는 함수 
	void				Height_On_Terrain(); // 지형타기 

public:
	FOOD_NAME	Get_FoodName() { return m_pCurName; }
	_float		Get_Hp() { return m_fHp; }
	_bool		m_bRayEaten = FALSE;
private:
	CRcBufferComp* m_pBufferComp = nullptr;
	CTextureComponent* m_pTextureComp = nullptr;
	CTransformComponent* m_pTransformComp = nullptr;
	CCalculatorComponent* m_pCalculatorComp = nullptr;
	CColliderComponent* m_pColliderComp = nullptr;

private:// 함수
	void				FoodName(const _tchar* pObjTag); // TCHAR를 ENUM에 맞게 고치기 
	void				Eat_Food(FOOD_NAME eCurName, const _float& fTimeDelta, _bool bEat);

private: //변수
	FOOD_NAME			m_pCurName;
	_bool				m_bDead = false;  // 죽는거 생기면 그걸로 변경 
	_vec3				CurPos;			  // 현재 위치 
	_float				m_fChangeTextureSpeed = 0.001f;
	OBJECT_CLASS		m_eFactoryClass;
	_float				m_fHp;

public:
	GETSET_EX2(OBJECT_CLASS, m_eFactoryClass, FACTORY_NAME, GET, SET)
	GETSET_EX2(CRcBufferComp*, m_pBufferComp, BufferComponent, GET, SET)
	GETSET_EX2(CTransformComponent*, m_pTransformComp, TransformComponent, GET, SET)
	GETSET_EX2(CTextureComponent*, m_pTextureComp, TextureComp, GET, SET)

	GETSET_EX2(_bool, m_bRayEaten, FoodEat, GET, SET)

};


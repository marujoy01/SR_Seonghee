#pragma once

#include "GameObjComponent.h"

BEGIN(Engine)

/// <summary>
/// ActorComponent에서 좌표계를 쓸 수 있도록 기능이 추가된 컴포넌트이다.
/// TransformComponent와는 별개
/// </summary>
class ENGINE_DLL CSceneComponent abstract : public CGameObjComponent
{
	DERIVED_CLASS(CGameObjComponent, CSceneComponent)

protected:
	explicit CSceneComponent();
	explicit CSceneComponent(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSceneComponent(const CSceneComponent& rhs);
	virtual ~CSceneComponent();

public:
	virtual CComponent*		Clone() PURE;
	virtual void			Free();

public:
	virtual HRESULT	Ready_Component() PURE;
	virtual _int	Update_Component(const _float& fTimeDelta) { return 0; }
	virtual void	LateUpdate_Component() PURE;
	virtual void	Render_Component() PURE;

public:
#pragma region 트랜스폼 변경 함수들
	// 로컬 행렬을 재조정한다
	void Readjust_Transform()
	{
		D3DXMatrixIdentity(&m_matTransform);

		// 3x3만큼 월드 행렬로부터 vInfo에 복사
		for (_int i = 0; i < INFO_POS; ++i)
			memcpy(&m_vInfo[i], &m_matTransform.m[i][0], sizeof(_vec3));

		// 크기 변환
		for (_int i = 0; i < INFO_POS; ++i)
		{
			D3DXVec3Normalize(&m_vInfo[i], &m_vInfo[i]);
			m_vInfo[i] *= *(((_float*)&m_vScale) + i);
		}

		// 회전 변환
		_matrix		matRot[ROT_END];

		D3DXMatrixRotationX(&matRot[ROT_X], m_vRotation.x);
		D3DXMatrixRotationY(&matRot[ROT_Y], m_vRotation.y);
		D3DXMatrixRotationZ(&matRot[ROT_Z], m_vRotation.z);

		for (_int i = 0; i < INFO_POS; ++i)
		{
			for (_int j = 0; j < ROT_END; ++j)
			{
				D3DXVec3TransformNormal(&m_vInfo[i], &m_vInfo[i], &matRot[j]);
			}
		}

		// 월드 행렬 구성
		for (_int i = 0; i < INFO_END; ++i)
			memcpy(&m_matTransform.m[i][0], &m_vInfo[i], sizeof(_vec3));
	}

	// 현재 행렬을 실제 월드 행렬로 변환
	void Set_TransformToWorld(const _matrix& matBaseTransform)
	{
		m_matTransform *= matBaseTransform;
	}

	// 로컬 행렬을 재조정하고 월드 행렬로 변환하여 반환
	void Get_CalculatedWorldTransform(const _matrix& matBaseTransform)
	{
		Readjust_Transform();
		Set_TransformToWorld(matBaseTransform);
	}
	
#pragma endregion

public:		// 트랜스폼 영역, Transform에서 옮겨온 거임
	GETSET_EX1(_vec3, m_vInfo[INFO_RIGHT],	Right,	GET_C_REF)
	GETSET_EX1(_vec3, m_vInfo[INFO_UP],		Up,		GET_C_REF)
	GETSET_EX1(_vec3, m_vInfo[INFO_LOOK],	Look,	GET_C_REF)
	GETSET_EX2(_vec3, m_vInfo[INFO_POS],	Pos,	GET_C_REF, SET_C)


	GETSET_EX2(_vec3,	m_vRotation,		Rotation,		GET_C_REF, SET_C)
	GETSET_EX2(_vec3,	m_vScale,			Scale,			GET_C_REF, SET_C)
	GETSET_EX2(_matrix, m_matTransform,		Transform,		GET_C_REF, SET_C)

protected:
	_vec3		m_vInfo[INFO_END];		// 위치, 방향 정보
	_vec3		m_vRotation;			// 오일러 회전축
	_vec3		m_vScale;				// 크기
	_matrix		m_matTransform;			// 월드 행렬
};

END
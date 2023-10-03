#include "BackGround.h"

#include "Export_System.h"
#include "Export_Utility.h"
#include <ImguiMgr.h>

CBackGround::CBackGround(LPDIRECT3DDEVICE9 pGraphicDev)
	: Base(pGraphicDev)
{
}

CBackGround::CBackGround(const CBackGround& rhs)
	: Base(rhs)
{
}

CBackGround::~CBackGround()
{
}

CBackGround* CBackGround::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	ThisClass* pInstance = new ThisClass(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);

		MSG_BOX("BackGround Create Failed");
		return nullptr;
	}

	return pInstance;
}


HRESULT CBackGround::Add_Component()
{
	// 트랜스폼 컴포넌트
	NULL_CHECK_RETURN(m_pTransformComp = Set_DefaultComponent_FromProto<CTransformComponent>(ID_DYNAMIC, L"Com_Transform", L"Proto_TransformComp"), E_FAIL);
	// 버퍼
	NULL_CHECK_RETURN(m_pBufferComp = Set_DefaultComponent_FromProto<CRcBufferComp>(ID_STATIC, L"Com_Buffer", L"Proto_RcTexBufferComp"), E_FAIL);
	// 텍스쳐 컴포넌트
	NULL_CHECK_RETURN(m_pBackTextureComp = Set_DefaultComponent_FromProto<CTextureComponent>(ID_STATIC, L"Comp_TitleTexture", L"Proto_TitleBackTextureComp"), E_FAIL);
	// 텍스쳐 컴포넌트
	NULL_CHECK_RETURN(m_pTextureComp = Set_DefaultComponent_FromProto<CTextureComponent>(ID_STATIC, L"Comp_LogoTexture", L"Proto_LogoTextureComp"), E_FAIL);
	
	return S_OK;
}

HRESULT CBackGround::Ready_GameObject()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pAnimationTool = dynamic_cast<CImguiAnimationTool*>
		(CImguiMgr::GetInstance()->Get_MapImguiWin()[L"AnimationTool"]);

	if (m_pAnimationTool->Get_Animation()->empty())
	{
		m_vecAnimationInfo = m_pAnimationTool->Get_Animation();
	}	

	m_fSizeX = 400;
	m_fSizeY = 300;

	m_fX = m_fSizeX * 0.5f; // 중점위치 
	m_fY = m_fSizeY * 0.5f;

	m_pTransformComp->Set_Pos({ 0.f, 0.f, 0.f });	// 이미지 위치
	m_pTransformComp->Set_Scale({ m_fSizeX, m_fSizeY, 1.f });	// 이미지 크기

	return S_OK;
}

_int CBackGround::Update_GameObject(const _float& fTimeDelta)
{

	SUPER::Update_GameObject(fTimeDelta);
	
	m_fAniamtionFrame += m_fAnimationSpeed * fTimeDelta;
	if (m_fAniamtionFrame > 5.f)
		m_fAniamtionFrame = 0.f;

	//auto iter = m_vecAnimationInfo->begin();

	// 비었는지 검사
	if (!m_vecAnimationInfo->empty())
	{
		if (m_pAnimationTool->Get_FramePlaying())
		{
			m_fMaxFrame = m_vecAnimationInfo->size(); // 사이즈를 최대 프레임으로 설정
		}
	}

	if (m_pAnimationTool->Get_FramePlaying())
	{
		//int test = m_pAnimationTool->Get_FramePlaying();

		// 현재 프레임을 시간(프레임)마다 증가시키기
		
		//m_iFrameCount;

		// 현재 프레임이 최대 프레임에 도달한 경우
		if (m_pAnimationTool->Get_currentTime() >= m_fMaxFrame)
		{
			// 현재 프레임 초기화
			m_pAnimationTool->Set_currentTime(0);

			// 프레임 Off
			m_pAnimationTool->Set_FramePlaying(false);
		}
	}

	if (!m_vecAnimationInfo->empty())
	{
		if (m_fAniamtionFrame >= 0.f &&
			m_fAniamtionFrame <= m_vecAnimationInfo->back().time)
		{
			//m_eAnimationInfo = m_vecAnimationInfo[(int)m_iFrameCount].front();
			_uint iFrameIndex = 0U;
			for (_uint i = m_vecAnimationInfo->size() - 1; i >= 0 ; i--)
			{
				if ((*m_vecAnimationInfo)[i].time <= m_fAniamtionFrame)
				{
					iFrameIndex = i;
					break;
				}
			}

			// Constant
			//m_fSizeX = (*m_vecAnimationInfo)[iFrameIndex].vScale.x;
			//m_fSizeY = (*m_vecAnimationInfo)[iFrameIndex].vScale.y;

			//m_fX = m_fSizeX * 0.5f; // 중점위치 
			//m_fY = m_fSizeY * 0.5f;

			//m_pTransformComp->Set_Pos({ (*m_vecAnimationInfo)[iFrameIndex].vPos.x,
			//							(*m_vecAnimationInfo)[iFrameIndex].vPos.y,
			//							0.f });	// 이미지 위치

			//m_pTransformComp->Set_Scale({ m_fSizeX, m_fSizeY, 1.f });	// 이미지 크기


			// Linear
			if (iFrameIndex + 1U < m_vecAnimationInfo->size())
			{
				_float fFrameTimeDelta, fCurFrameTimeDelta;	//dt
				_float fX_Delta, fY_Delta;
				_float fSizeX_Delta, fSizeY_Delta;
				
				// 키 프레임간 시간 변화율
				fFrameTimeDelta = (*m_vecAnimationInfo)[iFrameIndex + 1U].time - (*m_vecAnimationInfo)[iFrameIndex].time;
				// 현재 키 프레임시간부터 현재 시간 변화율
				fCurFrameTimeDelta = (m_fAniamtionFrame - (*m_vecAnimationInfo)[iFrameIndex].time);
				
				fSizeX_Delta = (*m_vecAnimationInfo)[iFrameIndex + 1U].vScale.x - (*m_vecAnimationInfo)[iFrameIndex].vScale.x;
				fSizeX_Delta *= fCurFrameTimeDelta / fFrameTimeDelta;
				fSizeY_Delta = (*m_vecAnimationInfo)[iFrameIndex + 1U].vScale.y - (*m_vecAnimationInfo)[iFrameIndex].vScale.y;
				fSizeY_Delta *= fCurFrameTimeDelta / fFrameTimeDelta;

				m_fSizeX = (*m_vecAnimationInfo)[iFrameIndex].vScale.x + fSizeX_Delta;
				m_fSizeY = (*m_vecAnimationInfo)[iFrameIndex].vScale.y + fSizeY_Delta;

				fX_Delta = (*m_vecAnimationInfo)[iFrameIndex + 1U].vPos.x - (*m_vecAnimationInfo)[iFrameIndex].vPos.x;
				fX_Delta *= fCurFrameTimeDelta / fFrameTimeDelta;
				fY_Delta = (*m_vecAnimationInfo)[iFrameIndex + 1U].vPos.y - (*m_vecAnimationInfo)[iFrameIndex].vPos.y;
				fY_Delta *= fCurFrameTimeDelta / fFrameTimeDelta;

				m_pTransformComp->Set_Pos({ (*m_vecAnimationInfo)[iFrameIndex].vPos.x + fX_Delta,
											(*m_vecAnimationInfo)[iFrameIndex].vPos.y + fY_Delta,
											0.f });	// 이미지 위치

				m_pTransformComp->Set_Scale({ m_fSizeX, m_fSizeY, 1.f });	// 이미지 크기
			}
			else
			{
				m_fSizeX = (*m_vecAnimationInfo)[iFrameIndex].vScale.x;
				m_fSizeY = (*m_vecAnimationInfo)[iFrameIndex].vScale.y;

				m_fX = m_fSizeX * 0.5f; // 중점위치 
				m_fY = m_fSizeY * 0.5f;

				m_pTransformComp->Set_Pos({ (*m_vecAnimationInfo)[iFrameIndex].vPos.x,
											(*m_vecAnimationInfo)[iFrameIndex].vPos.y,
											0.f });	// 이미지 위치

				m_pTransformComp->Set_Scale({ m_fSizeX, m_fSizeY, 1.f });	// 이미지 크기
			}
		}

	}

	Engine::Add_RenderGroup(RENDER_UI, this);

	return 0;
}

void CBackGround::LateUpdate_GameObject()
{
	SUPER::LateUpdate_GameObject();
}

void CBackGround::Render_GameObject()
{
	// 텍스처의 트랜스폼을 월드 행렬, DYNAMIC으로 설정시 수동으로 해줄 필요가 없음
	m_pBackTextureComp->Readjust_Transform();	
	// 텍스처 행렬 * 부모(게임오브젝트)의 행렬
	m_pBackTextureComp->Set_TransformToWorld(*m_pTransformComp->Get_Transform());
	// 위의 두개만 쓰면 텍스처 행렬과 부모 행렬을 별개로 두고 계산할 수 있음.

	// 이제부터 Render_Texture 함수 안에서 자동으로 텍스처의 행렬이 디바이스에 들어간다.(SetTransform(D3DTS_WORLD, 텍스처 행렬))
	m_pBackTextureComp->Render_Texture(0, true);
	m_pBufferComp->Render_Buffer();

	// 이건 부모 행렬을 텍스처 행렬에 그대로 쓰는 방법, 텍스처 별개의 행렬이 필요없을 때 사용
	m_pTextureComp->Set_Transform(m_pTransformComp->Get_Transform());

	// m_pBackTextureComp에 적용한 것과 m_pTextureComp에 적용한 것. 두개다 백그라운드에서 동일한 위치, 크기로 설정되므로 유효함.

	// Set_Transform : 단순 행렬 덮어쓰기
	// Readjust_Transform : 텍스처의 로컬 좌표, 회전, 크기를 텍스처의 월드 행렬(트랜스폼)에 적용한다.
	// Set_TransformToWorld : 텍스처 월드 행렬 * 부모 행렬, 행렬곱임

	m_pTextureComp->Render_Texture(0, true);
	m_pBufferComp->Render_Buffer();
}

// 애니메이션 불러오기
void CBackGround::LoadAnimationFromFile(const char* fileName)
{
	// .dat 파일 확장자를 추가한 파일 이름 생성
	std::string datFileName = "../Data/" + std::string(fileName) + ".dat";

	// 파일을 UTF-8로 열기
	std::ifstream file(datFileName.c_str(), std::ios::in | std::ios::binary);

	if (!file.is_open()) {
		// 파일을 열 수 없을 때의 오류 처리
		return;
	}



	m_vecAnimationInfo->clear();
	Keyframe keyframe;

	while (file >> keyframe.time >> keyframe.value >> keyframe.type >>
		keyframe.isEaseIn >> keyframe.isEaseOut >>
		keyframe.vScale.x >> keyframe.vScale.y >> keyframe.vScale.z >>
		keyframe.vRot.x >> keyframe.vRot.y >> keyframe.vRot.z >>
		keyframe.vPos.x >> keyframe.vPos.y >> keyframe.vPos.z) {
		m_vecAnimationInfo->push_back(keyframe);
	}

	file.close();
}

void CBackGround::Free()
{
	SUPER::Free();


}

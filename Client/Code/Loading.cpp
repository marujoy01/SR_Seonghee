#include "stdafx.h"
#include "Header/Loading.h"

#include "Export_System.h"
#include "Export_Utility.h"


CLoading::CLoading(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
	, m_bFinish(false)
{
	m_pGraphicDev->AddRef();
}

CLoading::~CLoading()
{
}

CLoading* CLoading::Create(LPDIRECT3DDEVICE9 pGraphicDev, LOADINGID eID)
{
	ThisClass* pInstance = new ThisClass(pGraphicDev);

	if (FAILED(pInstance->Ready_Loading(eID)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Loading Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CLoading::Free()
{
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
	DeleteCriticalSection(&m_Crt);

	Safe_Release(m_pGraphicDev);
}

HRESULT CLoading::Ready_Loading(LOADINGID eID)
{
	InitializeCriticalSection(&m_Crt);

	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, Thread_Main, this, 0, nullptr);

	m_eLoadingID = eID;

	return S_OK;
}

_uint CLoading::Loading_For_Stage()
{
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_TriColBufferComp", CTriCol::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_TerrainBufferComp", CTerrainTexComponent::Create(m_pGraphicDev, L"./Resource/Texture/Terrain/Height.bmp", VTXCNTX, VTXCNTZ, VTXITV)), E_FAIL);
	
	//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_CameraComp", CCameraComponent::Create(m_pGraphicDev, g_hWnd)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_CalculatorComp", CCalculator::Create(m_pGraphicDev)), E_FAIL);

	// 텍스처 컴포넌트
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_TerrainTextureComp", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"./Resource/Texture/Terrain/Terrain0.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_SkyBoxTextureComp", CTexture::Create(m_pGraphicDev, TEX_CUBE, L"./Resource/Texture/SkyBox/burger%d.dds", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_PlayerTextureComp", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"./Resource/Texture/Player0.png")), E_FAIL);

	
	FAILED_CHECK_RETURN(Engine::Ready_SoundDev(), E_FAIL);

	//Engine::CSoundMgr::GetInstance()->Play_Sound(L"loop_battle.mp3", SOUND_BGM, 0.3f);

	FAILED_CHECK_RETURN(Ready_Layer_Completed(), E_FAIL);

	m_bFinish = true;

	return 0;
}

_uint CLoading::Thread_Main(void * pArg)
{
	CLoading*		pLoading = reinterpret_cast<CLoading*>(pArg);

	_uint iFlag(0);

	EnterCriticalSection(pLoading->Get_Crt());

	switch (pLoading->Get_LoadingID())
	{
	case LOADING_STAGE:
		iFlag = pLoading->Loading_For_Stage();
		break;

	case LOADING_BOSS:
		break;

	}

	LeaveCriticalSection(pLoading->Get_Crt());

	//_endthreadex(0);

	return iFlag;
}

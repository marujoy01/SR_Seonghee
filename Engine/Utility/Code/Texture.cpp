#include "Texture.h"

CTexture::CTexture()
{
}

CTexture::CTexture(LPDIRECT3DDEVICE9 pGraphicDev)
    : Base(pGraphicDev)
{
}

CTexture::CTexture(const CTexture& rhs)
    : Base(rhs)
{
    // 벡터는 공간 예약 후 복사
    size_t	iSize = rhs.m_vecTexture.size();
    m_vecTexture.reserve(iSize);

    m_vecTexture = rhs.m_vecTexture;

    // 텍스처별로 레퍼카운트 증가
    for (size_t i = 0; i < iSize; ++i)
        m_vecTexture[i]->AddRef();
}

CTexture::~CTexture()
{
}

CTexture* CTexture::Create(LPDIRECT3DDEVICE9 pGraphicDev, TEXTUREID eType, _tchar* pPath, const _uint& iCnt)
{
	ThisClass* pInstance = new ThisClass(pGraphicDev);

	if (FAILED(pInstance->Ready_Texture(eType, pPath, iCnt)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Texture Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent* CTexture::Clone()
{
	return new ThisClass(*this);
}

void CTexture::Free()
{
	SUPER::Free();
}

HRESULT CTexture::Ready_Texture(TEXTUREID eType, const _tchar* pPath, const _uint& iCnt)
{
	m_vecTexture.reserve(iCnt);

	IDirect3DBaseTexture9* pTexture = nullptr;

	for (_uint i = 0; i < iCnt; ++i)
	{
		TCHAR	szFileName[256] = L"";
		wsprintf(szFileName, pPath, i);

		switch (eType)
		{
		case TEX_NORMAL:
			FAILED_CHECK_RETURN(D3DXCreateTextureFromFile(m_pGraphicDev, szFileName, (LPDIRECT3DTEXTURE9*)&pTexture), E_FAIL);
			break;

		case TEX_CUBE:
			FAILED_CHECK_RETURN(D3DXCreateCubeTextureFromFile(m_pGraphicDev, szFileName, (LPDIRECT3DCUBETEXTURE9*)&pTexture), E_FAIL);
			break;
		}

		m_vecTexture.push_back(pTexture);
	}

	return S_OK;
}

void CTexture::Render_Texture(const _uint& iIndex)
{
	// 인덱스 오버플로우 막기
	if (m_vecTexture.size() <= iIndex)
		return;

	m_pGraphicDev->SetTexture(0, m_vecTexture[iIndex]);
}

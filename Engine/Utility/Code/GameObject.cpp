#include "GameObject.h"

CGameObject::CGameObject(LPDIRECT3DDEVICE9 pGraphicDev)
    : m_pGraphicDev(pGraphicDev)
{
    m_pGraphicDev->AddRef();
}

CGameObject::CGameObject(const CGameObject& rhs)
    : m_pGraphicDev(rhs.m_pGraphicDev)
{
    m_pGraphicDev->AddRef();
}

CGameObject::~CGameObject()
{

}

void CGameObject::Free()
{
    for (size_t i = 0; i < ID_END; i++)
    {
        for_each(m_mapComponent[i].begin(), m_mapComponent[i].end(), CDeleteMap());
        m_mapComponent[i].clear();
    }

    Safe_Release(m_pGraphicDev);
}

CComponent* CGameObject::Get_Component(COMPONENTID eID, const _tchar* pComponentTag)
{
    // 외부에서 컴포넌트에 대한 주소를 얻어올 수 있도록 하는 함수
    // 오브젝트 -> 컴포넌트
    CComponent* pComponent = Find_Component(pComponentTag, eID);
    
    NULL_CHECK_RETURN(pComponent, nullptr);

    return pComponent;
}

HRESULT CGameObject::Bind_Component(COMPONENTID eID, CComponent*& pComponent, const _tchar* pComponentTag)
{
    auto result = m_mapComponent[eID].emplace(pComponentTag, pComponent);

    // 컴포넌트 연결 실패
    if (!result.second)
        return E_FAIL;

    pComponent->Set_Owner(this);

    return S_OK;
}

HRESULT CGameObject::Ready_GameObject()
{
    return S_OK;
}

_int CGameObject::Update_GameObject(const _float& fTimeDelta)
{
    // 프레임 업데이트를 수행해야하는 컴포넌트 집단에 대해 업데이트 수행
    for (auto& iter : m_mapComponent[ID_DYNAMIC])
        iter.second->Update_Component(fTimeDelta);

    return 0;
}

void CGameObject::LateUpdate_GameObject()
{
    // 프레임 업데이트를 수행해야하는 컴포넌트 집단에 대해 업데이트 수행
    for (auto& iter : m_mapComponent[ID_DYNAMIC])
        iter.second->LateUpdate_Component();
}

CComponent* CGameObject::Find_Component(const _tchar* pComponentTag, COMPONENTID eID)
{
    // 내부적으로 컴포넌트를 태그를 통해 찾도록 지원하는 함수
    //auto iter = find_if(m_mapComponent[eID].begin(), m_mapComponent[eID].end(), CTag_Finder(pComponentTag));
    auto iter = m_mapComponent[eID].find(pComponentTag);

    if (iter == m_mapComponent[eID].end())
        return nullptr;

    return iter->second;
}


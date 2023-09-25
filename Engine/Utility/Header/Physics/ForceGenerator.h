#pragma once

#include "Engine_Define.h"

#include "RigidBody.h"

BEGIN(Engine)

class FForceGenerator;

/// <summary>
/// 힘 등록기
/// </summary>
class FForceRegistry
{
protected:
    struct FForceRegistration
    {
        FRigidBody* body;
        FForceGenerator* fg;
    };
    typedef vector<FForceRegistration> Registry;
    Registry registrations;

public:
    void Add(FRigidBody* body, FForceGenerator* fg);
    void Remove(FRigidBody* body, FForceGenerator* fg);
    void Clear();
    void Update_Forces(Real duration);
};


/// <summary>
/// 각종 힘을 발생시키는 클래스의 원형
/// </summary>
class FForceGenerator abstract
{
	THIS_CLASS(FForceGenerator)

public:
	virtual void Update_Force(FRigidBody* pBody, const Real& fDuration) PURE;

};


/// <summary>
/// 중력 힘 발생기
/// </summary>
class FForce_Gravity
{
	THIS_CLASS(FForce_Gravity)

private:
	FVector3 vGravity;

public:
	FForce_Gravity(const FVector3& gravity);

	virtual void Update_Force(FRigidBody* pBody, const Real& fDuration);
};


/// <summary>
/// 스프링 힘 발생기
/// </summary>
class FForce_Spring
{
	THIS_CLASS(FForce_Spring)

private:
	FVector3 vConnectionPoint;		// 연결 포인트
	FVector3 vOtherConnectionPoint;	// 다른 객체 연결 포인트

	FRigidBody* pOther;				// 다른 객체

	Real		fSpringConstant;	// 스프링 상수
	Real		fRestLength;		// 유휴 길이, 원본 길이

public:
	FForce_Spring(const FVector3& localConnectionPt, FRigidBody* other, const FVector3& otherConnectionPt,
						Real springConstant, Real restLength);

	virtual void Update_Force(FRigidBody* pBody, const Real& fDuration);
};

END
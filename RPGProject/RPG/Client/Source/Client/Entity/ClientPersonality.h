#pragma once
#include "KBEngine.h"
/*
 KBEngine�ص��ӿ�
*/
class ClientPersonality : public KBEngine::KBEPersonality
{
public:
	/* ��ĳ��space data���ı������ʱ���˷��������� */
	virtual void OnSetSpaceData(uint32 spaceID, const FString &key, const FString &value)override;

	/* ��ĳ��space data��ɾ��ʱ���˷��������� */
	virtual void OnDelSpaceData(uint32 spaceID, const FString &key)override;

	/* ���������е�Space�����˵�ͼ�ĵ�������ʱ���˷��������� */
	virtual void OnAddSpaceGeometryMapping(uint32 spaceID, const FString &respath)override;

	/* ����¼ʧ��ʱ���˷��������� */
	virtual void OnLoginFailed(int32 errCode, const FString& errName, const FString& errDesc, const TArray<uint8>& serverDatas)override;

	/* ��������������ӶϿ�ʱ���˷��������� */
	virtual void OnDisconnect()override;




	/* ���ɹ�ͨ��KBEngineApp::ReLoginBaseapp()�޸�����󣬴˷���������*/
	virtual void OnReLoginBaseapp(int32 errCode, const FString& errName, const FString& errDesc)override;

	/* ���ɹ�ͨ��KBEngineApp::NewPassword()�޸�����󣬴˷���������*/
	virtual void OnNewPassword(int32 errCode, const FString& errName, const FString& errDesc)override;

	/* ���ɹ�ͨ��KBEngineApp::BindAccountEmail()�޸�����󣬴˷���������*/
	virtual void OnBindAccountEmail(int32 errCode, const FString& errName, const FString& errDesc)override;

	/* ���ɹ�ͨ��KBEngineApp::CreateAccount()�������˺��Ժ󣬴˷��������� */
	virtual void OnCreateAccountSuccess(const FString& account)override;

	/* ���ɹ�ͨ��KBEngineApp::ResetPassword()�����˺�����󣬴˷��������� */
	virtual void OnResetPasswordSuccess(const FString& account)override;

};

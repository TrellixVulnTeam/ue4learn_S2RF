#pragma once




///��Ϸ״̬
UENUM(Blueprintable)
enum class EGameStatus : uint8
{
	Login = 1,			///�˺ŵ�¼
	LoginLoading,		///�˺ŵ�¼����
	SelectRole,			///��ɫѡ��
	SelectRoleLoading,	///��ɫѡ�����
	BackToSelectRoleLoading, ///���ؽ�ɫѡ�����
	CreateRole,			///��ɫ����
	CreateRoleLoading,	///��ɫ��������
	Teleport,			///����
	TeleportLoading,	///���ͼ���
	InWorld,			///��Ϸ����
	InWorldLoading,		///��Ϸ�������
};

///��¼�׶�
UENUM(Blueprintable)
enum class ELoginStage : uint8
{
	NoLoginStage = 1,		///δ��¼�׶�
	TryLoginStage,			///���Ե�¼�׶� 
	AccountLoginStage,		///�˺ŵ�¼�׶�
	RoleLoginStage			///��ɫ��¼�׶�
};

///��������
UENUM(Blueprintable)
enum class ELoadingType : uint8
{
	None = 1,					///û���ڼ���
	LoginLoading,				///�˺ŵ�¼����
	SelectRoleLoading,			///��ɫѡ�����	
	BackToSelectRoleLoading,	///���ؽ�ɫѡ�����
	CreateRoleLoading,			///��ɫ��������
	TeleportLoading,			///���ͼ���
	InWorldLoading,				///��Ϸ�������
};
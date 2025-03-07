#pragma once

#include "Core.h"
#include "MemoryStream.h"

namespace KBEngine
{
	/*
	 KBEngine的入口类，想要使用KBEngine插件，必须继承于这个类，并在类中实现自己特定的行为。
	*/
	class KBENGINE_API KBEPersonality
	{
	public:
		virtual ~KBEPersonality() {};
	public:
		/* 当某个space data被改变或设置时，此方法被触发 */
		virtual void OnSetSpaceData(uint32 spaceID, const FString &key, const FString &value) {}

		/* 当某个space data被删除时，此方法被触发 */
		virtual void OnDelSpaceData(uint32 spaceID, const FString &key) {}

		/* 当服务器中的Space加载了地图的导航数据时，此方法被触发 */
		virtual void OnAddSpaceGeometryMapping(uint32 spaceID, const FString &respath) {}

		/* 当登录失败时，此方法被触发 */
		virtual void OnLoginFailed(int32 errCode, const FString& errName, const FString& errDesc, const TArray<uint8>& serverDatas) {}

		/* 当与服务器的连接断开时，此方法被触发 */
		virtual void OnDisconnect() {}




		/* 当成功通过KBEngineApp::ReLoginBaseapp()修改密码后，此方法被触发*/
		virtual void OnReLoginBaseapp(int32 errCode, const FString& errName, const FString& errDesc) {}

		/* 当成功通过KBEngineApp::NewPassword()修改密码后，此方法被触发*/
		virtual void OnNewPassword(int32 errCode, const FString& errName, const FString& errDesc) {}

		/* 当成功通过KBEngineApp::BindAccountEmail()修改密码后，此方法被触发*/
		virtual void OnBindAccountEmail(int32 errCode, const FString& errName, const FString& errDesc) {}

		/* 当成功通过KBEngineApp::CreateAccount()创建了账号以后，此方法被触发 */
		virtual void OnCreateAccountSuccess(const FString& account) {}

		/* 当成功通过KBEngineApp::ResetPassword()重置账号密码后，此方法被触发 */
		virtual void OnResetPasswordSuccess(const FString& account) {}

		/*
		服务端通知流数据下载开始
		see also: 服务器文档，baseapp -> classes -> Proxy::streamStringToClient()
		*/
		void OnStreamDataStarted(int16 id, uint32 datasize, const FString& descr) {}
		void OnStreamDataRecv(MemoryStream &stream) {}
		void OnStreamDataCompleted(int16 id) {}

	public:
		static void Register(KBEPersonality * inst);
		static void Deregister();
		FORCEINLINE static KBEPersonality* Instance() { return instance_; }

	private:
		static KBEPersonality* instance_;
	};
}

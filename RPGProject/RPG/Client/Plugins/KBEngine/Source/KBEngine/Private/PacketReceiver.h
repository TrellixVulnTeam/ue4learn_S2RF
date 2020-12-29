#pragma once
#include "KBEnginePrivatePCH.h"
#include "MessageReader.h"

namespace KBEngine
{
	class MessageReader;
	class NetworkInterface;

	class PacketReceiver : public FRunnable
	{

	public:
		PacketReceiver(NetworkInterface* networkInterface, uint32 buffLength = 65535);
		~PacketReceiver();

		void StartBackgroundRecv();
		void WillClose() { willClose_ = true; }

	public:
		// for FRunnable
		virtual uint32 Run() override;

	private:
		// ����������socket�У���������ӿڿ��ܻᵼ�¿������ⲿ�ǲ������ɱ���
		void StopBackgroundRecv();

	private:
		NetworkInterface* networkInterface_ = NULL;

		FRunnableThread* thread_ = nullptr;
		bool breakThread_ = false;

		// ��NetworkInterface�ر�����ʱ֪ͨ��
		// �Ա����������ر�����ʱҲ����������Ϣ
		bool willClose_ = false;
	};

}
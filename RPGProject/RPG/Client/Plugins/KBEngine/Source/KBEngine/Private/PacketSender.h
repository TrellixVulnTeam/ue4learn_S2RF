#pragma once

namespace KBEngine
{
	class NetworkInterface;

	class PacketSender : public FRunnable
	{
	public:
		PacketSender(NetworkInterface* networkInterface, uint32 buffLength = 65535);
		~PacketSender();

		bool Send(uint8* datas, uint32 length);

		void StartBackgroundSend();
		void WillClose() { willClose_ = true; }

	public:
		// for FRunnable
		virtual uint32 Run() override;
		void DoThreadedWork();

	private:
		// �����п���������socket�У���������ӿڿ��ܻᵼ�¿������ⲿ�ǲ������ɱ���
		void StopBackgroundSend();

		uint32 SendSize() const;
		void BackgroundSend();
		FString ReadPipe();
		void WritePipe();
		void InitPipe();
		void ClosePipe();

	private:
		uint8* buffer_;
		uint32	bufferLength_ = 0;

		uint32 wpos_ = 0;				// д�������λ��
		uint32 spos_ = 0;				// ������ϵ�����λ��
		bool sending_ = false;

		NetworkInterface* networkInterface_ = NULL;

		FRunnableThread* thread_ = nullptr;
		bool breakThread_ = false;

		void* readPipe_;
		void* writePipe_;

		// ��NetworkInterface�ر�����ʱ֪ͨ��
		// �Ա����������ر�����ʱҲ����������Ϣ
		bool willClose_ = false;
	};

}
#pragma once
#include <functional>

#include "Networking.h"
#include "MessageReader.h"


namespace KBEngine
{
	class KBEngineApp;
	class PacketReceiver;
	class PacketSender;


	class KBENGINE_API NetworkInterface
	{
	public:
		typedef std::function<void(FString, int, bool)> ConnectCallbackFun;

		class NetworkStatus
		{
		public:
			virtual ~NetworkStatus() {}
			virtual void MainThreadProcess(NetworkInterface *networkInterface) = 0;
		};

		typedef struct
		{
			// for connect
			FString connectIP = "";
			uint16 connectPort = 0;
			ConnectCallbackFun connectCB;
			FSocket* socket = nullptr;
			NetworkInterface* networkInterface = nullptr;
			FString error = "";
		}ConnectState;

	public:
		NetworkInterface(MessageReader* messageReader);
		~NetworkInterface();

		static const int TCP_PACKET_MAX = 65535;

		bool InitSocket(uint32 receiveBufferSize = 0, uint32 sendBufferSize = 0);
		void Reset();

		ISocketSubsystem* SocketSubsystem() { return socketSubsystem_; }
		FSocket* Socket() { return socket_; }

		bool Valid();

		// ��������������ģʽ����Ϊ���ڲ���ı�״̬��ɾ��ԭ����״̬����
		void OnConnected(ConnectState state);

		void ConnectTo(const FString& ip, uint16 port, ConnectCallbackFun callback);

		void Close();

		bool Send(uint8* datas, int32 length);

		void Process();

		void ChangeNetworkStatus(NetworkStatus* status);

		PacketReceiver* GetReceiver() { return packetReceiver_; }

		void ProcessMessage();

	public:
		// for internal

		// ����PacketReceiver��PacketSender����Socket�д���ʱ��֪ͨ�ر�ʹ��
		// �˽ӿڽ������̵߳���
		void WillClose();

	public:
		MessageReader* messageReader_ = nullptr;
	private:
		FSocket* socket_ = nullptr;
		ISocketSubsystem* socketSubsystem_ = nullptr;

		PacketReceiver* packetReceiver_ = nullptr;
		PacketSender* packetSender_ = nullptr;

		bool willClose_ = false;

		NetworkStatus* networkStatus_ = nullptr;
	};

}
#pragma once

#include "Engine.h"

#include "KBEMath.h"
#include "EntityDeclareDefine.h"

DECLARE_STATS_GROUP(TEXT("KBEngine_Entity"), STATGROUP_KBEngine_Entity, STATCAT_Advanced);

namespace KBEngine
{
	class KBEngineApp;
	class BaseApp;
	class ScriptModule;
	class Mailbox;
	class Property;

	/*
	KBEngine逻辑层的实体基础类
	所有扩展出的游戏实体都应该继承于该模块
	*/
	class KBENGINE_API Entity
	{
	public:
		friend class KBEngineApp;
		friend class BaseApp;
		friend class ScriptModule;

		Entity();
		virtual ~Entity();

		FORCEINLINE bool InWorld() { return inWorld_; }
		FORCEINLINE bool Inited() { return inited_; }

		FORCEINLINE int32 ID() { return id_; }

		FORCEINLINE const FString& ClassName() { return className_; }

		FORCEINLINE const FVector &Position() { return position_; }
		FORCEINLINE const FVector &Direction() { return direction_; }
		FORCEINLINE const FVector &LocalPosition() { return localPosition_; }
		FORCEINLINE const FVector &LocalDirection() { return localDirection_; }

		// 用于被控制者（如角色）定期向服务器更新坐标和朝向
		void UpdateVolatileDataToServer(const FVector& pos, const FVector& dir);

		FORCEINLINE bool IsOnGround() { return isOnGround_; }
		FORCEINLINE void IsOnGround(bool yes) { isOnGround_ = yes; }

		FORCEINLINE Mailbox* BaseMailbox() { return baseMailbox_; }
		FORCEINLINE Mailbox* CellMailbox() { return cellMailbox_; }

		FORCEINLINE void Actor(AActor* actor) { actor_ = actor; }
		FORCEINLINE AActor* Actor() { return actor_; }

		FORCEINLINE bool IsControlled() { return isControlled_; }

		// 该Entity是否是玩家自己
		bool IsPlayer();

		// 通过属性名查询值
		virtual FVariant GetDefinedProperty(FString name);

		// 调用服务器的方法
		void BaseCall(const FString &methodname, const FVariantArray &arguments);
		void CellCall(const FString &methodname, const FVariantArray &arguments);
		FORCEINLINE bool EntityCallEnable() { return entityCallEnable_; }
		FORCEINLINE void EntityCallEnable(bool enable) { entityCallEnable_ = enable; }

		int32 ParentID() { return parentID_; }
		Entity* Parent() { return parent_; }

		// 世界坐标和本地坐标互換
		virtual FVector PositionLocalToWorld(const FVector& localPos);
		virtual FVector PositionWorldToLocal(const FVector& worldPos);
		virtual FVector DirectionLocalToWorld(const FVector& localDir);
		virtual FVector DirectionWorldToLocal(const FVector& worldDir);

		// 父对象位置改变，同步更新子对象的坐标和朝向
		void SyncVolatileDataToChildren(bool positionOnly);

		/* 通知子对象更新自己的易变数据----即坐标和朝向。
		 * 此方法有必要时可以由外部逻辑调用。
		 */
		void SyncAndNotifyVolatileDataToChildren(bool positionOnly);

		bool IsMultCastProperty(const FString& propertyname);

	protected:
		/*
		KBEngine的实体构造函数，与服务器脚本对应。
		存在于这样的构造函数是因为KBE需要创建好实体并将属性等数据填充好才能告诉脚本层初始化
		*/
		virtual void __init__() { }

		virtual void OnDestroy() { }

		// 用于继承类的重载
		virtual void OnEnterWorld() { }                  // 当Entity进入世界时，此方法被调用
		virtual void OnLeaveWorld() { }                  // 当Entity离开世界（被销毁时）时，此方法被调用
		virtual void OnEnterSpace() { }                  // 当Entity进入地图时，此方法被调用
		virtual void OnLeaveSpace() { }                  // 当Entity离开地图时，此方法被调用
		virtual void OnUpdateVolatileData() { }          // 当Entity的位置或朝向因移动而被改变时，此方法被调用
		virtual void OnUpdateVolatileDataByParent() { }  // 当Entity的因为父对象的移动而改变位置时，此方法被调用


		// 当Entity的某个属性产生变化时，此方法被调用，通常情况下，我们不需要重载这个方法
		virtual void OnUpdateProperty(const FString &name, const FVariant &newVal, const FVariant &oldVal);

		virtual void Set_Position(const FVector &oldVal);
		virtual void Set_Direction(const FVector &oldVal);

		virtual void OnRemoteMethodCall(const FString &name, const TArray<FVariant> &args);

		/*
		 * This callback method is called when the local entity control by the client has been enabled or disabled. 
		 * See the Entity.controlledBy() method in the CellApp server code for more infomation.

		 * @param isControlled:
		 *   对于玩家自身来说，它表示是否自己被其它玩家控制了；
		 *   对于其它entity来说，表示我本机是否控制了这个entity
		 */
		virtual void OnControlled(bool isControlled) {}

		// 初始化Entity的属性字典；
		virtual void InitProperties(ScriptModule& scriptModule);

		/* 当获得父对象时，此方法被触发 */
		virtual void OnGotParentEntity() {}

		/* 当失去父对象时，此方法被触发 */
		virtual void OnLoseParentEntity() {}

	private:
		// 以下所有私有方法或属性，都由KBEngine内部机制调用

		FORCEINLINE void ID(int32 v) { id_ = v; }
		FORCEINLINE void ClassName(const FString& className) { className_ = className; }
		FORCEINLINE void InWorld(bool yes) { inWorld_ = yes; }
		FORCEINLINE void Inited(bool yes) { inited_ = yes; }
		FORCEINLINE void BaseMailbox(Mailbox* mb) { baseMailbox_ = mb; }
		FORCEINLINE void CellMailbox(Mailbox* mb) { cellMailbox_ = mb; }

		// 设置被控制状态
		void SetControlled(bool yes);

		// 来自服务器：强制位置改变
		void OnPositionSet(const FVector &unrealPos);

		// 来自服务器：强制朝向改变
		void OnDirectionSet(const FVector &unrealDir);

		void CallPropertysSetMethods();

		// 用于引擎内部销毁Entity实例使用
		void Destroy();

		void EnterWorld();
		void LeaveWorld();
		void EnterSpace();
		void LeaveSpace();

		void AddDefinedProperty(FString name, const FVariant &v);
		void SetDefinedProperty(FString name, const FVariant &val);
		FVariant GetDefinedPropertyByUType(uint16 utype);
		void SetDefinedPropertyByUType(uint16 utype, const FVariant &val);

		void RemoteMethodCall(const FString &name, const TArray<FVariant> &args);

		void SetParent(Entity* ent);
		void AddChild(Entity* ent) { children_.Add(ent->ID(), ent); }
		void RemoveChild(Entity* ent) { children_.Remove(ent->ID()); }



	protected:
		// 用于 KBE_BEGIN_ENTITY_METHOD_MAP、KBE_END_ENTITY_METHOD_MAP 机制的基础声明
		static const KBE_ENTITY_METHOD_MAP* GetThisMethodMap() { return nullptr; }
		virtual const KBE_ENTITY_METHOD_MAP* GetMethodMap() const { return nullptr; }

		// 用于 KBE_BEGIN_ENTITY_PROPERTY_MAP、KBE_END_ENTITY_PROPERTY_MAP 机制的基础声明
		static const KBE_ENTITY_PROPERTY_MAP* GetThisPropertyMap() { return nullptr; }
		virtual const KBE_ENTITY_PROPERTY_MAP* GetPropertyMap() const { return nullptr; }

	protected:
		// 当前玩家最后一次同步到服务端的位置与朝向
		// 这两个属性是给引擎KBEngineApp用的，别的地方不要修改
		FVector lastSyncPos_ = FVector::ZeroVector;
		FVector lastSyncDir_ = FVector::ZeroVector;
		FVector lastSyncLocalPos_ = FVector::ZeroVector;
		FVector lastSyncLocalDir_ = FVector::ZeroVector;

		// EnterWorld()之后设置为true
		bool inWorld_ = false;

		// __init__()调用之后设置为true
		bool inited_ = false;

		Mailbox *baseMailbox_ = NULL;
		Mailbox *cellMailbox_ = NULL;
		bool entityCallEnable_ = true;


		// entityDef属性，服务端同步过来后存储在这里
		TMap<FString, Property*> defpropertys_;

		TMap<uint16, Property*> iddefpropertys_;

		int32 id_ = 0;
		FString className_;
		FVector position_ = FVector::ZeroVector;
		FVector direction_ = FVector::ZeroVector;
		bool isOnGround_ = true;

		// 与之对应的Actor实例指针
		AActor* actor_ = nullptr;

		/*
		 * 对于玩家自身来说，它表示是否自己被其它玩家控制了；
		 * 对于其它entity来说，表示我本机是否控制了这个entity
		 */
		bool isControlled_ = false;

		// 本地坐标
		FVector localPosition_ = FVector::ZeroVector;
		FVector localDirection_ = FVector::ZeroVector;

		// 父对象
		int32 parentID_ = 0;
		Entity* parent_ = nullptr;

		// 子对象列表
		TMap<int32, Entity*> children_;

	};


	/* 默认Entity类，当客户端需要创建没有注册的Entity时，会使用些Entity代替	*/
	class KBENGINE_API UnknownEntity : public Entity
	{
	public:

	};
}

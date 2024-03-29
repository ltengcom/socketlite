#ifndef TEST_SERVER_H
#define TEST_SERVER_H

#include "SL_Config.h"
#include "SL_Application.h"
#include "SL_ObjectPool.h"
#include "SL_Sync_Mutex.h"
#include "SL_Sync_Guard.h"
#include "SL_Socket_Iocp_Runner.h"
#include "SL_Socket_Select_Runner.h"
#include "SL_Socket_Epoll_Runner.h"
#include "SL_Socket_SendControl_HandlerManager.h"
#include "SL_Seda_Stage.h"
#include "SL_Seda_Event.h"
#include "SL_Rpc_Message.h"
#include "SL_Logger.h"
#include "SL_Disruptor_LockFreeQueue.h"
#include "SL_Disruptor_SingleWriteQueue.h"

#include "test_handler.h"
#include "test_seda_handler.h"
#include "test_disruptor_handler.h"

class TestServerApp: public SL_Application<TestServerApp>
{
public:
    TestServerApp();
    virtual ~TestServerApp();
    int run();

    SL_ObjectPool_SimpleEx<TestHandler, SL_Sync_SpinMutex> test_obj_pool_;
    SL_Socket_TcpServer<TestHandler, SL_ObjectPool_SimpleEx<TestHandler, SL_Sync_SpinMutex> > test_tcpserver_;
#ifdef SOCKETLITE_OS_WINDOWS
    SL_Socket_Iocp_Runner<SL_Sync_SpinMutex>    test_runner_;
#else
    SL_Socket_Epoll_Runner<SL_Sync_SpinMutex>   test_runner_;
#endif
    SL_Socket_SendControl_HandlerManager handler_mgr_;

    //seda
    SL_Seda_Stage<TestStageHandler> stage_;

    //disruptor
    SL_Disruptor_LockFreeQueue      disruptor_queue1_;
    SL_Disruptor_SingleWriteQueue   disruptor_queue2_;
    TestDisruptorHandler            disruptor_handler_;

    ushort port_;
};

#endif


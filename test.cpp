// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream>

#include <tchar.h>
#include <malloc.h>
#include <map>

#include "windows.h"

#include "boost/bind.hpp"
#include "boost/function.hpp"

void func(void)
{
    std::cout << "sldkjf" <<std::endl;
}


#define FUNCTYPED R (T0)
template<typename F>
class MyFuncA;

template<typename R, typename T0>
class MyFuncA<R (T0)>
{
public:
    typedef MyFuncA self_type;
    typedef R (*func_type)(T0);
    MyFuncA(func_type f):m_f(f){}

    //     static void invoke_void(func_type f, T0 a0)
    //     {
    // 
    //     }
    R operator()(T0 a0)
    {
        m_f(a0); 
    }
private:
    func_type m_f;
};


template<typename F>
class MemFunc;

template<typename R, typename C>
class MemFunc<R (C*)>
{
    typedef R (C::*MemFuncPtr)(void);
public:
    MemFunc(MemFuncPtr ptr, C*  a):_ptr(ptr),_a(a){}

    R operator()()
    {
        return (_a->*_ptr)();
    }
private:
    MemFuncPtr _ptr;
    C* _a;
};

class ThreadPool
{
    typedef std::vector<Thread*> ThreadVec;
public:
    ThreadPool()
    {
//         m_event = CreateEvent(NULL, TRUE, FALSE, NULL);
    }

    template<typename Functor>
    int RegServ(Functor f)
    {
        Thread* pThread = ThreadPool::CreateThread();
        if (!pThread)
            return -1;

        pThread->Reg(f);
        m_threads.push_back(pThread);
        pThread->start();

//         SetEvent(m_event);
        return 0;
    }

    int wait()
    {
        return 0;
    }
private:
//     HANDLE m_event;
    ThreadVec m_threads;
};

class Thread
{
    typedef boost::function<void (void)> Functor;
public:
    Thread():m_thread(NULL), m_run(0), m_active(false)
    {
        m_thread = CreateThread(NULL, 0, WorkFunc, this, CREATE_SUSPENDED, 0);
    }

    template<typename Functor>
    int Reg(Functor f)
    {
        m_f = f;
        start();
    }
    static DWORD WINAPI WorkFunc(LPVOID lpParameter)
    {
        Thread* pThread = (Thread*)lpParameter;
        assert(pThread);

        {
            while(pThread->m_run != -1)
            {
                pThread->m_f();

                pThread->m_active?0:pThread->m_active = !pThread->m_active;
            }
        }

        return 0;
    }

    bool start()
    {
        m_run = 1;
        return ResumeThread(m_thread)!=-1 ;
    }
    void term() {m_run = 0;}

private:
    HANDLE m_thread;
    volatile UINT m_run;        //0:suspend, 1:runing, -1:terminate
    volatile bool m_active;     //check for endless loop or deadlock

    Functor m_f;
    //boost::function<void ()> m_f;
};

class TA
{
public:
    void func(void){    std::cout << "sldkjf" <<std::endl;}
};
int _tmain(int argc, _TCHAR* argv[])
{
//     void (TA::*memfunc)(int) = &TA::func;
//         TA a;
//     TA* b = &a;
//     (b->*memfunc)(0);
//     (a.*memfunc)(0);
//     MemFunc<void (TA::)(void)> f;

    TA a;
    Thread t(func);
    t.start();

    WaitForMultipleObjects()
    t.wait();
    

//         MemFunc <void (TA*)> f(&TA::func, &a);
//         f();
//      a(0);
        //BOOST_PP_NODE_ENTRY_4(BOOST_PP_REPEAT_P)
    //        BOOST_PP_NODE_2(BOOST_PP_REPEAT_P)(BOOST_PP_REPEAT_P)
    //boost::_bi::bind_t<void, FuncType, boost::_bi::list_av_3<int,int,int>::type> a = boost::bind(func, 3,_1,_2);
   // boost::function<void (int,int,int)> f = boost::bind(func, 3, 2, 2);
//     f(1,2,3);
// 
//     a(1,2,3);
    //a(5, 7);
    //GetLastError();
    //EnumerateLoadedModules64(GetCurrentProcess(), CBEnumerateLoadedModulesProc64, NULL);

    //HANDLE hThread = CreateThread(NULL, 0, proc, NULL, 0, NULL);

    //Sleep(3000);
    //DWORD ret2 = SuspendThread(hThread);

    //CONTEXT _c;
    //BOOL ret = GetThreadContext(hThread, &_c);

    //typedef boost::error_info<int, std::string> file_name;
    //typedef boost::error_info<int, std::string> file_name2;
    //TException e;
    //e << file_name("skd.txt");
    //e << file_name2("skd2.txt");

    //std::string const* sss = boost::get_error_info<file_name>(e);
    //std::string const* sss2 = boost::get_error_info<file_name2>(e);

    system("pause");
    //file_read_error() << errno_code(3);
    return 0;
}


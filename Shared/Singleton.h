// Singleton.h: definition of the Singleton function.
//
//////////////////////////////////////////////////////////////////////

#ifndef _SINGLETON_
#define _SINGLETON_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

///////////////////////////////////////////////////////////////////////////////
// BEGIN : Singleton 생성 패턴을 위한 클래스
template<typename T>
class Singleton {
public:
    static T& instance();

    Singleton(const Singleton&) = delete;
    Singleton& operator= (const Singleton) = delete;

protected:
    struct token {};
    Singleton() {}
};

#include <memory>
template<typename T>
T& Singleton<T>::instance()
{
    static const std::unique_ptr<T> instance{new T{token{}}};
    return *instance;
}
// END
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// BEGIN
//template<typename T> T* TSingleton<T>::s_pInstance = NULL;
// END
///////////////////////////////////////////////////////////////////////////////
#endif
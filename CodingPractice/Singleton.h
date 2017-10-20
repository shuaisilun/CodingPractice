#ifndef __SYSTEM_SINGLETON__
#define __SYSTEM_SINGLETON__

#include <assert.h>

#define ASSERT assert

template <class CLASS>
class Singleton
{
public:
	static CLASS& Instance();
	static bool IsValid();
	static void Delete();

protected:
	Singleton();
	~Singleton();

private:
	static CLASS *m_Instance;
};

//==============================================================================
template <class CLASS>
CLASS& Singleton<CLASS>::Instance()
{
	ASSERT(m_Instance);
	return *m_Instance;
}


//==============================================================================
template <class CLASS>
bool Singleton<CLASS>::IsValid()
{
	return m_Instance != nullptr;
}


//==============================================================================
template <class CLASS>
void Singleton<CLASS>::Delete()
{
	ASSERT(m_Instance);
	delete m_Instance;
}


//==============================================================================
template <class CLASS>
Singleton<CLASS>::Singleton()
{
	ASSERT(!m_Instance);
	m_Instance = static_cast<CLASS *> (this);
}


//==============================================================================
template <class CLASS>
Singleton<CLASS>::~Singleton()
{
	ASSERT(m_Instance);
	m_Instance = NULL;
}

//==============================================================================
template< class CLASS >
CLASS * Singleton< CLASS >::m_Instance = NULL;

//==============================================================================
#endif //__SYSTEM_SINGLETON__

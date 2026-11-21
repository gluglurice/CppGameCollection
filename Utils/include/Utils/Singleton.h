#pragma once

template <typename T>
class CSingleton
{
public:
	static T* GetInstance();

protected:
	static T* m_instance;

	CSingleton();
};

template <typename T>
T* CSingleton<T>::m_instance = nullptr;

template <typename T>
T* CSingleton<T>::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new T();
	}
	return m_instance;
}

template <typename T>
CSingleton<T>::CSingleton() {}

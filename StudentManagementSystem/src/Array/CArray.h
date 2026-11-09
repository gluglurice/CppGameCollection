#pragma once

#include <fstream>
#include <Utils/Utils.h>

template<typename T>
class CArray
{
GET_SET_FUN_DECLAR(int, m_size, Size)
GET_SET_FUN_DECLAR(int, m_count, Count)
GET_SET_FUN_DECLAR(T*, m_array, Array)

public:

	CArray();

	CArray(int size);

	~CArray();

	void Expand();

	void Insert(int id, T elem);

	void Delete(int id);

	T& Select(int id);

	void SelectAll();

	void Update(int id, T& elem);

	void SaveToFile(const std::string& filename);

	void LoadFromFile(const std::string& filename);

	T* InsertSortAscend();
};

template<typename T>
CArray<T>::CArray() : m_size(0), m_count(0), m_array(nullptr) {}

template<typename T>
CArray<T>::CArray(int size) : m_size(size), m_count(0), m_array(new T[m_size]) {}

template<typename T>
CArray<T>::~CArray()
{
	if (m_array)
	{
		delete[] m_array;
		m_array = nullptr;
	}
}

template<typename T>
void CArray<T>::Expand()
{
	m_size *= 2;
	T* new_array = new T[m_size];
	for (int i = 0; i < m_count; i++)
	{
		new_array[i] = m_array[i];
	}
	delete[] m_array;
	m_array = new_array;
}

template<typename T>
void CArray<T>::Insert(int id, T elem)
{
	if (id < 0 || id >= m_size)
	{
		return;
	}

	if (m_count >= m_size)
	{
		Expand();
	}

	for (int i = m_count; i > id; i--)
	{
		m_array[i] = m_array[i - 1];
	}
	m_array[id] = elem;

	m_count++;
}

template<typename T>
void CArray<T>::Delete(int id)
{
	if (id < 0 || id >= m_size)
	{
		return;
	}

	for (int i = id; i < m_count - 1; i++)
	{
		m_array[i] = m_array[i + 1];
	}
	m_array[m_count - 1] = NULL;

	m_count--;
}

template<typename T>
T& CArray<T>::Select(int id)
{
	return m_array[id];
}

template<typename T>
void CArray<T>::SelectAll()
{
	for (int i = 0; i < m_count; i++)
	{
		std::cout << m_array[i] << std::endl;
	}
}

template<typename T>
void CArray<T>::Update(int id, T& elem)
{
	m_array[id] = elem;
}

template<typename T>
void CArray<T>::SaveToFile(const std::string& filename)
{
	std::ofstream out_file(filename, std::out);
	if (!out_file)
	{
		std::cout << "打开文件 " << filename  << " 失败！" << std::endl;
		return;
	}

	for (int i = 0; i < m_count; i++)
	{
		out_file << m_array[i] << std::endl;
	}

	out_file.close();
}

template<typename T>
void CArray<T>::LoadFromFile(const std::string& filename)
{
	std::ifstream in_file(filename, std::in);
	if (!in_file)
	{
		std::cout << "打开文件 " << filename  << " 失败！" << std::endl;
		return;
	}

	T elem;
	while (in_file >> elem)
	{
		Insert(m_count, elem);
	}

	in_file.close();
}

template<typename T>
T* CArray<T>::InsertSortAscend()
{
	for (int i = 1; i < m_count; i++)
	{
		T key = m_array[i];
		int j = i - 1;
		while (j >= 0 && m_array[j] > key)
		{
			m_array[j + 1] = m_array[j];
			j--;
		}
		m_array[j + 1] = key;
	}
	return m_array;
}

GET_SET_FUN_DEFINE_TEMPLATE(int, CArray, m_size, Size)
GET_SET_FUN_DEFINE_TEMPLATE(int, CArray, m_count, Count)
GET_SET_FUN_DEFINE_TEMPLATE(T*, CArray, m_array, Array)

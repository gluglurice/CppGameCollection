#pragma once

#include <Singleton.h>

class CSolution : public CSingleton<CSolution>
{
	friend CSingleton<CSolution>;

protected:
	CSolution();

public:
	void Run();
};

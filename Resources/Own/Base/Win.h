#pragma once
#define Win_Class_H
#include<Base/Data/WinData.h>

namespace WinH
{
	class Win
	{
	private:
		WinData Data;
#ifdef _WINDOWS_
#endif // _WINDOWS_

	public:
		Win(WinData& data);
		bool GetIsWorking();
		void CheckEvents();
		~Win();
	};

};



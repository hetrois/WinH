#ifdef _EXE
#include<Base/Win.h>
#include<iostream>

void TestErrors(const char* description)
{
	std::cout << description << std::endl;
}

int main()
{
	WinH::WinData data;
	data.Active = true;
	data.SizeX = 800;
	data.SizeY = 500;
	data.ErrCallback = TestErrors;
	WinH::Win* win = new WinH::Win(data);

	while (win->GetIsWorking())
	{
		win->CheckEvents();
	}

	delete win;
}
#endif // _EXE

#pragma once

namespace WinForm
{

	public ref class MyDoubleComparer : System::Collections::Generic::IComparer<double>
	{
	public: virtual int Compare(double x, double y)
	{
		if (x < y)
		{
			return 1;
		}

		if (x > y)
		{
			return -1;
		}

		return 0;
	}
	};
}
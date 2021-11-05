#pragma once
#include <fileName.hxx>
template<class T>
void tnbLib::file::SaveTo(const T & t, const std::string & name, const unsigned short verbose)
{
	fileName fn(name);
	std::ofstream f(fn);

	TNB_oARCH_FILE_TYPE oa(f);
	oa << t;

	f.close();

	if (verbose)
	{
		Info << endl;
		Info << " the file is saved in: " << fn << ", successfully!" << endl;
		Info << endl;
	}
}

namespace tnbLib
{
	namespace file
	{

		template<class T>
		T LoadFile(const std::string & name, const unsigned short verbose)
		{
			fileName fn(name);
			if (verbose)
			{
				Info << endl;
				Info << " loading the file from, " << fn << endl;
				Info << endl;
			}
			std::ifstream myFile(fn);

			T myObj;
			{
				Global_Timer timer;
				timer.SetInfo(Global_TimerInfo_ms);

				TNB_iARCH_FILE_TYPE ar(myFile);
				ar >> myObj;
			}

			myFile.close();

			if (verbose)
			{
				Info << endl;
				Info << " the file is loaded, from: " << name << ", successfully in " << global_time_duration << " ms." << endl;
				Info << endl;
			}

			return std::move(myObj);
		}
	}
}
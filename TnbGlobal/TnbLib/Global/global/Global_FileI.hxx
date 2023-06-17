#pragma once
#include <fileName.hxx>
#include <Global_Null.hxx>

#include <fstream>
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

template<class T>
void tnbLib::file::SaveListTo
(
	const std::vector<T>& items,
	const std::string & name,
	const unsigned short verbose
)
{
	size_t i = 0;
	for (const auto& x : items)
	{
		std::string address = ".\\" + std::to_string(i) + "\\" + name;
		boost::filesystem::path dir(std::to_string(i));
		boost::filesystem::create_directory(dir);

		std::ofstream file(address);

		TNB_oARCH_FILE_TYPE oa(file);

		oa << x;

		if (verbose)
		{
			Info << " the file, " << i << ", is saved in: " << address << ", successfully!" << endl;
		}
		i++;
	}

	if (verbose)
	{
		Info << endl;
		Info << " all files have been saved, successfully!" << endl;
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

		template<class T>
		T LoadSingleFile
		(
			const std::string& name, 
			const std::string& extension,
			const unsigned short verbose
		)
		{
			std::string file_name;
			auto obj = file::LoadSingleFile<T>(name, extension, verbose, file_name);
			return std::move(obj);
		}

		template<class T>
		T LoadSingleFile
		(
			const std::string& name,
			const std::string& extension,
			const unsigned short verbose,
			std::string& file_name
		)
		{
			CheckDirectory(name);

			const auto currentPath = boost::filesystem::current_path();

			// Change the current path [3/18/2023 Payvand]
			boost::filesystem::current_path(currentPath.string() + R"(\)" + name);
			if (file::IsFile(boost::filesystem::current_path(), ".PATH"))
			{
				auto name = file::GetSingleFile(boost::filesystem::current_path(), ".PATH").string();
				fileName fn(name + ".PATH");

				std::ifstream myFile;
				myFile.open(fn);
				if (myFile.is_open())
				{
					std::string address;
					std::getline(myFile, address);

					// Change the current path [3/18/2023 Payvand]
					boost::filesystem::current_path(address);

					auto name = GetSingleFile(boost::filesystem::current_path(), extension).string();
					file_name = name;
					auto loaded = file::LoadFile<T>(name + extension, verbose);

					//- change back the current path
					boost::filesystem::current_path(currentPath);
					return std::move(loaded);
				}
				else
				{
					//- change back the current path
					boost::filesystem::current_path(currentPath);

					FatalErrorIn(FunctionSIG)
						<< " the file is null." << endl
						<< abort(FatalError);
					//return null_object<T>::type;
					return T();
				}
			}
			else
			{
				auto name = GetSingleFile(boost::filesystem::current_path(), extension).string();
				file_name = name;
				auto loaded = file::LoadFile<T>(name + extension, verbose);

				//- change back the current path
				boost::filesystem::current_path(currentPath);
				return std::move(loaded);
			}
		}
	}
}
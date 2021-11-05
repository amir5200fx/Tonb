#pragma once
#ifndef _Global_File_Header
#define _Global_File_Header

#include <Global_Module.hxx>
#include <Global_Timer.hxx>
#include <Global_Serialization.hxx>
#include <word.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/filesystem.hpp>

#include <vector>
#include <memory>

namespace tnbLib
{

	namespace file
	{

		extern TnbGlobal_EXPORT const tnbLib::word homeDir;

		TnbGlobal_EXPORT std::string GetHomeDir();
		TnbGlobal_EXPORT std::string GetSystemFile(const std::string& theAppName);

		TnbGlobal_EXPORT std::vector<boost::filesystem::path> GetAllFileNames(const boost::filesystem::path&);
		TnbGlobal_EXPORT std::vector<boost::filesystem::path> GetAllFileNames(const boost::filesystem::path&, const std::string& extension);
		TnbGlobal_EXPORT boost::filesystem::path GetSingleFile(const boost::filesystem::path&, const std::string& extension);

		TnbGlobal_EXPORT void CheckExtension(const std::string&);

		template<class T>
		void SaveTo(const T&, const std::string& name, const unsigned short verbose);

		template<class T>
		T LoadFile(const std::string& name, const unsigned short verbose);
	}
}

#include <Global_FileI.hxx>

#endif // !_Global_File_Header

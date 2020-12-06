#pragma once
#ifndef _dynamicCode_Header
#define _dynamicCode_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
	 \\/     M anipulation  |
-------------------------------------------------------------------------------
License
	This file is part of OpenFOAM.

	OpenFOAM is free software: you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
	FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
	for more details.

	You should have received a copy of the GNU General Public License
	along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
	tnbLib::dynamicCode

Description
	Tools for handling dynamic code compilation

SourceFiles
	dynamicCode.C

\*---------------------------------------------------------------------------*/

#include <Tuple2.hxx>
#include <HashTable.hxx>
#include <DynamicList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class dynamicCodeContext;
	class ISstream;
	class OSstream;
	class SHA1Digest;

	/*---------------------------------------------------------------------------*\
							Class dynamicCode Declaration
	\*---------------------------------------------------------------------------*/

	class dynamicCode
	{

	public:

		typedef Tuple2<fileName, string> fileAndContent;


	private:

		// Private Data

			//- Root for dynamic code compilation
		fileName codeRoot_;

		//- Subdirectory name for loading libraries
		const fileName libSubDir_;

		//- Name for code
		word codeName_;

		//- Name for code subdirectory
		word codeDirName_;

		//- Files to copy and filter
		DynamicList<fileName> compileFiles_;

		//- Files to copy and filter
		DynamicList<fileName> copyFiles_;

		//- Direct contents for files
		DynamicList<fileAndContent> createFiles_;

		//- Variables to use during filtering
		HashTable<string> filterVars_;

		//- Contents for Make/options
		std::string makeOptions_;


	protected:

		// Static Data Members

			//- Root of the LIB target for Make/files
		static FoamBase_EXPORT const char* const libTargetRoot;

		//- Top-level directory name for copy/compiling
		static FoamBase_EXPORT const char* const topDirName;


		// Protected Member Functions

			//- Copy lines while expanding variables
		static FoamBase_EXPORT void copyAndFilter
		(
			ISstream&,
			OSstream&,
			const HashTable<string>& mapping
		);

		//- Resolve code-templates via the codeTemplateEnvName
		//  alternatively in the codeTemplateDirName via tnbLib::findEtcFile
		static FoamBase_EXPORT bool resolveTemplates
		(
			const UList<fileName>& templateNames,
			DynamicList<fileName>& resolvedFiles,
			DynamicList<fileName>& badFiles
		);

		//- Write SHA1 value as C-comment
		FoamBase_EXPORT bool writeCommentSHA1(Ostream&) const;

		//- Copy/create Make/files prior to compilation
		FoamBase_EXPORT bool createMakeFiles() const;

		//- Copy/create Make/options prior to compilation
		FoamBase_EXPORT bool createMakeOptions() const;


		//- Write digest to Make/SHA1Digest
		FoamBase_EXPORT bool writeDigest(const SHA1Digest&) const;

		//- Write digest to Make/SHA1Digest
		FoamBase_EXPORT bool writeDigest(const std::string&) const;


	public:

		// Static Data Members

			//- Name of the code template environment variable
			//  Used to located the codeTemplateName
		static FoamBase_EXPORT const word codeTemplateEnvName;

		//- Name of the code template sub-directory
		//  Used when locating the codeTemplateName via tnbLib::findEtcFile
		static FoamBase_EXPORT const fileName codeTemplateDirName;

		//- Flag if system operations are allowed
		static FoamBase_EXPORT int allowSystemOperations;


		// Static Member functions

			//- Check security for creating dynamic code
		static FoamBase_EXPORT void checkSecurity(const char* title, const dictionary&);

		//- Return the library basename without leading 'lib' or trailing '.so'
		static FoamBase_EXPORT word libraryBaseName(const fileName& libPath);


		// Constructors

			//- Construct for a specified code name and code directory name
			//  Defaults to using the code name for the code directory name
		FoamBase_EXPORT dynamicCode
		(
			const word& codeName,
			const word& codeDirName = ""
		);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT dynamicCode(const dynamicCode&) = delete;


		// Member Functions

			//- Return the code-name
		const word& codeName() const
		{
			return codeName_;
		}

		//- Return the code-dirname
		const word& codeDirName() const
		{
			return codeDirName_;
		}

		//- Root for dynamic code compilation
		//  Expanded from \$FOAM_CASE/dynamicCode
		const fileName& codeRoot() const
		{
			return codeRoot_;
		}

		//- Subdirectory name for loading libraries
		//  Expanded from platforms/\$WM_OPTIONS/lib
		fileName libSubDir() const
		{
			return libSubDir_;
		}

		//- Path for specified code name
		//  Corresponds to codeRoot()/codeDirName()
		fileName codePath() const
		{
			return codeRoot_ / codeDirName_;
		}

		//- Library path for specified code name
		//  Corresponds to codeRoot()/libSubDir()/lib\<codeName\>.so
		fileName libPath() const
		{
			return codeRoot_ / libSubDir_ / "lib" + codeName_ + ".so";
		}

		//- Path for specified code name relative to \$FOAM_CASE
		//  Corresponds to topDirName/codeDirName()
		FoamBase_EXPORT fileName codeRelPath() const;


		//- Library path for specified code name relative to \$FOAM_CASE
		//  Corresponds to
		//  dynamicCode/codeDirName()/libSubDir()/lib\<codeName\>.so
		FoamBase_EXPORT fileName libRelPath() const;


		//- Path for SHA1Digest
		//  Corresponds to codePath()/Make/SHA1Digest
		fileName digestFile() const
		{
			return codeRoot_ / codeDirName_ / "Make/SHA1Digest";
		}


		//- Clear files and variables
		FoamBase_EXPORT void clear();

		//- Clear files and reset variables to specified context
		FoamBase_EXPORT void reset(const dynamicCodeContext&);


		//- Add a file template name, which will be found and filtered
		FoamBase_EXPORT void addCompileFile(const fileName& name);

		//- Add a file template name, which will be found and filtered
		FoamBase_EXPORT void addCopyFile(const fileName& name);

		//- Add a file to create with its contents. Will not be filtered
		FoamBase_EXPORT void addCreateFile(const fileName& name, const string& contents);

		//- Define a filter variable
		FoamBase_EXPORT void setFilterVariable(const word& key, const std::string& value);

		//- Define contents for Make/options
		FoamBase_EXPORT void setMakeOptions(const std::string& content);


		//- Verify if the copied code is up-to-date, based on Make/SHA1Digest
		FoamBase_EXPORT bool upToDate(const dynamicCodeContext& context) const;

		//- Verify if the copied code is up-to-date, based on Make/SHA1Digest
		FoamBase_EXPORT bool upToDate(const SHA1Digest& sha1) const;

		//- Copy/create files prior to compilation
		FoamBase_EXPORT bool copyOrCreateFiles(const bool verbose = false) const;

		//- Compile a libso
		FoamBase_EXPORT bool wmakeLibso() const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const dynamicCode&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_dynamicCode_Header

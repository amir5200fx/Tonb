#pragma once
#ifndef _CadIO_IGES_Header
#define _CadIO_IGES_Header

#include <Global_Verbose.hxx>
#include <CadIO_Info.hxx>
#include <CadIO_Shape.hxx>
#include <Cad_Module.hxx>

namespace tnbLib
{

	class CadIO_IGES
		: public CadIO_Info
		, public CadIO_Shape
		, public Global_Verbose
	{

		/*Private Data*/

	public:

		CadIO_IGES()
		{}

		TnbCad_EXPORT void ReadFile
		(
			const fileName& theName
		);
	};
}

#endif // !_CadIO_IGES_Header

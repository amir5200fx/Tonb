#pragma once
#ifndef _Global_Tools_Header
#define _Global_Tools_Header

#include <Global_Module.hxx>

#include <Standard_TypeDef.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations [1/11/2022 Amir]
	class Global_Table;

	class Global_Tools
	{

	public:

		template<class Type>
		static size_t
			FindSpan
			(
				const Standard_Real x,
				const std::vector<Type>& theSorted,
				Standard_Real(*xValue)(const Type&)
			);

		static TnbGlobal_EXPORT size_t
			FindSpan
			(
				const Standard_Real x,
				const std::vector<Standard_Real>& theSorted
			);

		static inline Standard_Real 
			LinearInterpolate
			(
				const Standard_Real theX0,
				const Standard_Real theX1,
				const Standard_Real theY0,
				const Standard_Real theY1,
				const Standard_Real x
			);

		static inline Standard_Real 
			LinearInterpolate
			(
				const std::pair<Standard_Real, Standard_Real>& theXY0,
				const std::pair<Standard_Real, Standard_Real>& theXY1,
				const Standard_Real x
			);

		static TnbGlobal_EXPORT Standard_Real 
			Interpolate
			(
				const Standard_Real theRow, 
				const Standard_Real theCol,
				const Global_Table&
			);

		static TnbGlobal_EXPORT void 
			Check
			(
				const Standard_Real theRow,
				const Standard_Real theCol,
				const Global_Table&
			);

		static TnbGlobal_EXPORT void
			CheckSorted
			(
				const std::vector<Standard_Real>& theSorted,
				const char* theName
			);
	};
}

#include <Global_ToolsI.hxx>

#endif // !_Global_Tools_Header

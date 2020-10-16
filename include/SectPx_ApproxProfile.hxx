#pragma once
#ifndef _SectPx_ApproxProfile_Header
#define _SectPx_ApproxProfile_Header

#include <Pnt2d.hxx>
#include <SectPx_TopoProfile.hxx>

#include <vector>

namespace tnbLib
{

	class SectPx_ApproxProfile
		: public SectPx_TopoProfile
	{

		/*Private Data*/



	public:

		static const char* typeName_;

		template<class... _Types>
		SectPx_ApproxProfile(_Types&&... _Args)
			: SectPx_TopoProfile(_Args...)
		{}

		SectPx_ApproxProfile(const Standard_Integer theIndex);

		SectPx_ApproxProfile(const Standard_Integer theIndex, const word& theName);


		word RegObjTypeName() const override;


		void MakeProfile(const std::vector<Pnt2d>& theCoords, const Standard_Integer deg);

		/*static std::shared_ptr<SectPx_ApproxProfile>
			MakeProfile
			(
				const std::shared_ptr<SectPx_Node>& theNode0,
				const std::shared_ptr<SectPx_Node>& theNode1,
				const std::shared_ptr<SectPx_Registry>& theReg
			);*/
	};
}

#endif // !_SectPx_ApproxProfile_Header

#pragma once
#ifndef _SectPx_OneParCPtsMap_Single_Header
#define _SectPx_OneParCPtsMap_Single_Header

#include <SectPx_OneParCPtsMap.hxx>

namespace tnbLib
{

	namespace sectPxLib
	{

		class OneParCPtsMap_Single
			: public SectPx_OneParCPtsMap
		{

			/*Private Data*/

		public:

			static const char* typeName_;

			
			//- default constructor

			OneParCPtsMap_Single()
			{}


			//- constructors

			OneParCPtsMap_Single
			(
				const Standard_Integer theIndex
			);

			OneParCPtsMap_Single
			(
				const Standard_Integer theIndex,
				const word& theName
			);


			//- public functions and operators

			word RegObjTypeName() const override;

			Standard_Integer NbPts() const override;

			std::vector<Pnt2d> Pts() const override;

			Pnt2d CalcCoord() const;

		};
	}
}

#endif // !_SectPx_OneParCPtsMap_Single_Header

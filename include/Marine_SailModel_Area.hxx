#pragma once
#ifndef _Marine_SailModel_Area_Header
#define _Marine_SailModel_Area_Header

#include <Marine_SailModel.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class SailModel_Area
			: public Marine_SailModel
		{

			/*Private Data*/

			Standard_Real theArea_;


		public:

			SailModel_Area(const Standard_Real theArea);

			SailModel_Area(const Standard_Integer theIndex, const Standard_Real theArea);

			SailModel_Area(const Standard_Integer theIndex, const word& theName, const Standard_Real theArea);


			auto Area() const
			{
				return theArea_;
			}
		};
	}
}

#endif // !_Marine_SailModel_Area_Header

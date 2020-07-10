#pragma once
#ifndef _Marine_SailModel_Shape_Header
#define _Marine_SailModel_Shape_Header

#include <Marine_GeoSailModel.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		// Forward Declarations
		class Shape_Sail;

		class SailModel_Shape
			: public Marine_GeoSailModel
		{

			/*Private Data*/

			std::shared_ptr<Shape_Sail> theShape_;

		public:

			SailModel_Shape(const std::shared_ptr<Shape_Sail>& theSail);

			SailModel_Shape(std::shared_ptr<Shape_Sail>&& theSail);

			SailModel_Shape(const Standard_Integer theIndex, const std::shared_ptr<Shape_Sail>& theSail);

			SailModel_Shape(const Standard_Integer theIndex, std::shared_ptr<Shape_Sail>&& theSail);

			SailModel_Shape(const Standard_Integer theIndex, const word& theName, const std::shared_ptr<Shape_Sail>& theSail);

			SailModel_Shape(const Standard_Integer theIndex, const word& theName, std::shared_ptr<Shape_Sail>&& theSail);


			const auto& Shape() const
			{
				return theShape_;
			}
		};
	}
}

#endif // !_Marine_SailModel_Shape_Header

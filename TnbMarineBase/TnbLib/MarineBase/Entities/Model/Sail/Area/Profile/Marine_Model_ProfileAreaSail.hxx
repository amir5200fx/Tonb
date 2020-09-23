#pragma once
#ifndef _Marine_Model_ProfileAreaSail_Header
#define _Marine_Model_ProfileAreaSail_Header

#include <Standard_Handle.hxx>
#include <Marine_AreaSailModel.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Geo_ProfileFun;

	namespace marineLib
	{

		class Model_ProfileAreaSail
			: public Marine_AreaSailModel
		{

			/*Private Data*/

			std::shared_ptr<Geo_ProfileFun> theArea_;
			std::shared_ptr<Geo_ProfileFun> theZbar_;

		public:

			Model_ProfileAreaSail
			(
				const std::shared_ptr<Geo_ProfileFun>& theArea, 
				const std::shared_ptr<Geo_ProfileFun>& theZbar
			);

			Model_ProfileAreaSail
			(
				std::shared_ptr<Geo_ProfileFun>&& theArea,
				std::shared_ptr<Geo_ProfileFun>&& theZbar
			);

			Model_ProfileAreaSail
			(
				const Standard_Integer theIndex,
				const word& theName, 
				const std::shared_ptr<Geo_ProfileFun>& theArea,
				const std::shared_ptr<Geo_ProfileFun>& theZbar
			);

			Model_ProfileAreaSail
			(
				const Standard_Integer theIndex, 
				const word& theName, 
				std::shared_ptr<Geo_ProfileFun>&& theArea,
				std::shared_ptr<Geo_ProfileFun>&& theZbar
			);

			Marine_SailModelType SailType() const override
			{
				return Marine_SailModelType::profile_area;
			}

			const auto& Area() const
			{
				return theArea_;
			}

			const auto& zBar() const
			{
				return theZbar_;
			}
		};
	}
}

#endif // !_Marine_Model_ProfileAreaSail_Header

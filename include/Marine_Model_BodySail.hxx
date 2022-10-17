#pragma once
#ifndef _Marine_Model_BodySail_Header
#define _Marine_Model_BodySail_Header

#include <Marine_Model_GeoSail.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		// Forward Declarations
		class Body_Sail;

		class Model_BodySail
			: public Model_GeoSail
		{

			/*Private Data*/

			std::shared_ptr<Body_Sail> theBody_;


			TNB_SERIALIZATION(TnbMarine_EXPORT);

		protected:

			Model_BodySail()
			{}

		public:

			TnbMarine_EXPORT Model_BodySail
			(
				const std::shared_ptr<Body_Sail>& theSail
			);

			TnbMarine_EXPORT Model_BodySail
			(
				std::shared_ptr<Body_Sail>&& theSail
			);

			TnbMarine_EXPORT Model_BodySail
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Body_Sail>& theSail
			);

			TnbMarine_EXPORT Model_BodySail
			(
				const Standard_Integer theIndex, 
				std::shared_ptr<Body_Sail>&& theSail
			);

			TnbMarine_EXPORT Model_BodySail
			(
				const Standard_Integer theIndex, 
				const word& theName, 
				const std::shared_ptr<Body_Sail>& theSail
			);

			TnbMarine_EXPORT Model_BodySail
			(
				const Standard_Integer theIndex, 
				const word& theName,
				std::shared_ptr<Body_Sail>&& theSail
			);

			Marine_SailModelType SailType() const override
			{
				return Marine_SailModelType::shape;
			}

			const auto& Body() const
			{
				return theBody_;
			}
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::Model_BodySail);

#endif // !Marine_Model_BodySail_Header

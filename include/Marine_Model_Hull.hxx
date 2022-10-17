#pragma once
#ifndef _Marine_Model_Hull_Header
#define _Marine_Model_Hull_Header

#include <Marine_Model.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		// Forward Declarations
		class Body_Displacer;

		class Model_Hull
			: public Marine_Model
		{

			/*Private Data*/

			std::shared_ptr<Body_Displacer> theDisplacer_;


			TNB_SERIALIZATION(TnbMarine_EXPORT);

		protected:

			TnbMarine_EXPORT Model_Hull()
			{}

		public:

			TnbMarine_EXPORT Model_Hull
			(
				const std::shared_ptr<Body_Displacer>& theBody
			);

			TnbMarine_EXPORT Model_Hull
			(
				std::shared_ptr<Body_Displacer>&& theBody
			);

			TnbMarine_EXPORT Model_Hull
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Body_Displacer>& theBody
			);

			TnbMarine_EXPORT Model_Hull
			(
				const Standard_Integer theIndex,
				std::shared_ptr<Body_Displacer>&& theBody
			);

			TnbMarine_EXPORT Model_Hull
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<Body_Displacer>& theBody
			);

			TnbMarine_EXPORT Model_Hull
			(
				const Standard_Integer theIndex,
				const word& theName,
				std::shared_ptr<Body_Displacer>&& theBody
			);


			Marine_ModelType Type() const override
			{
				return Marine_ModelType::hull;
			}

			Standard_Boolean IsHull() const override
			{
				return Standard_True;
			}

			const auto& Body() const
			{
				return theDisplacer_;
			}
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::Model_Hull);

#endif // !_Marine_Model_Hull_Header

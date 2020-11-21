#pragma once
#ifndef _Marine_Model_Tank_Header
#define _Marine_Model_Tank_Header

#include <Marine_Model.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		// Forward Declarations
		class Body_Tank;

		class Model_Tank
			: public Marine_Model
		{

			/*Private Data*/

			std::shared_ptr<Body_Tank> theTank_;


			DECLARE_SAVE_LOAD_HEADER(TnbMarine_EXPORT);

		protected:

			//- default constructor

			Model_Tank()
			{}

		public:

			//- constructors

			TnbMarine_EXPORT Model_Tank
			(
				const std::shared_ptr<Body_Tank>& theBody
			);

			TnbMarine_EXPORT Model_Tank
			(
				std::shared_ptr<Body_Tank>&& theBody
			);

			TnbMarine_EXPORT Model_Tank
			(
				const Standard_Integer theIndex, 
				const std::shared_ptr<Body_Tank>& theBody
			);

			TnbMarine_EXPORT Model_Tank
			(
				const Standard_Integer theIndex,
				std::shared_ptr<Body_Tank>&& theBody
			);

			TnbMarine_EXPORT Model_Tank
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<Body_Tank>& theBody
			);

			TnbMarine_EXPORT Model_Tank
			(
				const Standard_Integer theIndex,
				const word& theName, 
				std::shared_ptr<Body_Tank>&& theBody
			);


			const auto& Body() const
			{
				return theTank_;
			}

			Marine_ModelType Type() const override
			{
				return Marine_ModelType::tank;
			}

			Standard_Boolean IsTank() const override
			{
				return Standard_True;
			}

		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::Model_Tank);

#endif // !_Marine_Model_Tank_Header

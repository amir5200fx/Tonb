#pragma once
#ifndef _Marine_Body_WettedS_Header
#define _Marine_Body_WettedS_Header

#include <Marine_Body_Wetted.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Body_WettedS
			: public Body_Wetted
		{

			friend class Marine_DisctLib;

			/*Private Data*/

			std::shared_ptr<Marine_CmpSection> theWater_;

			//- private functions and operators

			void SetWater(const std::shared_ptr<Marine_CmpSection>& theWater)
			{
				theWater_ = theWater;
			}

			void SetWater(const std::shared_ptr<Marine_CmpSection>&& theWater)
			{
				theWater_ = std::move(theWater);
			}

		public:

			template<class... _Types>
			Body_WettedS(_Types&&... _Args)
				: Body_Wetted(_Args...)
			{}

			const auto& WL() const
			{
				return theWater_;
			}

			Standard_Boolean HasWaterSection() const override
			{
				return Standard_True;
			}

		};
	}
}

#endif // !_Marine_Body_WettedS_Header

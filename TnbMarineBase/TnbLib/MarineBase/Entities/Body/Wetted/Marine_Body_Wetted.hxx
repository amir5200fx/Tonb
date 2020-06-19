#pragma once
#ifndef _Marine_Body_Wetted_Header
#define _Marine_Body_Wetted_Header

#include <Marine_HullBody.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Body_Wetted
			: public Marine_HullBody
		{

			friend class Marine_DisctLib;

			/*Private Data*/

			std::shared_ptr<Marine_CmpSection> theWater_;
			std::shared_ptr<Marine_CmpSection> theMid_;


			//- private functions and operators

			void SetWater(const std::shared_ptr<Marine_CmpSection>& theWater)
			{
				theWater_ = theWater;
			}

			void SetWater(const std::shared_ptr<Marine_CmpSection>&& theWater)
			{
				theWater_ = std::move(theWater);
			}

			void SetMid(const std::shared_ptr<Marine_CmpSection>& theMid)
			{
				theMid_ = theMid;
			}

			void SetMid(const std::shared_ptr<Marine_CmpSection>&& theMid)
			{
				theMid_ = std::move(theMid);
			}

		public:

			template<class... _Types>
			Body_Wetted(_Types&&... _Args)
				: Marine_HullBody(_Args...)
			{}

			Standard_Boolean IsWetted() const override
			{
				return Standard_True;
			}

			Marine_BodyType Type() const override
			{
				return Marine_BodyType::wetted;
			}

			const auto& WL() const
			{
				return theWater_;
			}

			const auto& Mid() const
			{
				return theMid_;
			}

			std::shared_ptr<Marine_Body> Copy() const override;
		};
	}
}

#endif // !_Marine_Body_Wetted_Header

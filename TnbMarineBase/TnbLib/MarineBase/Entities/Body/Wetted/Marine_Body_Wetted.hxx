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

			
			std::shared_ptr<Marine_CmpSection> theMid_;


			//- private functions and operators

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

			virtual Standard_Boolean HasWaterSection() const
			{
				return Standard_False;
			}

			Standard_Boolean IsWetted() const override
			{
				return Standard_True;
			}

			Marine_BodyType Type() const override
			{
				return Marine_BodyType::wetted;
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

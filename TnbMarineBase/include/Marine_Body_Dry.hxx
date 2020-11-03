#pragma once
#ifndef _Marine_Body_Dry_Header
#define _Marine_Body_Dry_Header

#include <Marine_HullBody.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Body_Dry
			: public Marine_HullBody
		{

			/*Private Data*/


			/*private functions and operators*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<Marine_HullBody>(*this);
			}

		protected:

			template<class... _Types>
			Body_Dry(_Types&&... _Args)
				: Marine_HullBody(_Args...)
			{}

		public:

			Standard_Boolean IsDry() const override
			{
				return Standard_True;
			}

			Marine_BodyType Type() const override
			{
				return Marine_BodyType::dry;
			}

			virtual Standard_Boolean ShapeType() const
			{
				return Standard_False;
			}

			std::shared_ptr<Marine_Body> Copy() const override;
		};
	}
}

#include <Marine_BodyConstructor.hxx>

#endif // !_Marine_Body_Dry_Header

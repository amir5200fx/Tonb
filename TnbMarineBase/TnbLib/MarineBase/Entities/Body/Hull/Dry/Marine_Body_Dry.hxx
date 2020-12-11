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

			TnbMarine_EXPORT std::shared_ptr<Marine_Body> Copy() const override;
		};
	}
}

#include <Marine_BodyConstructor.hxx>

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::marineLib::Body_Dry);

BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::BodyConstructor_Shape<tnbLib::marineLib::Body_Dry>);
BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::BodyConstructor_noShape<tnbLib::marineLib::Body_Dry>);

namespace tnbLib
{
	namespace marineLib
	{

		template<>
		template<>
		TnbMarine_EXPORT void BodyConstructor_Shape<Body_Dry>::serialize<TNB_iARCH_TYPE>
			(
				TNB_iARCH_TYPE& ar,
				const unsigned int file_vertion
				);

		template<>
		template<>
		TnbMarine_EXPORT void BodyConstructor_Shape<Body_Dry>::serialize<TNB_oARCH_TYPE>
			(
				TNB_oARCH_TYPE& ar,
				const unsigned int file_vertion
				);
	}
}

#endif // !_Marine_Body_Dry_Header

#pragma once
#ifndef _SectPx_ExtrProfile_Header
#define _SectPx_ExtrProfile_Header

#include <Pnt2d.hxx>
#include <SectPx_Parent.hxx>

namespace tnbLib
{

	class SectPx_ExtrProfile
		: public SectPx_Parent
	{

		/*Private Data*/


		/*private functions and operators*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<SectPx_Parent>(*this);
		}


	protected:


		template<class... _Types>
		SectPx_ExtrProfile(_Types&&... _Args)
			: SectPx_Parent(_Args...)
		{}

	public:

		TnbSectPx_EXPORT Standard_Boolean IsExtrProfile() const override;

		virtual Standard_Real Lower() const = 0;

		virtual Standard_Real Upper() const = 0;

		virtual Standard_Integer NbPoints() const = 0;

		virtual Pnt2d Point(const Standard_Integer theIndex) const = 0;
	};
}


BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_ExtrProfile);

#endif // !_SectPx_ExtrProfile_Header

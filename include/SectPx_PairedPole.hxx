#pragma once
#ifndef _SectPx_PairedPole_Header
#define _SectPx_PairedPole_Header

#include <SectPx_BndPole.hxx>

namespace tnbLib
{

	class SectPx_PairedPole
		: public SectPx_BndPole
	{

		/*Private Data*/


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<SectPx_BndPole>(*this);
		}

	protected:

		template<class... _Types>
		SectPx_PairedPole(_Types&&... Args)
			: SectPx_BndPole(Args...)
		{}

	public:

		Standard_Boolean IsPaired() const override
		{
			return Standard_True;
		}

		virtual Standard_Boolean IsMaster() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsSlave() const
		{
			return Standard_False;
		}
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_PairedPole);

#endif // !_SectPx_PairedPole_Header
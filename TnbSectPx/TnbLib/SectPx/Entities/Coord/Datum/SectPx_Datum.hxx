#pragma once
#ifndef _SectPx_Datum_Header
#define _SectPx_Datum_Header

#include <SectPx_TCoord.hxx>
#include <SectPx_Parent.hxx>

namespace tnbLib
{

	class SectPx_Datum
		: public SectPx_TCoord
		, public SectPx_Parent
	{

		/*Private Data*/

		friend boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<SectPx_TCoord>(*this);
			ar & boost::serialization::base_object<SectPx_Parent>(*this);
		}

	protected:

		template<class... _Types>
		SectPx_Datum(_Types&&... _Args)
			: SectPx_Parent(_Args...)
		{}

	public:

		Standard_Boolean IsDatum() const override;

		sectPxLib::regObjType RegObjType() const override;
	};
}

#endif // !_SectPx_Datum_Header

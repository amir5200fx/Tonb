#pragma once
#ifndef _SectPx_GeoMap_Header
#define _SectPx_GeoMap_Header

#include <SectPx_Parent.hxx>
#include <Pnt2d.hxx>

#include <memory>

namespace tnbLib
{

	class SectPx_GeoMap
		: public SectPx_Parent
	{

		/*Private Data*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<SectPx_Parent>(*this);
		}

	protected:

		template<class... _Types>
		SectPx_GeoMap(_Types&&... _Args)
			: SectPx_Parent(_Args...)
		{}

	public:

		Standard_Boolean IsGeoMap() const override;

		sectPxLib::regObjType RegObjType() const override;

		virtual Standard_Boolean IsComplete() const = 0;

		virtual Pnt2d CalcCoord() const = 0;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_GeoMap);

#endif // !_SectPx_GeoMap_Header

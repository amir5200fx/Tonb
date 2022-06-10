#pragma once
#ifndef _SectPx_TCoord_Header
#define _SectPx_TCoord_Header

#include <SectPx_Coord.hxx>
#include <SectPx_ParentAdaptor.hxx>

namespace tnbLib
{

	class SectPx_TCoord
		: public SectPx_Coord
		/*, public SectPx_ParentAdaptor*/
	{

		/*Private Data*/

		friend boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<SectPx_Coord>(*this);
		}

	protected:

		template<class... _Types>
		SectPx_TCoord(_Types&&... _Args)
			: SectPx_Coord(_Args...)
		{}

	public:


	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_TCoord);

#endif // !_SectPx_TCoord_Header

#pragma once
#ifndef _SectPx_Datum_Header
#define _SectPx_Datum_Header

#include <SectPx_TCoord.hxx>
#include <SectPx_Parent.hxx>

namespace tnbLib
{

	class SectPx_Datum
		: public SectPx_Coord
		, public SectPx_Parent
	{

		/*Private Data*/

		friend boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<SectPx_Coord>(*this);
			ar & boost::serialization::base_object<SectPx_Parent>(*this);
		}

	protected:


		// default constructor [4/27/2022 Amir]

		SectPx_Datum()
		{}


		// constructors [4/27/2022 Amir]

		explicit SectPx_Datum(const Standard_Integer theIndex)
			: SectPx_Parent(theIndex)
		{}


		SectPx_Datum
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: SectPx_Parent(theIndex, theName)
		{}


	public:

		// public functions and operators [4/27/2022 Amir]

		TnbSectPx_EXPORT virtual Standard_Boolean IsComponent() const;

		TnbSectPx_EXPORT virtual Standard_Boolean IsGeoField() const;

		TnbSectPx_EXPORT Standard_Boolean IsDatum() const override;

		TnbSectPx_EXPORT Standard_Boolean IsFrameRegObj() const override;

		TnbSectPx_EXPORT sectPxLib::regObjType RegObjType() const override;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_Datum);

#endif // !_SectPx_Datum_Header

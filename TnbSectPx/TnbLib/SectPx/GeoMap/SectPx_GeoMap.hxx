#pragma once
#ifndef _SectPx_GeoMap_Header
#define _SectPx_GeoMap_Header

#include <SectPx_Parent.hxx>
#include <Pnt2d.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Coord;

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


		// default constructor [4/27/2022 Amir]

		SectPx_GeoMap()
		{}


		// constructors [4/27/2022 Amir]

		explicit SectPx_GeoMap(const Standard_Integer theIndex)
			: SectPx_Parent(theIndex)
		{}

		SectPx_GeoMap
		(
			const Standard_Integer theIndex, 
			const word& theName
		)
			: SectPx_Parent(theIndex, theName)
		{}

	public:

		// public functions and operators [4/27/2022 Amir]

		TnbSectPx_EXPORT virtual ~SectPx_GeoMap();

		TnbSectPx_EXPORT Standard_Boolean IsGeoMap() const override;

		TnbSectPx_EXPORT Standard_Boolean IsFrameRegObj() const override;

		TnbSectPx_EXPORT sectPxLib::regObjType RegObjType() const override;

		virtual Standard_Boolean IsComplete() const = 0;

		virtual Pnt2d CalcCoord() const = 0;

		virtual Standard_Integer NbCoords() const = 0;

		TnbSectPx_EXPORT virtual std::vector<std::shared_ptr<SectPx_Coord>> RetrieveCoords() const;

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_GeoMap);

#endif // !_SectPx_GeoMap_Header

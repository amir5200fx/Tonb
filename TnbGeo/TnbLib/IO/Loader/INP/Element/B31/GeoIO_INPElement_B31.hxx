#pragma once
#ifndef _GeoIO_INPElement_B31_Header
#define _GeoIO_INPElement_B31_Header

#include <GeoIO_INPElement.hxx>

#include <array>

namespace tnbLib
{

	// Forward Declarations [9/5/2023 aamir]
	class GeoIO_INPElement_B31;

	TnbGeo_EXPORT Istream& operator>>(Istream&, GeoIO_INPElement_B31&);
	TnbGeo_EXPORT std::istream& operator>>(std::istream&, GeoIO_INPElement_B31&);

	class GeoIO_INPElement_B31
		: public GeoIO_INPElement
	{

	public:

		enum 
		{
			nbPoints = 2
		};

		typedef std::array<Standard_Integer, nbPoints>
			Array;

	private:

		/*Private Data*/

		Array theIndices_;


		// Private functions and operators [9/5/2023 aamir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<GeoIO_INPElement>(*this);
			ar& theIndices_;
		}

	public:

		static TnbGeo_EXPORT const char* typeName_;

		// default constructor [9/5/2023 aamir]

		GeoIO_INPElement_B31()
		{}

		// constructors [9/5/2023 aamir]

		GeoIO_INPElement_B31
		(
			const Standard_Integer theIndex, 
			const Array& theIndices
		)
			: GeoIO_INPElement(theIndex)
			, theIndices_(theIndices)
		{}

		GeoIO_INPElement_B31
		(
			const Standard_Integer theIndex,
			Array&& theIndices
		)
			: GeoIO_INPElement(theIndex)
			, theIndices_(std::move(theIndices))
		{}

		TnbGeo_EXPORT GeoIO_INPElement_B31(Istream& is);
		TnbGeo_EXPORT GeoIO_INPElement_B31(std::istream& is);

		// Public functions and operators [9/5/2023 aamir]

		TnbGeo_EXPORT word ElementType() const override;

		TnbGeo_EXPORT Standard_Integer
			NbPoints() const override;
		TnbGeo_EXPORT std::vector<Standard_Integer> 
			RetrieveIndices() const override;

		const auto& Indices() const { return theIndices_; }

	};

}

BOOST_CLASS_EXPORT_KEY(tnbLib::GeoIO_INPElement_B31);

#endif // !_GeoIO_INPElement_B31_Header

#pragma once
#ifndef _Geo2d_2ndNurbsPx_3Pts_Header
#define _Geo2d_2ndNurbsPx_3Pts_Header

#include <Geo2d_2ndNurbsPx.hxx>

namespace tnbLib
{

	class Geo2d_2ndNurbsPx_3Pts
		: public Geo2d_2ndNurbsPx
	{

	public:

		enum 
		{
			nbNodes = 3
		};

	private:

		/*Private Data*/

		Standard_Real theLength_;
		Standard_Real theMaxValue_;
		Standard_Real theAngle_;
		Standard_Real theWeight_;

		// Private functions and operators [8/15/2023 aamir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Geo2d_2ndNurbsPx>(*this);
			ar& theLength_;
			ar& theMaxValue_;
			ar& theAngle_;
			ar& theWeight_;
		}

	public:

		// default constructor [8/15/2023 aamir]

		Geo2d_2ndNurbsPx_3Pts()
			: theLength_(0)
			, theMaxValue_(0)
			, theAngle_(0)
			, theWeight_(0)
		{}

		// constructors [8/15/2023 aamir]


		// Public functions and operators [8/15/2023 aamir]

		auto Length() const { return theLength_; }
		auto MaxValue() const { return theMaxValue_; }
		auto Angle() const { return theAngle_; }
		auto Weight() const { return theWeight_; }

		TnbGeo_EXPORT void Perform();

		void SetLength(const Standard_Real x) { theLength_ = x; }
		void SetMaxValue(const Standard_Real x) { theMaxValue_ = x; }
		void SetAngle(const Standard_Real x) { theAngle_ = x; }
		void SetWeight(const Standard_Real x) { theWeight_ = x; }

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Geo2d_2ndNurbsPx_3Pts);

#endif // !_Geo2d_2ndNurbsPx_3Pts_Header

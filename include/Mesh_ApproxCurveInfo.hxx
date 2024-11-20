#pragma once
#ifndef _Mesh_ApproxCurveInfo_Header
#define _Mesh_ApproxCurveInfo_Header

#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

namespace tnbLib
{

	class Mesh_ApproxCurveInfo
	{

		/*Private Data*/

		Standard_Real theTargetSize_;
		Standard_Real theMinSize_;

		Standard_Integer theMinNbSubdivisions_;
		Standard_Integer theMaxNbSubdivisions_;

		Standard_Integer theNbSamples_;

		// Private functions and operators [11/4/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & theTargetSize_;
			ar & theMinSize_;

			ar & theMinNbSubdivisions_;
			ar & theMaxNbSubdivisions_;
		}

	public:

		// default constructor [11/4/2022 Amir]

		Mesh_ApproxCurveInfo()
			: theTargetSize_(0)
			, theMinSize_(0)
			, theMinNbSubdivisions_(0)
			, theMaxNbSubdivisions_(0)
			, theNbSamples_(0)
		{}


		// constructors [11/4/2022 Amir]


		// public functions and operators [11/4/2022 Amir]

		auto TargetSize() const
		{
			return theTargetSize_;
		}

		auto MinSize() const
		{
			return theMinSize_;
		}

		auto MinNbSubdivisions() const
		{
			return theMinNbSubdivisions_;
		}

		auto MaxNbSubdivisions() const
		{
			return theMaxNbSubdivisions_;
		}

		auto NbSamples() const
		{
			return theNbSamples_;
		}

		void SetTargetSize(const Standard_Real theValue)
		{
			theTargetSize_ = theValue;
		}

		void SetMinSize(const Standard_Real theValue)
		{
			theMinSize_ = theValue;
		}

		void SetMinNbSubdivisions(const Standard_Integer n)
		{
			theMinNbSubdivisions_ = n;
		}

		void SetMaxNbSubdivisions(const Standard_Integer n)
		{
			theMaxNbSubdivisions_ = n;
		}

		void SetNbSamples(const Standard_Integer n)
		{
			theNbSamples_ = n;
		}
	};
}

#endif // !_Mesh_ApproxCurveInfo_Header

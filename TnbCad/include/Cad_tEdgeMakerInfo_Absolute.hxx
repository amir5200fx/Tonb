#pragma once
#ifndef _Cad_tEdgeMakerInfo_Absolute_Header
#define _Cad_tEdgeMakerInfo_Absolute_Header

#include <Cad_tEdgeMakerInfo.hxx>

namespace tnbLib
{

	class Cad_tEdgeMakerInfo_Absolute
		: public Cad_tEdgeMakerInfo
	{

		/*private Data*/

		Standard_Real theTolerance_;


		// private functions and operators [1/7/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Cad_tEdgeMakerInfo>(*this);
			ar & theTolerance_;
		}

	public:

		static TnbCad_EXPORT const Standard_Real DEFAULT_TOLERANCE;

		// default constructor [1/7/2022 Amir]

		Cad_tEdgeMakerInfo_Absolute()
			: theTolerance_(DEFAULT_TOLERANCE)
		{}


		// constructors [1/7/2022 Amir]

		explicit Cad_tEdgeMakerInfo_Absolute(const Standard_Real theTol)
			: theTolerance_(theTol)
		{}


		// public functions and operators [1/7/2022 Amir]

		Standard_Real Tolerance() const override
		{
			return theTolerance_;
		}

		void SetTolerance(const Standard_Real theTol)
		{
			theTolerance_ = theTol;
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Cad_tEdgeMakerInfo_Absolute);

#endif // !_Cad_tEdgeMakerInfo_Absolute_Header

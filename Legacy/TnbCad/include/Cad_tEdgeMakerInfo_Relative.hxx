#pragma once
#ifndef _Cad_tEdgeMakerInfo_Relative_Header
#define _Cad_tEdgeMakerInfo_Relative_Header

#include <Cad_tEdgeMakerInfo.hxx>
#include <Entity3d_BoxFwd.hxx>

#include <memory>

namespace tnbLib
{

	class Cad_tEdgeMakerInfo_Relative
		: public Cad_tEdgeMakerInfo
	{

		/*Private Data*/

		std::shared_ptr<Entity3d_Box> theDomain_;
		Standard_Real theTolerance_;


		// private functions and operators [1/7/2022 Amir]

		TNB_SERIALIZATION(TnbCad_EXPORT);

	public:

		static TnbCad_EXPORT const Standard_Real DEFAULT_TOLERANCE;

		// default constructor [1/7/2022 Amir]

		Cad_tEdgeMakerInfo_Relative()
			: theTolerance_(DEFAULT_TOLERANCE)
		{}

		// constructors [1/7/2022 Amir]

		Cad_tEdgeMakerInfo_Relative
		(
			const std::shared_ptr<Entity3d_Box>& theDomain,
			const Standard_Real theTol
		)
			: theDomain_(theDomain)
			, theTolerance_(theTol)
		{}


		// public functions and operators [1/7/2022 Amir]

		Standard_Real Tolerance() const override;

		const auto& Domain() const
		{
			return theDomain_;
		}

		void SetDomain(const std::shared_ptr<Entity3d_Box>& theDomain)
		{
			theDomain_ = theDomain;
		}

		void SetDomain(std::shared_ptr<Entity3d_Box>&& theDomain)
		{
			theDomain_ = std::move(theDomain);
		}

		void SetTolerance(const Standard_Real theTol)
		{
			theTolerance_ = theTol;
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Cad_tEdgeMakerInfo_Relative);

#endif // !_Cad_tEdgeMakerInfo_Relative_Header

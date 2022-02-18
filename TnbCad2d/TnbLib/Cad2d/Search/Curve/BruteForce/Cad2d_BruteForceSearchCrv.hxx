#pragma once
#ifndef _Cad2d_BruteForceSearchCrv_Header
#define _Cad2d_BruteForceSearchCrv_Header

#include <Cad2d_SearchCrv.hxx>

namespace tnbLib
{

	class Cad2d_BruteForceSearchCrv
		: public Cad2d_SearchCrv
	{

		/*Private Data*/

		std::vector<std::shared_ptr<Pln_Edge>> theCurves_;

	public:

		// default constructor [1/26/2022 Amir]

		Cad2d_BruteForceSearchCrv()
		{}

		// constructors [1/26/2022 Amir]


		// override functions and operators [1/26/2022 Amir]

		TnbCad2d_EXPORT Standard_Integer NbCurves() const override;

		TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Edge>>
			Find(const std::shared_ptr<Pln_Edge>&) const override;
		TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Edge>> AllCurves() const override;

		// public functions and operators [1/26/2022 Amir]

		const auto& Curves() const
		{
			return theCurves_;
		}

		auto& CurvesRef()
		{
			return theCurves_;
		}

		TnbCad2d_EXPORT void Insert(const std::shared_ptr<Pln_Edge>& theCurve);
		TnbCad2d_EXPORT void Insert(std::shared_ptr<Pln_Edge>&& theCurve);
	};
}

#endif // !_Cad2d_BruteForceSearchCrv_Header

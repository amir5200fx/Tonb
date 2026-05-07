#pragma once
#ifndef _Entity2d_Eigen_Header
#define _Entity2d_Eigen_Header

#include <Global_Done.hxx>
#include <Geo_Module.hxx>
#include <Pnt2d.hxx>
#include <armadillo>


namespace tnbLib
{

	// Forward Declarations
	class Entity2d_Metric1;

	struct Entity2d_EigenInfo
	{
		Standard_Real Zero;

		Entity2d_EigenInfo() : Zero(1.0E-6) {}
	};

	class Entity2d_Eigen
		: public Entity2d_EigenInfo
		, public Global_Done
	{

		/*Private Data*/

		Pnt2d theE1_ = Pnt2d::null;
		Pnt2d theE2_ = Pnt2d::null;

		Standard_Real theH1_ = 0;
		Standard_Real theH2_ = 0;

		Standard_Real theLamda1_ = 0;
		Standard_Real theLamda2_ = 0;

	public:

		// default constructor
		Entity2d_Eigen()
			= default;

		// constructors

		// Public functions and operators
		const auto& E1() const { return theE1_; }
		const auto& E2() const { return theE2_; }

		auto H1() const { return theH1_; }
		auto H2() const { return theH2_; }
		auto& H1() { return theH1_; }
		auto& H2() { return theH2_; }

		auto Lamda1() const { return theLamda1_; }
		auto Lamda2() const { return theLamda2_; }
		auto& Lamda1() { return theLamda1_; }
		auto& Lamda2() { return theLamda2_; }

		TnbGeo_EXPORT void CalcEigen(const Entity2d_Metric1& M);
		TnbGeo_EXPORT void CalcEigen(const arma::mat22& M);
		TnbGeo_EXPORT void CalcGenEigen(const Entity2d_Metric1& A, const Entity2d_Metric1& B);

		TnbGeo_EXPORT void ExportToPlt(std::fstream& File) const;
		TnbGeo_EXPORT void ExportToPlt(const Pnt2d& Centre, OFstream& File) const;

		TnbGeo_EXPORT void Print(Standard_OStream& ostream = cout) const;

		//- Static functions and operators


	};
}

#include <Entity2d_EigenI.hxx>

#endif // !_Entity2d_Eigen_Header

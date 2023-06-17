#pragma once
#ifndef _PtdShapeFit2d_ScatterMap_Header
#define _PtdShapeFit2d_ScatterMap_Header

#include <PtdShapeFit_Module.hxx>
#include <Pnt2d.hxx>
#include <Global_Serialization.hxx>

#include <map>
#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [4/28/2023 Payvand]
	class Cad2d_Plane;
	class Pln_Curve;

	class PtdShapeFit2d_ScatterMap
	{

	public:

		typedef std::vector<Pnt2d> ptList;

	private:

		/*Private Data*/


		// Private functions and operators [2/10/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{}


	protected:

		// default constructor [2/10/2023 Payvand]

		PtdShapeFit2d_ScatterMap()
		{}


		// constructors [2/10/2023 Payvand]


	public:

		static TnbPtdShapeFit_EXPORT const std::string extension;

		// Public functions and operators [2/10/2023 Payvand]

		virtual Standard_Integer NbRegions() const = 0;
		virtual std::shared_ptr<ptList> Region(const Standard_Integer theIndex) const = 0;

		TnbPtdShapeFit_EXPORT virtual std::vector<std::pair<std::shared_ptr<Pln_Curve>, std::shared_ptr<ptList>>>
			RetrieveCurves(const std::shared_ptr<Cad2d_Plane>&) const;

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdShapeFit2d_ScatterMap);

#endif // !_PtdShapeFit2d_ScatterMap_Header

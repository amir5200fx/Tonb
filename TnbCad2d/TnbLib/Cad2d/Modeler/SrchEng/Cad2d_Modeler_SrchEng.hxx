#pragma once
#ifndef _Cad2d_Modeler_SrchEng_Header
#define _Cad2d_Modeler_SrchEng_Header

#include <Geo_AdTree.hxx>
#include <Cad2d_Modeler_Corner.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Vertex;

	class Cad2d_Modeler_SrchEng
	{

		/*Private Data*/

		Geo_AdTree<std::shared_ptr<cad2dLib::Modeler_Corner>>
			theCorners_;

	protected:


		static const std::shared_ptr<cad2dLib::Modeler_Corner> null;

		Cad2d_Modeler_SrchEng()
		{}


		Standard_Real Radius() const;

		const std::shared_ptr<cad2dLib::Modeler_Corner>& SelectCorner(const Pnt2d& theCoord) const;

		const std::shared_ptr<cad2dLib::Modeler_Corner>& FindCorner(const std::shared_ptr<Pln_Vertex>& theVtx) const;

		void ReArrangeSrchEngine();

		void InsertToSrchEngine(const std::shared_ptr<cad2dLib::Modeler_Corner>& theCorner);

		void RemoveFromSrchEngine(const std::shared_ptr<cad2dLib::Modeler_Corner>& theCorner);


		static Standard_Boolean IsNull(const std::shared_ptr<cad2dLib::Modeler_Corner>& theCorner);

		static const std::shared_ptr<cad2dLib::Modeler_Corner>& MinDist(const std::vector<std::shared_ptr<cad2dLib::Modeler_Corner>>& theCorners, const Pnt2d& theCentre);
	};

	
}

#endif // !_Cad2d_Modeler_SrchEng_Header

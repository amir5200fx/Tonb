#pragma once
#ifndef _Geo3d_ApprxSurfPatch_Samples_Header
#define _Geo3d_ApprxSurfPatch_Samples_Header

#include <Mesh_Module.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Entity2d_TriangleFwd.hxx>
#include <Pnt2d.hxx>

#include <Standard_TypeDef.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	class Geo3d_ApprxSurfPatch_Samples
	{

	public:

		enum class Type
		{
			four_points,
			five_points
		};

		/*Private Data*/

	protected:

		// default constructor [9/2/2022 Amir]

		Geo3d_ApprxSurfPatch_Samples()
		{}

		// constructors [9/2/2022 Amir]


	public:

		static TnbMesh_EXPORT const Standard_Real one;

		// public functions and operators [9/2/2022 Amir]

		virtual Standard_Integer NbPoints() const = 0;
		virtual Pnt2d CalcPoint(const Standard_Integer theIndex, const Entity_Triangle<const Pnt2d &>&) const = 0;

		virtual std::vector<Pnt2d> RetrieveSamples(const Entity_Triangle<const Pnt2d &>&) const = 0;
	};
}

#endif // !_Geo3d_ApprxSurfPatch_Samples_Header

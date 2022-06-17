#pragma once
#ifndef _Aft_MetricPrcsrIdentifier_Header
#define _Aft_MetricPrcsrIdentifier_Header

#include <Aft2d_EdgeSurfaceFwd.hxx>
#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>

#include <Standard_Handle.hxx>

class Geom_Surface;

namespace tnbLib
{

	// Forward Declarations [6/13/2022 Amir]
	class Pnt2d;
	class Pnt3d;

	template<class FrontType>
	class Aft_MetricPrcsrIdentifier
	{

		/*Private Data*/


		// private functions and operators [6/13/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			// empty body [6/13/2022 Amir]
		}

	protected:

		// default constructor [6/13/2022 Amir]

		Aft_MetricPrcsrIdentifier()
		{}


	};


	// Forward Declarations [6/13/2022 Amir]

	template<>
	class Aft_MetricPrcsrIdentifier<Aft2d_EdgeSurface>
	{

		/*Private Data */

		Handle(Geom_Surface) theGeometry_;

	protected:

		// default constructor [6/13/2022 Amir]

		Aft_MetricPrcsrIdentifier()
		{}

		// constructors [6/13/2022 Amir]


	public:

		// public functions and operators [6/13/2022 Amir]

		const auto& Geometry() const
		{
			return theGeometry_;
		}

		TnbMesh_EXPORT Pnt3d CalcCoord3D(const Pnt2d&) const;

		void SetGeometry(const Handle(Geom_Surface)& theGeometry)
		{
			theGeometry_ = theGeometry;
		}

	};
}

#endif // !_Aft_MetricPrcsrIdentifier_Header

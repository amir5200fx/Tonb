#pragma once
#ifndef _Geo3d_ApprxSurfPatch_hSizeFunMode_Header
#define _Geo3d_ApprxSurfPatch_hSizeFunMode_Header

#include <Geo3d_ApprxSurfPatch_FunMode.hxx>

namespace tnbLib
{

	class Geo3d_ApprxSurfPatch_hSizeFunMode
		: public Geo3d_ApprxSurfPatch_FunMode
	{

		/*Private Data*/

		Standard_Integer theNbSamples_;

	public:

		static TnbMesh_EXPORT Standard_Integer DEFAULT_NB_SAMPLES;

		// default constructor [9/5/2022 Amir]

		Geo3d_ApprxSurfPatch_hSizeFunMode()
			: theNbSamples_(DEFAULT_NB_SAMPLES)
		{}


		// constructors [9/5/2022 Amir]

		explicit Geo3d_ApprxSurfPatch_hSizeFunMode(const Standard_Integer theNbSamples)
			: theNbSamples_(theNbSamples)
		{}


		// public functions and operators [9/5/2022 Amir]

		auto NbSamples() const
		{
			return theNbSamples_;
		}

		void SetNbSamples(const Standard_Integer n)
		{
			theNbSamples_ = n;
		}

		TnbMesh_EXPORT Standard_Boolean 
			DoSubdivide
			(
				const Entity2d_Box&,
				const Geom_Surface& theSurface,
				const Standard_Real theSize
			) const override;

	};
}

#endif // !_Geo3d_ApprxSurfPatch_hSizeFunMode_Header

#pragma once
#ifndef _Aft2d_AltrOptNodeSurface_SubTri_Header
#define _Aft2d_AltrOptNodeSurface_SubTri_Header

#include <Aft2d_AltrOptNodeSurface.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	// Forward Declarations [5/25/2022 Amir]
	class Aft_SizeCorr_IterativeInfo;

	class Aft2d_AltrOptNodeSurface_SubTri
		: public Aft2d_AltrOptNodeSurface
	{

		/*Private Data*/

		std::shared_ptr<Aft_SizeCorr_IterativeInfo> theInfo_;

		Standard_Integer theMaxLev_;

		// private functions and operators [5/25/2022 Amir]

		TnbMesh_EXPORT Standard_Boolean 
			Iter
			(
				const Standard_Integer theLev, 
				const Pnt2d&, const Pnt2d& theP0, 
				const Pnt2d& theP1,
				const Standard_Real h
			);

	public:

		static TnbMesh_EXPORT const Standard_Integer DEFAULT_MAX_LEV;

		// default constructor [5/25/2022 Amir]

		Aft2d_AltrOptNodeSurface_SubTri()
			: theMaxLev_(DEFAULT_MAX_LEV)
		{}


		// constructors [5/25/2022 Amir]

		explicit Aft2d_AltrOptNodeSurface_SubTri
		(
			const std::shared_ptr<Aft_SizeCorr_IterativeInfo>& theInfo
		)
			: theInfo_(theInfo)
			, theMaxLev_(DEFAULT_MAX_LEV)
		{}

		// public functions and operators [5/25/2022 Amir]

		const auto& IterInfo() const
		{
			return theInfo_;
		}

		auto MaxLevel() const
		{
			return theMaxLev_;
		}

		TnbMesh_EXPORT void Perform() override;

		void SetInfo(const std::shared_ptr<Aft_SizeCorr_IterativeInfo>& theInfo)
		{
			theInfo_ = theInfo;
		}

		void SetMaxLev(const Standard_Integer theMax)
		{
			theMaxLev_ = theMax;
		}

	};
}

#endif // !_Aft2d_AltrOptNodeSurface_SubTri_Header

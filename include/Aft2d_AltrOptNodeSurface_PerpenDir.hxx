#pragma once
#ifndef _Aft2d_AltrOptNodeSurface_PerpenDir_Header
#define _Aft2d_AltrOptNodeSurface_PerpenDir_Header

#include <Aft2d_AltrOptNodeSurface.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	// Forward Declarations [5/8/2022 Amir]
	class Aft_SizeCorr_IterativeInfo;

	class Aft2d_AltrOptNodeSurface_PerpenDir
		: public Aft2d_AltrOptNodeSurface
	{

		/*Private Data*/

		std::shared_ptr<Aft_SizeCorr_IterativeInfo> theInfo_;

		Standard_Integer theMaxLev_;


		// Private functions and operators [5/8/2022 Amir]

		TnbMesh_EXPORT Standard_Boolean 
			Iter
			(
				const Standard_Integer theLev,
				const Pnt2d& theCentre
			);

	public:

		static TnbMesh_EXPORT const Standard_Integer DEFAULT_MAX_LEV;
		static TnbMesh_EXPORT const Standard_Real Perpendicular_Size;

		// default constructor [5/8/2022 Amir]

		Aft2d_AltrOptNodeSurface_PerpenDir()
			: theMaxLev_(DEFAULT_MAX_LEV)
		{}


		// constructors [5/8/2022 Amir]

		explicit Aft2d_AltrOptNodeSurface_PerpenDir
		(
			const std::shared_ptr<Aft_SizeCorr_IterativeInfo>& theInfo
		)
			: theInfo_(theInfo)
			, theMaxLev_(DEFAULT_MAX_LEV)
		{}

		// public functions and operators [5/8/2022 Amir]

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

#endif // !_Aft2d_AltrOptNodeSurface_PerpenDir_Header

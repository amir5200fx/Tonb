#pragma once
#ifndef _Cad_MergeParaCurves_Wire_Header
#define _Cad_MergeParaCurves_Wire_Header

#include <Cad_MergeParaCurves_Entity.hxx>

#include <vector>

namespace tnbLib
{

	namespace cadLib
	{

		namespace mergeParaCurves
		{

			// Forward Declarations [6/4/2022 Amir]
			class Link;

			class Wire
				: public Entity
			{

				/*Private Data*/

				std::vector<std::shared_ptr<Link>> theCurves_;

			public:

				// default constructor [6/4/2022 Amir]

				Wire()
				{}

				// constructors [6/4/2022 Amir]

				Wire
				(
					const Standard_Integer theIndex,
					const std::vector<std::shared_ptr<Link>>& theCurves
				)
					: Entity(theIndex)
					, theCurves_(theCurves)
				{}

				Wire
				(
					const Standard_Integer theIndex,
					std::vector<std::shared_ptr<Link>>&& theCurves
				)
					: Entity(theIndex)
					, theCurves_(std::move(theCurves))
				{}


				// public functions and operators [6/4/2022 Amir]

				const auto& Curves() const
				{
					return theCurves_;
				}

				auto& CurvesRef()
				{
					return theCurves_;
				}

				void SetCurves(const std::vector<std::shared_ptr<Link>>& theCurves)
				{
					theCurves_ = theCurves;
				}

				void SetCurves(std::vector<std::shared_ptr<Link>>&& theCurves)
				{
					theCurves_ = std::move(theCurves);
				}
			};
		}
	}
}

#endif // !_Cad_MergeParaCurves_Wire_Header

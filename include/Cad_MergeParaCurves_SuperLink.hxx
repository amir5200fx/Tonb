#pragma once
#ifndef _Cad_MergeParaCurves_SuperLink_Header
#define _Cad_MergeParaCurves_SuperLink_Header

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
			class SuperNode;

			class SuperLink
				: public Entity
			{

				/*Private Data*/

				std::vector<std::shared_ptr<Link>> theCurves_;

			protected:

				// default constructor [6/4/2022 Amir]

				SuperLink()
				{}


				// constructors [6/4/2022 Amir]

				explicit SuperLink(const Standard_Integer theIndex)
					: Entity(theIndex)
				{}

			public:

				// public functions and operators [6/4/2022 Amir]

				const auto& Curves() const
				{
					return theCurves_;
				}

				auto& CurvesRef() const
				{
					return theCurves_;
				}

				virtual Standard_Boolean IsSegment() const
				{
					return Standard_False;
				}

				virtual Standard_Boolean IsRing() const
				{
					return Standard_False;
				}
			};
		}
	}
}

#endif // !_Cad_MergeParaCurves_SuperLink_Header

#pragma once
#ifndef _Cad_MergeParaCurves_Node_Header
#define _Cad_MergeParaCurves_Node_Header

#include <Cad_MergeParaCurves_Entity.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	namespace cadLib
	{

		namespace mergeParaCurves
		{

			class Node
				: public Entity
			{

				/*Private Data*/

				Pnt2d theCoord_;

			protected:

				// default constructor [6/4/2022 Amir]

				Node()
				{}


				// constructors [6/4/2022 Amir]

				Node(const Standard_Integer theIndex, const Pnt2d& theCoord)
					: Entity(theIndex)
					, theCoord_(theCoord)
				{}

				Node(const Standard_Integer theIndex, Pnt2d&& theCoord)
					: Entity(theIndex)
					, theCoord_(std::move(theCoord))
				{}

			public:

				// public functions and operators [6/4/2022 Amir]

				virtual Standard_Boolean IsBoundary() const
				{
					return Standard_False;
				}

				virtual Standard_Boolean IsInternal() const
				{
					return Standard_False;
				}

				virtual Standard_Boolean IsIntersection() const
				{
					return Standard_False;
				}
			};
		}
	}
}

#endif // !_Cad_MergeParaCurves_Node_Header

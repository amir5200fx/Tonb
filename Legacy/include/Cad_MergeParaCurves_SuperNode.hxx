#pragma once
#ifndef _Cad_MergeParaCurves_SuperNode_Header
#define _Cad_MergeParaCurves_SuperNode_Header

#include <Cad_MergeParaCurves_Entity.hxx>
#include <Pnt2d.hxx>

#include <map>

namespace tnbLib
{

	namespace cadLib
	{

		namespace mergeParaCurves
		{

			// Forward Declarations [6/4/2022 Amir]
			class Node;

			class SuperNode
				: public Entity
			{

				/*Private Data*/

				Pnt2d theCoord_;

				std::map<Standard_Integer, std::shared_ptr<Node>> theNodes_;

			public:

				// default constructor [6/4/2022 Amir]

				SuperNode()
				{}

				// constructors [6/4/2022 Amir]

				SuperNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
					: Entity(theIndex)
					, theCoord_(theCoord)
				{}

				SuperNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
					: Entity(theIndex)
					, theCoord_(std::move(theCoord))
				{}


				// public functions and operators [6/4/2022 Amir]

				Standard_Integer NbNodes() const
				{
					return (Standard_Integer)theNodes_.size();
				}

				const auto& Coord() const
				{
					return theCoord_;
				}

				const auto& Nodes() const
				{
					return theNodes_;
				}

				void SetCoord(const Pnt2d& theCoord)
				{
					theCoord_ = theCoord;
				}

				void SetCoord(Pnt2d&& theCoord)
				{
					theCoord_ = std::move(theCoord);
				}

				void InsertToNodes(const Standard_Integer theIndex, const std::shared_ptr<Node>& theNode);
				void InsertToNodes(const Standard_Integer theIndex, std::shared_ptr<Node>&& theNode);

				void RemoveFromNodes(const Standard_Integer theIndex);

			};
		}
	}
}

#endif // !_Cad_MergeParaCurves_SuperNode_Header

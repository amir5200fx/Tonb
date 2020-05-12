#pragma once
#ifndef _Cad2d_Modeler_SelectList_Header
#define _Cad2d_Modeler_SelectList_Header

#include <Standard_TypeDef.hxx>

#include <vector>
#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Edge;
	class Cad2d_Modeler;

	namespace cad2dLib
	{

		class Modeler_SelectList
		{

			friend class Cad2d_Modeler;

			/*Private Data*/

			std::map<Standard_Integer, std::shared_ptr<Pln_Edge>> theItems_;


			//- private functions and operators

			auto& ChangeItems()
			{
				return theItems_;
			}

			Standard_Boolean IsContain(const Standard_Integer theIndex) const;

			std::shared_ptr<Pln_Edge> Remove(const Standard_Integer theIndex);

			void Import(const Standard_Integer theIndex, const std::shared_ptr<Pln_Edge>& theEdge);

			void Clear();

		public:

			Modeler_SelectList()
			{}

			auto NbItems() const
			{
				return (Standard_Integer)theItems_.size();
			}

			const auto& Items() const
			{
				return theItems_;
			}

			std::vector<std::shared_ptr<Pln_Edge>> RetrieveItems() const;

			void RetrieveItemsTo(std::vector<std::shared_ptr<Pln_Edge>>& theItems) const;
		};
	}
}

#endif // !_Cad2d_Modeler_SelectList_Header

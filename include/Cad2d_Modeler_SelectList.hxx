#pragma once
#ifndef _Cad2d_Modeler_SelectList_Header
#define _Cad2d_Modeler_SelectList_Header

#include <Cad2d_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

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

			std::map<Standard_Integer, std::weak_ptr<Pln_Edge>> theItems_;


			//- private functions and operators

			TNB_SERIALIZATION(TnbCad2d_EXPORT);

			auto& ChangeItems()
			{
				return theItems_;
			}

			TnbCad2d_EXPORT Standard_Boolean IsContain(const Standard_Integer theIndex) const;

			TnbCad2d_EXPORT std::weak_ptr<Pln_Edge> Remove(const Standard_Integer theIndex);

			TnbCad2d_EXPORT void Import(const Standard_Integer theIndex, const std::shared_ptr<Pln_Edge>& theEdge);

			TnbCad2d_EXPORT void Clear();

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

			TnbCad2d_EXPORT std::vector<std::weak_ptr<Pln_Edge>> RetrieveItems() const;

			TnbCad2d_EXPORT void RetrieveItemsTo(std::vector<std::weak_ptr<Pln_Edge>>& theItems) const;
		};
	}
}

#endif // !_Cad2d_Modeler_SelectList_Header

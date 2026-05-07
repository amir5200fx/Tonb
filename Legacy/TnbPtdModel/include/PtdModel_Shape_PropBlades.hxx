#pragma once
#ifndef _PtdModel_Shape_PropBlades_Header
#define _PtdModel_Shape_PropBlades_Header

#include <PtdModel_Shape_PropEntity.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	namespace ptdModel
	{

		// Forward Declarations
		class Shape_PropBlade;

		class Shape_PropBlades
			: public Shape_PropEntity
		{

			/*Private Data*/

			std::shared_ptr<Shape_PropBlade> theParent_;

			std::vector<std::shared_ptr<Shape_PropBlade>> theChildren_;


			//- private functions and operators

			TNB_SERIALIZATION(TnbPtdModel_EXPORT);


			TnbPtdModel_EXPORT void CheckParent(const std::shared_ptr<Shape_PropBlade>&);
			TnbPtdModel_EXPORT void CheckChild(const std::shared_ptr<Shape_PropBlade>&);

		public:

			//- default constructor

			Shape_PropBlades()
			{}


			//- constructors

			TnbPtdModel_EXPORT Shape_PropBlades
			(
				const std::shared_ptr<Shape_PropBlade>& theParent, 
				const std::vector<std::shared_ptr<Shape_PropBlade>>& theChildren
			);

			TnbPtdModel_EXPORT Shape_PropBlades
			(
				std::shared_ptr<Shape_PropBlade>&& theParent,
				std::vector<std::shared_ptr<Shape_PropBlade>>&& theChildren
			);


			//- public functions and operators

			TnbPtdModel_EXPORT Standard_Integer NbBlades() const;

			const auto& Parent() const
			{
				return theParent_;
			}

			const auto& Children() const
			{
				return theChildren_;
			}

			auto& ChildrenRef()
			{
				return theChildren_;
			}

			TnbPtdModel_EXPORT void SetParent(const std::shared_ptr<Shape_PropBlade>&);
			TnbPtdModel_EXPORT void SetParent(std::shared_ptr<Shape_PropBlade>&&);

			TnbPtdModel_EXPORT void SetChildren(const std::vector<std::shared_ptr<Shape_PropBlade>>&);
			TnbPtdModel_EXPORT void SetChildren(std::vector<std::shared_ptr<Shape_PropBlade>>&&);
			
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::ptdModel::Shape_PropBlades);

#endif // !_PtdModel_Shape_PropBlades_Header

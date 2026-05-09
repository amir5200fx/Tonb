#pragma once
#ifndef _PtdModel_Shape_PropHub_Header
#define _PtdModel_Shape_PropHub_Header

#include <PtdModel_Shape_PropEntity.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_Face;

	namespace ptdModel
	{

		class Shape_PropHub
			: public Shape_PropEntity
		{

			/*Private Data*/


			std::vector<std::shared_ptr<PtdModel_Face>> theFaces_;

			//- public functions and operators

			TNB_SERIALIZATION(TnbPtdModel_EXPORT);

		public:


			//- default constructor

			Shape_PropHub()
			{}


			//- constructors

			TnbPtdModel_EXPORT Shape_PropHub(const std::shared_ptr<Cad_Shape>&);

			TnbPtdModel_EXPORT Shape_PropHub(std::shared_ptr<Cad_Shape>&&);

			TnbPtdModel_EXPORT Shape_PropHub
			(
				const Standard_Integer theIndex, 
				const word& theName, 
				const std::shared_ptr<Cad_Shape>&
			);

			TnbPtdModel_EXPORT Shape_PropHub
			(
				const Standard_Integer theIndex,
				const word& theName, 
				std::shared_ptr<Cad_Shape>&&
			);


			//- public functions and operators

			const auto& Faces() const
			{
				return theFaces_;
			}

			void SetFaces(const std::vector<std::shared_ptr<PtdModel_Face>>& theFaces)
			{
				theFaces_ = theFaces;
			}

			void SetFaces(std::vector<std::shared_ptr<PtdModel_Face>>&& theFaces)
			{
				theFaces_ = std::move(theFaces);
			}

		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::ptdModel::Shape_PropHub);

#endif // !_PtdModel_Shape_PropHub_Header


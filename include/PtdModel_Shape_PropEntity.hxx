#pragma once
#ifndef _PtdModel_Shape_PropEntity_Header
#define _PtdModel_Shape_PropEntity_Header

#include <PtdModel_Shape.hxx>

namespace tnbLib
{

	namespace ptdModel
	{

		class Shape_PropEntity
			: public PtdModel_Shape
		{

			/*Private Data*/


			//- private functions and operators

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar & boost::serialization::base_object<PtdModel_Shape>(*this);
			}

		protected:

			//- default constructor

			Shape_PropEntity()
			{}


			//- constructors

			TnbPtdModel_EXPORT Shape_PropEntity(const std::shared_ptr<Cad_Shape>&);

			TnbPtdModel_EXPORT Shape_PropEntity(std::shared_ptr<Cad_Shape>&&);

			TnbPtdModel_EXPORT Shape_PropEntity
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<Cad_Shape>&
			);

			TnbPtdModel_EXPORT Shape_PropEntity
			(
				const Standard_Integer theIndex, 
				const word& theName,
				std::shared_ptr<Cad_Shape>&&
			);

		public:

			//- public functions and operators


		};
	}
}


BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::ptdModel::Shape_PropEntity);

#endif // !_PtdModel_Shape_PropEntity_Header

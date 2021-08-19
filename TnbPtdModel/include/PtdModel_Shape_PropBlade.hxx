#pragma once
#ifndef _PtdModel_Shape_PropBlade_Header
#define _PtdModel_Shape_PropBlade_Header

#include <PtdModel_Shape_PropEntity.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_PropBlade;
	class PtdModel_BladeGlobalPars;
	class PtdModel_Face;

	namespace ptdModel
	{

		class Shape_PropBlade
			: public Shape_PropEntity
		{

			/*Private Data*/


			//- private functions and operators

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar & boost::serialization::base_object<Shape_PropEntity>(*this);
			}


		protected:


			//- default constructor

			Shape_PropBlade()
			{}


			//- constructors

			TnbPtdModel_EXPORT Shape_PropBlade
			(
				const std::shared_ptr<Cad_Shape>&
			);

			TnbPtdModel_EXPORT Shape_PropBlade
			(
				std::shared_ptr<Cad_Shape>&&
			);

			TnbPtdModel_EXPORT Shape_PropBlade
			(
				const Standard_Integer theIndex, 
				const word& theName,
				const std::shared_ptr<Cad_Shape>&
			);

			TnbPtdModel_EXPORT Shape_PropBlade
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

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::ptdModel::Shape_PropBlade);

#endif // !_PtdModel_Shape_PropBlade_Header

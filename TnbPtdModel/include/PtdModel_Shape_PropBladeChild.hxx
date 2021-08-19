#pragma once
#ifndef _PtdModel_Shape_PropBladeChild_Header
#define _PtdModel_Shape_PropBladeChild_Header

#include <PtdModel_Shape_PropBlade.hxx>

namespace tnbLib
{

	namespace ptdModel
	{

		class Shape_PropBladeChild
			: public Shape_PropBlade
		{

			/*Private Data*/


			//- private functions and operators

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar & boost::serialization::base_object<Shape_PropBlade>(*this);
			}

		public:

			//- default constructor

			Shape_PropBladeChild()
			{}


			//- constructors

			TnbPtdModel_EXPORT Shape_PropBladeChild
			(
				const std::shared_ptr<Cad_Shape>&
			);

			TnbPtdModel_EXPORT Shape_PropBladeChild
			(
				std::shared_ptr<Cad_Shape>&&
			);

			TnbPtdModel_EXPORT Shape_PropBladeChild
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<Cad_Shape>&
			);

			TnbPtdModel_EXPORT Shape_PropBladeChild
			(
				const Standard_Integer theIndex,
				const word& theName,
				std::shared_ptr<Cad_Shape>&&
			);

			//- public functions and operators

		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::ptdModel::Shape_PropBladeChild);

#endif // !_PtdModel_Shape_PropBladeChild_Header

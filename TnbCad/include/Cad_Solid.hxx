#pragma once
#ifndef _Cad_Solid_Header
#define _Cad_Solid_Header

#include <Cad_TModel.hxx>

#include <memory>

class TopoDS_Shape;

namespace tnbLib
{

	// Forward Declarations [6/13/2023 Payvand]
	class Cad_TModel;
	class Cad_tModelMakerInfo;
	class Cad_tEdgeMakerInfo;
	class Cad_tSurfaceMakerInfo;
	class Cad_tModelMaker_PairCrvCriterion;

	class Cad_Solid
		: public Cad_TModel
	{

	public:

		struct MakerInfo
		{
			std::shared_ptr<Cad_tModelMakerInfo> modelInfo;
			std::shared_ptr<Cad_tEdgeMakerInfo> edgeInfo;
			std::shared_ptr<Cad_tSurfaceMakerInfo> surfInfo;
			std::shared_ptr<Cad_tModelMaker_PairCrvCriterion> pairCrit;
		};

	private:

		/*Private Data*/


		TnbCad_EXPORT void Check() const;


		// Private functions and operators [6/13/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Cad_TModel>(*this);
		}

		// default constructor [6/13/2023 Payvand]

		Cad_Solid()
		{}

	public:


		// constructors [6/13/2023 Payvand]

		TnbCad_EXPORT Cad_Solid(const TopoDS_Shape& theShape);

		TnbCad_EXPORT Cad_Solid
		(
			const Standard_Integer theIndex, 
			const word& theName,
			const TopoDS_Shape& theShape
		);


		// Public functions and operators [6/13/2023 Payvand]

		TnbCad_EXPORT Standard_Real CalcVolume() const;

		static TnbCad_EXPORT std::shared_ptr<Cad_Solid> 
			MakeSolid
			(
				const TopoDS_Shape& theShape,
				const MakerInfo& theInfo
			);

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Cad_Solid);

#endif // !_Cad_Solid_Header

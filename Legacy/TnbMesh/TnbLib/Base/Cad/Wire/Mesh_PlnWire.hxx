#pragma once
#ifndef _Mesh_PlnWire_Header
#define _Mesh_PlnWire_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Entity2d_Box.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	template<class MeshPlnCurve>
	class Mesh_PlnWire
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/

		std::vector<std::shared_ptr<MeshPlnCurve>> theCurves_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			Info << "WARNING! This function is not supposed to be called!" << endl;
			NotImplemented;
		}


		static Entity2d_Box CalcBoundingBox(const MeshPlnCurve&);

	public:

		typedef MeshPlnCurve plnCurveType;


		//- default constructor
		Mesh_PlnWire()
			: Global_Named("wire")
		{}


		//- constructors
		explicit Mesh_PlnWire
		(
			const std::vector<std::shared_ptr<MeshPlnCurve>>& theCurves
		)
			: Global_Named("wire")
			, theCurves_(theCurves)
		{}

		Mesh_PlnWire
		(
			std::vector<std::shared_ptr<MeshPlnCurve>>&& theCurves
		)
			: Global_Named("wire")
			, theCurves_(std::move(theCurves))
		{}

		Mesh_PlnWire
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::vector<std::shared_ptr<MeshPlnCurve>>& theCurves
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
			, theCurves_(theCurves)
		{}

		Mesh_PlnWire
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::vector<std::shared_ptr<MeshPlnCurve>>&& theCurves
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
			, theCurves_(std::move(theCurves))
		{}


		//- public functions and operators

		auto NbCurves() const
		{
			return (Standard_Integer)theCurves_.size();
		}

		Entity2d_Box CalcParametricBoundingBox() const;

		const auto& Curves() const
		{
			return theCurves_;
		}

		void ExportToPlt(OFstream& File) const;

		static std::vector<std::shared_ptr<MeshPlnCurve>>
			RetrieveCurvesFrom
			(
				const std::vector<std::shared_ptr<Mesh_PlnWire>>& theWires
			);

		static void OrientSingularCurves(std::vector<std::shared_ptr<MeshPlnCurve>>& theWire);

		template<class WireType>
		static std::shared_ptr<WireType> MakeOrignWire(const std::shared_ptr<Mesh_PlnWire>&);
	};
}

#include <Mesh_PlnWireI.hxx>

#endif // !_Mesh_PlnWire_Header

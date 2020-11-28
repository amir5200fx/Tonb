#pragma once
#ifndef _StbGMaker_Alg_Header
#define _StbGMaker_Alg_Header

#include <Geo_ItemCounter.hxx>
#include <StbGMaker_Entity.hxx>
#include <StbGMaker_AlgAux.hxx>
#include <Entity3d_ChainFwd.hxx>

#include <map>
#include <vector>

class TopoDS_Shape;

namespace tnbLib
{

	// Forward Declarations
	class StbGMaker_WP;
	class StbGMaker_Volume;
	class Geo_xDistb;

	class StbGMaker_Alg
		: public StbGMaker_AlgAux
	{

		/*Private Data*/

		std::map<Standard_Integer, std::shared_ptr<StbGMaker_WP>>
			theWorkingPlanes_;

		mutable Geo_ItemCounter theCounter_;

		//- private functions and operators


		TNB_SERIALIZATION(TnbStbGMaker_EXPORT);

		TnbStbGMaker_EXPORT void ImportWP
		(
			const Standard_Integer theIndex, 
			const std::shared_ptr<StbGMaker_WP>&& theWP
		);

	protected:

		StbGMaker_Alg()
		{}

		TnbStbGMaker_EXPORT std::shared_ptr<StbGMaker_WP>
			RemoveWP
			(
				const Standard_Integer theIndex
			);

		TnbStbGMaker_EXPORT Standard_Integer
			AddWP
			(
				const std::shared_ptr<StbGMaker_WP>&& theWp
			);
	

		auto& WpCounter() const
		{
			return theCounter_;
		}

		TnbStbGMaker_EXPORT Standard_Integer
			CreateWpFromShape
			(
				const TopoDS_Shape& theShape,
				const Standard_Real x
			);

	public:

		auto NbWorkingPlane() const
		{
			return (Standard_Integer)theWorkingPlanes_.size();
		}

		const auto& WorkingPlanes() const
		{
			return theWorkingPlanes_;
		}

		TnbStbGMaker_EXPORT std::shared_ptr<Entity3d_Chain>
			Mesh
			(
				const Standard_Integer theIndex
			) const;

		TnbStbGMaker_EXPORT std::vector<std::shared_ptr<Entity3d_Chain>>
			Mesh() const;

		TnbStbGMaker_EXPORT std::shared_ptr<StbGMaker_WP>
			SelectWP
			(
				const Standard_Integer theIndex
			) const;

		TnbStbGMaker_EXPORT std::vector<std::shared_ptr<StbGMaker_WP>>
			RetrieveWPs() const;

		TnbStbGMaker_EXPORT virtual Standard_Integer
			CreateWorkingPlane
			(
				const Standard_Real x
			);

		//virtual const std::shared_ptr<StbGMaker_Volume>& Volume() const = 0;

		TnbStbGMaker_EXPORT void CreateWorkingPlanes
		(
			const Geo_xDistb& theX
		);

		TnbStbGMaker_EXPORT void RetrieveWPsTo
		(
			std::vector<std::shared_ptr<StbGMaker_WP>>& theWPs
		) const;

		//virtual void MakeBody() = 0;

		static TnbStbGMaker_EXPORT void SortWPs
		(
			std::vector<std::shared_ptr<StbGMaker_WP>>& theWPs
		);

		static TnbStbGMaker_EXPORT void CheckSort
		(
			const std::vector<std::shared_ptr<StbGMaker_WP>>& theWPs,
			const char* theFunName
		);
	};
}

#endif // !_StbGMaker_Alg_Header


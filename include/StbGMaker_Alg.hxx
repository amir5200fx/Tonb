#pragma once
#ifndef _StbGMaker_Alg_Header
#define _StbGMaker_Alg_Header

#include <Geo_ItemCounter.hxx>
#include <StbGMaker_Entity.hxx>
#include <StbGMaker_AlgAux.hxx>
#include <Entity3d_ChainFwd.hxx>

#include <map>

class TopoDS_Shape;

namespace tnbLib
{

	// Forward Declarations
	class StbGMaker_WP;
	class StbGMaker_Volume;
	class Geo_xDistb;

	class StbGMaker_Alg
		: public StbGMaker_Entity
		, public StbGMaker_AlgAux
	{

		/*Private Data*/

		std::map<Standard_Integer, std::shared_ptr<StbGMaker_WP>>
			theWorkingPlanes_;

		mutable Geo_ItemCounter theCounter_;

		//- private functions and operators

		void ImportWP
		(
			const Standard_Integer theIndex, 
			const std::shared_ptr<StbGMaker_WP>&& theWP
		);

	protected:

		template<class... _Types>
		StbGMaker_Alg(_Types&&... _Args)
			: StbGMaker_Entity(_Args...)
		{}

		std::shared_ptr<StbGMaker_WP> 
			RemoveWP
			(
				const Standard_Integer theIndex
			);

		Standard_Integer 
			AddWP
			(
				const std::shared_ptr<StbGMaker_WP>&& theWp
			);
	

		auto& WpCounter() const
		{
			return theCounter_;
		}

		Standard_Integer
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

		std::shared_ptr<Entity3d_Chain>
			Mesh
			(
				const Standard_Integer theIndex
			) const;

		std::vector<std::shared_ptr<Entity3d_Chain>>
			Mesh() const;

		std::shared_ptr<StbGMaker_WP> 
			SelectWP
			(
				const Standard_Integer theIndex
			) const;

		virtual Standard_Integer
			CreateWorkingPlane
			(
				const Standard_Real x
			);

		//virtual const std::shared_ptr<StbGMaker_Volume>& Volume() const = 0;

		void CreateWorkingPlanes
		(
			const Geo_xDistb& theX
		);

		//virtual void MakeBody() = 0;

		static void SortWPs
		(
			std::vector<std::shared_ptr<StbGMaker_WP>>& theWPs
		);

		static void CheckSort
		(
			const std::vector<std::shared_ptr<StbGMaker_WP>>& theWPs,
			const char* theFunName
		);
	};
}

#endif // !_StbGMaker_Alg_Header


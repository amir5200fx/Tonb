#pragma once
#ifndef _Voyage_WptsGrid_Header
#define _Voyage_WptsGrid_Header

#include <Entity_Connectivity.hxx>
#include <Pnt2d.hxx>

#include <vector>

namespace tnbLib
{

	class Voyage_WptsGrid
	{

		/*Private Data*/

		std::vector<std::vector<Pnt2d>> thePoints_;


		// Private functions and operators [7/10/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar& thePoints_;
		}

	public:

		// default constructor [7/10/2023 Payvand]

		Voyage_WptsGrid()
		{}


		// Public functions and operators [7/10/2023 Payvand]

		auto NbStages() const { return (Standard_Integer)thePoints_.size(); }
		auto NbRows(const Standard_Integer theStage) const 
		{ return (Standard_Integer)thePoints_.at(theStage).size(); }

		const auto& Point(const Standard_Integer theStage, const Standard_Integer theRow) const
		{
			return thePoints_.at(theStage).at(theRow);
		}

		auto& PointsRef() { return thePoints_; }
		auto& StageRef(const Standard_Integer theIndex) { return thePoints_.at(theIndex); }

		void SetPoint
		(
			const Standard_Integer theStage, 
			const Standard_Real theRow, 
			const Pnt2d& theCoord
		)
		{
			thePoints_.at(theStage).at(theRow) = theCoord;
		}

		void SetPoint(const Standard_Integer theStage, const Standard_Real theRow, Pnt2d&& theCoord)
		{
			thePoints_.at(theStage).at(theRow) = std::move(theCoord);
		}

		void SetRowSize(const Standard_Integer theStage, const Standard_Integer theSize) 
		{ thePoints_.at(theStage).resize(theSize); }
		void SetStageSize(const Standard_Integer theSize) { thePoints_.resize(theSize); }

	};

}

#endif // !_Voyage_WptsGrid_Header

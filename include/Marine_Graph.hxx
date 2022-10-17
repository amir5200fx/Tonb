#pragma once
#ifndef _Marine_Graph_Header
#define _Marine_Graph_Header

#include <Marine_GraphEntity.hxx>
#include <Marine_GraphTitle.hxx>
#include <Marine_GraphAxis_X.hxx>
#include <Marine_GraphAxis_Y.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Marine_GraphCurve;

	class Marine_Graph
		: public Marine_GraphEntity
	{

		/*Private Data*/

		Marine_GraphTitle theTitle_;
		
		Marine_GraphAxis_X theX_;
		Marine_GraphAxis_Y theY_;

		std::vector<std::shared_ptr<Marine_GraphCurve>> theCurves_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbMarine_EXPORT);

	public:


		//- default constructor

		Marine_Graph()
		{}


		//- constructors

		TnbMarine_EXPORT Marine_Graph
		(
			const Standard_Integer theIndex
		);

		TnbMarine_EXPORT Marine_Graph
		(
			const Standard_Integer theIndex,
			const word& theName
		);


		//- public functions and operators

		TnbMarine_EXPORT Standard_Integer NbCurves() const;

		const auto& X() const
		{
			return theX_;
		}

		auto& X()
		{
			return theX_;
		}

		const auto& Y() const
		{
			return theY_;
		}

		auto& Y()
		{
			return theY_;
		}

		const auto& Title() const
		{
			return theTitle_;
		}

		auto& Title()
		{
			return theTitle_;
		}

		auto& ChangeCurves()
		{
			return theCurves_;
		}

		const auto& Curves() const
		{
			return theCurves_;
		}


	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Marine_Graph);

#endif // !_Marine_Graph_Header

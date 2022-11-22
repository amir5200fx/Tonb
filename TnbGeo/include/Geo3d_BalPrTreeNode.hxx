#pragma once
#ifndef _Geo3d_BalPrTreeNode_Header
#define _Geo3d_BalPrTreeNode_Header

#include <Entity3d_BoxFwd.hxx>

#include <string>
#include <memory>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{


	class Geo3d_BalPrTreeNode
	{

		/*Private Data*/

		std::shared_ptr<Entity3d_Box> theBox_;

		Standard_Integer theLev_;

	protected:

		// default constructor [7/5/2022 Amir]

		Geo3d_BalPrTreeNode()
			: theLev_(0)
		{}


		// constructors [7/5/2022 Amir]

		explicit Geo3d_BalPrTreeNode(const std::shared_ptr<Entity3d_Box>& theBox)
			: theBox_(theBox)
			, theLev_(0)
		{}

		Geo3d_BalPrTreeNode(std::shared_ptr<Entity3d_Box>&& theBox)
			: theBox_(std::move(theBox))
			, theLev_(0)
		{}

	public:

		// public functions and operators [7/5/2022 Amir]

		virtual ~Geo3d_BalPrTreeNode()
		{}

		virtual std::string Type() const = 0;

		const auto& Box() const
		{
			return theBox_;
		}

		auto Lev() const
		{
			return theLev_;
		}

		void SetBox(const std::shared_ptr<Entity3d_Box>& theBox)
		{
			theBox_ = theBox;
		}

		void SetBox(std::shared_ptr<Entity3d_Box>&& theBox)
		{
			theBox_ = std::move(theBox);
		}

		void SetLev(const Standard_Integer theLev)
		{
			theLev_ = theLev;
		}

	};
}

#endif // !_Geo3d_BalPrTreeNode_Header

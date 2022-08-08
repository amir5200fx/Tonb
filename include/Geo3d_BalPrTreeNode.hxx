#pragma once
#ifndef _Geo3d_BalPrTreeNode_Header
#define _Geo3d_BalPrTreeNode_Header

#include <Entity3d_BoxFwd.hxx>

#include <memory>

namespace tnbLib
{


	class Geo3d_BalPrTreeNode
	{

		/*Private Data*/

		std::shared_ptr<Entity3d_Box> theBox_;

	public:

		// default constructor [7/5/2022 Amir]

		Geo3d_BalPrTreeNode()
		{}


		// constructors [7/5/2022 Amir]

		explicit Geo3d_BalPrTreeNode(const std::shared_ptr<Entity3d_Box>& theBox)
			: theBox_(theBox)
		{}

		Geo3d_BalPrTreeNode(std::shared_ptr<Entity3d_Box>&& theBox)
			: theBox_(std::move(theBox))
		{}


		// public functions and operators [7/5/2022 Amir]

		virtual ~Geo3d_BalPrTreeNode()
		{}

		const auto& Box() const
		{
			return theBox_;
		}

		void SetBox(const std::shared_ptr<Entity3d_Box>& theBox)
		{
			theBox_ = theBox;
		}

		void SetBox(std::shared_ptr<Entity3d_Box>&& theBox)
		{
			theBox_ = std::move(theBox);
		}

	};
}

#endif // !_Geo3d_BalPrTreeNode_Header

#pragma once
#ifndef _TModel_GeneratedEdgeAdaptor_Header
#define _TModel_GeneratedEdgeAdaptor_Header

#include <Cad_Module.hxx>
#include <Global_Serialization.hxx>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [1/6/2022 Amir]
	class TModel_Edge;
	class TModel_Paired;

	class TModel_GeneratedEdgeAdaptor
	{

		/*Private Data*/

		std::weak_ptr<TModel_Paired> thePaired_;
		std::weak_ptr<TModel_Edge> thePairedEdge_;

		// private functions and operators [1/6/2022 Amir]

		TNB_SERIALIZATION(TnbCad_EXPORT);

	protected:

		// default constructor [1/6/2022 Amir]

		TModel_GeneratedEdgeAdaptor()
		{}

		// constructors [1/6/2022 Amir]

	public:


		// public functions and operators [1/6/2022 Amir]

		const auto& Paired() const
		{
			return thePaired_;
		}

		const auto& PairedEdge() const
		{
			return thePairedEdge_;
		}

		void SetPaired(const std::weak_ptr<TModel_Paired>& thePaired)
		{
			thePaired_ = thePaired;
		}

		void SetPairedEdge(const std::weak_ptr<TModel_Edge>& theEdge)
		{
			thePairedEdge_ = theEdge;
		}
	};
}

#endif // !_TModel_GeneratedEdgeAdaptor_Header

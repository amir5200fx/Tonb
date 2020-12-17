#pragma once
#ifndef _Geo_RealPriorityList_Header
#define _Geo_RealPriorityList_Header

#include <Geo_PriorityList.hxx>

namespace tnbLib
{

	template<>
	class Geo_PriorityList<Standard_Real>
		: public Geo_PriorityListBase
	{

		/*Private Data*/


		std::vector<Standard_Real> theData_;


		//- private functions

		//TNB_SERIALIZATION(TnbGeo_EXPORT);

		friend boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Geo_PriorityListBase>(*this);
			ar & theData_;
		}

		void ShiftUp(const Standard_Integer Index)
		{
			if (Index)
			{
				auto ParentIndex = Parent(Index);

				if (theData_[ParentIndex] > theData_[Index])
				{
					std::swap(theData_[ParentIndex], theData_[Index]);

					ShiftUp(ParentIndex);
				}
			}
		}

		void ShiftDown(const Standard_Integer Index)
		{
			Standard_Integer
				LeftChildIndex,
				RightChildIndex,
				MinIndex;

			LeftChildIndex = LeftChild(Index);
			RightChildIndex = RightChild(Index);

			if (RightChildIndex >= NbPriorities())
			{
				if (LeftChildIndex >= NbPriorities())
					return;
				else
					MinIndex = LeftChildIndex;
			}
			else
			{
				if (theData_[LeftChildIndex] <= theData_[RightChildIndex])
					MinIndex = LeftChildIndex;
				else
					MinIndex = RightChildIndex;
			}

			if (theData_[Index] > theData_[MinIndex])
			{
				std::swap(theData_[MinIndex], theData_[Index]);

				ShiftDown(MinIndex);
			}
		}

		Standard_Real Remove()
		{
			if (theData_.empty())
			{
				FatalErrorIn(FunctionSIG)
					<< " Heap is empty"
					<< abort(FatalError);
			}

			auto Item = theData_[0];
			theData_[0] = theData_[NbPriorities() - 1];
			Decrement();

			if (NbPriorities() > 0) ShiftDown(0);
			return Item;
		}

	public:

		Geo_PriorityList()
		{}

		Standard_Boolean overFlow() const
		{
			return NbPriorities() >= theData_.size();
		}

		Standard_Boolean RetrieveFromPriority(Standard_Real& theItem)
		{
			if (IsPriorityEmpty()) return Standard_False;
			else
			{
				theItem = Remove();
				return Standard_True;
			}
		}

		void SetSizeToPriority(const Standard_Integer theSize)
		{
			theData_.resize(theSize);
		}

		void InsertToPriority(const Standard_Real theItem)
		{
			if (overFlow())
			{
				FatalErrorIn(FunctionSIG)
					<< " Heap's underlying storage is overflow"
					<< abort(FatalError);
			}

			Increment();
			theData_[NbPriorities() - 1] = theItem;

			ShiftUp(NbPriorities() - 1);
		}

		void InsertToPriority(const std::vector<Standard_Real>& theItems)
		{
			theData_.resize(theItems.size());
			for (const auto& item : theItems)
				InsertToPriority(item);
		}
	};
}

#endif // !_Geo_RealPriorityList_Header

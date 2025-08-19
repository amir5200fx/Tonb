#pragma once
#ifndef _Aft2d_Plane_Header
#define _Aft2d_Plane_Header

#include <Aft2d_Edge.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Geo_PriorityList.hxx>
#include <Pnt2d.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>
#include <set>

namespace tnbLib
{ 

	namespace legLib
	{

		// Forward Declarations [2/1/2023 Payvand]

		class Aft2d_Edge;
		class Aft2d_Node;
		class Aft2d_Element;

		static auto edge_cmp = [](const std::shared_ptr<Aft2d_Edge>& theEdge0, const std::shared_ptr<Aft2d_Edge>& theEdge1)
		{
			return theEdge0->Index() < theEdge1->Index();
		};

		class Aft2d_Plane
			: public Global_Done
		{

		public:

			class frontHandler
			{

				/*Private Data*/

				Geo_PriorityList<std::shared_ptr<Aft2d_Edge>> theFronts_;

				Standard_Integer theLevel_ = 0;
				Standard_Integer theMaxId_ = 0;

				std::set<std::shared_ptr<Aft2d_Edge>, decltype(edge_cmp)>
					theCurrentLev_;
				std::set<std::shared_ptr<Aft2d_Edge>, decltype(edge_cmp)>
					theNextLev_;

			public:

				// default constructor [2/1/2023 Payvand]

				frontHandler()
					: theCurrentLev_(edge_cmp)
					, theNextLev_(edge_cmp)
				{}

				// constructors [2/1/2023 Payvand]


				// Public functions and operators [2/1/2023 Payvand]

				Standard_Boolean IsCurrentEmpty() const;
				Standard_Boolean IsNextEmtpy() const;

				Standard_Boolean IsOnCurrentLevel(const std::shared_ptr<Aft2d_Edge>&) const;

				const auto& Fronts() const
				{
					return theFronts_;
				}

				const auto& CurrentLevel() const
				{
					return theCurrentLev_;
				}

				const auto& NextLevel() const
				{
					return theNextLev_;
				}

				void InsertToCurrent(const std::shared_ptr<Aft2d_Edge>&);
				void InsertToNext(const std::shared_ptr<Aft2d_Edge>&);

				void InsertToFronts(const std::vector<std::shared_ptr<Aft2d_Edge>>&);

				void ClearCurrent();
				void ClearNext();

				void SetCurrentLev(const Standard_Integer);
				void SetMaxLevel(const Standard_Integer);

				std::vector<std::shared_ptr<Aft2d_Edge>> RetrieveCurrentLevel() const;
				std::vector<std::shared_ptr<Aft2d_Edge>> RetrieveNexLevel() const;

			};

			enum class cycleMode
			{
				generation = 0,
				repair
			};

			enum class nodeMode
			{
				newPoint = 0,
				pickedUp
			};

			class cycleSpecs
			{

				/*Private Data*/

				Pnt2d theCoord_;

				std::shared_ptr<Entity2d_Box> theRegion_;

				std::shared_ptr<Aft2d_Node> theTemp_;
				std::shared_ptr<Aft2d_Node> theValid_;

				std::shared_ptr<Aft2d_Edge> theCurrent_;

				std::shared_ptr<Aft2d_Element> theElement_;

				Standard_Boolean appendedNode_;

				cycleMode theCycleModel_;
				nodeMode theNodeModel_;

				Standard_Real theSize_ = 0;

				Standard_Real theLocalRadius_ = 0;
				Standard_Real theSearchRadius_ = 0;
				Standard_Real theMaxElemLength_ = 0;

				Standard_Real theMinDistanceFactor_ = 0;

				std::array<std::shared_ptr<Aft2d_Edge>, 2> thePaired_;
				std::array<std::shared_ptr<Aft2d_Edge>, 2> theCreated_;

			public:

				// default constructor [2/1/2023 Payvand]

				cycleSpecs()
				{}

				// constructors [2/1/2023 Payvand]


				// Public functions and operators [2/1/2023 Payvand]

				const auto& Coord() const
				{
					return theCoord_;
				}

				const auto& Region() const
				{
					return theRegion_;
				}

				const auto& TempoNode() const
				{
					return theTemp_;
				}

				const auto& Current() const
				{
					return theCurrent_;
				}

				const auto& Element() const
				{
					return theElement_;
				}

				auto AppendedNode() const
				{
					return appendedNode_;
				}

				auto CycleMode() const
				{
					return theCycleModel_;
				}

				auto NodeMode() const
				{
					return theNodeModel_;
				}

				auto Size() const
				{
					return theSize_;
				}

				auto LocalFrontRadius() const
				{
					return theLocalRadius_;
				}

				auto SquareLocalFrontRadius() const
				{
					return theLocalRadius_ * theLocalRadius_;
				}

				auto SearchRadius() const
				{
					return theSearchRadius_;
				}

				auto MaxElmLength() const
				{
					return theMaxElemLength_;
				}

				auto SquareMaxElmLength() const
				{
					return theMaxElemLength_ * theMaxElemLength_;
				}

				auto MinDistFactor() const
				{
					return theMinDistanceFactor_;
				}

				const auto& PairedEdges() const
				{
					return thePaired_;
				}

				const auto& CreatedEdges() const
				{
					return theCreated_;
				}

				const std::shared_ptr<Aft2d_Edge>& Paired0() const;
				const std::shared_ptr<Aft2d_Edge>& Paired1() const;

				const std::shared_ptr<Aft2d_Edge>& Created0() const;
				const std::shared_ptr<Aft2d_Edge>& Created1() const;

				void SetCoord(const Pnt2d& theCoord);
				void SetCoord(Pnt2d&& theCoord);
				void SetTempoNode(const std::shared_ptr<Aft2d_Node>&);
				void SetRegion(const std::shared_ptr<Entity2d_Box>&);
				void SetRegion(std::shared_ptr<Entity2d_Box>&&);


			};

		private:

			/*Private Data*/

			cycleSpecs theSpecs_;

		public:

			static unsigned short verbose;

			// default constructor [2/1/2023 Payvand]

			Aft2d_Plane()
			{}

			// constructors [2/1/2023 Payvand]



			// Public functions and operators [2/1/2023 Payvand]


		};
	}
}

#include <Aft2d_PlaneI.hxx>

#endif // !_Aft2d_Plane_Header

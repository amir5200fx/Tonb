#pragma once
#ifndef _Cad2d_IdentRings_Header
#define _Cad2d_IdentRings_Header

#include <Global_Done.hxx>
#include <Cad2d_IdentRings_Node.hxx>
#include <Cad2d_IdentRings_Link.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations [1/25/2022 Amir]
	class Pln_Edge;
	class Pln_Vertex;
	class Cad2d_IdentRings;

	namespace cad2dLib
	{

		// Forward Declarations [1/25/2022 Amir]
		class IdentRings_Ring;
		class IdentRings_Segment;
		class IdentRings_Petal;
	}

	class Cad2d_IdentRingsCache
	{

		friend class Cad2d_IdentRings;

		/*Private Data*/

		std::map<Standard_Integer, std::shared_ptr<cad2dLib::IdentRings_Node>> theNodesCache_;
		std::map<Standard_Integer, std::shared_ptr<cad2dLib::IdentRings_Link>> theLinksCache_;

	protected:

		// default constructor [1/25/2022 Amir]

		Cad2d_IdentRingsCache()
		{}

		// constructors [1/25/2022 Amir]


		// protected functions and operators [1/25/2022 Amir]

		const auto& Nodes() const
		{
			return theNodesCache_;
		}

		auto& NodesRef()
		{
			return theNodesCache_;
		}

		const auto& Links() const
		{
			return theLinksCache_;
		}

		auto& LinksRef()
		{
			return theLinksCache_;
		}

		TnbCad2d_EXPORT Standard_Boolean ContainsNode(const Standard_Integer theIndex) const;
		TnbCad2d_EXPORT std::shared_ptr<cad2dLib::IdentRings_Node> 
			FindNode(const Standard_Integer theIndex) const;

		Standard_Integer NbNodes() const
		{
			return (Standard_Integer)theNodesCache_.size();
		}

		Standard_Integer NbLinks() const
		{
			return (Standard_Integer)theLinksCache_.size();
		}

		TnbCad2d_EXPORT void ImportToNodes(const std::shared_ptr<cad2dLib::IdentRings_Node>&);
		TnbCad2d_EXPORT void ImportToNodes(std::shared_ptr<cad2dLib::IdentRings_Node>&&);
		TnbCad2d_EXPORT void ImportToLinks(const std::shared_ptr<cad2dLib::IdentRings_Link>&);
		TnbCad2d_EXPORT void ImportToLinks(std::shared_ptr<cad2dLib::IdentRings_Link>&&);

		TnbCad2d_EXPORT void RemoveNode(const std::shared_ptr<cad2dLib::IdentRings_Node>&);
		TnbCad2d_EXPORT void RemoveLink(const std::shared_ptr<cad2dLib::IdentRings_Link>&);

	public:

		// public functions and operators [1/25/2022 Amir]


	};

	class Cad2d_IdentRings
		: public Global_Done
	{

		/*Private Data*/

		// inputs [1/25/2022 Amir]

		const std::vector<std::shared_ptr<Pln_Edge>>& theEdges_;


		// outputs [1/25/2022 Amir]
		std::vector<std::shared_ptr<cad2dLib::IdentRings_Segment>> theSegments_;
		std::vector<std::shared_ptr<cad2dLib::IdentRings_Petal>> thePetals_;
		

		// private data [1/25/2022 Amir]

		std::shared_ptr<Cad2d_IdentRingsCache> theCache_;

		// Private functions and operators [1/25/2022 Amir]

		const auto& CacheData() const
		{
			return theCache_;
		}

		auto& CacheDataRef()
		{
			return theCache_;
		}

		auto& PetalsRef()
		{
			return thePetals_;
		}

		auto& SegmentsRef()
		{
			return theSegments_;
		}

		TnbCad2d_EXPORT std::shared_ptr<cad2dLib::IdentRings_Node> SearchFirstNode() const;
		TnbCad2d_EXPORT std::shared_ptr<cad2dLib::IdentRings_Link> CreateLink
		(
			const std::shared_ptr<cad2dLib::IdentRings_Node>&,
			const std::shared_ptr<Pln_Edge>& theDir
		) const;
		TnbCad2d_EXPORT std::vector<std::shared_ptr<cad2dLib::IdentRings_Link>> CreateLinks() const;
		std::shared_ptr<cad2dLib::IdentRings_Petal> FindAPetal();

		TnbCad2d_EXPORT void InsertVerticesToCache(const std::vector<std::shared_ptr<Pln_Vertex>>&);
		TnbCad2d_EXPORT void InsertLinksToCache(const std::vector<std::shared_ptr<cad2dLib::IdentRings_Link>>&);
		TnbCad2d_EXPORT void RemoveLink(const std::shared_ptr<cad2dLib::IdentRings_Link>&);
		TnbCad2d_EXPORT void RemoveDangles();

		// static functions [1/25/2022 Amir]

		static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge> 
			RetrieveDir
			(
				const std::shared_ptr<cad2dLib::IdentRings_Node>&
			);
		
		static TnbCad2d_EXPORT std::shared_ptr<cad2dLib::IdentRings_Petal> 
			FindPetal
			(
				const std::shared_ptr<cad2dLib::IdentRings_Node>&
			);

		static TnbCad2d_EXPORT std::tuple
			<
			std::vector<std::shared_ptr<cad2dLib::IdentRings_Link>>,
			std::shared_ptr<cad2dLib::IdentRings_Node>,
			std::shared_ptr<cad2dLib::IdentRings_Node>
			> 
			MarchOnLinks
			(
				const std::shared_ptr<cad2dLib::IdentRings_Node>&, 
				const std::shared_ptr<cad2dLib::IdentRings_Link>& dir
			);

		static TnbCad2d_EXPORT void Detach(const std::shared_ptr<cad2dLib::IdentRings_Link>&);
		static TnbCad2d_EXPORT void reAttach(const std::shared_ptr<cad2dLib::IdentRings_Link>&);
		static TnbCad2d_EXPORT void Attach(const std::vector<std::shared_ptr<cad2dLib::IdentRings_Link>>&);

	public:

		static TnbCad2d_EXPORT unsigned short verbose;

		// default constructor [1/25/2022 Amir]

		Cad2d_IdentRings
		(
			const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
		)
			: theEdges_(theEdges)
		{}

		// constructors [1/25/2022 Amir]


		// public functions and operators [1/25/2022 Amir]

		const auto& Edges() const
		{
			return theEdges_;
		}

		const auto& Segments() const
		{
			return theSegments_;
		}

		const auto& Petals() const
		{
			return thePetals_;
		}

		TnbCad2d_EXPORT void Perform();

		
	};
}

#endif // !_Cad2d_IdentRings_Header

#pragma once
#ifndef _Mesh_IO_Header
#define _Mesh_IO_Header

#include <Global_TypeDef.hxx>

#include <map>
#include <memory>
#include <vector>

namespace tnbLib
{


	class Mesh2d_IO
	{

	public:


		struct Pair
		{
			Standard_Integer Left;
			Standard_Integer Right;
		};

	private:

		/*Private Data*/

		std::map<Standard_Integer, std::vector<Standard_Integer>> theNodeToEdges_;
		std::map<Standard_Integer, std::vector<Standard_Integer>> theNodeToElements_;

		std::map<Standard_Integer, std::vector<Pair>> theEdgeToElements_;

		std::map<Standard_Integer, std::vector<Standard_Integer>> theElementToElements_;

	public:


		// default constructor [12/18/2021 Amir]

		Mesh2d_IO()
		{}

		// constructors [12/18/2021 Amir]



		// public functions and operators [12/18/2021 Amir]

		const auto& NodeToEdges() const
		{
			return theNodeToEdges_;
		}

		auto& NodeToEdgesRef()
		{
			return theNodeToEdges_;
		}

		const auto& NodeToElements() const
		{
			return theNodeToElements_;
		}

		auto& NodeToElementsRef()
		{
			return theNodeToElements_;
		}

		const auto& EdgeToElements() const
		{
			return theEdgeToElements_;
		}

		auto& EdgeToElementsRef()
		{
			return theEdgeToElements_;
		}

		const auto& ElementToElements() const
		{
			return theElementToElements_;
		}

		auto& ElementToElementsRef()
		{
			return theElementToElements_;
		}



		
	};

	extern std::shared_ptr<Mesh2d_IO> mesh2d_loader;


	class Mesh3d_IO
	{

	public:

		struct Pair
		{
			Standard_Integer Left;
			Standard_Integer Right;
		};

	private:

		/*Private Data*/

		std::map<Standard_Integer, std::vector<Standard_Integer>> theNodeToEdges_;
		std::map<Standard_Integer, std::vector<Standard_Integer>> theNodeToFacets_;
		std::map<Standard_Integer, std::vector<Standard_Integer>> theNodeToElements_;

		std::map<Standard_Integer, std::vector<Standard_Integer>> theEdgeToFacets_;
		std::map<Standard_Integer, std::vector<Standard_Integer>> theEdgeToElements_;

		std::map<Standard_Integer, std::vector<Pair>> theFacetToElements_;

		std::map<Standard_Integer, std::vector<Standard_Integer>> theElementToElements_;

	public:

		// default constructor [12/18/2021 Amir]

		Mesh3d_IO()
		{}

		// constructors [12/18/2021 Amir]



		// public functions and operators [12/18/2021 Amir]

		const auto& NodeToEdges() const
		{
			return theNodeToEdges_;
		}

		auto& NodeToEdgesRef()
		{
			return theNodeToEdges_;
		}

		const auto& NodeToFacets() const
		{
			return theNodeToFacets_;
		}

		auto& NodeToFacetsRef()
		{
			return theNodeToFacets_;
		}

		const auto& NodeToElements() const
		{
			return theNodeToElements_;
		}

		auto& NodeToElementsRef()
		{
			return theNodeToElements_;
		}

		const auto& EdgeToFacets() const
		{
			return theEdgeToFacets_;
		}

		auto& EdgeToFacets()
		{
			return theEdgeToFacets_;
		}
			 
		const auto& EdgeToElements() const
		{
			return theEdgeToElements_;
		}

		auto& EdgeToElementsRef()
		{
			return theEdgeToElements_;
		}

		const auto& FacetToElements() const
		{
			return theFacetToElements_;
		}

		auto& FacetToElementsRef()
		{
			return theFacetToElements_;
		}

		const auto& ElementToElements() const
		{
			return theElementToElements_;
		}

		auto& ElementToElementsRef()
		{
			return theElementToElements_;
		}
	};

	extern std::shared_ptr<Mesh3d_IO> mesh3d_loader;
}

#include <Mesh_IOI.hxx>

#endif // !_Mesh_IO_Header

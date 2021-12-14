#pragma once
#ifndef _Aft_Model_Cache_Header
#define _Aft_Model_Cache_Header

#include <map>
#include <memory>

#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>

namespace tnbLib
{

	// Forward Declarations

	class Aft2d_Model_Cache
	{

	public:

		typedef std::map<unsigned, unsigned> indexMap;

	private:

		/*Private Data*/


		// Private functions and operators [11/25/2021 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & nodeIndex;
			ar & edgeIndex;
			ar & elementIndex;

			ar & NodesIndices;
			ar & EdgesIndices;
			ar & ElementsIndices;
		}

	protected:

		mutable unsigned nodeIndex;
		mutable unsigned edgeIndex;
		mutable unsigned elementIndex;

		mutable std::shared_ptr<indexMap> NodesIndices;
		mutable std::shared_ptr<indexMap> EdgesIndices;
		mutable std::shared_ptr<indexMap> ElementsIndices;


		// default constructor [11/25/2021 Amir]

		Aft2d_Model_Cache()
		{}

		// constructors [11/25/2021 Amir]

	};

	class Aft3d_Model_Cache
	{

	public:

		typedef std::map<unsigned, unsigned> indexMap;

	private:

		/*Private Data*/


		// Private functions and operators [11/25/2021 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & nodeIndex;
			ar & edgeIndex;
			ar & facetIndex;
			ar & elementIndex;

			ar & NodesIndices;
			ar & EdgesIndices;
			ar & FacetsIndices;
			ar & ElementsIndices;
		}

	protected:

		mutable unsigned nodeIndex;
		mutable unsigned edgeIndex;
		mutable unsigned facetIndex;
		mutable unsigned elementIndex;

		mutable std::shared_ptr<indexMap> NodesIndices;
		mutable std::shared_ptr<indexMap> EdgesIndices;
		mutable std::shared_ptr<indexMap> FacetsIndices;
		mutable std::shared_ptr<indexMap> ElementsIndices;

		// default constructors [11/25/2021 Amir]

		Aft3d_Model_Cache()
		{}

		// constructors [11/25/2021 Amir]

	};
}

#endif // !_Aft_Model_Cache_Header

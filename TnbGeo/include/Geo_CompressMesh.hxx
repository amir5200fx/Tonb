#pragma once
#ifndef _Geo_CompressMesh_Header
#define _Geo_CompressMesh_Header

#include <Entity3d_Tetrahedralization.hxx>
#include <Global_Done.hxx>
#include <Global_Macros.hxx>

#include <map>
#include <vector>
#include <memory>

namespace tnbLib
{
	/*
	 * This class is supposed to compress a point list of a mesh based on its connectivity matrix.
	 * This means the points that aren't used in the connectivity matrix will be eliminated form the
	 * structure and the connectivity matrix will be updated.
	 * [Amir 10-24-2024]
	 */
	template<class Mesh>
	class Geo_CompressMesh
		: public Global_Done
	{
	public:
		typedef typename Mesh::ptType Point;
		typedef typename Mesh::connectType Matrix;

		DisallowBitWiseCopy(Geo_CompressMesh)
	private:
		/*Private Data*/
		std::shared_ptr<Mesh> theUncompressed_;
		std::shared_ptr<Mesh> theCompressed_;

		// Private functions and operators
		static const std::vector<Matrix>& retrieve_matrices(const Mesh&);
		static const std::vector<Point>& retrieve_coords(const Mesh&);
		static std::vector<Standard_Integer> get_components(const Matrix&);

		static Matrix update_matrix(const Matrix&, const std::map<Standard_Integer, Standard_Integer>& ids);
	public:
		
		// default constructor
		Geo_CompressMesh() = default;
		// constructors
		explicit Geo_CompressMesh(std::shared_ptr<Mesh> theUncompressed)
			: theUncompressed_(std::move(theUncompressed))
		{}
		// Public functions and operators
		const auto& Uncompressed() const { return theUncompressed_; }
		const auto& Compressed() const { return theCompressed_; }

		void Perform();

		void SetUncompressed(std::shared_ptr<Mesh> theUncompressed);
	};
}
// ReSharper disable once CppUnusedIncludeDirective
#include <Geo_CompressMeshI.hxx>
// ReSharper disable once CppUnusedIncludeDirective
#include <Geo2d_CompressMesh_Composite.hxx>
// ReSharper disable once CppUnusedIncludeDirective
#include <Geo3d_CompressMesh_Composite.hxx>
#endif
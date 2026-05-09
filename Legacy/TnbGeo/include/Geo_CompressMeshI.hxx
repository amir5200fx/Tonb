#pragma once
template <class Mesh>
const std::vector<typename tnbLib::Geo_CompressMesh<Mesh>::Matrix>& tnbLib::Geo_CompressMesh<Mesh>::
retrieve_matrices(const Mesh& mesh)
{
	return mesh.Connectivity();
}

template<class Mesh>
const std::vector<typename tnbLib::Geo_CompressMesh<Mesh>::Point>& tnbLib::Geo_CompressMesh<
	Mesh>::retrieve_coords(const Mesh& mesh)
{
	return mesh.Points();
}

template<class Mesh>
std::vector<Standard_Integer> tnbLib::Geo_CompressMesh<Mesh>::get_components(const Matrix& mat)
{
	return mat.Cmpts();
}

template <class Mesh>
typename tnbLib::Geo_CompressMesh<Mesh>::Matrix tnbLib::Geo_CompressMesh<Mesh>::update_matrix(const Matrix& mat,
	const std::map<Standard_Integer, Standard_Integer>& ids)
{
	auto cmpts = mat.Cmpts();
	for (size_t i = 0; cmpts.size(); i++)
	{
		cmpts.at(i) = ids.at(cmpts.at(i));
	}
	return { std::move(cmpts) };
}

template <class Mesh>
void tnbLib::Geo_CompressMesh<Mesh>::Perform()
{
	std::map<Standard_Integer, Standard_Integer> ids;
	Standard_Integer k = 0;
	for (const auto& mat: retrieve_matrices(*theUncompressed_))
	{
		const auto cmpts = get_components(mat);
		for (const auto i: cmpts)
		{
			if (const auto iter = ids.find(i); iter == ids.end())
			{
				ids.insert({ i, ++k });
			}
		}
	}
	const auto uncompressed_coords = retrieve_coords(*theUncompressed_);
	std::vector<Point> compressed_coords(ids.size());
	for (Standard_Integer i = 1; i <= static_cast<Standard_Integer>(uncompressed_coords.size()); i++)
	{
		if (const auto iter = ids.find(i); iter != ids.end())
		{
			compressed_coords.at(Index_Of(ids.at(i))) = uncompressed_coords.at(Index_Of(i));
		}
	}
	std::vector<Matrix> elements;
	for (const auto& elm: retrieve_matrices(*theUncompressed_))
	{
		elements.emplace_back(update_matrix(elm, ids));
	}
	theCompressed_ = std::make_shared<Mesh>(std::move(compressed_coords), std::move(elements));
	SetItDone;
}

template <class Mesh>
void tnbLib::Geo_CompressMesh<Mesh>::SetUncompressed(std::shared_ptr<Mesh> theUncompressed)
{
	theUncompressed_ = std::move(theUncompressed);
}

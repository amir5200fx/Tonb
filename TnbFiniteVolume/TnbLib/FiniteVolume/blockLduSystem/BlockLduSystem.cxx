#include <BlockLduSystem.hxx>

#include <fvMatrix.hxx>
#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class blockType, class sourceType>
tnbLib::BlockLduSystem<blockType, sourceType>::BlockLduSystem
(
	const lduMesh& ldu
)
	:
	BlockLduMatrix<blockType>(ldu),
	source_(ldu.lduAddr().size(), pTraits<sourceType>::zero)
{}


template<class blockType, class sourceType>
tnbLib::BlockLduSystem<blockType, sourceType>::BlockLduSystem
(
	const lduMesh& ldu,
	const Field<sourceType>& s
)
	:
	BlockLduMatrix<blockType>(ldu),
	source_(s)
{
	if (ldu.lduAddr().size() != s.size())
	{
		FatalErrorIn
		(
			"BlockLduSystem::BlockLduSystem\n"
			"(\n"
			"    const lduMesh& ldu,"
			"    const Field<sourceType>& s,"
			")\n"
		) << "Sizes of ldu addressing and source field are not the same."
			<< abort(FatalError);
	}
}


template<class blockType, class sourceType>
tnbLib::BlockLduSystem<blockType, sourceType>::BlockLduSystem
(
	const BlockLduMatrix<blockType>& bm,
	const Field<sourceType>& s
)
	:
	BlockLduMatrix<blockType>(bm),
	source_(s)
{
	if (this->lduAddr().size() != s.size())
	{
		FatalErrorIn
		(
			"BlockLduSystem::BlockLduSystem\n"
			"(\n"
			"    const BlockLduMatrix<blockType>& bm,"
			"    const Field<sourceType>& s,"
			")\n"
		) << "Sizes of block matrix and source field are not the same."
			<< abort(FatalError);
	}
}


template<class blockType, class sourceType>
tnbLib::BlockLduSystem<blockType, sourceType>::BlockLduSystem
(
	const BlockLduSystem<blockType, sourceType>& bs
)
	:
	BlockLduMatrix<blockType>(bs),
	source_(bs.source())
{}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class blockType, class sourceType>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const BlockLduSystem<blockType, sourceType>& bs
	)
{
	os << static_cast<const BlockLduMatrix<blockType>&>(bs) << nl
		<< bs.source() << endl;

	return os;
}


// ************************************************************************* //